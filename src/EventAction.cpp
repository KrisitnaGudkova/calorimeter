#include "EventAction.hpp"
#include "CalorimeterSD.hpp"
#include "CalorHit.hpp"
//#include "Analysis.hh"
#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4SDManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4UnitsTable.hh"
#include "Randomize.hh"
#include <iomanip>
#include <stdlib.h>
#include <sstream>
#include "common.hpp"
#include "TData.hpp"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::EventAction()
 : G4UserEventAction()
{
//  fEnergy = RUN_ENERGY;
}

void EventAction::SetData (TData *fdata)
{
  data = fdata;
}
  
//EventAction::EventAction(G4double Energy)
// : G4UserEventAction()
//{
//  fEnergy = Energy;
//}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::~EventAction()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

CalorHitsCollection* EventAction::GetHitsCollection(const G4String& hcName, const G4Event* event) const
{
  G4int hcID = G4SDManager::GetSDMpointer()->GetCollectionID(hcName);
  CalorHitsCollection* hitsCollection = static_cast<CalorHitsCollection*>(event->GetHCofThisEvent()->GetHC(hcID));
  
  if ( ! hitsCollection )
 {
    G4cerr << "Cannot access hitsCollection " << hcName << G4endl;
    exit(1);
  }         

  return hitsCollection;
}    

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::PrintEventStatistics(G4double calorEdep) const
{
  // print event statistics
  G4cout
     << "   Calorimeter: total energy: " 
     << std::setw(7) << G4BestUnit(calorEdep, "Energy")
     << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::BeginOfEventAction(const G4Event* event)
{  

  /*  G4int eventID = event->GetEventID();
  //if ( eventID % fPrintModulo == 0 )  
  { 
    G4cout << "\n---> Begin of event: " << eventID << G4endl;
    CLHEP::HepRandom::showEngineStatus();
    }*/
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::EndOfEventAction(const G4Event* event)
{  
  //  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  //G4double sum_energy = 0.;
  //G4double y_E [NOYLAYERS];
  //G4double z_E [NOZLAYERS];
  //G4double energy_3x3 = 0.;
  //  std::fill (y_E, y_E+NOYLAYERS, 0);
  //std::fill (z_E, z_E+NOZLAYERS, 0);
	 //     }
	 //   G4double y_CM, z_CM;
   /*   for (G4int i=0; i< NOYLAYERS;i++)
     y_CM += CALORSIZEYZ/NOYLAYERS*(i-NOYLAYERS/2)*y_E[i]/sum_energy;
   for (G4int i=0; i< NOZLAYERS;i++)
   z_CM += CALORSIZEYZ/NOZLAYERS*(i-NOZLAYERS/2)*z_E[i]/sum_energy;*/
   //Side volume
   for (int i = 0; i < data->e_abs.size(); i++)
   {
     CalorHit* calorHitSide;
     CalorHitsCollection* calorHCSide;
     std::stringstream ssB;
     ssB << i;

     calorHCSide   = GetHitsCollection(("CalorHitsCollection"+ssB.str()).c_str(), event);
     calorHitSide = (*calorHCSide)[0];
      
     data->e_abs[i] = calorHitSide->GetEdep ();
     data->eabs_calor += data->e_abs[i];
   }
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
   
