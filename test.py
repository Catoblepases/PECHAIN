import pandas as pd
from matplotlib import pyplot as plt
import numpy as np

data = pd.read_csv("q1.5.csv")
m = data["m"]
algo1 = data["time1(ms)"]
algo2 = data["time2(ms)"]

plt.subplot(3, 1, 1)
plt.plot(m, algo2, label="naive")
plt.xlabel("m")
plt.ylabel("time(ms)")
plt.legend("upper right")
plt.subplot(3, 1, 2)
plt.plot(m, algo1, label="Exponentiation")
plt.xlabel("m")
plt.ylabel("time(ms)")
plt.legend("upper right")
plt.subplot(3, 1, 3)
plt.plot(m, algo1, label="Exponentiation")
plt.plot(m, algo2, label="naive")
plt.xlabel("m")
plt.ylabel("time(ms)")
plt.legend("upper right")
plt.show()
