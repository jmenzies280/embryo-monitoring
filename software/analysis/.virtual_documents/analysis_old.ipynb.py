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
fileName = "test22021-12-06T18_13_52.csv"




#load data into "data" variable
data = pd.read_csv(filePath+fileName)
#grab every other column so that we are only using the average brightness in each ROI (discarding rolling average calculated with Bonsai)
data=data[data.columns[::2]]
#display data
data


#calculate rolling average for each ROI and subtract that from brightness value

rolling = data.rolling(window=60).mean()
subtracted = data-rolling

#make all values positive by squaring all values than getting the square root
module = np.sqrt(subtracted**2)


plt.hist(module[module.columns[0]],bins=50)


#show the names of each column
# from this we learn that the data is organised pairwise, that is every two columns come from a specific ROI,
# with the first column being the average brightness of a ROI and the second the running average of the same ROI
#print(data.columns)
data.info()


roll = 60
maxlen=10000
fig = plt.figure(figsize=[25,20])
sub1=plt.subplot(2,1,1)
plt.plot(data["Item1.Item1.Item1.brightAverage"][0:maxlen])
plt.plot(data["Item1.Item1.Item1.brightAverage"].rolling(roll, min_periods=1).mean()[0:maxlen])
sub2=plt.subplot(2,1,2)
plt.plot(data["Item1.Item1.Item1.brightAverage"][0:maxlen]-data["Item1.Item1.Item1.brightAverage"].rolling(roll, min_periods=1).mean()[0:maxlen])



b, a = signal.butter(2, 0.5, 'low', analog=True)
w, h = signal.freqs(b, a)

filtered = signal.filtfilt(b,a, data["Item1.Item1.Item1.brightAverage"])


plt.semilogx(w, 20 * np.log10(abs(h)))
plt.title('Butterworth filter frequency response')
plt.xlabel('Frequency [radians / second]')
plt.ylabel('Amplitude [dB]')
plt.margins(0, 0.1)
plt.grid(which='both', axis='both')
plt.axvline(100, color='green') # cutoff frequency
plt.show()



maxlen=2000
fig = plt.figure(figsize=[25,20])
#sub1=plt.subplot(4,1,1)
#plt.plot(data["Item1.Item1.Item1.brightAverage"][40000:50000])
#plt.plot(filtered[40000:50000])
#sub2=plt.subplot(4,1,2)

sub3=plt.subplot(4,1,1)
plt.plot(data["Item1.Item1.Item1.brightAverage"][40000:50000])

sub4=plt.subplot(4,1,2)
plt.plot(filtered[40000:50000])


#create an empty dataframe to store new arrays that are the running average subtracted from the average brightness in each roi
detrended = pd.DataFrame(index =list(range(len(data))))
#run a loop to pairwise subtract the running average from the brightness average
j=0
for i in range(0,len(data.columns),2):
    temp = pd.DataFrame(data[data.columns[i]]-data[data.columns[i+1]],columns=["ROI"+str(j+1)])
    detrended = detrended.join(temp,)
    j=j+1

# do the square root of the square of each value to get only positive values    
detrended = np.sqrt(detrended**2)
detrended


fig = plt.figure(figsize=[25,20])
maxlen=1000
sub1=plt.subplot(2,1,1)
plt.plot(data["Item1.Item1.Item1.brightAverage"][70000:70400])
sub2=plt.subplot(2,1,2)
plt.plot(np.diff(data["Item1.Item1.Item1.brightAverage"][70000:70400]))


#plot one raw, one average and one detrended
fig = plt.figure(figsize=[25,20])
sub1 = plt.subplot(2,1,1)
plt.plot(data["Item1.Item1.Item1.brightAverage"][0:maxlen])
plt.plot(data["Item1.Item1.Item2.runningAverage"][0:maxlen])
sub2 = plt.subplot(2,1,2)
plt.plot(detrended.ROI1[0:maxlen])


#plt.plot(detrended.ROI1[0:3000])
fig = plt.figure(figsize=[20,10])
powerSpectrum, frequenciesFound, time, imageAxis = plt.specgram(detrended.ROI1, Fs=10)
plt.xlabel('Time')
plt.ylabel('Frequency')
fig.colorbar(imageAxis)






