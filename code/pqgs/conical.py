import numpy as np
import math
import matplotlib.pyplot as plt
from mpl_toolkits import mplot3d

def cart2elaz(pt):
    x, y, z = pt[0], pt[1], pt[2]
    XsqPlusYsq = x**2 + y**2
    r = math.sqrt(XsqPlusYsq + z**2)                # r
    elev = math.atan2(z, math.sqrt(XsqPlusYsq))     # theta
    az = math.atan2(y,x)                            # phi
    return r, elev, az

def elaz2cart(r, elev, az):
    x = r * math.cos(az) * math.cos(elev)
    y = r * math.sin(az) * math.cos(elev)
    z = r * math.sin(elev)
    return np.array((x, y, z))

def conicalPositionMethod1(azCentre, elCentre, radius, scanAngle):
    R = 1

    conicalVec = np.array(elaz2cart(radius, scanAngle, 1.0))
    a = elaz2cart(azCentre, elCentre , 1.0)

    g = 1.0 - a[2]
    rMat = np.zeros((3, 3))
    
    rMat[0, 0] = 1.0 - g * a[0] * a[0]
    rMat[0, 1] = g * a[0] * a[1]
    rMat[0, 2] = a[0]
    rMat[1, 0] = g * a[0] * a[1]
    rMat[1, 1] = 1.0 - g * a[1] * a[1]
    rMat[1, 2] = -a[1]
    rMat[2, 0] = -a[0]
    rMat[2, 1] = -a[1]
    rMat[2, 2] = 1.0 - g * (a[0] * a[0] - a[1] * a[1])

    conicalVec = rMat @ conicalVec 

    return cart2elaz(conicalVec)

def conicalPositionMethod2(azCentre, elCentre, radius, scanAngle):
    boresightVec = elaz2cart(1.0, elCentre, azCentre)
    iVec = np.array([1, 0, 0])
    jVec = np.array([0, 1, 0])
    iVecLocal = np.cross(jVec, boresightVec)
    jVecLocal = np.cross(boresightVec, iVecLocal)

    point = radius * math.cos(scanAngle) * iVecLocal + radius * math.sin(scanAngle) * jVecLocal
    return point

azCentre = 30
elCentre = math.radians(40)
radius = math.radians(10)
scanAngle = 0
point = conicalPositionMethod2(azCentre, elCentre, radius, scanAngle)

# Data for a three-dimensional line
fig = plt.figure()
ax = plt.axes(projection='3d')
zline = np.linspace(0, 15, 1000)
xline = np.sin(zline)
yline = np.cos(zline)
ax.plot3D(xline, yline, zline, 'gray')