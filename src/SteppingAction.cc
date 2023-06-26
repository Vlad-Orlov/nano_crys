/// \file SteppingAction.cc
/// \brief Implementation of the SteppingAction class

#include "SteppingAction.hh"
#include "EventAction.hh"
#include "DetectorConstruction.hh"
#include "G4RandomDirection.hh"
#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include "G4OpticalPhoton.hh"
#include "G4Gamma.hh"
#include <random>
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double sample_from_distribution(G4double energy) {
    // create a uniform distribution between 0 and 1
    // G4cout << "Start of ChatGPT function" << G4endl;
    std::vector<G4double> bins = {1.77142857 * eV, 1.77396280 * eV, 1.77650430 * eV, 1.77905308 * eV, 1.7816092 * eV,
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

  std::vector<G4double> values = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
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
    std::uniform_real_distribution<double> uniform_distribution(0.0, 1.0);
    
    // normalize the values to obtain a probability distribution
    double total = 0.0;
    for (double v : values) {
        total += v;
    }
    for (int i = 0; i < values.size(); ++i) {
        values[i] /= total;
    }
    
    // select a random value according to the probability distribution
        // seed the random number generator with the current time
    // std::srand(std::time(nullptr));
    
    // generate a random integer between 0 and RAND_MAX
    int rand_int = std::rand();
    
    // scale the integer to a value between 0 and 1
    // double r = static_cast<double>(rand_int) / RAND_MAX;
    G4double r = double(rand())/RAND_MAX;
    // G4cout << "Random " << r << G4endl;

    double cumulative_prob = 0.0;
    for (int i = 0; i < bins.size(); ++i) {
        cumulative_prob += values[i];
        if (r < cumulative_prob) {
          // G4cout << "Cumulative prob " << cumulative_prob << G4endl;
            return bins[i];
        }
    }
    
    // if for some reason no bin was selected, return the first one
    return bins.front();
}

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

  // if (isPhoton){
  //   G4cout << step->GetTrack()->GetCreatorProcess()->GetProcessName() << "\t";
  //   G4cout << step->GetTrack()->GetCurrentStepNumber() << "\t";
  //   G4cout << step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName() << "\n";
  // }

  // const std::vector<const G4Track*>* secondaries =
  //                           step->GetSecondaryInCurrentStep();

  // step->GetTrack()->SetKineticEnergy(2*eV);
  G4bool isFirstSecondary = true;

  // if (isPhoton){
  //   for (auto sec : *secondaries) {
  //     G4bool isSecPhoton = sec->GetDynamicParticle()->GetParticleDefinition() == G4OpticalPhoton::OpticalPhoton();

  //     if(isFirstSecondary) {
  //       photonEnergy = sec->GetKineticEnergy();
  //       step->GetTrack()->SetTrackStatus(fKillTrackAndSecondaries);  
  //       G4cout << "Killed photons and its secondaries!!!";
  //       // step->GetTrack()->SetTrackStatus(fAlive);
  //       step->GetTrack()->SetKineticEnergy(photonEnergy);
  //     }
  //     if (isSecPhoton){
  //       G4String creator_process = sec->GetCreatorProcess()->GetProcessName();
  //       G4cout << "CP: " << creator_process << G4endl;
  //       G4cout << "isFirstSecondary: " << isFirstSecondary << G4endl;
  //       isFirstSecondary = false;
  //     }
  //   }
  // }

  // G4cout << "entering energy hack"<< G4endl;

  if (isPhoton && step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName() == "OpAbsorption"){
    G4double pl_qy = 0.9;
    G4double random_value = double(rand())/RAND_MAX;
    // G4cout << "death value " << random_value << G4endl;
    if (random_value < (1 - pl_qy)) {
      step->GetTrack()->SetTrackStatus(fStopAndKill);
      // G4cout << "This photon is killed" << G4endl;
    } 
    else {
      // G4cout << "This photon survived" << G4endl;
      G4double old_energy = step->GetTrack()->GetKineticEnergy();
      step->GetTrack()->SetTrackStatus(fAlive);
      G4double new_energy = old_energy;
      while (new_energy >= old_energy){
        new_energy = sample_from_distribution(old_energy);
      }
      // G4cout << "Changing photon energy from " << old_energy << " to " << new_energy << G4endl;
      step->GetTrack()->SetKineticEnergy(new_energy);
      // G4cout << step->GetTrack()->GetKineticEnergy() << G4endl;

      step->GetTrack()->SetMomentumDirection(G4RandomDirection());
    }
  }

  // G4cout << "Current energy of the step is: " << step->GetTrack()->GetKineticEnergy() << G4endl;
   if (isPhoton && step->GetTrack()->GetCurrentStepNumber() == 1){
    fEventAction->AddGeneratedPhoton();
  }
 
  // if (isPhoton){
  //   G4cout << step->GetTrack()->GetTrackID() << "\t" 
  //          << prevolume->GetName() << "\t" << postvolume->GetName() << "\t"
  //          << step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName() << "\n";
  // }

  G4bool isGamma = step->GetTrack()->GetDynamicParticle()->GetParticleDefinition()
                    == G4Gamma::GammaDefinition();
  if (isPhoton && 
     ((prevolume->GetName() == "NC") || (prevolume->GetName() == "capNC")) && 
     (postvolume->GetName() == "Wafer") ){
    // G4cout << "Detection!!!" << G4endl; 
    // G4cout << "Copy number is: " << prevolume->GetCopyNo() << G4endl;
    man->FillH1(2, step->GetTrack()->GetKineticEnergy());
    man->FillNtupleDColumn(0,0, step->GetTrack()->GetKineticEnergy());
    man->FillNtupleDColumn(0,2, step->GetPostStepPoint()->GetPosition().getX());
    man->FillNtupleDColumn(0,3, step->GetPostStepPoint()->GetPosition().getY());
    man->FillNtupleDColumn(0,4, step->GetPostStepPoint()->GetPosition().getZ());
    man->FillNtupleIColumn(0,5, prevolume->GetCopyNo());
    man->FillNtupleIColumn(0,6, step->GetTrack()->GetDynamicParticle()->
                                      GetParticleDefinition()->GetPDGEncoding());
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
