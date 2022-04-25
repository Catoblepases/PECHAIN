from matplotlib import pyplot as plt
import numpy as np
import pandas as pd
from numpy import polyfit, poly1d

data = pd.read_csv("temp/proof_of_work.csv")

print(data)

d = data["d"]
time = data["time"]

plt.figure(figsize=(15, 5), dpi=100)


plt.title("temps moyen en fonction de d")
plt.plot(d, time,marker='o', mec='b', mfc='w')
plt.xlabel("d")
plt.ylabel("temp moyen(s)")
# plt.legend(loc="upper right")

plt.savefig("temp/q7_8.png")
plt.show()
