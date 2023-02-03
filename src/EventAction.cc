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
/// \file EventAction.cc
/// \brief Implementation of the EventAction class

#include "EventAction.hh"
#include "RunAction.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::EventAction(RunAction* runAction)
: G4UserEventAction(),
  fRunAction(runAction),
  fEdep(0.),
  fNphotons(0),
  fGeneratedPhotons(0),
  fNgammas(0)
{} 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::~EventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::BeginOfEventAction(const G4Event* event)
{    
  fEdep = 0.;
  fNphotons = 0;
  fGeneratedPhotons = 0;
  fNgammas = 0;

  G4int eventNum = event->GetEventID();

	if (eventNum%1000 == 0) {
		G4cout << "\n---> Begin of Event: " << eventNum << G4endl;
	}

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::EndOfEventAction(const G4Event*)
{   
  // accumulate statistics in run action
  fRunAction->AddEdep(fEdep);
  G4AnalysisManager* man = G4AnalysisManager::Instance();
  man->FillH1(0, fEdep);
  man->FillH1(1, fEdep);
  man->FillH1(3, fNphotons);
  man->FillH1(4, fNgammas);
  man->FillH1(6, fGeneratedPhotons);

  man->FillNtupleIColumn(0, 1, fNphotons);
  // man->FillNtupleIColumn(0, 2, fNphotons);
  // G4cout << "Registered " << fNphotons << G4endl;
  man->AddNtupleRow(0);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
