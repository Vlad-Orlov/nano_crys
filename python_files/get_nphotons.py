import ROOT
from ROOT import TFile

scan_folder = "/home/vorlov/work/build_nano_crys/scan_pitch/"
for energy in [10, 30 ,60, 80, 100]:
  for pitch in [1,2,5,10,15,20,30,40,50]:
    file = TFile(scan_folder + f"scan_{energy}_keV_{pitch}_um_.root")
    hist = file.Get("6")
    hist.GetXaxis().SetRange(2,2500)
    s = 0
    for i in range(hist.GetNbinsX()):
      s += i * hist.GetBinContent(i)

    print(energy, pitch, s)