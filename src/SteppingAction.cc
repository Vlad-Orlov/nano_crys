//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
/// \file SteppingAction.cc
/// \brief Implementation of the SteppingAction class

#include "SteppingAction.hh"
#include "EventAction.hh"
#include "DetectorConstruction.hh"

#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include "G4OpticalPhoton.hh"
#include "G4Gamma.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::SteppingAction(EventAction* eventAction)
: G4UserSteppingAction(),
  fEventAction(eventAction),
  fScoringVolume(0)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::~SteppingAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SteppingAction::UserSteppingAction(const G4Step* step)
{
  if (!fScoringVolume) { 
    const DetectorConstruction* detectorConstruction
      = static_cast<const DetectorConstruction*>
        (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
    fScoringVolume = detectorConstruction->GetScoringVolume();   
  }

  G4AnalysisManager* man = G4AnalysisManager::Instance();

  // get volume of the current step
  G4VPhysicalVolume* prevolume = step->GetPreStepPoint()->GetPhysicalVolume();


  // get volutme of the previous step 
  G4VPhysicalVolume* postvolume = step->GetPostStepPoint()->GetPhysicalVolume();


  // // check if we are in scoring volume
  // if (prevolume != fScoringVolume) return;

  // // collect energy deposited in this step
  // G4double edepStep = step->GetTotalEnergyDeposit();
  // fEventAction->AddEdep(edepStep);  

  G4bool isPhoton = step->GetTrack()->GetDynamicParticle()->GetParticleDefinition()
                    == G4OpticalPhoton::OpticalPhotonDefinition();

  if (isPhoton && step->GetTrack()->GetCurrentStepNumber() == 1){
    fEventAction->AddGeneratedPhoton();
  }

  G4bool isGamma = step->GetTrack()->GetDynamicParticle()->GetParticleDefinition()
                    == G4Gamma::GammaDefinition();
  if (isPhoton && 
     ((prevolume->GetName() == "NC") || (prevolume->GetName() == "capNC")) && 
     (postvolume->GetName() == "Wafer") ){
    // G4cout << "Copy number is: " << prevolume->GetCopyNo() << G4endl;
    man->FillH1(2, step->GetTrack()->GetKineticEnergy());
    man->FillNtupleDColumn(0,0, step->GetTrack()->GetKineticEnergy());
    man->FillNtupleIColumn(0,1,prevolume->GetCopyNo());
    man->AddNtupleRow(0);
    fEventAction->AddPhoton();
  }

  
  if (isGamma && step->GetPostStepPoint()->
      GetProcessDefinedStep()->GetProcessName() == "phot" &&
      postvolume->GetName() == "capNC" ){

    fEventAction->AddGamma();
    man->FillH1(5, step->GetPreStepPoint()->GetKineticEnergy());
  }


}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

