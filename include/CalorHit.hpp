#ifndef CalorHit_h
#define CalorHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"

/// Calorimeter hit class
///
/// It defines data members to store the the energy deposit and track lengths
/// of charged particles in a selected volume:
/// - fEdep, fTrackLength

class CalorHit : public G4VHit
{
  public:
    CalorHit();
    CalorHit(const CalorHit&);
    virtual ~CalorHit();

    // operators
    const CalorHit& operator=(const CalorHit&);
    G4int operator==(const CalorHit&) const;

    inline void* operator new(size_t);
    inline void  operator delete(void*);

    // methods from base class
    virtual void Draw() {}
    virtual void Print();

    // methods to handle data
    void Add(G4double de);

    // get methods
    G4double GetEdep() const;
      
  private:
    G4double fEdep;        ///< Energy deposit in the sensitive volume
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

typedef G4THitsCollection<CalorHit> CalorHitsCollection;

extern G4Allocator<CalorHit> CalorHitAllocator;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void* CalorHit::operator new(size_t)
{
  void *hit;
  hit = (void *) CalorHitAllocator.MallocSingle();
  return hit;
}

inline void CalorHit::operator delete(void *hit)
{
  CalorHitAllocator.FreeSingle((CalorHit*) hit);
}

inline void CalorHit::Add(G4double de)
 {
  fEdep += de; 
}

inline G4double CalorHit::GetEdep() const
 { 
  return fEdep; 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
