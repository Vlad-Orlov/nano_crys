import os
import sys
from time import sleep

executable_folder = "/home/orlov/work/nano_crys/build_nano_crys/"

for energy in [10,30,60,90,120]:
  for thickness in [0.01,0.05,0.2,0.3,0.4,0.6,0.8,1.25,1.75]:

    root_file = f"{executable_folder}scan_cap_col/scan_cap_col_reemit_{energy}_keV_{thickness}_mm_.root"
    log_file  = f"{executable_folder}scan_cap_col/scan_cap_col_reemit_{energy}_keV_{thickness}_mm_.txt"
    run_file  = f"{executable_folder}run_{energy}keV_thickness_{thickness}mm_.mac"

    with open(run_file,"w") as f:
      file_content = f"""/run/numberOfThreads 2
/run/initialize
/analysis/setFileName {root_file}
/gun/particle gamma
/gun/energy {energy} keV
#
/detector/setPitch 60 um
/detector/setSpacing 60 um
/detector/setCapSize {thickness} mm
/run/beamOn 100000
"""
      f.write(file_content)
      # print(file_content)
      os.system(executable_folder + f"exampleB1 {run_file} > {log_file} &")