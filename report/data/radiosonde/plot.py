import csv
import math
import geopy.distance
import matplotlib.pyplot as plt

filename = '1_fridayDay_track.csv'


launch = (-33.9783333, 18.5994444, 40)

# print(geopy.distance.geodesic(coords_1, coords_2).km)

# print geopy.distance.geodesic(coords_1, coords_2).km

dists = []
snrs = []

with open(filename, newline='') as csvfile:
    spamreader = csv.reader(csvfile, delimiter=' ', quotechar='|')
    for i, row in enumerate(spamreader):
        if i == 0:
            continue
        vals = row[0].split(',')
        lat = float(vals[0])
        lng = float(vals[1])
        alt = float(vals[2])
        snr = float(vals[3])

        horizDist = geopy.distance.geodesic((launch[0], launch[1]), (lat, lng)).km
        altDist = (alt - launch[2]) * 1e-3

        dist = math.sqrt(horizDist**2 + altDist**2)
        dists.append(dist)
        snrs.append(snr)

fs = 11


plt.figure(figsize=(6, 4.2))
plt.scatter(dists, snrs, s=2)
plt.xticks(fontsize=fs)
plt.yticks(fontsize=fs)
plt.xlabel('Distance (km)', fontsize=fs) 
plt.ylabel('SNR (dB)', fontsize=fs) 
plt.legend(prop={'size': fs}) 
plt.show() 