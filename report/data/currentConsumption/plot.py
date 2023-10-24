import matplotlib.pyplot as plt 
import numpy as np

x = [5, 6, 7 , 8 , 9 , 10, 11, 12, 13, 14, 15, 16, 17, 18]
y = [5, 8, 11, 12, 15, 18, 22, 27, 29, 34, 42, 52, 70, 96]

plt.plot(x, y)
plt.scatter(x, y)
# plt.xticks(np.arange(min(x), max(x)+1, 20.0))
fontsize = 20
plt.xticks(fontsize=fontsize)
plt.yticks(fontsize=fontsize)
plt.xlabel('TX Power (dBm)', fontsize=fontsize) 
plt.ylabel('Current Consumption (mA)', fontsize=fontsize) 
# plt.title('Helical Antenna Return Loss vs Frequency') 
plt.legend() 
plt.show() 