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
  fRunAction->AddTotalPhotons(fNphotons);
  G4AnalysisManager* man = G4AnalysisManager::Instance();
  man->FillH1(0, fEdep);
  man->FillH1(1, fEdep);
  man->FillH1(3, fNphotons);
  man->FillH1(4, fNgammas);
  man->FillH1(6, fGeneratedPhotons);
  man->FillNtupleIColumn(0,1, fNphotons);  


  // man->FillNtupleIColumn(0, 2, fNphotons);
  // G4cout << "Registered " << fNphotons << G4endl;
  man->AddNtupleRow(0);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
