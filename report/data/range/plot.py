import matplotlib.pyplot as plt 
import numpy as np
from scipy.optimize import curve_fit

extrapolate_range = 200000

dist = np.array([1400, 4600, 9700, 34500, 49000])
rssi_h = [-79, -87, -88, -102, -105]
rssi_v = [-80, -85, -92, -106, -107]
snr_h = [6.9, 7.2, 6.7, 2.8, 1.2]
snr_v = [6.8, 7.0, 6.4, -0.6, -0.25]
prr_h = [100, 100, 100, 100, 100]
prr_v = [100, 100, 100, 100, 100]

y_h, y_v = rssi_h, rssi_v
initial = [20, -100]
# tick_values = [10.0, 7.5, 5.0, 2.5, 0.0, -2.5, -5.0, -7.5, -10.0]
tick_values = [-70, -80, -90, -100, -110, -120]
def func(x, a, b):
    return a*np.log10(x) + b

popt_h, pcov = curve_fit(func, dist, y_h, p0=initial)
popt_v, pcov = curve_fit(func, dist, y_v, p0=initial)

fs = 20
exp_dists = np.linspace(0, extrapolate_range, 1000)

plt.scatter(dist, y_h, label='Horizontal Polarization')
plt.scatter(dist, y_v, color='red', label='Vertical Polarization')
plt.plot(exp_dists, func(exp_dists, *popt_h))
plt.plot(exp_dists, func(exp_dists, *popt_v), color='red')
plt.xticks(fontsize=fs)
plt.yticks(fontsize=fs)
plt.yticks(tick_values)
# plt.xticks(np.arange(min(x), max(x)+1, 50.0))
plt.xlabel('Distance (km)', fontsize=fs) 
plt.ylabel('RSSI (dBm)', fontsize=fs) 
plt.legend(prop={'size': fs}) 
plt.show() 