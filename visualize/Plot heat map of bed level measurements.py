"""

This script creates nice 2-d "heat map" chart to help you visualize the adjustments you need to do to make your Delta Kossel printer level

Tested with Python 3.5. Get it from https://www.continuum.io/downloads 

To run, place a CSV file in the same folder, rename it to spiral.csv

File must be in 3 columns - Z-height, X-coordinate and Y-coordinate, like this:

22.69	5.79	5.52
22.66	-1.9	9.87
22.66	-9.75	6.44
22.61	-13.02	-1.31
22.6	-10.85	-9.37

"""

import sys
import os
import matplotlib
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.mlab import griddata

in_filename = "spiral.csv"

matplotlib.rcParams['xtick.direction'] = 'out'
matplotlib.rcParams['ytick.direction'] = 'out'

# Read in CSV file
import csv
lineid = []
xcoords = []
ycoords = []
zcoords = []
with open(in_filename,'r') as csvfile:
    plots = csv.reader(csvfile, delimiter='\t') # file must be tab-delimited
    for row in plots:
        zcoords.append(float(row[0])) # 1st column - Z-probe measurement
        xcoords.append(float(row[1])) # 2nd column - x coordinate
        ycoords.append(float(row[2])) # 3rd column - y coordinate

xi = np.linspace(min(xcoords)-10, max(xcoords)+10) # slightly extend boundaries of the chart
yi = np.linspace(min(ycoords)-10, max(ycoords)+10)
X, Y = np.meshgrid(xi, yi)
Z = griddata(xcoords, ycoords, zcoords, xi, yi)

plt.figure(figsize=(12,10)) # almost square chart (wider to accomodate legend)

# we combine 2 types of fill. One uses line counters:
CS = plt.contour(X, Y, Z)
plt.clabel(CS, inline=1, fontsize=10)

# second is a gradient color fill:
colorlevels = np.arange(min(zcoords) - 0.1, max(zcoords) + 0.1, ((max(zcoords) - min(zcoords)) + 0.2) / 100 ) # color gradient from min to max with 100 steps in between
#colorlevels = [-1,	-0.9,	-0.8,	-0.7,	-0.6,	-0.5,	-0.4,	-0.3,	-0.2,	-0.1,	0,	0.1,	0.2,	0.3,	0.4,	0.5,	0.6,	0.7,	0.8,	0.9,	1]
CS2 = plt.contourf(CS, levels=colorlevels, origin='lower')
cbar = plt.colorbar(CS2)
cbar.add_lines(CS)
cbar.ax.set_ylabel('Z-probe value')

# chart title:
plt.title('3d printer height map')

# labels of axes:
plt.xlabel('X axis')
plt.ylabel('Y axis')

# set the figure boundaries so it becomes square:
lowboundary = min(
    min(xcoords),
    min(ycoords)
) - 10

upboundary = max(
    max(xcoords),
    max(ycoords)
) + 10

plt.xlim([lowboundary,upboundary])
plt.ylim([lowboundary,upboundary])

# Fixed points for tower positions (I've placed them roughly, fix this with trigonometric formulas if you'd like):
plt.annotate("Tower A (X)", xy=(-64.95, -37.5), arrowprops=dict(facecolor='black', shrink=0.05))
plt.annotate("Tower B (Y)", xy=( 64.95, -37.5), arrowprops=dict(facecolor='black', shrink=0.05))
plt.annotate("Tower C (Z)", xy=(  0   ,  75  ), arrowprops=dict(facecolor='black', shrink=0.05))

plt.show()
