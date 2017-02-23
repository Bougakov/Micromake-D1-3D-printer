# Draft of the code that makes spiral-path measurement of bed height

Links to discussion:
 * https://www.facebook.com/groups/173676226330714/permalink/386872075011127/
 * https://vk.com/wall-134740295_4954

## Python code that produces "height map" chart

Install https://www.continuum.io/downloads#windows first (you need Python 3.5 variant). After installing, open command prompt and run `pip install spyder`. This will install an interactive editor you can use to run my script.

Save my code in any folder. Also create a file with the name `spiralcoordinates.csv` in the same directory. CSV file must be tab-delimited, without header. Copy is attached below; alternatively you can generate your own dummy CSV file using my JavaScript wizard.

It will produce the chart like this:

![Surface plot](https://scontent-arn2-1.xx.fbcdn.net/v/t1.0-9/16864382_1066469400125820_1971672729963592477_n.jpg?oh=22cba2d7a887f3ae8db9e0609dc41091&oe=594651A5)

Save this to a file with `.py` extension:

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
plt.annotate("Tower B (Y)", xy=( upboundary*2/3, lowboundary*1/3), arrowprops=dict(facecolor='black', shrink=0.05))
plt.annotate("Tower A (X)", xy=(upboundary*-2/3, lowboundary*1/3), arrowprops=dict(facecolor='black', shrink=0.05))
plt.annotate("Tower C (Z)", xy=(              0,  upboundary*4/5), arrowprops=dict(facecolor='black', shrink=0.05))

plt.show()
```

And here is the CSV data (I obtained it from my printer after resetting it to factory defaults, so it is not "dummy"). First column is ID, next three are X, Y and Z-height.

Save it with the name `spiralcoordinates.csv` in the same directory as Python script. CSV file must be tab-delimited, without headers.

```csv
1	0	0	33.5
2	-9.53	7.29	33.43
3	-13.29	-4.8	33.4
4	-5.84	-14.84	33.45
5	6.47	-16.31	33.53
6	16.59	-9.26	33.58
7	20.2	2.48	33.59
8	16.36	14.11	33.59
9	6.81	21.75	33.54
10	-5.29	23.32	33.43
11	-16.56	18.7	33.32
12	-24.29	9.3	33.27
13	-26.86	-2.58	33.25
14	-23.95	-14.38	33.25
15	-16.31	-23.8	33.31
16	-5.47	-29.23	33.41
17	6.63	-29.87	33.5
18	18.02	-25.75	33.56
19	27	-17.63	33.56
20	32.34	-6.76	33.57
21	33.4	5.28	33.59
22	30.14	16.93	33.63
23	23.07	26.73	33.61
24	13.1	33.57	33.52
25	1.43	36.72	33.45
26	-10.61	35.9	33.34
27	-21.77	31.29	33.27
28	-30.93	23.42	33.18
29	-37.22	13.11	33.12
30	-40.08	1.39	33.06
31	-39.33	-10.65	33.06
32	-35.07	-21.94	33.11
33	-27.74	-31.52	33.2
34	-17.98	-38.61	33.27
35	-6.63	-42.68	33.37
36	5.4	-43.45	33.46
37	17.18	-40.91	33.52
38	27.84	-35.29	33.53
39	36.63	-27.03	33.52
40	42.93	-16.75	33.54
41	46.34	-5.2	33.56
42	46.68	6.84	33.59
43	43.96	18.58	33.6
44	38.38	29.26	33.63
45	30.33	38.22	33.57
46	20.33	44.93	33.53
47	9	49.02	33.43
48	-2.98	50.26	33.36
49	-14.91	48.63	33.29
50	-26.12	44.22	33.18
51	-36	37.34	33.1
52	-44.01	28.35	33.03
53	-49.76	17.77	32.97
54	-52.97	6.17	32.93
55	-53.49	-5.86	32.88
56	-51.31	-17.7	32.9
57	-46.59	-28.76	32.92
58	-39.55	-38.54	33.01
59	-30.56	-46.54	33.12
60	-20.07	-52.43	33.24
61	-8.56	-55.95	33.35
62	3.43	-56.95	33.43
63	15.36	-55.4	33.51
64	26.72	-51.41	33.56
65	37	-45.16	33.57
66	45.78	-36.93	33.54
67	52.7	-27.09	33.4
68	57.49	-16.05	33.43
69	59.97	-4.28	33.43
70	60.04	7.75	33.49
71	57.75	19.55	33.53
72	53.16	30.68	33.55
73	46.51	40.7	33.52
74	38.04	49.24	33.49
75	28.07	55.98	33.37
76	17.01	60.7	33.39
77	5.26	63.22	33.42
78	-6.77	63.48	33.35
79	-18.63	61.48	33.22
80	-29.9	57.31	33.11
81	-40.22	51.11	33.03
82	-49.2	43.13	32.95
83	-56.58	33.63	32.92
84	-62.11	22.95	32.87
85	-65.6	11.44	32.81
86	-66.98	-0.5	32.78
87	-66.19	-12.5	32.77
88	-63.29	-24.16	32.75
89	-58.36	-35.13	32.79
90	-51.58	-45.06	32.86
91	-43.17	-53.66	32.93
92	-33.4	-60.65	33.04
93	-22.55	-65.85	33.15
94	-10.98	-69.11	33.29
95	0.98	-70.33	33.42
96	12.97	-69.5	33.44
97	24.65	-66.65	33.35
98	35.68	-61.88	33.28
99	45.75	-55.31	33.28
100	54.59	-47.16	33.33
101	61.95	-37.66	33.41
102	67.63	-27.06	33.2
103	71.5	-15.68	33.25
104	73.45	-3.82	33.24
105	73.44	8.19	33.27
106	71.48	20.05	33.38
107	67.63	31.44	33.42
108	62.01	42.06	33.22
```

## JavaScript implementation of spiral algorithm. 

Save it to a local file and open. Feel free to play with `width`, `coils` and `chord` values. Defaults are for bed diameter of 150mm (1px equals to 1mm). It will visualize spiral and create dummy CSV file like this:

<!-- ![Spiral](https://scontent-arn2-1.xx.fbcdn.net/v/t1.0-9/16832090_1066396203466473_7609443908364565218_n.jpg?oh=52cac2f8183a77609d5a0991ea6c9a70&oe=59366366) -->

<svg width="150" height="150"><g><path d="M75,75Q70.86079718861339,61.5265606166991,72.18928028121411,60.26569123906967C74.18200492011518,58.37438717262552,84.71415803982818,59.99301170982515,88.28483092600715,62.391306223705676S95.47414890717474,71.91269134211944,95.99376618907387,76.25432133160653S94.3003418251552,87.74231235771788,91.74894613866799,91.33550615361965S83.21819285824961,98.91545925742635,78.9844616124925,100.20894663761835S67.76209152822301,101.28265288817529,63.52407116695388,99.95875535489964S53.64113159760132,94.7484036161156,50.730992537364955,91.38296308244728S44.97962529026587,81.89534825501754,44.12314409871142,77.52248513044415S43.71626062611598,66.49660375664152,45.02111792700197,62.23054225195802S49.738487533153645,52.31154562714173,52.82219277128466,49.08207509922086S61.40379620892579,42.29289063271376,65.57915284787543,40.70073873248555S76.19492527653578,38.19379156492034,80.65790369761561,38.46772909769945S91.34477293614732,40.49887747001168,95.3323423217409,42.52698895101294S104.338956169343,48.58176093689144,107.24169960157278,51.988472304374525S113.25755168016735,60.99432428138129,114.68396520327269,65.2383980675668S116.95408834882117,75.80805242001765,116.75112308894168,80.2822975456113S115.09227045229892,90.94733682134311,113.33086347074277,95.06669890485782S108.0724355761991,104.47458253132199,105.00840987856735,107.74471143570935S96.88342376410726,114.8046563339413,92.90402548653111,116.86755826744022S82.91394929652287,120.84057137760163,78.47908802805966,121.49739099236879S67.75280877589212,122.03299285819148,63.338283696776344,121.24635569922128S53.00091809445164,118.37334971848739,49.048920833954526,116.25314326590087S40.111393495635454,110.33450070843048,36.991635293462224,107.11164601531121S30.267453979899525,98.7746030908672,28.250532819466322,94.7674453117724S24.3023014920484,84.8196659942539,23.54549422390754,80.39726082134594S22.66058044848975,69.7387987007848,23.20515103186058,65.28474415905268S25.397609844570876,54.82387782308603,27.17596477971307,50.703563876465154S32.21028307718639,41.282661878618036,35.060850599475195,37.81598451491352S42.49223092066766,30.151594277543246,46.17974826163842,27.592381451768354S55.40538703569052,22.231889345929588,59.64429953928027,20.754565676414238S69.96030974708502,18.050149000546114,74.43916495223677,17.7435569883327S85.09832461646437,17.84280480212539,89.50333424029188,18.710618928324813S99.769596902162,21.56216450481474,103.80589577775348,23.52898449632886S113.00247758391829,28.900767159637365,116.41199341090177,31.822752205085614S123.96077044983409,39.33009039703629,126.53600129097666,43.00888479931718S131.98684443576346,52.14936197779181,133.58019901851887,56.34804822029159S136.62969258038632,66.54024743108725,137.1583651760128,71.00012641598234S137.65806644773093,81.62345347275232,137.1046829893621,86.08057478625884S135.05966218233704,96.5137392990121,133.46914212022062,100.71426850602575S129.02798769902722,110.37040437090806,126.50121590858609,114.0841028330165S119.93899962437638,122.44096731080155,116.623996850613,125.47225825341529S108.3198737402559,132.0964187899211,104.40119741683023,134.29270911710807S94.81238168927166,138.85708278848765,90.49948802777517,140.11419376799506S80.13331249464485,142.40872479194832,75.64857300685361,142.6734489804909S65.03422576002126,142.60907996327768,60.601224775833565,141.87902169161214S50.26258096554667,139.48542429669556,46.09523311226904,137.806393836054S36.52598028275435,133.224169157204,32.81890575398272,130.6854852873352S24.46091537735365,124.15372217388284,21.381402920458214,120.88183470359552S14.60704389488837,112.72202767728436,12.288822708013136,108.87290215208637S7.387657890717632,99.47028398875509,5.926595007956649,95.22099786894222S3.096660266162452,85.00434188436876,2.548403489606585,80.54432802000058S1.892048842432063,69.96522933875173,2.271549830917536,65.48757210648769S3.795630291648845,55.00013414409417,5.078410079509737,50.693279804906965Q5.933596604750332,47.82204357878216,10.823415083323482,36.77520984523966" stroke="gray" stroke-width="0.5" fill="none"></path><circle cx="75" cy="75" r="2"></circle><circle cx="72.18928028121411" cy="60.26569123906967" r="2"></circle><circle cx="88.28483092600715" cy="62.391306223705676" r="2"></circle><circle cx="95.99376618907387" cy="76.25432133160653" r="2"></circle><circle cx="91.74894613866799" cy="91.33550615361965" r="2"></circle><circle cx="78.9844616124925" cy="100.20894663761835" r="2"></circle><circle cx="63.52407116695388" cy="99.95875535489964" r="2"></circle><circle cx="50.730992537364955" cy="91.38296308244728" r="2"></circle><circle cx="44.12314409871142" cy="77.52248513044415" r="2"></circle><circle cx="45.02111792700197" cy="62.23054225195802" r="2"></circle><circle cx="52.82219277128466" cy="49.08207509922086" r="2"></circle><circle cx="65.57915284787543" cy="40.70073873248555" r="2"></circle><circle cx="80.65790369761561" cy="38.46772909769945" r="2"></circle><circle cx="95.3323423217409" cy="42.52698895101294" r="2"></circle><circle cx="107.24169960157278" cy="51.988472304374525" r="2"></circle><circle cx="114.68396520327269" cy="65.2383980675668" r="2"></circle><circle cx="116.75112308894168" cy="80.2822975456113" r="2"></circle><circle cx="113.33086347074277" cy="95.06669890485782" r="2"></circle><circle cx="105.00840987856735" cy="107.74471143570935" r="2"></circle><circle cx="92.90402548653111" cy="116.86755826744022" r="2"></circle><circle cx="78.47908802805966" cy="121.49739099236879" r="2"></circle><circle cx="63.338283696776344" cy="121.24635569922128" r="2"></circle><circle cx="49.048920833954526" cy="116.25314326590087" r="2"></circle><circle cx="36.991635293462224" cy="107.11164601531121" r="2"></circle><circle cx="28.250532819466322" cy="94.7674453117724" r="2"></circle><circle cx="23.54549422390754" cy="80.39726082134594" r="2"></circle><circle cx="23.20515103186058" cy="65.28474415905268" r="2"></circle><circle cx="27.17596477971307" cy="50.703563876465154" r="2"></circle><circle cx="35.060850599475195" cy="37.81598451491352" r="2"></circle><circle cx="46.17974826163842" cy="27.592381451768354" r="2"></circle><circle cx="59.64429953928027" cy="20.754565676414238" r="2"></circle><circle cx="74.43916495223677" cy="17.7435569883327" r="2"></circle><circle cx="89.50333424029188" cy="18.710618928324813" r="2"></circle><circle cx="103.80589577775348" cy="23.52898449632886" r="2"></circle><circle cx="116.41199341090177" cy="31.822752205085614" r="2"></circle><circle cx="126.53600129097666" cy="43.00888479931718" r="2"></circle><circle cx="133.58019901851887" cy="56.34804822029159" r="2"></circle><circle cx="137.1583651760128" cy="71.00012641598234" r="2"></circle><circle cx="137.1046829893621" cy="86.08057478625884" r="2"></circle><circle cx="133.46914212022062" cy="100.71426850602575" r="2"></circle><circle cx="126.50121590858609" cy="114.0841028330165" r="2"></circle><circle cx="116.623996850613" cy="125.47225825341529" r="2"></circle><circle cx="104.40119741683023" cy="134.29270911710807" r="2"></circle><circle cx="90.49948802777517" cy="140.11419376799506" r="2"></circle><circle cx="75.64857300685361" cy="142.6734489804909" r="2"></circle><circle cx="60.601224775833565" cy="141.87902169161214" r="2"></circle><circle cx="46.09523311226904" cy="137.806393836054" r="2"></circle><circle cx="32.81890575398272" cy="130.6854852873352" r="2"></circle><circle cx="21.381402920458214" cy="120.88183470359552" r="2"></circle><circle cx="12.288822708013136" cy="108.87290215208637" r="2"></circle><circle cx="5.926595007956649" cy="95.22099786894222" r="2"></circle><circle cx="2.548403489606585" cy="80.54432802000058" r="2"></circle><circle cx="2.271549830917536" cy="65.48757210648769" r="2"></circle><circle cx="5.078410079509737" cy="50.693279804906965" r="2"></circle><circle cx="10.823415083323482" cy="36.77520984523966" r="2"></circle></g></svg>

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
		textarea {
			width: 90%;
			height: 250px;
		}
    </style>
  </head>
  <body>
    <h1>Spiral path for 3d printer's height probe</h1>
    <div id="chart"></div>

	<h2>G-code:</h2>
	<textarea id="gcode"></textarea>	
	
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
        <tbody id="coords"></tbody>
	</table>

    <script type="text/javascript"><!--

        var width = 160; // width of spiral in px ("virtual" mm). Must be smaller than plate diameter
        var height = width;
        var coils = 5.6; // Sets the number of turns the spiral makes
        var chord = 12; // distance in px ("virtual" mm between hops of spiral)
		
		var z_probe_height = 28;

		document.getElementById("gcode").innerHTML = "G28 ; Home\n" +
			"M322 ; Resets auto level matrix  (adding S3 will make change permanent)\n" +
			"M321 ; Deactivates auto level (adding S2 will make change permanent)\n" +
			"G28\n" +
			"G1 X0 Y0 Z" + z_probe_height + " ;\tProbe point 0\n" +
			"G30 P2\n";
		
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
        
			document.getElementById("gcode").innerHTML = document.getElementById("gcode").innerHTML + "G1" + " X" + offsetX + " Y" + offsetY + " Z" + z_probe_height + " ;\tProbe point " + i + "\nG30 P2\n";
		}
		
		document.getElementById("gcode").innerHTML = document.getElementById("gcode").innerHTML + "G28 ; Finished\nM320 S2 ; Activates auto level permanently\n\n";

		
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

## Implementation in Repetier code (does NOT work!!):

I added the following block into `commands.cpp` file, but it doesn't work properly:

```cpp
case 228: {
	long radius = 50; // Default radius. If you have custom Z-probe, feel free to use max radius
	float coils = 3.6; // Sets the number of turns the spiral makes
	int chord = 15; // distance between hops in mm
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

## Sample g-code (for bed with printable diameter of 160mm):

```
G28 ; Home
M322 ; Resets auto level matrix  (adding S3 will make change permanent)
M321 ; Deactivates auto level (adding S2 will make change permanent)
G28
G1 X0 Y0 Z28 ;	Probe point 0
G30 P2
G1 X-6.430 Y10.132 Z28 ;	Probe point 1
G30 P2
G1 X-14.273 Y0.076 Z28 ;	Probe point 2
G30 P2
G1 X-10.858 Y-12.002 Z28 ;	Probe point 3
G30 P2
G1 X0.108 Y-17.871 Z28 ;	Probe point 4
G30 P2
G1 X12.159 Y-15.113 Z28 ;	Probe point 5
G30 P2
G1 X20.024 Y-5.642 Z28 ;	Probe point 6
G30 P2
G1 X21.114 Y6.581 Z28 ;	Probe point 7
G30 P2
G1 X15.502 Y17.461 Z28 ;	Probe point 8
G30 P2
G1 X5.161 Y23.968 Z28 ;	Probe point 9
G30 P2
G1 X-7.018 Y24.651 Z28 ;	Probe point 10
G30 P2
G1 X-18.109 Y19.614 Z28 ;	Probe point 11
G30 P2
G1 X-25.783 Y10.171 Z28 ;	Probe point 12
G30 P2
G1 X-28.655 Y-1.641 Z28 ;	Probe point 13
G30 P2
G1 X-26.365 Y-13.569 Z28 ;	Probe point 14
G30 P2
G1 X-19.479 Y-23.563 Z28 ;	Probe point 15
G30 P2
G1 X-9.247 Y-30.075 Z28 ;	Probe point 16
G30 P2
G1 X2.683 Y-32.220 Z28 ;	Probe point 17
G30 P2
G1 X14.557 Y-29.811 Z28 ;	Probe point 18
G30 P2
G1 X24.763 Y-23.295 Z28 ;	Probe point 19
G30 P2
G1 X32.028 Y-13.612 Z28 ;	Probe point 20
G30 P2
G1 X35.527 Y-2.029 Z28 ;	Probe point 21
G30 P2
G1 X34.934 Y10.052 Z28 ;	Probe point 22
G30 P2
G1 X30.405 Y21.263 Z28 ;	Probe point 23
G30 P2
G1 X22.508 Y30.415 Z28 ;	Probe point 24
G30 P2
G1 X12.127 Y36.602 Z28 ;	Probe point 25
G30 P2
G1 X0.342 Y39.264 Z28 ;	Probe point 26
G30 P2
G1 X-11.690 Y38.212 Z28 ;	Probe point 27
G30 P2
G1 X-22.855 Y33.609 Z28 ;	Probe point 28
G30 P2
G1 X-32.168 Y25.926 Z28 ;	Probe point 29
G30 P2
G1 X-38.857 Y15.877 Z28 ;	Probe point 30
G30 P2
G1 X-42.404 Y4.341 Z28 ;	Probe point 31
G30 P2
G1 X-42.570 Y-7.724 Z28 ;	Probe point 32
G30 P2
G1 X-39.394 Y-19.364 Z28 ;	Probe point 33
G30 P2
G1 X-33.166 Y-29.695 Z28 ;	Probe point 34
G30 P2
G1 X-24.392 Y-37.971 Z28 ;	Probe point 35
G30 P2
G1 X-13.739 Y-43.623 Z28 ;	Probe point 36
G30 P2
G1 X-1.979 Y-46.289 Z28 ;	Probe point 37
G30 P2
G1 X10.069 Y-45.827 Z28 ;	Probe point 38
G30 P2
G1 X21.599 Y-42.307 Z28 ;	Probe point 39
G30 P2
G1 X31.868 Y-35.996 Z28 ;	Probe point 40
G30 P2
G1 X40.242 Y-27.327 Z28 ;	Probe point 41
G30 P2
G1 X46.224 Y-16.865 Z28 ;	Probe point 42
G30 P2
G1 X49.480 Y-5.263 Z28 ;	Probe point 43
G30 P2
G1 X49.848 Y6.780 Z28 ;	Probe point 44
G30 P2
G1 X47.340 Y18.564 Z28 ;	Probe point 45
G30 P2
G1 X42.127 Y29.425 Z28 ;	Probe point 46
G30 P2
G1 X34.527 Y38.772 Z28 ;	Probe point 47
G30 P2
G1 X24.977 Y46.113 Z28 ;	Probe point 48
G30 P2
G1 X14.004 Y51.078 Z28 ;	Probe point 49
G30 P2
G1 X2.193 Y53.433 Z28 ;	Probe point 50
G30 P2
G1 X-9.844 Y53.083 Z28 ;	Probe point 51
G30 P2
G1 X-21.503 Y50.072 Z28 ;	Probe point 52
G30 P2
G1 X-32.215 Y44.571 Z28 ;	Probe point 53
G30 P2
G1 X-41.470 Y36.870 Z28 ;	Probe point 54
G30 P2
G1 X-48.845 Y27.353 Z28 ;	Probe point 55
G30 P2
G1 X-54.011 Y16.480 Z28 ;	Probe point 56
G30 P2
G1 X-56.754 Y4.758 Z28 ;	Probe point 57
G30 P2
G1 X-56.969 Y-7.278 Z28 ;	Probe point 58
G30 P2
G1 X-54.669 Y-19.093 Z28 ;	Probe point 59
G30 P2
G1 X-49.974 Y-30.176 Z28 ;	Probe point 60
G30 P2
G1 X-43.105 Y-40.059 Z28 ;	Probe point 61
G30 P2
G1 X-34.368 Y-48.336 Z28 ;	Probe point 62
G30 P2
G1 X-24.139 Y-54.678 Z28 ;	Probe point 63
G30 P2
G1 X-12.847 Y-58.839 Z28 ;	Probe point 64
G30 P2
G1 X-0.954 Y-60.671 Z28 ;	Probe point 65
G30 P2
G1 X11.066 Y-60.118 Z28 ;	Probe point 66
G30 P2
G1 X22.745 Y-57.220 Z28 ;	Probe point 67
G30 P2
G1 X33.635 Y-52.104 Z28 ;	Probe point 68
G30 P2
G1 X43.332 Y-44.981 Z28 ;	Probe point 69
G30 P2
G1 X51.481 Y-36.130 Z28 ;	Probe point 70
G30 P2
G1 X57.795 Y-25.889 Z28 ;	Probe point 71
G30 P2
G1 X62.056 Y-14.638 Z28 ;	Probe point 72
G30 P2
G1 X64.126 Y-2.788 Z28 ;	Probe point 73
G30 P2
G1 X63.948 Y9.241 Z28 ;	Probe point 74
G30 P2
G1 X61.541 Y21.027 Z28 ;	Probe point 75
G30 P2
G1 X57.004 Y32.167 Z28 ;	Probe point 76
G30 P2
G1 X50.504 Y42.288 Z28 ;	Probe point 77
G30 P2
G1 X42.271 Y51.057 Z28 ;	Probe point 78
G30 P2
G1 X32.589 Y58.193 Z28 ;	Probe point 79
G30 P2
G1 X21.782 Y63.472 Z28 ;	Probe point 80
G30 P2
G1 X10.206 Y66.736 Z28 ;	Probe point 81
G30 P2
G1 X-1.765 Y67.893 Z28 ;	Probe point 82
G30 P2
G1 X-13.752 Y66.920 Z28 ;	Probe point 83
G30 P2
G1 X-25.382 Y63.858 Z28 ;	Probe point 84
G30 P2
G1 X-36.299 Y58.815 Z28 ;	Probe point 85
G30 P2
G1 X-46.176 Y51.955 Z28 ;	Probe point 86
G30 P2
G1 X-54.722 Y43.494 Z28 ;	Probe point 87
G30 P2
G1 X-61.690 Y33.694 Z28 ;	Probe point 88
G30 P2
G1 X-66.885 Y22.849 Z28 ;	Probe point 89
G30 P2
G1 X-70.165 Y11.281 Z28 ;	Probe point 90
G30 P2
G1 X-71.447 Y-0.675 Z28 ;	Probe point 91
G30 P2
G1 X-70.705 Y-12.676 Z28 ;	Probe point 92
G30 P2
G1 X-67.970 Y-24.385 Z28 ;	Probe point 93
G30 P2
G1 X-63.330 Y-35.477 Z28 ;	Probe point 94
G30 P2
G1 X-56.922 Y-45.650 Z28 ;	Probe point 95
G30 P2
G1 X-48.929 Y-54.632 Z28 ;	Probe point 96
G30 P2
G1 X-39.576 Y-62.186 Z28 ;	Probe point 97
G30 P2
G1 X-29.119 Y-68.119 Z28 ;	Probe point 98
G30 P2
G1 X-17.841 Y-72.281 Z28 ;	Probe point 99
G30 P2
G1 X-6.039 Y-74.572 Z28 ;	Probe point 100
G30 P2
G1 X5.977 Y-74.943 Z28 ;	Probe point 101
G30 P2
G1 X17.899 Y-73.393 Z28 ;	Probe point 102
G30 P2
G1 X29.423 Y-69.971 Z28 ;	Probe point 103
G30 P2
G1 X40.261 Y-64.771 Z28 ;	Probe point 104
G30 P2
G1 X50.148 Y-57.933 Z28 ;	Probe point 105
G30 P2
G1 X58.842 Y-49.632 Z28 ;	Probe point 106
G30 P2
G1 X66.137 Y-40.078 Z28 ;	Probe point 107
G30 P2
G1 X71.863 Y-29.509 Z28 ;	Probe point 108
G30 P2
G1 X75.889 Y-18.183 Z28 ;	Probe point 109
G30 P2
G1 X78.127 Y-6.373 Z28 ;	Probe point 110
G30 P2
G1 X78.532  Y5.640 Z28 ;	Probe point 111
G30 P2
G1 X77.103 Y17.575 Z28 ;	Probe point 112
G30 P2
G1 X73.882 Y29.155 Z28 ;	Probe point 113
G30 P2
G1 X68.949 Y40.115 Z28 ;	Probe point 114
G30 P2
G28 ; Finished
M320 S2 ; Activates auto level permanently
```
