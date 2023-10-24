import matplotlib.pyplot as plt 
import numpy as np
import csv 
  
x = [] 
y = [] 
  
with open('helicalReturnLoss.csv','r') as csvfile:
    values = csv.reader(csvfile, delimiter = ',') 
      
    i = 0
    for i, row in enumerate(values): 
        if i == 0:
            continue

        freq = float(row[0]) / 1e6
        s11 = float(row[1])

        if freq < 300 or freq > 600:
            continue
        
        x.append(freq) 
        y.append(s11) 

fs = 20
plt.plot(x, y)
plt.xticks(fontsize=fs)
plt.yticks(fontsize=fs)
plt.xticks(np.arange(min(x), max(x)+1, 50.0))
plt.xlabel('Frequency (MHz)', fontsize=fs) 
plt.ylabel('Return Loss (dB)', fontsize=fs) 
# plt.title('Helical Antenna Return Loss vs Frequency') 
plt.legend() 
plt.show() 