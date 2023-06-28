/// \file EventAction.hh
/// \brief Definition of the EventAction class

#ifndef EventAction_h
#define EventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

class RunAction;

/// Event action class
///

class EventAction : public G4UserEventAction
{
  public:
    EventAction(RunAction* runAction);
    virtual ~EventAction();

    virtual void BeginOfEventAction(const G4Event* event);
    virtual void EndOfEventAction(const G4Event* event);

    void AddEdep(G4double edep) { fEdep += edep; }
    void AddPhoton() { fNphotons += 1; }
    void AddGeneratedPhoton() { fGeneratedPhotons += 1; }
    void AddGamma() { fNgammas += 1; }

  private:
    RunAction* fRunAction;
    G4double     fEdep;
    G4int     fNphotons;
    G4int     fGeneratedPhotons;
    G4int     fNgammas;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

    
