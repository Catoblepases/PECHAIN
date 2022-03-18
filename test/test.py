from matplotlib import pyplot as plt
import numpy as np
import pandas as pd

data = pd.read_csv("q1_5.csv")
time1 = data["time1(ms)"]
time2 = data["time2(ms)"]
m = data["m"]

plt.subplot(2, 1, 1)
plt.plot(m, time1, label="mod_pow")
plt.plot(m, time2, label="mod_pow_naive")
plt.legend("upper right")

plt.subplot(2, 1, 2)
plt.plot(m, time1, label="mod_pow")

plt.show()
