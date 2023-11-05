import matplotlib.pyplot as plt 
import numpy as np
import csv 
  
x = [] 
y = [] 

fticks = [400.0, 433.0, 466.0, 500.0]
  
with open('dipoleReturnLoss.csv','r') as csvfile:
    values = csv.reader(csvfile, delimiter = ',') 
      
    i = 0
    for i, row in enumerate(values): 
        if i == 0:
            continue

        freq = float(row[0]) / 1e6
        s11 = float(row[1])

        if freq < fticks[0] or freq > fticks[-1]:
            continue
        
        x.append(freq) 
        y.append(s11) 

fs = 11

plt.figure(figsize=(6, 4.2))
plt.plot(x, y)
plt.xticks(fontsize=fs)
plt.yticks(fontsize=fs)
plt.xticks(fticks)
plt.xlabel('Frequency (MHz)', fontsize=fs) 
plt.ylabel('Return Loss (dB)', fontsize=fs) 
# plt.title('Helical Antenna Return Loss vs Frequency') 
plt.legend() 
plt.show() 