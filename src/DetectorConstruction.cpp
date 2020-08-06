#include "DetectorConstruction.hpp"
#include "CalorimeterSD.hpp"
#include "G4Material.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4VisAttributes.hh"
#include "globals.hh"
#include "G4TransportationManager.hh"
#include <sstream>
#include "G4SystemOfUnits.hh"
#include "common.hpp"
#include "G4PhysicalConstants.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


DetectorConstruction::DetectorConstruction() : G4VUserDetectorConstruction(),
    fCheckOverlaps(true)
{
  calorCrysS.resize();
  calorCrysL.resize();
  calorSD.resize();
  calorCrysPh.resize();
  calorBoxVisAtt.resize();
  intersect.resize();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::~DetectorConstruction()
{
  ;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  // Define materials 
  DefineMaterials();
  
  // Define volumes
  return DefineVolumes();

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::DefineMaterials()
{ 
  // Lead material defined using NIST Manager
  G4double density, temp, pressure;
  G4State state;
  G4String name, symbol;
  G4double z,a;
  G4int ncomponents, natoms;
  G4double fractionmass;

  // Vacuum
  new G4Material("Galactic", z=1., a=1.01*g/mole,density= universe_mean_density, kStateGas, 2.73*kelvin, 3.e-18*pascal);
  //CsI
  G4Element *elCs = new G4Element (name="Caesium", symbol="Cs", z=55, a=132.905*g/mole);
  G4Element *elI = new G4Element (name="Iodine", symbol="I", z=53, a=126.904 g/mole);   
  G4Material *CsI =  new G4Material("CsI", density= 4.534*g/cm3, ncomponents=2, state=kStateSolid);
  CsI->AddElement(elCs, natoms=1);
  CsI->AddElement(elI , natoms=1);
  CsI->GetIonisation()->SetMeanExcitationEnergy(553.1*eV); 

  // Print materials
  G4cout << *(G4Material::GetMaterialTable()) << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//
//

G4VPhysicalVolume* DetectorConstruction::DefineVolumes()
{
  // Geometry parameters
  calorWidth  = 30*mm;
  calorHeight = 30*mm;
  calorLength = 150*mm;

  G4double worldSizeXY = 15*calorWidth;
  
  // Get materials
  G4Material* defaultMaterial = G4Material::GetMaterial("Galactic");
  G4Material* calorMaterial = G4Material::GetMaterial("CsI");
  
  if ( ! defaultMaterial || ! calorMaterial)
    {
      G4cerr << "Cannot retrieve materials already defined. " << G4endl;
      G4cerr << "Exiting application " << G4endl;
      exit(1);
    }  
   
  //     
  // World
  //
  G4double world_length = 5*calorLength;
  G4VSolid* worldS  = new G4Box("World", world_length, worldSizeXY, worldSizeXY);         
  worldLV  = new G4LogicalVolume(worldS, defaultMaterial, "World");
  G4VPhysicalVolume* worldPV = new G4PVPlacement(0, G4ThreeVector(), worldLV, "World", 0, false, 0, fCheckOverlaps); 
  
  //                               
  // Calorimeter
  //  

  for (int i = 0; i < 3; i++)
    {
      for (int j = 0; j <3; j++)
  {
    std::stringstream ssB;
    ssB << j+3*i;
    calorCrysS[i] = new G4Box (("Crystal"+ssB.str()).c_str(), calorWidth, calorHeight, calorLength);
    calorCrysL[i] = new G4LogicalVolume(CrysS[i], calorMaterial, ("Crystal"+ssB.str()).c_str());
    calorCrysPh[i] = new G4PVPlacement(0, G4ThreeVector(2*calorWidth*(1-j), 2*calorHeight*(1-i), 0), calorCrysL[i], ("Crystal"+ssB.str()).c_str(), worldLV, false, 0, fCheckOverlaps);
 
   calorSD [i] = new CalorimeterSD(("CalorSD"+ssB.str()).c_str(), ("CalorHitsCollection"+ssB.str()).c_str());
   G4SDManager::GetSDMpointer()->AddNewDetector(calorSD[i]);
    calorLI[i]->SetSensitiveDetector(calorSD[i]);
  //Visualization
    calorBoxVisAtt[i] = new G4VisAttributes (G4Colour((i+1)%2,(i%3)/2.,((i+1)%5)/4.));
    calorBoxVisAtt[i]->SetVisibility(true);
    calorLI[i]->SetVisAttributes(calorBoxVisAtt[i]);
  } 
    }
  worldLV->SetVisAttributes (G4VisAttributes::Invisible);
   
  //
  // Always return the physical World
  //
  return worldPV;
}
