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
/// \file exampleB1.cc
/// \brief Main program of the B1 example

#include "DetectorConstruction.hh"
#include "ActionInitialization.hh"

#include "G4RunManagerFactory.hh"

#include "G4UImanager.hh"
#include "QBBC.hh"
#include "G4EmStandardPhysics_option4.hh"
#include "G4OpticalParameters.hh"
#include "G4OpticalPhysics.hh"
#include "G4SystemOfUnits.hh"


#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "g4root.hh"
#include "G4AnalysisMessenger.hh"
#include "Randomize.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int main(int argc,char** argv)
{
  // Detect interactive mode (if no arguments) and define UI session
  //
  G4UIExecutive* ui = 0;
  if ( argc == 1 ) {
    ui = new G4UIExecutive(argc, argv);
  }

  // Optionally: choose a different Random engine...
  // G4Random::setTheEngine(new CLHEP::MTwistEngine);
  // Construct the default run manager
  //
  auto* runManager =
    G4RunManagerFactory::CreateRunManager(G4RunManagerType::Default);

  G4int nThreads = 3;
  
	#ifdef G4MULTITHREADED
	  if(nThreads > 0) runManager->SetNumberOfThreads(nThreads);
	#endif

  // Set mandatory initialization classes
  //
  // Detector construction
  DetectorConstruction* detectorConstruction = new DetectorConstruction();
  runManager->SetUserInitialization(detectorConstruction);

  // Physics list
  G4VModularPhysicsList* physicsList = new QBBC;
  physicsList->ReplacePhysics(new G4EmStandardPhysics_option4());

  G4OpticalPhysics* opticalPhysics = new G4OpticalPhysics();
  auto opticalParams               = G4OpticalParameters::Instance();

  opticalParams->SetWLSTimeProfile("delta");

  opticalParams->SetScintYieldFactor(0.9);
  opticalParams->SetScintExcitationRatio(0.0);
  opticalParams->SetScintTrackSecondariesFirst(true);
  opticalParams->SetScintEnhancedTimeConstants(true);

  opticalParams->SetCerenkovMaxPhotonsPerStep(100);
  opticalParams->SetCerenkovMaxBetaChange(10.0);
  opticalParams->SetCerenkovTrackSecondariesFirst(true);

  physicsList->RegisterPhysics(opticalPhysics);
  physicsList->SetVerboseLevel(1);

  runManager->SetUserInitialization(physicsList);


    
  // User action initialization
  runManager->SetUserInitialization(new ActionInitialization());
  
  // Initialize visualization
  //
  G4VisManager* visManager = new G4VisExecutive;
  // G4VisExecutive can take a verbosity argument - see /vis/verbose guidance.
  // G4VisManager* visManager = new G4VisExecutive("Quiet");
  visManager->Initialize();

  // Get the pointer to the User Interface manager
  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  // Process macro or start UI session
  //
  if ( ! ui ) { 
    // batch mode
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command+fileName);
  }
  else { 
    std::stringstream fillFactor;   fillFactor   << std::fixed << std::setprecision(4) << detectorConstruction->GetFillFactor();
    std::stringstream capThickness; capThickness << std::fixed << std::setprecision(2) << detectorConstruction->GetCapSize()/mm;
    std::stringstream pitchSize;    pitchSize    << std::fixed << std::setprecision(2) << detectorConstruction->GetPitchSize()/um;
    std::stringstream spacingSize;  spacingSize  << std::fixed << std::setprecision(2) << detectorConstruction->GetSpacingSize()/um;
    // interactive mode/vis/scene/add/text2D -.9 -.8 24 ! ! text
    UImanager->ApplyCommand("/control/execute init_vis.mac");
    // UImanager->ApplyCommand("/vis/scene/add/text2D -.9 -.6 18 ! ! Fill factor: " + fillFactor.str());
    UImanager->ApplyCommand("/vis/scene/add/text2D -.9 -.7 18 ! ! Cap thickness: " + capThickness.str() + " mm");
    UImanager->ApplyCommand("/vis/scene/add/text2D -.9 -.8 18 ! ! Pitch:   " + pitchSize.str() + " um");
    UImanager->ApplyCommand("/vis/scene/add/text2D -.9 -.9 18 ! ! Spacing: " + spacingSize.str() + " um");
    ui->SessionStart();
    delete ui;
  }

  
  // Job termination
  // Free the store: user actions, physics_list and detector_description are
  // owned and deleted by the run manager, so they should not be deleted 
  // in the main() program !
  
  delete visManager;
  delete runManager;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....
