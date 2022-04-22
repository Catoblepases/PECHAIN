from matplotlib import pyplot as plt
import numpy as np
import pandas as pd
from numpy import polyfit, poly1d

data = pd.read_csv("./test/profOfWork.csv")

print(data)

time = data["time"]
d = data["d"]

plt.figure(figsize=(16, 14), dpi=100)

plt.subplot(3, 1, 1)
plt.title(
    "temps moyen en fonction de d")
plt.xlabel("d")
plt.ylabel("time(s)")
plt.scatter(d, time)
plt.legend(loc="upper right")
plt.show()