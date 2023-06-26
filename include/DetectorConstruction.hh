/// \file DetectorConstruction.hh
/// \brief Definition of the DetectorConstruction class

#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
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
    DetectorMessenger* fDetectorMessenger;
  // Materials & elements
    G4Material* world_mat;
    G4Material* wafer_mat;
    G4Material* NC_mat;
    G4Material* CsPbBr3_mat;
    G4Material* MAPbBr3_mat;
    G4Material* FAPbBr3_mat;

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

