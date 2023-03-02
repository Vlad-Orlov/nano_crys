import os
import sys
from time import sleep

executable_folder = "/home/orlov/work/nano_crys/build_nano_crys/"

for energy in [60]:
  for thickness in [0.1, 0.25, 0.5, 0.75, 1., 1.5, 2, 2.5]:
    run_file = executable_folder + f"run_{energy}keV_thickness_{thickness}mm_.mac"
    with open(run_file,"w") as f:
      file_content = f"""/run/initialize
/analysis/setFileName {executable_folder}scan_thickness/scan_no_reemit_wls_abs_{energy}_keV_{thickness}_mm_.root
/gun/particle gamma
/gun/energy {energy} keV
#
/detector/setCapSize {thickness} mm
/run/beamOn 100000
"""
      f.write(file_content)
      print(file_content)
      os.system(executable_folder + f"exampleB1 {run_file} &")
      # sleep(60)
      # os.system(f"mv nc_photons.root scan_{energy}_keV_{thickness}_um.root")