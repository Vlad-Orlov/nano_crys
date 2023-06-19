import ROOT
from ROOT import TFile

scan_folder = "/home/orlov/work/nano_crys/build_nano_crys/scan_thickness/"
for energy in [60]:
  for thickness in [0.1, 0.25, 0.5, 0.75, 1., 1.5, 2, 2.5]:
    file = TFile(scan_folder + f"scan_no_reemit_wls_abs_{energy}_keV_{thickness}_mm_.root")
    hist = file.Get("3")
    hist.GetXaxis().SetRange(2,500)
    c = ROOT.TCanvas("c")
    hist.Draw()
    c.SaveAs(f"run_no_reemit_wls_abs_{energy}keV_thickness_{thickness}mm.pdf")
