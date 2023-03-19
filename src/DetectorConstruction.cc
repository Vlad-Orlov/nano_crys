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
/// \file DetectorConstruction.cc
/// \brief Implementation of the DetectorConstruction class

#include "DetectorConstruction.hh"
#include "DetectorMessenger.hh"
#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::DetectorConstruction()
    : G4VUserDetectorConstruction(),
      fScoringVolume(0)
{
  world_mat = wafer_mat = NC_mat = nullptr;

  SetDefaults();
  DefineMaterials();
  fDetectorMessenger = new DetectorMessenger(this);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::~DetectorConstruction()
{
  if (physWorld)
  {
    delete physWorld;
  }
  delete fDetectorMessenger;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void DetectorConstruction::DefineMaterials()
{
  //***Material properties tables

  G4NistManager *man = G4NistManager::Instance();
  G4bool isotopes = true;

  G4Element *H = man->FindOrBuildElement("H", isotopes);
  G4Element *O = man->FindOrBuildElement("O", isotopes);
  G4Element *C = man->FindOrBuildElement("C", isotopes);
  G4Element *N = man->FindOrBuildElement("N", isotopes);
  G4Element *P = man->FindOrBuildElement("P", isotopes);
  G4Element *Cl = man->FindOrBuildElement("Cl", isotopes);
  G4Element *Mn = man->FindOrBuildElement("Mn", isotopes);
  G4Element *Br = man->FindOrBuildElement("Br", isotopes);
  G4Element *Pb = man->FindOrBuildElement("Pb", isotopes);
  G4Element *Cs = man->FindOrBuildElement("Cs", isotopes);

  MAPbBr3_mat = new G4Material("MAPbBr3_mat", 3.83 * g / cm3, 5);
  FAPbBr3_mat = new G4Material("FAPbBr3_mat", 3.83 * g / cm3, 5); //?? need to check this one
  CsPbBr3_mat = new G4Material("CsPbBr3_mat", 4.55 * g / cm3, 3);

  MAPbBr3_mat->AddElement(H, 6);
  MAPbBr3_mat->AddElement(C, 1);
  MAPbBr3_mat->AddElement(N, 1);
  MAPbBr3_mat->AddElement(Pb, 1);
  MAPbBr3_mat->AddElement(Br, 3);

  FAPbBr3_mat->AddElement(H, 5);
  FAPbBr3_mat->AddElement(C, 1);
  FAPbBr3_mat->AddElement(N, 2);
  FAPbBr3_mat->AddElement(Pb, 1);
  FAPbBr3_mat->AddElement(Br, 3);

  CsPbBr3_mat->AddElement(Cs, 1);
  CsPbBr3_mat->AddElement(Pb, 1);
  CsPbBr3_mat->AddElement(Br, 3);

  std::vector<G4double> FAPbBr3_em_en = {2.24221 * eV, 2.24713 * eV, 2.24713 * eV, 2.24963 * eV, 2.27408 * eV, 2.28943 * eV,
                                         2.30106 * eV, 2.32045 * eV, 2.33209 * eV, 2.34178 * eV, 2.35148 * eV, 2.36118 * eV,
                                         2.36893 * eV, 2.37087 * eV, 2.37863 * eV, 2.38445 * eV, 2.39221 * eV, 2.40190 * eV,
                                         2.41548 * eV, 2.42711 * eV, 2.43570 * eV, 2.44062 * eV, 2.45164 * eV, 2.46023 * eV,
                                         2.46882 * eV, 2.48101 * eV, 2.50062 * eV, 2.53124 * eV, 2.57529 * eV};

  std::vector<G4double> FAPbBr3_em = {0.07767, 0.10775, 0.10775, 0.13879, 0.21446, 0.31964,
                                      0.39200, 0.60909, 0.77794, 0.99503, 1.23624, 1.42921,
                                      1.64630, 1.86339, 2.10461, 2.34582, 2.58703, 2.78000,
                                      2.70764, 2.49055, 2.16154, 1.85691, 1.38542, 1.02065,
                                      0.76259, 0.48804, 0.22999, 0.06215, 0.01656};

  std::vector<G4double> FAPbBr3_abs_en = {2.38265460 * eV, 2.39257248 * eV, 2.39954536 * eV, 2.41227593 * eV, 2.42224983 * eV,
                                          2.42668771 * eV, 2.43386120 * eV, 2.44107717 * eV, 2.44853288 * eV, 2.45287018 * eV,
                                          2.46318331 * eV, 2.47077487 * eV, 2.47659993 * eV, 2.48427454 * eV, 2.49179301 * eV,
                                          2.49485401 * eV, 2.50243680 * eV, 2.51337918 * eV, 2.52420859 * eV, 2.53513166 * eV,
                                          2.55747861 * eV, 2.58000454 * eV, 2.61477182 * eV, 2.63832291 * eV, 2.66603003 * eV,
                                          2.69408697 * eV, 2.72298407 * eV, 2.75424980 * eV, 2.78624186 * eV, 2.81872506 * eV,
                                          2.85625294 * eV, 2.88465153 * eV, 2.91976399 * eV, 2.95344933 * eV, 2.99026728 * eV,
                                          3.02801478 * eV, 3.06425970 * eV, 3.10391077 * eV};

  std::vector<G4double> FAPbBr3_abs = {601.74171, 1379.92773, 1379.92773, 1379.92773, 2573.14631,
                                       3714.48581, 4907.70438, 5634.01134, 7605.41594, 10303.1275,
                                       13000.83905, 16891.76918, 20782.69931, 24258.59689, 28149.52702,
                                       31625.4246, 35101.32218, 38577.21976, 40548.62436, 39770.43834,
                                       35101.32218, 30484.0851, 31625.4246, 38992.25231, 47915.45207,
                                       54089.06121, 56060.46581, 56060.46581, 56060.46581, 56838.65183,
                                       58758.17736, 62234.07495, 64153.60048, 66125.00507, 68822.71663,
                                       72713.64676, 77330.88385, 82000.00000};

  std::transform(FAPbBr3_abs.begin(), FAPbBr3_abs.end(), FAPbBr3_abs.begin(), 
                 [](G4double value) -> G4double{return 1./value * cm;});


  std::vector<G4double> CsPbBr3_em_en = {1.77142857 * eV, 1.77396280 * eV, 1.77650430 * eV, 1.77905308 * eV, 1.7816092 * eV,
                                         1.78417266 * eV, 1.78674352 * eV, 1.78932179 * eV, 1.79190751 * eV, 1.79450072 * eV,
                                         1.79710145 * eV, 1.79970972 * eV, 1.80232558 * eV, 1.80494905 * eV, 1.80758017 * eV,
                                         1.81021898 * eV, 1.81286550 * eV, 1.81551977 * eV, 1.81818182 * eV, 1.82085169 * eV,
                                         1.82352941 * eV, 1.82621502 * eV, 1.82890855 * eV, 1.83161004 * eV, 1.83431953 * eV,
                                         1.83703704 * eV, 1.83976261 * eV, 1.84249629 * eV, 1.84523810 * eV, 1.84798808 * eV,
                                         1.85074627 * eV, 1.85351271 * eV, 1.85628743 * eV, 1.85907046 * eV, 1.86186186 * eV,
                                         1.86466165 * eV, 1.86746988 * eV, 1.87028658 * eV, 1.87311178 * eV, 1.87594554 * eV,
                                         1.87878788 * eV, 1.88163885 * eV, 1.88449848 * eV, 1.88736682 * eV, 1.89024390 * eV,
                                         1.89312977 * eV, 1.89602446 * eV, 1.89892802 * eV, 1.90184049 * eV, 1.90476190 * eV,
                                         1.90769231 * eV, 1.91063174 * eV, 1.91358025 * eV, 1.91653787 * eV, 1.91950464 * eV,
                                         1.92248062 * eV, 1.92546584 * eV, 1.92846034 * eV, 1.93146417 * eV, 1.93447738 * eV,
                                         1.93750000 * eV, 1.94053208 * eV, 1.94357367 * eV, 1.94662480 * eV, 1.94968553 * eV,
                                         1.95275591 * eV, 1.95583596 * eV, 1.95892575 * eV, 1.96202532 * eV, 1.96513471 * eV,
                                         1.96825397 * eV, 1.97138315 * eV, 1.97452229 * eV, 1.97767145 * eV, 1.98083067 * eV,
                                         1.98400000 * eV, 1.98717949 * eV, 1.99036918 * eV, 1.99356913 * eV, 1.99677939 * eV,
                                         2.00000000 * eV, 2.00323102 * eV, 2.00647249 * eV, 2.00972447 * eV, 2.01298701 * eV,
                                         2.01626016 * eV, 2.01954397 * eV, 2.02283850 * eV, 2.02614379 * eV, 2.02945990 * eV,
                                         2.03278689 * eV, 2.03612479 * eV, 2.03947368 * eV, 2.04283361 * eV, 2.04620462 * eV,
                                         2.04958678 * eV, 2.05298013 * eV, 2.05638474 * eV, 2.05980066 * eV, 2.06322795 * eV,
                                         2.06666667 * eV, 2.07011686 * eV, 2.07357860 * eV, 2.07705193 * eV, 2.08053691 * eV,
                                         2.08403361 * eV, 2.08754209 * eV, 2.09106239 * eV, 2.09459459 * eV, 2.09813875 * eV,
                                         2.10169492 * eV, 2.10526316 * eV, 2.10884354 * eV, 2.11243612 * eV, 2.11604096 * eV,
                                         2.11965812 * eV, 2.12328767 * eV, 2.12692967 * eV, 2.13058419 * eV, 2.13425129 * eV,
                                         2.13793103 * eV, 2.14162349 * eV, 2.14532872 * eV, 2.14904679 * eV, 2.15277778 * eV,
                                         2.15652174 * eV, 2.16027875 * eV, 2.16404887 * eV, 2.16783217 * eV, 2.17162872 * eV,
                                         2.17543860 * eV, 2.17926186 * eV, 2.18309859 * eV, 2.18694885 * eV, 2.19081272 * eV,
                                         2.19469027 * eV, 2.19858156 * eV, 2.20248668 * eV, 2.20640569 * eV, 2.21033868 * eV,
                                         2.21428571 * eV, 2.21824687 * eV, 2.22222222 * eV, 2.22621185 * eV, 2.23021583 * eV,
                                         2.23423423 * eV, 2.23826715 * eV, 2.24231465 * eV, 2.24637681 * eV, 2.25045372 * eV,
                                         2.25454545 * eV, 2.25865209 * eV, 2.26277372 * eV, 2.26691042 * eV, 2.27106227 * eV,
                                         2.27522936 * eV, 2.27941176 * eV, 2.28360958 * eV, 2.28782288 * eV, 2.29205176 * eV,
                                         2.29629630 * eV, 2.30055659 * eV, 2.30483271 * eV, 2.30912477 * eV, 2.31343284 * eV,
                                         2.31775701 * eV, 2.32209738 * eV, 2.32645403 * eV, 2.33082707 * eV, 2.33521657 * eV,
                                         2.33962264 * eV, 2.34404537 * eV, 2.34848485 * eV, 2.35294118 * eV, 2.35741445 * eV,
                                         2.36190476 * eV, 2.36641221 * eV, 2.37093690 * eV, 2.37547893 * eV, 2.38003839 * eV,
                                         2.38461538 * eV, 2.38921002 * eV, 2.39382239 * eV, 2.39845261 * eV, 2.40310078 * eV,
                                         2.40776699 * eV, 2.41245136 * eV, 2.41715400 * eV, 2.42187500 * eV, 2.42661448 * eV,
                                         2.43137255 * eV, 2.43614931 * eV, 2.44094488 * eV, 2.44575937 * eV, 2.45059289 * eV,
                                         2.45544554 * eV, 2.46031746 * eV, 2.46520875 * eV, 2.47011952 * eV, 2.47504990 * eV,
                                         2.48000000 * eV, 2.48496994 * eV, 2.48995984 * eV, 2.49496982 * eV, 2.50000000 * eV,
                                         2.50505051 * eV, 2.51012146 * eV, 2.51521298 * eV, 2.52032520 * eV, 2.52545825 * eV,
                                         2.53061224 * eV, 2.53578732 * eV, 2.54098361 * eV, 2.54620123 * eV, 2.55144033 * eV,
                                         2.55670103 * eV, 2.56198347 * eV, 2.56728778 * eV, 2.57261411 * eV, 2.57796258 * eV,
                                         2.58333333 * eV, 2.58872651 * eV, 2.59414226 * eV, 2.59958071 * eV, 2.60504202 * eV,
                                         2.61052632 * eV, 2.61603376 * eV, 2.62156448 * eV, 2.62711864 * eV, 2.63269639 * eV,
                                         2.63829787 * eV, 2.64392324 * eV, 2.64957265 * eV, 2.65524625 * eV, 2.66094421 * eV,
                                         2.66666667 * eV, 2.67241379 * eV, 2.67818575 * eV, 2.68398268 * eV, 2.68980477 * eV,
                                         2.69565217 * eV, 2.70152505 * eV, 2.70742358 * eV, 2.71334792 * eV, 2.71929825 * eV,
                                         2.72527473 * eV, 2.73127753 * eV, 2.73730684 * eV, 2.74336283 * eV, 2.74944568 * eV,
                                         2.75555556 * eV, 2.76169265 * eV, 2.76785714 * eV, 2.77404922 * eV, 2.78026906 * eV,
                                         2.78651685 * eV, 2.79279279 * eV, 2.79909707 * eV, 2.80542986 * eV, 2.81179138 * eV,
                                         2.81818182 * eV, 2.82460137 * eV, 2.83105023 * eV, 2.83752860 * eV, 2.84403670 * eV,
                                         2.85057471 * eV, 2.85714286 * eV, 2.86374134 * eV, 2.87037037 * eV, 2.87703016 * eV,
                                         2.88372093 * eV, 2.89044289 * eV, 2.89719626 * eV, 2.90398126 * eV, 2.91079812 * eV,
                                         2.91764706 * eV, 2.92452830 * eV, 2.93144208 * eV, 2.93838863 * eV, 2.94536817 * eV,
                                         2.95238095 * eV, 2.95942721 * eV, 2.96650718 * eV, 2.97362110 * eV, 2.98076923 * eV,
                                         2.98795181 * eV, 2.99516908 * eV, 3.00242131 * eV, 3.00970874 * eV, 3.01703163 * eV,
                                         3.02439024 * eV, 3.03178484 * eV, 3.03921569 * eV, 3.04668305 * eV, 3.05418719 * eV,
                                         3.06172840 * eV, 3.06930693 * eV, 3.07692308 * eV, 3.08457711 * eV, 3.09226933 * eV};

  std::vector<G4double> CsPbBr3_em = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                      0.0, 1024.09853, 651.23254, 755.26624, 638.78424, 551.46265,
                                      385.4375, 646.6123, 666.89401, 478.59937, 654.45642, 520.63179,
                                      313.42652, 461.08025, 407.39382, 526.94212, 327.03827, 711.13361,
                                      465.17503, 722.54632, 645.48502, 919.90032, 541.41985, 950.11378,
                                      532.62182, 483.07556, 770.06574, 1029.97049, 867.99476, 883.26552,
                                      919.89734, 805.16127, 1097.95849, 1068.75783, 1418.76763, 1073.97305,
                                      1045.23903, 975.64947, 1640.80878, 1727.88255, 1913.49161, 1558.77321,
                                      2353.0228, 1983.13897, 2880.1633, 2742.42939, 2415.39761, 2832.57667,
                                      3186.68023, 3590.84971, 3877.11396, 3956.30282, 4543.84984, 4615.25366,
                                      5706.44449, 5801.37249, 6546.06438, 6508.41163, 6981.59343, 8067.17393,
                                      9939.48491, 9729.86621, 11374.8641, 12782.32806, 13803.24493, 15863.02952,
                                      17286.03456, 18345.43528, 21671.34706, 23504.39005, 25290.60926, 28494.96769,
                                      31005.23753, 33997.52053, 39239.22958, 43347.08397, 49031.29523, 55698.4081,
                                      60896.2127, 66736.2869, 71312.62479, 80581.12376, 89764.89437, 99608.72685,
                                      109383.13536, 123303.29485, 136539.61063, 151442.28857, 168979.91482,
                                      189377.0873, 209379.6219, 235753.42702, 261555.46752, 295303.45605,
                                      331030.50204, 362939.51543, 402658.96702, 458785.81349, 505419.68144,
                                      567701.77243, 635093.57966, 706339.41849, 788219.48139, 873628.70102,
                                      969750.8726, 1076394.764, 1192979.25345, 1318981.85099, 1450417.99514,
                                      1593711.21007, 1725253.04369, 1865153.73125, 1964206.50581, 2050239.99458,
                                      2092565.67986, 2085477.40791, 2026319.05062, 1908458.10336, 1773373.90923,
                                      1589415.32175, 1390521.22566, 1191813.02943, 991478.25195, 820496.15186,
                                      668109.47357, 542175.11707, 431451.38564, 343666.35234, 271616.63262,
                                      216899.3355, 176177.33668, 141622.75049, 115576.23988, 95778.826, 80495.13656,
                                      69030.64749, 57216.88262, 48373.56571, 42323.29828, 35084.87606, 31967.22066,
                                      26413.22513, 22378.17359, 17786.21615, 16054.58612, 12988.04469, 10748.32879,
                                      8563.54921, 7524.39705, 5550.04421, 4858.75724, 4182.75147, 3490.12997, 2589.57367,
                                      2505.46577, 1982.36423, 1588.55547, 1550.86709, 1058.31116, 755.24954, 721.17315,
                                      626.17993, 603.07654, 379.10161, 530.28851, 398.08234, 518.48289, 396.79026,
                                      477.04744, 366.10265, 385.96756, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

  std::vector<G4double> CsPbBr3_abs_en = {
      1.90769231 * eV, 1.91063174 * eV, 1.91358025 * eV, 1.91653787 * eV, 1.91950464 * eV,
      1.92248062 * eV, 1.92546584 * eV, 1.92846034 * eV, 1.93146417 * eV, 1.93447738 * eV,
      1.93750000 * eV, 1.94053208 * eV, 1.94357367 * eV, 1.9466248 * eV, 1.94968553 * eV,
      1.95275591 * eV, 1.95583596 * eV, 1.95892575 * eV, 1.96202532 * eV, 1.96513471 * eV,
      1.96825397 * eV, 1.97138315 * eV, 1.97452229 * eV, 1.97767145 * eV, 1.98083067 * eV,
      1.98400000 * eV, 1.98717949 * eV, 1.99036918 * eV, 1.99356913 * eV, 1.99677939 * eV,
      2.00000000 * eV, 2.00323102 * eV, 2.00647249 * eV, 2.00972447 * eV, 2.01298701 * eV,
      2.01626016 * eV, 2.01954397 * eV, 2.0228385 * eV, 2.02614379 * eV, 2.02945990 * eV,
      2.03278689 * eV, 2.03612479 * eV, 2.03947368 * eV, 2.04283361 * eV, 2.04620462 * eV,
      2.04958678 * eV, 2.05298013 * eV, 2.05638474 * eV, 2.05980066 * eV, 2.06322795 * eV,
      2.06666667 * eV, 2.07011686 * eV, 2.0735786 * eV, 2.07705193 * eV, 2.08053691 * eV,
      2.08403361 * eV, 2.08754209 * eV, 2.09106239 * eV, 2.09459459 * eV, 2.09813875 * eV,
      2.10169492 * eV, 2.10526316 * eV, 2.10884354 * eV, 2.11243612 * eV, 2.11604096 * eV,
      2.11965812 * eV, 2.12328767 * eV, 2.12692967 * eV, 2.13058419 * eV, 2.13425129 * eV,
      2.13793103 * eV, 2.14162349 * eV, 2.14532872 * eV, 2.14904679 * eV, 2.15277778 * eV,
      2.15652174 * eV, 2.16027875 * eV, 2.16404887 * eV, 2.16783217 * eV, 2.17162872 * eV,
      2.1754386 * eV, 2.17926186 * eV, 2.18309859 * eV, 2.18694885 * eV, 2.19081272 * eV,
      2.19469027 * eV, 2.19858156 * eV, 2.20248668 * eV, 2.20640569 * eV, 2.21033868 * eV,
      2.21428571 * eV, 2.21824687 * eV, 2.22222222 * eV, 2.22621185 * eV, 2.23021583 * eV,
      2.23423423 * eV, 2.23826715 * eV, 2.24231465 * eV, 2.24637681 * eV, 2.25045372 * eV,
      2.25454545 * eV, 2.25865209 * eV, 2.26277372 * eV, 2.26691042 * eV, 2.27106227 * eV,
      2.27522936 * eV, 2.27941176 * eV, 2.28360958 * eV, 2.28782288 * eV, 2.29205176 * eV,
      2.2962963 * eV, 2.30055659 * eV, 2.30483271 * eV, 2.30912477 * eV, 2.31343284 * eV,
      2.31775701 * eV, 2.32209738 * eV, 2.32645403 * eV, 2.33082707 * eV, 2.33521657 * eV,
      2.33962264 * eV, 2.34404537 * eV, 2.34848485 * eV, 2.35294118 * eV, 2.35741445 * eV,
      2.36190476 * eV, 2.36641221 * eV, 2.37093690 * eV, 2.37547893 * eV, 2.38003839 * eV,
      2.38461538 * eV, 2.38921002 * eV, 2.39382239 * eV, 2.39845261 * eV, 2.40310078 * eV,
      2.40776699 * eV, 2.41245136 * eV, 2.41715400 * eV, 2.42187500 * eV, 2.42661448 * eV,
      2.43137255 * eV, 2.43614931 * eV, 2.44094488 * eV, 2.44575937 * eV, 2.45059289 * eV,
      2.45544554 * eV, 2.46031746 * eV, 2.46520875 * eV, 2.47011952 * eV, 2.47504990 * eV,
      2.48000000 * eV, 2.48496994 * eV, 2.48995984 * eV, 2.49496982 * eV, 2.50000000 * eV,
      2.50505051 * eV, 2.51012146 * eV, 2.51521298 * eV, 2.5203252 * eV, 2.52545825 * eV,
      2.53061224 * eV, 2.53578732 * eV, 2.54098361 * eV, 2.54620123 * eV, 2.55144033 * eV,
      2.55670103 * eV, 2.56198347 * eV, 2.56728778 * eV, 2.57261411 * eV, 2.57796258 * eV,
      2.58333333 * eV, 2.58872651 * eV, 2.59414226 * eV, 2.59958071 * eV, 2.60504202 * eV,
      2.61052632 * eV, 2.61603376 * eV, 2.62156448 * eV, 2.62711864 * eV, 2.63269639 * eV,
      2.63829787 * eV, 2.64392324 * eV, 2.64957265 * eV, 2.65524625 * eV, 2.66094421 * eV,
      2.66666667 * eV, 2.67241379 * eV, 2.67818575 * eV, 2.68398268 * eV, 2.68980477 * eV,
      2.69565217 * eV, 2.70152505 * eV, 2.70742358 * eV, 2.71334792 * eV, 2.71929825 * eV,
      2.72527473 * eV, 2.73127753 * eV, 2.73730684 * eV, 2.74336283 * eV, 2.74944568 * eV,
      2.75555556 * eV, 2.76169265 * eV, 2.76785714 * eV, 2.77404922 * eV, 2.78026906 * eV,
      2.78651685 * eV, 2.79279279 * eV, 2.79909707 * eV, 2.80542986 * eV, 2.81179138 * eV,
      2.81818182 * eV, 2.82460137 * eV, 2.83105023 * eV, 2.8375286 * eV, 2.8440367 * eV,
      2.85057471 * eV, 2.85714286 * eV, 2.86374134 * eV, 2.87037037 * eV, 2.87703016 * eV,
      2.88372093 * eV, 2.89044289 * eV, 2.89719626 * eV, 2.90398126 * eV, 2.91079812 * eV,
      2.91764706 * eV, 2.9245283 * eV, 2.93144208 * eV, 2.93838863 * eV, 2.94536817 * eV,
      2.95238095 * eV, 2.95942721 * eV, 2.96650718 * eV, 2.9736211 * eV, 2.98076923 * eV,
      2.98795181 * eV, 2.99516908 * eV, 3.00242131 * eV, 3.00970874 * eV, 3.01703163 * eV,
      3.02439024 * eV, 3.03178484 * eV, 3.03921569 * eV, 3.04668305 * eV, 3.05418719 * eV,
      3.0617284 * eV, 3.06930693 * eV, 3.07692308 * eV, 3.08457711 * eV, 3.09226933 * eV,
      3.1 * eV, 3.10776942 * eV, 3.11557789 * eV, 3.12342569 * eV, 3.13131313 * eV,
      3.13924051 * eV, 3.14720812 * eV, 3.15521628 * eV, 3.16326531 * eV, 3.1713555 * eV,
      3.17948718 * eV, 3.18766067 * eV, 3.19587629 * eV, 3.20413437 * eV, 3.21243523 * eV,
      3.22077922 * eV, 3.22916667 * eV, 3.23759791 * eV, 3.2460733 * eV, 3.25459318 * eV,
      3.26315789 * eV, 3.27176781 * eV, 3.28042328 * eV, 3.28912467 * eV, 3.29787234 * eV,
      3.30666667 * eV, 3.31550802 * eV, 3.32439678 * eV, 3.33333333 * eV, 3.34231806 * eV,
      3.35135135 * eV, 3.3604336 * eV, 3.36956522 * eV, 3.37874659 * eV, 3.38797814 * eV,
      3.39726027 * eV, 3.40659341 * eV, 3.41597796 * eV, 3.42541436 * eV, 3.43490305 * eV,
      3.44444444 * eV, 3.454039 * eV, 3.46368715 * eV, 3.47338936 * eV, 3.48314607 * eV,
      3.49295775 * eV, 3.50282486 * eV, 3.51274788 * eV, 3.52272727 * eV, 3.53276353 * eV,
      3.54285714 * eV, 3.5530086 * eV, 3.56321839 * eV, 3.57348703 * eV, 3.58381503 * eV,
      3.5942029 * eV, 3.60465116 * eV, 3.61516035 * eV, 3.62573099 * eV, 3.63636364 * eV,
      3.64705882 * eV, 3.65781711 * eV, 3.66863905 * eV, 3.67952522 * eV, 3.69047619 * eV,
      3.70149254 * eV, 3.71257485 * eV, 3.72372372 * eV, 3.73493976 * eV, 3.74622356 * eV,
      3.75757576 * eV, 3.76899696 * eV, 3.7804878 * eV, 3.79204893 * eV, 3.80368098 * eV,
      3.81538462 * eV, 3.82716049 * eV, 3.83900929 * eV, 3.85093168 * eV, 3.86292835 * eV,
      3.875 * eV, 3.88714734 * eV, 3.89937107 * eV, 3.91167192 * eV, 3.92405063 * eV,
      3.93650794 * eV, 3.94904459 * eV, 3.96166134 * eV, 3.97435897 * eV, 3.98713826 * eV,
      4. * eV, 4.01294498 * eV, 4.02597403 * eV, 4.03908795 * eV, 4.05228758 * eV,
      4.06557377 * eV, 4.07894737 * eV, 4.09240924 * eV, 4.10596026 * eV, 4.11960133 * eV,
      4.13333333 * eV};

  std::vector<G4double> CsPbBr3_abs = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                       0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                       0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                       0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                       0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                       0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                       0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                       0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                       0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 138.30091,
                                       499.38569, 942.01535, 1537.0929, 2312.28299, 3326.73876, 4656.5945, 6369.54032,
                                       8554.06503, 11244.05073, 14519.4515, 18349.93082, 22582.64163, 27137.92154,
                                       31646.91248, 35800.37729, 39340.75337, 41882.34511, 43326.81496, 43632.15005,
                                       42898.10913, 41386.39375, 39350.90128, 37052.80967, 34744.52027, 32618.51935,
                                       30817.92496, 29443.94199, 28522.02749, 28078.78546, 28077.31439, 28539.35624,
                                       29406.89088, 30636.68368, 32200.93385, 33995.66888, 35944.54252, 37959.73916,
                                       39912.77669, 41680.13479, 43159.71094, 44311.11296, 45040.61599, 45347.94576,
                                       45265.41602, 44815.79103, 44148.62164, 43297.86722, 42406.37153, 41483.48463,
                                       40633.30368, 39939.75469, 39383.43944, 39023.12608, 38841.33626, 38800.8942,
                                       38942.69076, 39267.94768, 39743.3788, 40395.16425, 41172.71404, 42053.58808,
                                       43006.29539, 44029.31505, 45030.69248, 46001.57628, 46916.50941, 47699.1955,
                                       48393.46756, 48959.68139, 49363.40389, 49672.00526, 49846.71398, 49916.42792,
                                       49956.12198, 49968.66351, 50004.86689, 50094.17852, 50227.57251, 50432.30111,
                                       50719.88358, 51068.57795, 51527.35352, 52064.42014, 52695.90976, 53367.79157,
                                       54098.94021, 54833.70419, 55573.23047, 56357.9611, 57054.22783, 57773.18401,
                                       58444.06848, 59062.19377, 59722.45659, 60345.7431, 60983.64061, 61657.1431,
                                       62356.70105, 63068.22705, 63825.28155, 64662.2727, 65479.56643, 66371.56078,
                                       67280.18575, 68220.22687, 69195.0751, 70146.98454, 71116.69648, 72050.87824,
                                       72990.42069, 73887.80067, 74747.53113, 75595.54287, 76380.84697, 77171.36216,
                                       77976.53823, 78745.85998, 79536.59958, 80342.17457, 81173.20663, 82000.0,
                                       82867.53463, 83744.86812, 84651.22414, 85638.73856, 86615.85573, 87677.84638,
                                       88742.15584, 89827.70861, 90950.68649, 92083.68762, 93247.10757, 94424.61491,
                                       95656.30266, 96892.30389, 98134.93743, 99467.68047, 100827.00257, 102240.3804,
                                       103731.02701, 105224.5659, 106869.72513, 108565.84834, 110378.16146, 112314.61824,
                                       114309.19491, 116496.25785, 118794.54894, 121287.59524, 123959.36455, 126682.59651,
                                       129717.94546, 133006.31911, 136446.4627, 139827.0652, 143104.3684, 146131.73865,
                                       148826.82074, 151295.88105, 153275.17352, 154964.83896, 156382.08148, 157615.93844,
                                       158749.61277, 159864.13821, 160920.39417, 162030.15732, 163208.23814, 164397.71354,
                                       165720.78240, 167006.80014, 168396.34159, 169835.50062, 171326.9451, 172874.86385,
                                       174441.73204, 176034.00741, 177723.57312, 179361.97539, 181049.79576, 182595.71984,
                                       184320.11759, 186151.35519, 187981.94453, 189749.67663, 191610.83438, 193442.14678,
                                       195248.70027, 197166.58163, 199119.84356, 201012.8912, 202906.53725, 204862.89093,
                                       206751.62508, 208706.60743, 210785.70851, 212930.70871, 215205.73688, 217600.1215,
                                       220180.60943, 222909.55116, 225804.52475, 229009.54586, 232364.64144, 235899.08336,
                                       239803.33829, 243896.9628, 248180.10651, 252672.89071, 257425.45657, 262336.59921,
                                       267549.43666, 273083.66634, 278678.48431, 284588.95983, 290553.29161, 296630.07327,
                                       302864.93304, 309173.59584, 315589.97116, 322013.82651};

  std::transform(CsPbBr3_abs.begin(), CsPbBr3_abs.end(), CsPbBr3_abs.begin(), 
                 [](G4double value) -> G4double{return 1./value * cm;});

  CsPbBr3_mpt = new G4MaterialPropertiesTable();
  CsPbBr3_mpt->AddProperty("SCINTILLATIONCOMPONENT1", CsPbBr3_em_en, CsPbBr3_em);
  CsPbBr3_mpt->AddProperty("RINDEX", CsPbBr3_em_en, std::vector<G4double>(CsPbBr3_em_en.size(), 1.8));
  // CsPbBr3_mpt->AddProperty("ABSLENGTH", CsPbBr3_abs_en, CsPbBr3_abs);
  CsPbBr3_mpt->AddConstProperty("SCINTILLATIONYIELD", 20000. / MeV);
  CsPbBr3_mpt->AddConstProperty("RESOLUTIONSCALE", 1.0);
  CsPbBr3_mpt->AddConstProperty("SCINTILLATIONTIMECONSTANT1", 20. * ns);
  CsPbBr3_mpt->AddConstProperty("SCINTILLATIONYIELD1", 1.0); 

// Re-emition section
  CsPbBr3_mpt->AddProperty("WLSABSLENGTH", CsPbBr3_abs_en, CsPbBr3_abs);
  CsPbBr3_mpt->AddProperty("WLSCOMPONENT", CsPbBr3_em_en, CsPbBr3_em);
  CsPbBr3_mpt->AddConstProperty("WLSMEANNUMBERPHOTONS", 0.9);
  CsPbBr3_mpt->AddConstProperty("WLSTIMECONSTANT", 0.5 * ns);

  CsPbBr3_mat->SetMaterialPropertiesTable(CsPbBr3_mpt);
}

void DetectorConstruction::SetDefaults()
{
  fNC_dx = 100 * um;
  fNC_dy = fNC_dx * 10.;
  fNC_dz = 100 * um;
  fInner_spacing = 100 * um;
  fCapSize = 1 * mm;
}

G4VPhysicalVolume *DetectorConstruction::Construct()
{

  // Cleanup old geometry
  G4GeometryManager::GetInstance()->OpenGeometry();
  G4PhysicalVolumeStore::GetInstance()->Clean();
  G4LogicalVolumeStore::GetInstance()->Clean();
  G4SolidStore::GetInstance()->Clean();

  // Get nist material manager
  G4NistManager *nist = G4NistManager::Instance();

  // Option to switch on/off checking of volumes overlaps
  G4bool checkOverlaps = false;

  //
  // World
  //
  G4double world_sizeXY = 20. * cm; // 1.2*env_sizeXY;
  G4double world_sizeZ = 20. * cm;  // 1.2*env_sizeZ;
  world_mat = nist->FindOrBuildMaterial("G4_AIR");

  G4Box *solidWorld =
      new G4Box("World",                                                    // its name
                0.5 * world_sizeXY, 0.5 * world_sizeXY, 0.5 * world_sizeZ); // its size

  G4LogicalVolume *logicWorld =
      new G4LogicalVolume(solidWorld, // its solid
                          world_mat,  // its material
                          "World");   // its name

  G4VPhysicalVolume *physWorld =
      new G4PVPlacement(0,               // no rotation
                        G4ThreeVector(), // at (0,0,0)
                        logicWorld,      // its logical volume
                        "World",         // its name
                        0,               // its mother  volume
                        false,           // no boolean operation
                        0,               // copy number
                        checkOverlaps);  // overlaps checking


  G4double wafer_dy = 5 * mm;

  //
  // Silicon wafer
  //
  wafer_mat = nist->FindOrBuildMaterial("G4_Si");
  G4ThreeVector pos_wafer = G4ThreeVector(0, 0, 0);

  G4Box *solidWafer =
      new G4Box("Wafer",                                         // its name
                0.5 * wafer_dx, 0.5 * wafer_dy, 0.5 * wafer_dz); // its size

  G4LogicalVolume *logicWafer =
      new G4LogicalVolume(solidWafer, // its solid
                          wafer_mat,  // its material
                          "Wafer");   // its name

  physWafer = new G4PVPlacement(0,              // no rotation
                                pos_wafer,      // at position
                                logicWafer,     // its logical volume
                                "Wafer",        // its name
                                logicWorld,     // its mother  volume
                                false,          // no boolean operation
                                0,              // copy number
                                checkOverlaps); // overlaps checking

  // Set Shape2 as scoring volume
  //
  fScoringVolume = logicWafer;

  //
  // NC
  //
  NC_mat = CsPbBr3_mat;

  G4ThreeVector pos1 = G4ThreeVector(0, (wafer_dy - fNC_dy) / 2., 0);

  solidNC =
      new G4Box("NC", 0.5 * fNC_dx, 0.5 * fNC_dy, 0.5 * fNC_dz); // its size

  logicNC =
      new G4LogicalVolume(solidNC, // its solid
                          NC_mat,  // its material
                          "NC");   // its name
  G4int N = std::floor(wafer_dx / (fNC_dx + fInner_spacing));

  N = N - N % 2 - 1;
  G4double outer_spacing = (wafer_dx - N * (fNC_dx + fInner_spacing) + fInner_spacing) / 2.;

  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < N; j++)
    {
      // physNC = new G4PVPlacement(0, // no rotation
      //                            G4ThreeVector(-0.5 * wafer_dx + outer_spacing + 0.5 * fNC_dx + (fInner_spacing + fNC_dx) * i,
      //                                          (wafer_dy - fNC_dy) / 2.,
      //                                          -0.5 * wafer_dz + outer_spacing + 0.5 * fNC_dz + (fInner_spacing + fNC_dz) * j), // at position
      //                            logicNC,                                                                                       // its logical volume
      //                            "NC",                                                                                          // its name
      //                            logicWafer,                                                                                    // its mother  volume
      //                            false,                                                                                         // no boolean operation
      //                            i + j,                                                                                         // copy number
      //                            checkOverlaps);                                                                                // overlaps checking
    }
  }

  G4double cap_thickness = fCapSize;

  capNC =
      new G4Box("capNC",                                              // its name
                0.5 * wafer_dx, 0.5 * cap_thickness, 0.5 * wafer_dz); // its size

  logicCapNC =
      new G4LogicalVolume(capNC,    // its solid
                          NC_mat,   // its material
                          "capNC"); // its name

  physNC = new G4PVPlacement(0, // no rotation
                             G4ThreeVector(0,
                                           (wafer_dy + cap_thickness) / 2.,
                                           0), // at position
                             logicCapNC,       // its logical volume
                             "capNC",          // its name
                             logicWorld,       // its mother  volume
                             false,            // no boolean operation
                             0,                // copy number
                             checkOverlaps);   // overlaps checking

  //
  // always return the physical World
  //
  return physWorld;
}

void DetectorConstruction::SetPitch(G4double NC_dx)
{
  fNC_dx = NC_dx;
  fNC_dz = NC_dx;
  G4RunManager::GetRunManager()->ReinitializeGeometry();
}

void DetectorConstruction::SetSpacing(G4double spacing)
{
  fInner_spacing = spacing;
  G4RunManager::GetRunManager()->ReinitializeGeometry();
}

void DetectorConstruction::SetCapSize(G4double size)
{
  fCapSize = size;
  G4RunManager::GetRunManager()->ReinitializeGeometry();
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
