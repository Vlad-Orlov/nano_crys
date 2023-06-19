
# 10'000 events of 60 keV
# 20000 photons per MeV -> 20 photons per keV -> 1200 photons per event MAX
# Efficiency = # of detected photons / (10k * 1.2k)

cap = 37_434_382.0 / (10_000 * 20_000) * 100
col = 23_648_026. / (10_000 * 20_000) * 100 / 0.188
cap_col = 124_338. / (10_000 * 20_000) * 100

print("Efficiency for different configurations:")
print(f"cap: {cap:.2f} %")
print(f"col: {col:.2f} %")
print(f"cap + col: {cap_col:.2f} %")