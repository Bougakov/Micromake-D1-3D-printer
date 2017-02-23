# Draft of the code that makes spiral-path measurement of bed height

## Python code that produces "height map" chart

Install https://www.continuum.io/downloads#windows first (you need Python 3.5 variant). After installing, open command prompt and run `pip install spyder`. This will install an interactive editor you can use to run my script.

Save my code in any folder. Also create a file with the name `spiralcoordinates.csv` in the same directory. CSV file must be tab-delimited, without header. Copy is attached below; alternatively you can generate your own dummy CSV file using my JavaScript wizard.

It will produce the chart like this:

![Surface plot](https://scontent-arn2-1.xx.fbcdn.net/v/t1.0-9/16831041_1066395483466545_9109059825969635227_n.jpg?oh=b0d2006219b3b90dd5a1edce98825525&oe=592D184B)

```python
import matplotlib
import numpy as np
import matplotlib.pyplot as plt

matplotlib.rcParams['xtick.direction'] = 'out'
matplotlib.rcParams['ytick.direction'] = 'out'

# Read in CSV file
import csv
lineid = []
xcoords = []
ycoords = []
zcoords = []
with open('spiralcoordinates.csv','r') as csvfile:
    plots = csv.reader(csvfile, delimiter='\t') # file must be tab-delimited
    for row in plots:
        lineid.append(   int(row[0])) # 1st column - line number (not used)
        xcoords.append(float(row[1])) # 2nd column - x coordinate
        ycoords.append(float(row[2])) # 3rd column - y coordinate
        zcoords.append(float(row[3])) # 4th column - Z-probe measurement

xi = np.linspace(min(xcoords)-10, max(xcoords)+10) # slightly extend boundaries of the chart
yi = np.linspace(min(ycoords)-10, max(ycoords)+10)
X, Y = np.meshgrid(xi, yi)
Z = griddata(xcoords, ycoords, zcoords, xi, yi)

plt.figure(figsize=(12,10)) # almost square chart (wider to accomodate legend)

# we combine 2 types of fill. One uses line counters:
CS = plt.contour(X, Y, Z)
plt.clabel(CS, inline=1, fontsize=10)

# second is a gradient color fill:
colorlevels = np.arange(min(zcoords), max(zcoords), (max(zcoords) - min(zcoords)) / 100 ) # color gradient from min to max with 100 steps in between
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
plt.annotate("Tower B (Y)", xy=( upboundary*2/3, lowboundary*1/3), arrowprops=dict(facecolor='black', shrink=0.05))
plt.annotate("Tower A (X)", xy=(upboundary*-2/3, lowboundary*1/3), arrowprops=dict(facecolor='black', shrink=0.05))
plt.annotate("Tower C (Z)", xy=(              0,  upboundary*4/5), arrowprops=dict(facecolor='black', shrink=0.05))

plt.show()
```

And here is the CSV data. First column is ID, next three are X, Y and Z-height.

```csv
1	-9.708	7.053	0.316
2	-13.158	-5.129	0.430
3	-5.451	-14.963	0.255
4	6.891	-16.113	0.493
5	16.816	-8.795	0.254
6	20.090	3.045	-0.911
7	15.916	14.562	0.267
8	6.146	21.907	0.389
9	-5.996	23.107	0.077
10	-17.119	18.135	0.661
11	-24.533	8.487	0.459
12	-26.716	-3.471	0.062
13	-23.408	-15.156	0.427
14	-15.440	-24.310	0.289
15	-4.412	-29.354	0.093
16	7.706	-29.553	0.692
17	18.938	-25.015	0.134
18	27.601	-16.557	0.714
19	32.516	-5.498	0.817
20	33.101	6.585	0.409
21	29.381	18.092	-0.974
22	21.915	27.600	0.068
23	11.674	34.018	0.243
24	-0.113	36.673	0.155
25	-12.119	35.348	0.452
26	-23.070	30.258	0.412
27	-31.868	21.990	0.175
28	-37.686	11.413	0.739
29	-40.020	-0.428	0.266
30	-38.714	-12.423	0.513
31	-33.942	-23.504	0.786
32	-26.167	-32.727	0.433
33	-16.087	-39.348	-0.924
34	-4.553	-42.868	0.648
35	7.503	-43.051	0.098
36	19.148	-39.928	0.905
37	29.516	-33.779	0.956
38	37.868	-25.089	0.591
39	43.637	-14.507	0.483
40	46.456	-2.791	0.009
41	46.168	9.255	0.987
42	42.830	20.831	0.091
43	36.692	31.198	0.562
44	28.172	39.713	0.767
45	17.821	45.874	0.379
46	6.284	49.332	0.379
47	-5.745	49.914	0.454
48	-17.566	47.613	0.556
49	-28.510	42.590	0.625
50	-37.977	35.152	0.945
51	-45.468	25.725	0.068
52	-50.599	14.834	0.899
53	-53.123	3.063	0.330
54	-52.934	-8.973	0.418
55	-50.067	-20.664	0.876
56	-44.687	-31.431	0.832
57	-37.079	-40.757	0.836
58	-27.627	-48.207	0.200
59	-16.792	-53.445	0.159
60	-5.088	-56.246	0.051
61	6.943	-56.501	0.939
62	18.758	-54.220	0.541
63	29.836	-49.524	0.085
64	39.701	-42.635	0.509
65	47.939	-33.866	0.915
66	54.214	-23.601	0.493
67	58.280	-12.278	0.023
68	59.986	-0.370	0.099
69	59.280	11.639	0.992
70	56.207	23.270	0.311
71	50.904	34.067	0.259
72	43.593	43.618	0.666
73	34.565	51.567	0.050
74	24.174	57.625	0.630
75	12.815	61.579	0.527
76	0.911	63.296	0.416
77	-11.102	62.730	0.930
78	-22.794	59.915	0.274
79	-33.754	54.965	0.612
80	-43.604	48.065	0.626
81	-52.011	39.466	0.531
82	-58.696	29.471	0.347
83	-63.446	18.424	0.127
84	-66.114	6.699	0.534
85	-66.624	-5.315	0.428
86	-64.972	-17.225	0.558
87	-61.224	-28.649	0.927
88	-55.510	-39.228	0.779
89	-48.021	-48.634	0.120
90	-38.999	-56.581	0.192
91	-28.730	-62.833	0.394
92	-17.532	-67.209	0.120
93	-5.747	-69.588	0.592
94	6.270	-69.909	0.872
95	18.166	-68.174	0.868
96	29.594	-64.443	0.428
97	40.227	-58.835	0.495
98	49.766	-51.519	0.766
99	57.946	-42.710	0.058
100	64.545	-32.663	0.503
101	69.389	-21.662	0.088
102	72.352	-10.012	0.481
103	73.364	1.965	0.645
104	72.406	13.947	0.611
105	69.514	25.614	0.854
106	64.772	36.658	0.938
107	58.314	46.795	0.710
108	50.314	55.766	0.868
109	40.986	63.345	0.786
110	30.572	69.345	0.235
111	19.341	73.623	0.489
112	7.576	76.080	0.011
113	-4.428	76.661	0.329
114	-16.376	75.362	0.468
115	-27.977	72.222	0.604
116	-38.951	67.324	0.485
117	-49.040	60.793	0.269
118	-58.007	52.792	0.958
119	-65.645	43.514	0.162
120	-71.783	33.183	0.814
121	-76.283	22.040	0.101
122	-79.050	10.346	0.834
```

## JavaScript implementation of spiral algorithm. 

Save it to a local file and open. Feel free to play with `width`, `coils` and `chord` values. Defaults are for bed diameter of 150mm (1px equals to 1mm). It will visualize spiral and create dummy CSV file like this:

![Spiral](https://scontent-arn2-1.xx.fbcdn.net/v/t1.0-9/16832090_1066396203466473_7609443908364565218_n.jpg?oh=52cac2f8183a77609d5a0991ea6c9a70&oe=59366366)

```html
<!DOCTYPE html>
<html>
  <head>
    <meta name="description" content="Points Along an Archimedean Spiral" />
    <meta http-equiv="Content-Type" content="text/html;charset=utf-8">
    <script type="text/javascript" src="http://d3js.org/d3.v2.js"></script>
    <style type="text/css">
        svg {
          background: white;
        }

        .spiral {
          fill: none;
          stroke: #303030;
          stroke-width: 3px;
        }
        .chart {
            margin: 10px;
        }
        td {
            text-align: right;
            min-width: 50px;
        }
        th, tr:nth-child(even) {
            background-color: lightgrey;
        }
        tr:nth-child(odd) {
            background-color: white;
        }
    </style>
  </head>
  <body>
    <h1>Spiral path for 3d printer's height probe</h1>
    <div id="chart"></div>

    <h1>Generated coordinates</h1>
    <p>Array that would hold the list of coordinates needs to be <code id="arr"></code> elements long (including element with id 0 that holds coordinates for center point 0,0).</p>
    <p>thetaMax is <code id="thetaMax"></code>.</p>
    <p>chord is <code id="chord"></code>.</p>
    
    <table border="1">
        <tr>
            <th>#</th>
            <th>X</th>
            <th>Y</th>
            <th>dummy Z</th>
            <th>theta</th>
        </tr>
        <tbody id="coords"></tbody></table>

    <script type="text/javascript"><!--

        var width = 150; // width of spiral in px ("virtual" mm). Must be smaller than plate diameter
        var height = width;
        var coils = 3.6; // Sets the number of turns the spiral makes
        var chord = 15; // distance in px ("virtual" mm between hops of spiral)

        var centerX = width/2,
            centerY = height/2,
            radius = width/2;

        var rotation = 2 * Math.PI;
        var thetaMax = coils * 2 * Math.PI;
        var awayStep = radius / thetaMax;

        var i = 0;
        var new_time = [];
        
        new_time.push({x: centerX, y: centerY, theta: NaN, chord: NaN}); // spiral starts at center point
        
        // Determining array size to hold spiral coordinates:
        for ( theta = chord / awayStep; theta <= thetaMax; ) {
            away = awayStep * theta;
            theta += chord / away;
            i++;
        }
        document.getElementById("arr").innerHTML = i + 1; 
        document.getElementById("thetaMax").innerHTML = thetaMax.toFixed(3); 
        document.getElementById("chord").innerHTML    = chord; 
        i = 0; // Reset counter
        
        // Calculating actual coordinates:
        for ( theta = chord / awayStep; theta <= thetaMax; ) {
            away = awayStep * theta;
            around = theta + rotation;

            x = centerX + Math.cos ( around ) * away;
            y = centerY + Math.sin ( around ) * away;

            theta += chord / away;
            new_time.push({x: x, y: y, theta: theta, chord: chord});

            // Code that appends the lines to the table on the page:
            i++;
            // here we adjust the coordinates so that the center of spiral is at 0, 0 point:
            offsetX = width/2 - x;
            offsetX = offsetX.toFixed(3);
            offsetY = height/2 - y;
            offsetY = offsetY.toFixed(3);
            dummyZ  = Math.random(); // For debugging purposes we use random numbers instead of actual Z-probe values
            dummyZ  = dummyZ.toFixed(3);
            document.getElementById("coords").innerHTML = document.getElementById("coords").innerHTML +
                "<tr><td>" +
                i +
                "</td><td>" +
                offsetX +
                "</td><td>" +
                offsetY +
                "</td><td>" +
                dummyZ +
                "</td><td><i>" +
                theta.toFixed(3) +
                "</i></td></tr>";
        }

        // code that draws spiral using SVG:
        var svg = d3.select("#chart").append("svg")
            .attr("width", width)
            .attr("height", height)
            .append("g");

        var lineFunction = d3.svg.line()
                            .x(function(d) { return d.x; })
                            .y(function(d) { return d.y; })
                            .interpolate("cardinal");

        svg.append("path")
          .attr("d", lineFunction(new_time))
          .attr("stroke", "gray")
          .attr("stroke-width", 0.5)
          .attr("fill", "none");


        var circles = svg.selectAll("circle")
                        .data(new_time)
                        .enter()
                        .append("circle")
                        .attr("cx", function (d) { return d.x; })
                        .attr("cy", function (d) { return d.y; })
                        .attr("r", 2);

    --></script>
  </body>
</html>
```

## Implementation in Repetier code:

I added the following block into `commands.cpp` file, but it doesn't work properly:

```cpp
case 228: {
	long radius = 50; // Default radius. If you have custom Z-probe, feel free to use max radius
	float coils = 3.6; // Sets the number of turns the spiral makes
	int chord = 15; // distance in px ("virtual" mm between hops of spiral)
	float rotation = 2 * PI;
	float thetaMax = coils * 2 * PI;
	float awayStep = radius / thetaMax;
	float offset = 0;
	Printer::homeAxis(true, true, true); // First we home the extruder
	GCode::executeFString(Com::tZProbeStartScript);
	bool oldAutolevel = Printer::isAutolevelActive();
	Printer::setAutolevelActive(false);
	float oldFeedrate = Printer::feedrate;
	int array_size = 0;
	//////////////

	// Determining array size to hold spiral coordinates:
	float theta = chord / awayStep;
	while (theta <= thetaMax) {
	  float away = awayStep * theta;
	  theta += chord / away;
	  array_size++;
	}
	const float position[array_size][2] {};
	position[0][0] == 0;
	position[0][1] == 0;

	// Calculating actual coordinates:
	array_size = 0;
	theta = chord / awayStep;
	while (theta <= thetaMax) {
	  array_size++;
	  float away = awayStep * theta;
	  float around = theta + rotation;
	  theta += chord / away;
	  position[array_size][0] == cos(around) * away;
	  position[array_size][1] == sin(around) * away;
	}

	// float distance[array_size];
	Printer::moveTo(0, 0, Z_PROBE_BED_DISTANCE * 3 + EEPROM::zProbeHeight(), IGNORE_COORDINATE, oldFeedrate); // We want the nozzle to get to the bed faster so we travel most of the distance at normal speed and slow down when close
	offset = Printer::runZProbe(false, false, 1, false); // + Z_PROBE_BED_DISTANCE; // For some reason the first measurement returns bogus results so we discard it 
	if (offset == ILLEGAL_Z_PROBE)
	  return false; // Without this firmware sometimes crashes with no apparent reason
	// Initial call to Printer::runZProbe is supposed to be with "TRUE" as first argument. But it crashes, so I call it with "false, false"        
	// Printer::moveTo(position[0][0], position[0][1], Z_PROBE_BED_DISTANCE * 3 + EEPROM::zProbeHeight(), IGNORE_COORDINATE, oldFeedrate);
	Printer::moveTo(position[0][0], position[0][1], Z_PROBE_BED_DISTANCE * 3 + EEPROM::zProbeHeight(), IGNORE_COORDINATE, EEPROM::zProbeXYSpeed());
	// distance[0] = Printer::runZProbe(false, false, Z_PROBE_REPETITIONS, false);
	for (uint8_t i = 1; i < (array_size - 1); i++) {
	  // Printer::moveTo(position[i][0], position[i][1], Z_PROBE_BED_DISTANCE * 3 + EEPROM::zProbeHeight(), IGNORE_COORDINATE, oldFeedrate);
	  Printer::moveTo(position[i][0], position[i][1], Z_PROBE_BED_DISTANCE * 3 + EEPROM::zProbeHeight(), IGNORE_COORDINATE, EEPROM::zProbeXYSpeed());
	  //distance[i] = Printer::runZProbe(false, false, Z_PROBE_REPETITIONS, false);
	}
	// Printer::moveTo(position[(array_size - 1)][0], position[(array_size - 1)][1], Z_PROBE_BED_DISTANCE * 3 + EEPROM::zProbeHeight(), IGNORE_COORDINATE, oldFeedrate);
	Printer::moveTo(position[(array_size - 1)][0], position[(array_size - 1)][1], Z_PROBE_BED_DISTANCE * 3 + EEPROM::zProbeHeight(), IGNORE_COORDINATE, EEPROM::zProbeXYSpeed());
	//distance[(array_size - 1)] = Printer::runZProbe(false, true, Z_PROBE_REPETITIONS, false); // Note "true" as 2nd argument
	Printer::updateCurrentPosition();
	// distance[(array_size - 1)] = Printer::zLength - Printer::currentPosition[Z_AXIS];
	// Com::printArrayFLN(Com::tZProbeDistance, distance, array_size, 2);
	//////////////////////////////////////

	Printer::feedrate = oldFeedrate;
	Printer::setAutolevelActive(oldAutolevel);
	Printer::updateCurrentPosition(true);
	printCurrentPosition(PSTR("229 "));
	GCode::executeFString(Com::tZProbeEndScript);
	Printer::homeAxis(true, true, true);
  }
  break;
```
