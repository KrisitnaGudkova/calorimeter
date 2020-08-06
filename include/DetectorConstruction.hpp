#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include <G4IntersectionSolid.hh>
#include "globals.hh"

class G4Box;
class G4LogicalVolume;
class G4VPhysicalVolume;
class G4VSolid;
class G4PVPlacement;
class G4VisAtributes;
class G4IntersectionSolid;
/// Detector construction class to define materials and geometry.
/// The calorimeter is a box made of a given number of layers. A layer consists
/// of an absorber plate and of a detection gap. The layer is replicated.
///
/// Four parameters define the geometry of the calorimeter :
///
/// - the thickness of an absorber plate,
/// - the thickness of a gap,
/// - the number of layers,
/// - the transverse size of the calorimeter (the input face is a square).
///
/// In DefineVolumes(), sensitive detectors of CalorimeterSD type
/// are created and associated with the Absorber and Gap volumes.
///
/// In addition a transverse uniform magnetic field is defined in
/// SetMagField() method which can be activated
/// via a command defined in the B4DetectorMessenger class. 
#include "G4Material.hh"
class G4VSolid;
class G4PVPlacement;
#include "CalorimeterSD.hpp"
#include "common.hpp"
#include "TData.hpp"


class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    DetectorConstruction();
    virtual ~DetectorConstruction();

  public:
    virtual G4VPhysicalVolume* Construct();

    // set methods
    //
     
  private:
    // methods
    //
    void DefineMaterials();
    G4VPhysicalVolume* DefineVolumes();
    // data members
    //
    G4bool  fCheckOverlaps; // option to activate checking of volumes overlaps
    G4double fDepth;
    G4double fForwardLength;    
    
    G4double calorLength;
    G4double calorWidth;
    G4double calorHeight;
    G4LogicalVolume* worldLV;
    std::vector<G4VSolid*> calorCrysS;
    std::vector<CalorimeterSD*> calorSD;
    std::vector<G4LogicalVolume*> calorCrysL;
    std::vector<G4PVPlacement*> calorCrysPh;
    std::vector<G4VisAttributes*> calorBoxVisAtt;
    std::vector<G4IntersectionSolid*> intersect;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

