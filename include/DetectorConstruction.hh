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
/// \file DetectorConstruction.hh
/// \brief Definition of the DetectorConstruction class

#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "SensitiveDetector.hh"
#include "DetectorMessenger.hh"
#include "globals.hh"
#include "G4SystemOfUnits.hh"
#include "g4root.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;
class G4Material;
class G4Box;
class G4MaterialPropertiesTable; 
/// Detector construction class to define materials and geometry.

class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    DetectorConstruction();
    virtual ~DetectorConstruction();
    G4VPhysicalVolume* Construct() override;

    // Functions to modify the geometry
    void SetPitch(G4double);
    void SetSpacing(G4double);
    void SetCapSize(G4double);
    void SetDefaults();
    
    G4double wafer_dx = 3 * mm;
    G4double wafer_dy = 0.5 * cm;
    G4double wafer_dz = wafer_dx;
    // Functions to get geometry values
    G4double GetPitchSize() const {return fNC_dx;}
    G4double GetSpacingSize() const {return fInner_spacing;}
    G4double GetCapSize() const {return fCapSize;}
    G4double GetFillFactor() const {return (fNC_dx*fNC_dz*N*N / (wafer_dx*wafer_dz) );}
    G4LogicalVolume* GetScoringVolume() const { return fScoringVolume; }

  protected:
    G4LogicalVolume*  fScoringVolume;
  
  private:

  
    void DefineMaterials();
    void DefineSurfaces();
    // virtual void ConstructSDandField();
    DetectorMessenger* fDetectorMessenger;
  // Materials & elements
    G4Material* world_mat;
    G4Material* wafer_mat;
    G4Material* NC_mat;
    G4Material* CsPbBr3_mat;
    G4Material* MAPbBr3_mat;
    G4Material* FAPbBr3_mat;
    G4Material* CsPbBr3_gdml_mat;
    G4MaterialPropertiesTable* CsPbBr3_mpt;
    G4MaterialPropertiesTable* MAPbBr3_mpt;
    G4MaterialPropertiesTable* FAPbBr3_mpt;

  // Geometry dimensions
    G4double fNC_dx;
    G4double fNC_dy;
    G4double fNC_dz;
    G4double fCapSize;
    G4double fInner_spacing;
    G4int N;
  // Volumes
    G4Box *capNC, *solidNC, *solidWafer, *solidWorld;
    G4LogicalVolume *logicCapNC, *logicNC, *logicWafer, *logicWorld;
    G4VPhysicalVolume *physNC, *physWafer, *physWorld;
    std::vector<G4VPhysicalVolume*> col_phys_vect;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

