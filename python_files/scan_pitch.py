import os
import sys
from time import sleep

executable_folder = "/home/vorlov/work/build_nano_crys/"

for energy in [10, 30 ,60, 80, 100]:
  for pitch in [1,2,5,10,15,20,30,40,50]:
    run_file = executable_folder + f"run_{energy}keV_pitch_{pitch}um_.mac"
    with open(run_file,"w") as f:
      file_content = f"""/run/initialize
/analysis/setFileName {executable_folder}scan_pitch/scan_{energy}_keV_{pitch}_um_.root
/gun/particle gamma
/gun/energy {energy} keV
#
#/detector/setCapSize 0. um
/detector/setPitch {pitch}. um
/detector/setSpacing {pitch}. um
/run/beamOn 100000
"""
      f.write(file_content)
      print(file_content)
      os.system(executable_folder + f"exampleB1 {run_file} &")
      # sleep(60)
      # os.system(f"mv nc_photons.root scan_{energy}_keV_{thickness}_um.root")