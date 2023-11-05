import matplotlib.pyplot as plt 
import numpy as np
from scipy.optimize import curve_fit

extrapolate_range = 200

1.4,-80,6.8
4.6,-85,7.0
10,-92,6.4
35,-106,-0.6
43,-103,2.89
50,-107,-0.25
71,-105,3.9
100,-116,-4.25
122,-108,0

dist = [1.4, 4.6, 9.7, 34.5, 43.5, 50, 71, 100, 122]
rssi_h = [-79, -87, -88, -102, -104, -105, -108, -120, -112]
snr_h = [6.9, 7.2, 6.7, 2.8, 2.65, 1.2, 1.4, -7.85, -3.4]
rssi_v = [-80, -85, -92, -106, -103, -107, -105, -116, -108]
snr_v = [6.8, 7.0, 6.4, -0.6, 2.89, -0.25, 3.9, -4.25, 0.0]
snr_tick_values = [10.0, 5.0, 0.0, -5.0, -10.0]
rssi_tick_values = [-70, -80, -90, -100, -110, -120]

# y_h, y_v = rssi_h, rssi_v
# y_tick_values = rssi_tick_values
# y_label = "RSSI (dBm)"

y_h, y_v = snr_h, snr_v
y_tick_values = snr_tick_values
y_label = "SNR (dB)"

initial = [20, -100]
x_tick_values = [0, 50, 100, 150, 200]
def func(x, a, b):
    return a*np.log10(x) + b

popt_h, pcov = curve_fit(func, dist, y_h, p0=initial)
popt_v, pcov = curve_fit(func, dist, y_v, p0=initial)

fs = 11
exp_dists = np.linspace(0, extrapolate_range, 1000)


plt.figure(figsize=(6, 4.2))
plt.scatter(dist, y_h, label='Horizontal Polarization')
plt.scatter(dist, y_v, color='red', label='Vertical Polarization')
plt.plot(exp_dists, func(exp_dists, *popt_h))
plt.plot(exp_dists, func(exp_dists, *popt_v), color='red')
plt.xticks(fontsize=fs)
plt.yticks(fontsize=fs)
plt.xticks(x_tick_values)
plt.yticks(y_tick_values)
plt.xlabel('Distance (km)', fontsize=fs) 
plt.ylabel(y_label, fontsize=fs) 
plt.legend(prop={'size': fs}) 
plt.show() 