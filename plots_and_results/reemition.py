import numpy as np
import matplotlib.pyplot as plt

mean_number_of_reemitted_photons = [0,1,2,3]
number_of_detected_photons = [21, 50, 126, 322]

plt.plot(mean_number_of_reemitted_photons, number_of_detected_photons, "ob-")
plt.xlabel("Mean number of re-emitted photons")
plt.ylabel("Mean number of registered photons in event")

plt.savefig("reemition.pdf")