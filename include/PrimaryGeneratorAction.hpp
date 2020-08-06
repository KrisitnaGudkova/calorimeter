#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"
#include "Randomize.hh"
//#include <vector>
#include "TData.hpp"

class G4ParticleGun;
class G4Event;

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
  PrimaryGeneratorAction();
  void SetData (TData*);
  ~PrimaryGeneratorAction();
  inline void SetInitEnergy (G4double Energy) {fEnergy = Energy;};
  inline G4double GetInitEnergy (void) {return fEnergy;};

public:
  void GeneratePrimaries(G4Event* anEvent);
  void SetCoord (G4double X, G4double Y, G4double Z);
  void SetEnergy (G4double EEnergy);

private:
  void PrimaryConstructor (G4double);
  G4ParticleGun* particleGun;
  G4double fEnergy, x, y, z;
  TData *data;
  CLHEP::HepJamesRandom rand;
};


#endif
