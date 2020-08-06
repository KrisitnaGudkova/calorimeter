#include "RunAction.hpp"
//#include "Analysis.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"

#include <stdlib.h>
#include <iostream>
#include <sstream>

#include "TFile.h"
#include "TTree.h"

#include "globals.hh"
#include "common.hpp"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::RunAction()
 : G4UserRunAction()
{ 
//  fEnergy = RUN_ENERGY;
}

/*RunAction::RunAction(G4double Energy)
 : G4UserRunAction()
{
  fEnergy = Energy;
}*/

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::~RunAction()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::BeginOfRunAction(const G4Run* run)
{ 
 // std::stringstream ss (std::stringstream::in | std::stringstream::out);
//  G4String fileName;

  G4cout << "\r### Run " << run->GetRunID() << " start." << G4endl;

  //inform the runManager to save random number seed
  //G4RunManager::GetRunManager()->SetRandomNumberStore(true);
  
  // Book histograms, ntuple
  //
  
  // Create analysis manager
  // The choice of analysis technology is done via selectin of a namespace
  // in Analysis.hh
//  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  
  // Open an output file
  //
//  ss << "_" << fEnergy << "MeV_" << calorDepth/cm << "cm";
//  ss >> fileName;
//  G4cout << "FileName: " << fileName << G4endl;
  
 // analysisManager->OpenFile(fileName);
  //analysisManager->SetFirstHistoId(1);

  // Creating histograms
  //
//  analysisManager->CreateNtuple (fileName, "Energy absorbtion");
//  G4String NameNtuple;
  //  ssntuple >> NameNtuple;
    //analysisManager->CreateH1(NameHist,
    //"Edep in calorimeter", 100, 0., (fEnergy+fEnergy/10)*MeV);
//    analysisManager->CreateNtupleDColumn(NameNtuple);
  //  G4cout << "Ntuple created: " << NameNtuple<< G4endl;
  //Histogram for initial energy
  //analysisManager->CreateH1 ("Energy_beam", "Initial photon's energy", 100, (fEnergy-fEnergy/10)*MeV, (fEnergy+fEnergy/10)*MeV);
  //Ntuple for the same
//  analysisManager->CreateNtupleDColumn("Energy_beam");
  //Histogram for absorbed energy
  //analysisManager->CreateH1 ("Energy_absorb", "Whole absorbed energy", 100, 0, (fEnergy+fEnergy/10)*MeV);
  //Ntuple for the same
//  analysisManager->CreateNtupleDColumn("Energy_total");
  //Hist for initial coordinats
  //analysisManager->CreateH1 ("y_coord", "Initial y coordinat", 100, -30,30);
  //analysisManager->CreateH1 ("z_coord", "Initial z coordinat", 100, -30,30);
  //Ntuple for the same
//  analysisManager->CreateNtupleDColumn("y_init");
  //analysisManager->CreateNtupleDColumn("z_init");
  //Hist for CM
  //analysisManager->CreateH1 ("CM_y", "Effective y coord", 100, -30,30);
  //analysisManager->CreateH1 ("CM_z", "Effective z coord", 100, -30,30);
  //Ntuple for the same
//  analysisManager->CreateNtupleDColumn("y_eff");
//  analysisManager->CreateNtupleDColumn("z_eff");
  //Ntuple for depth of crystal
//  analysisManager->CreateNtupleDColumn("depth");
  //Ntuple for 3x3 energy
//  analysisManager->CreateNtupleDColumn("energy_3x3");
  //Ntuple for side volumes
//  analysisManager->CreateNtupleDColumn("energy_side");
  //Ntuple for forward volume
//  analysisManager->CreateNtupleDColumn("energy_forward");


  // Close ntuple
//  analysisManager->FinishNtuple();
//  G4cout << "Ntuple finished" << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::EndOfRunAction(const G4Run* aRun)
{
  G4int nofEvents = aRun->GetNumberOfEvent();
  if ( nofEvents == 0 ) return;
  
  // print histogram statistics
  //
 // G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  //if ( analysisManager->GetH1(1) ) {
  //  G4cout << "\n ----> print histograms statistic \n" << G4endl;
    
  //  G4cout 
  //     << " ECal : mean = " << G4BestUnit(analysisManager->GetH1(1)->mean(), "Energy") 
  //             << " rms = " << G4BestUnit(analysisManager->GetH1(1)->rms(),  "Energy") 
  //             << G4endl;
  //  G4cout 
  //     << " LCal : mean = " << G4BestUnit(analysisManager->GetH1(2)->mean(), "Length") 
  //             << " rms = " << G4BestUnit(analysisManager->GetH1(2)->rms(),  "Length") 
  //             << G4endl;
  //}
  
  G4cout << "End of RunAction" << G4endl;
  // save histograms 
  //
//  analysisManager->Write();
 // analysisManager->CloseFile();
  
  // complete cleanup
  //
//  delete G4AnalysisManager::Instance();  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
