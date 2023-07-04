#include "SensitiveDetector.hh"
#include "g4root.hh"
#include "EventAction.hh"
#include "G4VProcess.hh"

/// Sensitive detector class.

SensitiveDetector::SensitiveDetector(G4String name,  EventAction*  eventAction)
 : G4VSensitiveDetector(name),  fEventAction(eventAction){}
SensitiveDetector::~SensitiveDetector() {}

G4bool SensitiveDetector::ProcessHits(G4Step *step, G4TouchableHistory *ROhist) {

  G4AnalysisManager* man = G4AnalysisManager::Instance();

  // get volume of the current step
  G4VPhysicalVolume* prevolume = step->GetPreStepPoint()->GetPhysicalVolume();

  // get volutme of the previous step 
  G4VPhysicalVolume* postvolume = step->GetPostStepPoint()->GetPhysicalVolume();

  G4bool isPhoton = step->GetTrack()->GetDynamicParticle()->GetParticleDefinition()
                    == G4OpticalPhoton::OpticalPhotonDefinition();


   if (isPhoton && step->GetTrack()->GetCurrentStepNumber() == 1){
    fEventAction->AddGeneratedPhoton();
  }
 

  G4bool isGamma = step->GetTrack()->GetDynamicParticle()->GetParticleDefinition()
                    == G4Gamma::GammaDefinition();
  if (isPhoton){
    man->FillH1(2, step->GetTrack()->GetKineticEnergy());
    man->FillNtupleDColumn(0,0, step->GetTrack()->GetKineticEnergy());
    man->FillNtupleDColumn(0,2, step->GetPostStepPoint()->GetPosition().getX());
    man->FillNtupleDColumn(0,3, step->GetPostStepPoint()->GetPosition().getY());
    man->FillNtupleDColumn(0,4, step->GetPostStepPoint()->GetPosition().getZ());
    man->FillNtupleIColumn(0,5, prevolume->GetCopyNo());
    man->FillNtupleIColumn(0,6, step->GetTrack()->GetDynamicParticle()->GetParticleDefinition()->GetPDGEncoding());
    man->AddNtupleRow(0);
    fEventAction->AddPhoton();
    step->GetTrack()->SetTrackStatus(fStopAndKill);
  }

  
  if (isGamma && step->GetPostStepPoint()->
      GetProcessDefinedStep()->GetProcessName() == "phot" &&
      postvolume->GetName() == "capNC" ){

    fEventAction->AddGamma();
    man->FillH1(5, step->GetPreStepPoint()->GetKineticEnergy());
  }

}