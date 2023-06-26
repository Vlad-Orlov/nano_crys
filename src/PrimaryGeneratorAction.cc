/// \file PrimaryGeneratorAction.cc
/// \brief Implementation of the PrimaryGeneratorAction class

#include "PrimaryGeneratorAction.hh"

#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include "DetectorConstruction.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorAction::PrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(),
  fParticleGun(0), 
  fWafer(0)
{
  G4int n_particle = 1;
  fParticleGun  = new G4ParticleGun(n_particle);

  // default particle kinematic
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  G4ParticleDefinition* particle
    = particleTable->FindParticle(particleName="gamma");
  fParticleGun->SetParticleDefinition(particle);
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,-1.,0.));
  fParticleGun->SetParticleEnergy(60 * keV);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete fParticleGun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  //this function is called at the begining of each event
  //
  G4double waferSizeXY = 0;
  G4double waferSizeZ = 0;

    if (!fWafer)
  {
    G4LogicalVolume* waferLV
      = G4LogicalVolumeStore::GetInstance()->GetVolume("Wafer");
    if ( waferLV ) fWafer = dynamic_cast<G4Box*>(waferLV->GetSolid());
  }

  if ( fWafer ) {
    waferSizeXY = fWafer->GetXHalfLength()*2.;
    waferSizeZ = fWafer->GetZHalfLength()*2.;
  } 


  // G4double x = ( G4UniformRand() - 0.5 ) * waferSizeXY;
  // G4double z = ( G4UniformRand() - 0.5 ) * waferSizeXY;
  // G4double y = 7 * mm;

  G4double x = ( G4UniformRand() - 0.5 ) * waferSizeXY;
  G4double z = ( G4UniformRand() - 0.5 ) * waferSizeXY;
  G4double y = 5 * mm;

  fParticleGun->SetParticlePosition(G4ThreeVector(x,y,z));
  fParticleGun->GeneratePrimaryVertex(anEvent);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

