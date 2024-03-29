/// \file RunAction.cc
/// \brief Implementation of the RunAction class

#include "RunAction.hh"
#include "PrimaryGeneratorAction.hh"
#include "DetectorConstruction.hh"
// #include "B1Run.hh"

#include "G4RunManager.hh"
#include "G4Run.hh"
#include "G4AccumulableManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


RunAction::RunAction()
: G4UserRunAction(),
  fTotalPhotons(0)
{ 

  // Register accumulable to the accumulable manager
  G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
  accumulableManager->RegisterAccumulable(fTotalPhotons); 

  G4AnalysisManager* man = G4AnalysisManager::Instance();
  man->SetFileName("nc_photons");
  man->SetNtupleMerging(true);
  // Open an output file
  // Create histogram(s)
  man->CreateH1("0","Edep in absorber", 100, 0., 800*MeV);
  man->CreateH1("1","Edep in gap", 100, 0., 100*MeV);
  man->CreateH1("2","Photon energy", 1000, 0., 5*eV);
  man->CreateH1("3","Number of photons", 50000, 0., 50000);
  man->CreateH1("4","Number of gammas", 1000, 0., 10000);
  man->CreateH1("5","Energy of gammas", 1000, 0., 200*keV);
  man->CreateH1("6","Number of generated photons", 10000, 0., 100000);
  man->CreateNtuple("Detected_photons", "Detected_photons");
  man->CreateNtupleDColumn("Photon_energy_spectrum");
  man->CreateNtupleIColumn("Number_of_photons_per_event");
  man->CreateNtupleDColumn("x");
  man->CreateNtupleDColumn("y");
  man->CreateNtupleDColumn("z");
  man->CreateNtupleIColumn("volumeId");
  man->CreateNtupleIColumn("pid");
  man->FinishNtuple(0);
  // man->CreateH1("3", "NC absorption spectrum", 100, 0., 5*eV);
  // man->CreateH1("4", "NC absorption spectrum", 100, 0., 5*eV);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::~RunAction()
{
  delete G4AnalysisManager::Instance();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::BeginOfRunAction(const G4Run*)
{ 
  // inform the runManager to save random number seed
  G4RunManager::GetRunManager()->SetRandomNumberStore(false);

  // reset accumulables to their initial values
  G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
  accumulableManager->Reset();

  // Get analysis manager
  G4AnalysisManager* man = G4AnalysisManager::Instance();
  man->OpenFile();

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::EndOfRunAction(const G4Run* run)
{
  G4int nofEvents = run->GetNumberOfEvent();
  if (nofEvents == 0) return;

  // Merge accumulables 
  G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
  accumulableManager->Merge();

  G4AnalysisManager* man = G4AnalysisManager::Instance();
  man->Write();
  man->CloseFile();


  const DetectorConstruction* detectorConstruction
   = static_cast<const DetectorConstruction*>
     (G4RunManager::GetRunManager()->GetUserDetectorConstruction());

  // Run conditions
  //  note: There is no primary generator action object for "master"
  //        run manager for multi-threaded mode.
  const PrimaryGeneratorAction* generatorAction
   = static_cast<const PrimaryGeneratorAction*>
     (G4RunManager::GetRunManager()->GetUserPrimaryGeneratorAction());
  G4String runCondition;
  if (generatorAction)
  {
    const G4ParticleGun* particleGun = generatorAction->GetParticleGun();
    runCondition += particleGun->GetParticleDefinition()->GetParticleName();
    runCondition += " of ";
    G4double particleEnergy = particleGun->GetParticleEnergy();
    runCondition += G4BestUnit(particleEnergy,"Energy");
  }
        
  // Print
  //  
  if (IsMaster()) {
    G4cout
     << G4endl
     << "--------------------End of Global Run-----------------------";
  }
  else {
    G4cout
     << G4endl
     << "--------------------End of Local Run------------------------";
  }
  
  G4cout
     << G4endl
     << " The run consists of " << nofEvents << " "<< runCondition
     << G4endl
     << " Total number of optical photons detected : " 
     << fTotalPhotons.GetValue() << G4endl
     << "Pitch size : "
     << detectorConstruction->GetPitchSize()/um << "um" << G4endl
     << "Cap thickness : "
     << detectorConstruction->GetCapSize()/um << "um" << G4endl
     << "Fill Factor : "
     << detectorConstruction->GetFillFactor() << G4endl
     << "------------------------------------------------------------"
     << G4endl
     << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


void RunAction::AddTotalPhotons(G4int Nphotons)
{
  fTotalPhotons += Nphotons;
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

