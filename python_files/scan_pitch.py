import os
import sys
from time import sleep

executable_folder = "/home/orlov/work/nano_crys/build_nano_crys/"

for energy in [10,30,60,90,120]:
  for pitch in [1,2,5,10,20,50,75,100,150,300]:
    root_file = f"{executable_folder}scan_pitch/pitch_scan_reemit_{energy}_keV_{pitch}_um_.root"
    log_file  = f"{executable_folder}scan_pitch/pitch_scan_reemit_{energy}_keV_{pitch}_um_.txt"
    run_file  = f"{executable_folder}run_{energy}keV_thickness_{pitch}um_.mac"

    with open(run_file,"w") as f:
      file_content = f"""/run/numberOfThreads 2
/run/initialize
/analysis/setFileName {root_file}
/gun/particle gamma
/gun/energy {energy} keV
#
/detector/setPitch {pitch}. um
/detector/setSpacing {pitch}. um
/run/beamOn 100000
"""
      f.write(file_content)
      # print(file_content)
      os.system(executable_folder + f"exampleB1 {run_file} > {log_file} &")