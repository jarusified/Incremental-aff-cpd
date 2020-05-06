import math

import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

from aff_cpp import AFF

"""
    Generate a random time series with "n" change points. 
    
    n -> Required number of change points.
    minl -> minimum limit along y
    maxl -> maximum limit along y
  
"""
def generate_random_time_series(n, minl, maxl):
    data = np.array([], dtype=np.float64)
    partition = np.random.randint(minl, maxl, n)
    for p in partition:
        mean = np.random.randn()*1
        var = np.random.randn()*1
        # if less than 0, change the direction. 
        if var < 0:
            var = var * -0.2
        temp_data = np.random.normal(mean, var, p)
        data = np.concatenate((data, temp_data))
    return data

"""
   Load the rt-bin sample data with high rollback ratio from KP = 4.
"""
def read_rt_bin_data(file_name):
    data = pd.read_csv(file_name)
    return data['RbSec']

"""
   Load a random data generated using seed(5)
   data = rnorm(400, 0, 1) + rep(c(0:3), each=100)
"""            
def read_rnorm_data(file_name):
    data = []
    with open(file_name) as f:
        contents = f.read()
        arr = contents.split("\n")
        for idx, line in enumerate(arr):
            split_line = line.split(",")
            if len(split_line) == 2:
                data.append(float(split_line[1]))
    return data

# Sample case 1: Random Data. 
data = generate_random_time_series(5, 10, 100)

alpha = 0.05
eta = 0.01
bl = 5  # burn-in length
aff = AFF(alpha, eta, bl)

#init_data = data[0:5]
#stream_data = data[6:]
cp = aff.insert(data)[1]

xdata = []
ydata = []

#plt.ion()
fig = plt.figure()
fig, ax = plt.subplots(figsize=[18, 16])
ax = fig.add_subplot(3,1,1)
ax.plot(data)

# for idx, val in enumerate(stream_data):
#     xdata.append(idx)
#     ydata.append(val)
#     line.set_xdata(xdata)
#     line.set_ydata(ydata)
#     plt.draw()
#     plt.pause(1e-17)
#     time.sleep(0.1)
    
ax.set_ylabel('random time series')

parameters = aff.params()

for idx, val in enumerate(cp):
    if val != 0:
        plt.axvline(val, color='r')


# Sample case 2: Rt-bin Data for Kp = 4  
data = pd.read_csv('./rt-bin-time.csv')
data_rbsec = data['RbSec']
# convert to numpy array
data = data_rbsec.values

alpha = 0.01
eta = 0.01
bl = 5  # burn-in length
aff = AFF(alpha, eta, bl)

ax = fig.add_subplot(3,1,2)
ax.plot(data)
ax.set_ylabel('rt-bin_kp-4')


change_points = aff.insert(data)[1]
parameters = aff.params()

for idx, val in enumerate(change_points):
    if val != 0:
        plt.axvline(val, color='r')


data = read_rnorm_data("rnorm.csv")
alpha = 0.01
eta = 0.01
bl = 5  # burn-in length
aff = AFF(alpha, eta, bl)

ax = fig.add_subplot(3,1,3)
ax.plot(data)
ax.set_ylabel('rnorm data')


change_points = aff.insert(data)[1]
parameters = aff.params()

for idx, val in enumerate(change_points):
    if val != 0:
        plt.axvline(val, color='r')

plt.show()
