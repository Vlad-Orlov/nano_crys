/// \file SensitiveDetector.hh
/// \brief Definition of the SensitiveDetector class

#ifndef SensitiveDetector_h
#define SensitiveDetector_h 1

#include "G4VSensitiveDetector.hh"
#include "G4OpticalPhoton.hh"
#include "G4Gamma.hh"
/// Sensitive detector class.
class EventAction;

class SensitiveDetector : public G4VSensitiveDetector
{
  public:
    SensitiveDetector(G4String, EventAction* );
    virtual ~SensitiveDetector();

 private:
    virtual G4bool ProcessHits(G4Step*, G4TouchableHistory*);
    EventAction*  fEventAction;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// 
#endif

    
