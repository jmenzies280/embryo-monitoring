#import necessary libraries

import pandas as pd
import os
import seaborn as sns
import matplotlib.pyplot as plt
import numpy as np
from scipy import signal
#get_ipython().run_line_magic("matplotlib", " widget")



#tell python where the data is located, based on the current folder
filePath = "..//..//data//"
# tell what is the file name we will open and load data
fileName = "output2022-01-20T11_12_09.csv"




#load data into "data" variable
data = pd.read_csv(filePath+fileName)
#display data
data


#show the names of each column
# from this we learn that the data is organised pairwise, that is every two columns come from a specific ROI,
# with the first column being the average brightness of a ROI and the second the running average of the same ROI
#print(data.columns)
data.info()



allBright=data
#calculate rolling average for each ROI and subtract that from brightness value
roll = 60
rolling = allBright.rolling(window=roll).mean()
subtracted = allBright-rolling

#make all values positive by squaring all values than getting the square root
module = np.sqrt(subtracted**2)


#plt.hist(module[module.columns[0]],bins=50)





start = 90000
end = -1
fig = plt.figure(figsize=[25,20])
sub1=plt.subplot(3,1,1)
plt.plot(data["topLeft.Item1.avgBright"][start:end])
plt.plot(rolling["topLeft.Item1.avgBright"][start:end])
sub2=plt.subplot(3,1,2)
plt.plot(data["topLeft.Item1.width"][start:end])
plt.plot(rolling["topLeft.Item1.width"][start:end])
sub3=plt.subplot(3,1,3)
plt.plot(data["topLeft.Item1.height"][start:end])
plt.plot(rolling["topLeft.Item1.height"][start:end])


sns.pairplot(data.iloc[:,0:3])


#plt.plot(detrended.ROI1[0:3000])
fig = plt.figure(figsize=[20,10])
powerSpectrum, frequenciesFound, time, imageAxis = plt.specgram(data["topLeft.Item1.width"], Fs=100)
plt.xlabel('Time')
plt.ylabel('Frequency')
fig.colorbar(imageAxis)






