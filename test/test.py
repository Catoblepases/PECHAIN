from matplotlib import pyplot as plt
import numpy as np
import pandas as pd

data = pd.read_csv("q1_5.csv")
time1 = data["time1(ms)"]
time2 = data["time2(ms)"]
m = data["m"]

plt.figure(figsize=(16, 8), dpi=500)

plt.subplot(3, 1, 1)
plt.scatter(m, time2, label="mod_pow_naive", s=3)
plt.legend("upper right")

plt.subplot(3, 1, 2)
plt.scatter(m, time1, label="mod_pow", s=3)

plt.subplot(3, 1, 3)
plt.scatter(m, time1, label="mod_pow", s=3)
plt.scatter(m, time2, label="mod_pow_naive", s=3)
plt.legend("upper right")
# plt.show()
plt.savefig("q1_5.png")
