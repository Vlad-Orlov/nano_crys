import ROOT
from ROOT import TFile

hist_filename = "../../build_nano_crys/reemit_cap_col_10k_1mm_60keV.root" # existing file with histograms
hist_file = TFile(hist_filename, "READ") # open file in "read" mode

hist = hist_file.Get("3")
integral = 0
for bin in range(1, hist.GetNbinsX() + 1):
    bin_content = hist.GetBinContent(bin)
    integral += bin * bin_content
print(f"Integral of {hist_filename}: {integral}")

hist_file.Close() # close file when finished reading