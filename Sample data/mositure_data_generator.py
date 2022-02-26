import math
import pandas as pd
import numpy as np
import time
import re
import sys
import matplotlib.pyplot as plt
import random


# dy/dx = -x^2
watering_duration, moisture = 4, .1
watering = False
df = pd.DataFrame(data=[[0, moisture]], columns=['Time', 'Moisture'])
for time in range(1, 24):
    if time == 2: watering = True
    if watering: moisture += .1
    else: moisture -= .25 * moisture ** 2
    if time == 6: watering = False
    moisture += moisture * (random.random() - .5)/10
    tmp = pd.DataFrame([[time, moisture]], columns = ["Time", "Moisture"]) 
    df = df.append(tmp)
print(df)

print(df.shape)

plt.plot(df["Time"],df["Moisture"])
plt.xlabel("Time Elapsed(hours)")
plt.ylabel("Soil Mositure Level")
plt.title("Soil Mositure Over Time")
plt.gcf().autofmt_xdate()
plt.show()
