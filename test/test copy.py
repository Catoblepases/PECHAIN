from matplotlib import pyplot as plt
import numpy as np
import pandas as pd
from numpy import polyfit, poly1d

data = pd.read_csv("q1_5.csv")


# data = data.loc[data["time1(ms)"] > 0.0005]
# data = data.loc[data["time1(ms)"] < 0.002]
# data = data.loc[data["time2(ms)"] < 2]
# data = data.loc[data["time2(ms)"] > 0.5]

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

# plt.subplot(3, 1, 3)
# plt.title("Comparez les performances des deux m´ethodes")
# plt.scatter(m, time2, s=3, label="mod_pow_naive")
# plt.scatter(m, time1, s=3, label="mod_pow")
# plt.xlabel("m")
# plt.ylabel("time(ms)")
# plt.legend(loc="upper right")

# d = time2/time1
# coeff = polyfit(m, d, 1)
# plt.subplot(4, 1, 4)
# plt.title("Comparez les performances des deux methodes")
# plt.scatter(m, time2/time1, s=3, label="time(modPowNaive)/time(mosPow)")
# plt.plot(m, coeff[0] * m + coeff[1], 'k-',
#          label="fit: {:.2f}*m+{:.2f}".format(coeff[0], coeff[1]))
# plt.xlabel("m")
# plt.ylabel("time(ms)")
# plt.legend(loc="upper right")
plt.savefig("q1_5.png")
plt.show()
