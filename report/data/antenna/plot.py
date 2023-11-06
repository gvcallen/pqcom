import matplotlib.pyplot as plt 
import numpy as np
import csv 
  
x = [] 
y = [] 

# fticks = [400.0, 420.0, 440.0, 460.0]
# fticks = [405.0, 410.0, 415.0, 420.0, 425.0, 430.0, 435.0]
# fticks = [400.0, 410.0, 415.0, 420.0, 425.0, 430.0, 435.0]
# yticks = [230.0, 419.0, 265.0]
  
with open('simulatedDipoleReturnLoss.csv','r') as csvfile:
    values = csv.reader(csvfile, delimiter = ',') 
      
    i = 0
    for i, row in enumerate(values): 
        if i == 0:
            continue

        freq = float(row[0]) / 1e6
        val = float(row[1])

        # if freq < fticks[0] or freq > fticks[-1]:
            # continue
        
        x.append(freq) 
        y.append(val) 

fs = 12
plt.figure(figsize=(6, 5))
plt.plot(x, y)
plt.xticks(fontsize=fs)
plt.yticks(fontsize=fs)
# plt.xticks(fticks)
plt.xlabel('Frequency (MHz)', fontsize=fs) 
plt.ylabel('Return Loss (dB)', fontsize=fs) 
# plt.ylabel('Impedance (ohm)', fontsize=fs) 
# plt.title('Helical Antenna Return Loss vs Frequency') 
plt.legend() 
plt.show() 