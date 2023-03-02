import matplotlib.pyplot as plt
import numpy as np

number_of_events = 100000

nphot_10_kev = np.array([5171712.0, 4919544.0, 4809061.0, 4706052.0, 4618759.0, 4477006.0, 4466023.0, 4122746.0, 4423223.0])
nphot_30_kev = np.array([11598779.0, 12752304.0, 14182120.0, 14399635.0, 14362288.0, 13999357.0, 14091649.0, 13085017.0, 14032113.0])
nphot_60_kev = np.array([13979285.0, 14204623.0, 15855249.0, 18039649.0, 19500993.0, 19752467.0, 20974640.0, 19928461.0, 21695860.0])
nphot_80_kev = np.array([11093771.0,11160674.0,11780025.0,13075715.0,14592001.0,15222594.0,17056313.0,16704710.0,18444453.0])
nphot_100_kev = np.array([11249313.0,11696089.0,12359021.0,12871313.0,13602501.0,13979929.0,15502105.0,15352125.0,16890650.0])

pitch_size = [1,2,5,10,15,20,30,40,50]

plt.plot(pitch_size, nphot_100_kev/number_of_events, "o", label = "100 keV")
plt.plot(pitch_size, nphot_80_kev/number_of_events, "o", label = "80 keV")
plt.plot(pitch_size, nphot_60_kev/number_of_events, "o", label = "60 keV")
plt.plot(pitch_size, nphot_30_kev/number_of_events, "o", label = "30 keV")
plt.plot(pitch_size, nphot_10_kev/number_of_events, "o", label = "10 keV")


plt.xlabel("Pitch size, um")
plt.ylabel("Number of detected photons per event")

plt.legend()
plt.show()