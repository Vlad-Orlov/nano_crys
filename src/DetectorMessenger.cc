
#include "DetectorMessenger.hh"

#include "DetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4Scintillation.hh"
#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWith3VectorAndUnit.hh"
#include "G4UIcommand.hh"
#include "G4UIdirectory.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorMessenger::DetectorMessenger(DetectorConstruction* detector)
  : fDetector(detector)
{
  // Setup a command directory for detector controls with guidance
  fDetectorDir = new G4UIdirectory("/detector/");
  fDetectorDir->SetGuidance("Detector geometry control");


  fSetPitchCmd =
    new G4UIcmdWithADoubleAndUnit("/detector/setPitch", this);
  fSetPitchCmd->SetGuidance("Set pitch size of NC");
  fSetPitchCmd->SetParameterName("pitch", false);
  fSetPitchCmd->SetDefaultUnit("um");
  fSetPitchCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
  fSetPitchCmd->SetToBeBroadcasted(false);

  fSetSpacingCmd =
    new G4UIcmdWithADoubleAndUnit("/detector/setSpacing", this);
  fSetSpacingCmd->SetGuidance("Set spacing between pitches.");
  fSetSpacingCmd->SetParameterName("spacing", false);
  fSetSpacingCmd->SetDefaultUnit("um");
  fSetSpacingCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
  fSetSpacingCmd->SetToBeBroadcasted(false);

  fSetCapSizeCmd =
    new G4UIcmdWithADoubleAndUnit("/detector/setCapSize", this);
  fSetCapSizeCmd->SetGuidance("Set size of the cap");
  fSetCapSizeCmd->SetParameterName("cap", false);
  fSetCapSizeCmd->SetDefaultUnit("um");
  fSetCapSizeCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
  fSetCapSizeCmd->SetToBeBroadcasted(false);

  fDefaultsCmd = 
    new G4UIcommand("/detector/defaults", this);
  fDefaultsCmd->SetGuidance("Set all detector geometry values to defaults.");
  fDefaultsCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
  fDefaultsCmd->SetToBeBroadcasted(false);


}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorMessenger::~DetectorMessenger()
{
  delete fSetPitchCmd;
  delete fSetSpacingCmd;
  delete fSetCapSizeCmd;
  delete fDetectorDir;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{
  
  if(command == fSetPitchCmd)
  {
    fDetector->SetPitch(fSetPitchCmd->GetNewDoubleValue(newValue));
  }
  else if(command == fSetSpacingCmd)
  {
    fDetector->SetSpacing(fSetSpacingCmd->GetNewDoubleValue(newValue));
  }
  else if(command == fSetCapSizeCmd)
  {
    fDetector->SetCapSize(fSetCapSizeCmd->GetNewDoubleValue(newValue));
  }
  else if(command == fDefaultsCmd)
  {
    fDetector->SetDefaults();
    G4RunManager::GetRunManager()->ReinitializeGeometry();
  }

 
}

