from matplotlib import pyplot as plt
import numpy as np
import pandas as pd
from numpy import polyfit, poly1d

data = pd.read_csv("temp/q1_5.csv")

print(data)

time1 = data["time1(ms)"]
time2 = data["time2(ms)"]
m = data["m"]

plt.figure(figsize=(15, 3), dpi=100)

plt.subplot(1, 2, 1)
plt.title(
    "exponentiation modulaire courbes de temps en fonction de m pour mod_pow_naive",fontsize=10)
plt.xlabel("m")
plt.ylabel("time(ms)")
plt.scatter(m, time2, s=3, label="mod_pow_naive")
plt.legend(loc="upper right")

plt.subplot(1, 2, 2)
plt.title(
    "exponentiation modulaire courbes de temps en fonction de m pour mod_pow",fontsize=10)
plt.xlabel("m")
plt.ylabel("time(ms)")
# coeff = polyfit(m, time1, 1)
plt.scatter(m, time1, s=3, label="mod_pow")
plt.legend(loc="upper right")

plt.savefig("temp/q1_5.png")
plt.show()
