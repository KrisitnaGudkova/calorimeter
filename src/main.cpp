#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4UIExecutive.hh"

#include "DetectorConstruction.hpp"
#include "PhysicsList.hpp"
#include "PrimaryGeneratorAction.hpp"
#include "RunAction.hpp"
#include "EventAction.hpp"
//#include "FTFP_BERT.hh"
#include "G4VisExecutive.hh"
#include "G4VisExtent.hh"

#include "Randomize.hh"
#include "common.hpp"

#include "TData.hpp"

#include <sstream>
#include <vector>
#include <string>
//ROOT include files for analysis
#include "TFile.h"
#include "TTree.h"
#include "G4SystemOfUnits.hh"
#include "TRandom.h"
#include <time.h>
#include <unistd.h>
#include <fstream>
#include <string.h>

int main(int argc,char** argv)
{
  // Construct the default run manager
  
  G4RunManager* runManager = new G4RunManager;
  CLHEP::HepRandom::setTheEngine (new CLHEP::HepJamesRandom);
  CLHEP::HepJamesRandom randEngine;

  // set mandatory initialization classes
  
  G4VUserPhysicsList* physics = new PhysicsList;
  runManager->SetUserInitialization(physics);

  //G4double init_energy;
  PrimaryGeneratorAction* gen_action;
  RunAction *run_action;
  EventAction *event_action;
  G4int numberOfEvents = NUM_RUNS;
  G4double energy;
  std::string fileName;
  switch (argc)
  {
    default :
      G4cout << "Photon energy is " <<RUN_ENERGY<<"MeV" << " [number of events]" << " fileName " << G4endl << "Aborted." << G4endl;
      exit (1);
    case 5:
    {
      std::stringstream ss (std::stringstream::in | std::stringstream::out);
      ss << argv [1] <<" " << argv[2] << " " << argv[3];
      ss >> energy >>  numberOfEvents >> n_div;
      fileName = argv[4];
      break;
    }
/*    case 4:
    {
      std::stringstream ss (std::stringstream::in | std::stringstream::out);
      ss << argv [2];
      ss >> ppc; 
    }*/
    case 2:
    {
      std::stringstream ss;
      ss << argv[1];
      fileName = ss.str();
      break;
    }
  }

  TData *data = new TData();
  gen_action = new PrimaryGeneratorAction(); //I wish I shouldn't do random in geant code
  run_action = new RunAction();
  event_action = new EventAction();
  //
  G4VUserDetectorConstruction* detector = new DetectorConstruction();
  runManager->SetUserInitialization(detector);
  //G4VModularPhysicsList* physicsList = new FTFP_BERT;
  //runManager->SetUserInitialization (physicsList);

  // set mandatory user action class
  //
  runManager->SetUserAction(gen_action);
  runManager->SetUserAction(run_action);
  runManager->SetUserAction(event_action);

  // Initialize G4 kernel
  //
  runManager->Initialize();

#if !VIS
  // Start a run
  //
  std::stringstream sstree;
  sstree << "_CsI_" << energy <<"MeV";
  TFile *file = new TFile ((fileName+sstree.str()+".root").c_str(), "recreate");
  TTree *tree = new TTree (sstree.str().c_str(), "Monte-Carlo generator");
  tree->Branch ("y", &(data->y), "y/D");
  tree->Branch ("z", &(data->z), "z/D");
  tree->Branch ("e_begin", &(data->e_begin), "e_begin/D");
  tree->Branch ("eabs_calor", &(data->eabs_calor), "eabs_calor/D");

  for (int i = 0; i < 9; i++)
  {
    std::stringstream ssb;
    ssb << i;
    tree->Branch (("e_abs_"+ssb.str()).c_str(), &(data->e_abs[i]), ("e_abs_"+ssb.str()+"/D").c_str());
  }
/*  int nthreads, tid;
  char host[32];*/
  runManager->SetVerboseLevel (0);
  G4long seed = time(NULL)*getpid();
  CLHEP::HepRandom::setTheSeed(seed);
  for (int i = 0; i< numberOfEvents; i++)
  {
    G4double y =  CLHEP::RandFlat::shoot(&randEngine,-PRIMARYY/2,PRIMARYY/2), 
    z =  CLHEP::RandFlat::shoot(&randEngine,-PRIMARYZ/2,PRIMARYZ/2), 
    ener = energy;
    data->y = y;
    data->z = z;
    data->e_begin = energy;
    gen_action->SetData(data);
    event_action->SetData(data);
    gen_action->SetCoord(y*mm,z*mm);
    gen_action->SetEnergy(ener*MeV);
    runManager->BeamOn(1);
    tree->Fill();
    data->Zero();
  }
  tree->Write ();
  file->Close ();
#endif
  //
#if VIS
  //Visualisation
  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialise();

  // Get the pointer to the UI manager and set verbosities
  //
  G4UImanager* UI = G4UImanager::GetUIpointer();
  UI->ApplyCommand("/run/verbose 1");
  UI->ApplyCommand("/event/verbose 1");
  UI->ApplyCommand("/tracking/verbose 1");
  G4UIExecutive* ui = new G4UIExecutive (argc,argv);
  UI->ApplyCommand ("/control/execute init.mac");
  ui->SessionStart();
  delete visManager;
  delete ui;
#endif

  // Job termination
  //
  // Free the store: user actions, physics_list and detector_description are
  //                 owned and deleted by the run manager, so they should not
  //                 be deleted in the main() program !
  //
  delete runManager;

  return 0;
}
