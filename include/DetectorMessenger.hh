#ifndef DetectorMessenger_h
#define DetectorMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class DetectorConstruction;

class G4UIcmdWithABool;
class G4UIcmdWithADouble;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithAnInteger;
class G4UIcmdWith3VectorAndUnit;
class G4UIcommand;
class G4UIdirectory;

class DetectorMessenger : public G4UImessenger
{
 public:
  DetectorMessenger(DetectorConstruction*);
  ~DetectorMessenger();

  void SetNewValue(G4UIcommand*, G4String) override;

 private:
  DetectorConstruction*      fDetector;
  G4UIdirectory*             fDetectorDir;
  G4UIcommand*               fDefaultsCmd;
  G4UIcmdWithADoubleAndUnit* fSetPitchCmd;
  G4UIcmdWithADoubleAndUnit* fSetSpacingCmd;
  G4UIcmdWithADoubleAndUnit* fSetCapSizeCmd;
};

#endif

