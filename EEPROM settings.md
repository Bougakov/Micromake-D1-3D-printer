# EEPROM settings for Micromake D1

## This Arduino sketch wipes EEPROM clean:

~~~~
/*
 * EEPROM Clear
 *
 * Sets all of the bytes of the EEPROM to 0.
 * Please see eeprom_iteration for a more in depth
 * look at how to traverse the EEPROM.
 *
 * This example code is in the public domain.
 */

#include <EEPROM.h>

void setup() {
  // initialize the LED pin as an output.
  pinMode(13, OUTPUT);
  
  /***
    Iterate through each byte of the EEPROM storage.

    Larger AVR processors have larger EEPROM sizes, E.g:
    - Arduno Duemilanove: 512b EEPROM storage.
    - Arduino Uno:        1kb EEPROM storage.
    - Arduino Mega:       4kb EEPROM storage.

    Rather than hard-coding the length, you should use the pre-provided length function.
    This will make your code portable to all AVR processors.
  ***/

  for (int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);
  }

  // turn the LED on when we're done
  digitalWrite(13, HIGH);
}

void loop() {
  /** Empty loop. **/
}
~~~~

## These are factory EEPROM settings from Cura 15.04.0917:

~~~~
20:41:32.789 : M205
20:41:33.732 : EPR:2 75 250000 Baudrate
20:41:33.735 : EPR:0 1028 0 Language
20:41:33.738 : EPR:3 129 0.000 Filament printed [m]
20:41:33.740 : EPR:2 125 0 Printer active [s]
20:41:33.743 : EPR:2 79 0 Max. inactive time [ms,0=off]
20:41:33.745 : EPR:2 83 360000 Stop stepper after inactivity [ms,0=off]
20:41:33.748 : EPR:3 11 100.0000 Steps per mm
20:41:33.750 : EPR:3 23 200.000 Max. feedrate [mm/s]
20:41:33.753 : EPR:3 35 40.000 Homing feedrate [mm/s]
20:41:33.755 : EPR:3 39 20.000 Max. jerk [mm/s]
20:41:33.758 : EPR:3 133 0.000 X min pos [mm]
20:41:33.760 : EPR:3 137 0.000 Y min pos [mm]
20:41:33.763 : EPR:3 141 0.000 Z min pos [mm]
20:41:33.766 : EPR:3 145 90.000 X max length [mm]
20:41:33.768 : EPR:3 149 90.000 Y max length [mm]
20:41:33.771 : EPR:3 153 300.000 Z max length [mm]
20:41:33.773 : EPR:1 891 70 Segments/s for travel
20:41:33.777 : EPR:1 889 180 Segments/s for printing
20:41:33.780 : EPR:3 59 1000.000 Acceleration [mm/s^2]
20:41:33.782 : EPR:3 71 2000.000 Travel acceleration [mm/s^2]
20:41:33.785 : EPR:3 881 210.000 Diagonal rod length [mm]
20:41:33.787 : EPR:3 885 92.000 Horizontal rod radius at 0,0 [mm]
20:41:33.790 : EPR:3 925 90.000 Max printable radius [mm]
20:41:33.793 : EPR:1 893 100 Tower X endstop offset [steps]
20:41:33.796 : EPR:1 895 100 Tower Y endstop offset [steps]
20:41:33.798 : EPR:1 897 100 Tower Z endstop offset [steps]
20:41:33.801 : EPR:3 901 210.000 Alpha A(210):
20:41:33.805 : EPR:3 905 330.000 Alpha B(330):
20:41:33.808 : EPR:3 909 90.000 Alpha C(90):
20:41:33.810 : EPR:3 913 0.000 Delta Radius A(0):
20:41:33.813 : EPR:3 917 0.000 Delta Radius B(0):
20:41:33.816 : EPR:3 921 0.000 Delta Radius C(0):
20:41:33.819 : EPR:3 933 0.000 Corr. diagonal A [mm]
20:41:33.822 : EPR:3 937 0.000 Corr. diagonal B [mm]
20:41:33.825 : EPR:3 941 0.000 Corr. diagonal C [mm]
20:41:33.827 : EPR:3 1024 0.000 Coating thickness [mm]
20:41:33.831 : EPR:3 808 0.000 Z-probe height [mm]
20:41:33.834 : EPR:3 929 5.000 Max. z-probe - bed dist. [mm]
20:41:33.837 : EPR:3 812 5.000 Z-probe speed [mm/s]
20:41:33.840 : EPR:3 840 40.000 Z-probe x-y-speed [mm/s]
20:41:33.842 : EPR:3 800 0.000 Z-probe offset x [mm]
20:41:33.846 : EPR:3 804 0.000 Z-probe offset y [mm]
20:41:33.849 : EPR:3 816 0.000 Z-probe X1 [mm]
20:41:33.852 : EPR:3 820 0.000 Z-probe Y1 [mm]
20:41:33.855 : EPR:3 824 0.000 Z-probe X2 [mm]
20:41:33.857 : EPR:3 828 0.000 Z-probe Y2 [mm]
20:41:33.861 : EPR:3 832 4.300 Z-probe X3 [mm]
20:41:33.864 : EPR:3 836 0.000 Z-probe Y3 [mm]
20:41:33.867 : EPR:3 1036 0.000 Z-probe bending correction A [mm]
20:41:33.870 : EPR:3 1040 0.000 Z-probe bending correction B [mm]
20:41:33.873 : EPR:3 1044 0.000 Z-probe bending correction C [mm]
20:41:33.876 : EPR:0 880 0 Autolevel active (1/0)
20:41:33.879 : EPR:0 106 1 Bed Heat Manager [0-3]
20:41:33.883 : EPR:0 107 255 Bed PID drive max
20:41:33.885 : EPR:0 124 80 Bed PID drive min
20:41:33.889 : EPR:3 108 196.000 Bed PID P-gain
20:41:33.892 : EPR:3 112 33.020 Bed PID I-gain
20:41:33.895 : EPR:3 116 290.000 Bed PID D-gain
20:41:33.898 : EPR:0 120 255 Bed PID max value [0-255]
20:41:33.901 : EPR:0 1020 0 Enable retraction conversion [0/1]
20:41:33.905 : EPR:3 992 3.000 Retraction length [mm]
20:41:33.908 : EPR:3 1000 40.000 Retraction speed [mm/s]
20:41:33.912 : EPR:3 1004 0.000 Retraction z-lift [mm]
20:41:33.915 : EPR:3 1008 0.000 Extra extrusion on undo retract [mm]
20:41:33.919 : EPR:3 1016 20.000 Retraction undo speed
20:41:33.922 : EPR:3 200 150.000 Extr.1 steps per mm
20:41:33.925 : EPR:3 204 30.000 Extr.1 max. feedrate [mm/s]
20:41:33.928 : EPR:3 208 10.000 Extr.1 start feedrate [mm/s]
20:41:33.932 : EPR:3 212 4000.000 Extr.1 acceleration [mm/s^2]
20:41:33.935 : EPR:0 216 1 Extr.1 heat manager [0-3]
20:41:33.938 : EPR:0 217 150 Extr.1 PID drive max
20:41:33.941 : EPR:0 245 60 Extr.1 PID drive min
20:41:33.944 : EPR:3 218 24.0000 Extr.1 PID P-gain/dead-time
20:41:33.948 : EPR:3 222 0.8800 Extr.1 PID I-gain
20:41:33.951 : EPR:3 226 80.0000 Extr.1 PID D-gain
20:41:33.954 : EPR:0 230 255 Extr.1 PID max value [0-255]
20:41:33.957 : EPR:2 231 0 Extr.1 X-offset [steps]
20:41:33.960 : EPR:2 235 0 Extr.1 Y-offset [steps]
20:41:33.963 : EPR:2 290 0 Extr.1 Z-offset [steps]
20:41:33.966 : EPR:1 239 1 Extr.1 temp. stabilize time [s]
20:41:33.969 : EPR:1 250 150 Extr.1 temp. for retraction when heating [C]
20:41:33.972 : EPR:1 252 0 Extr.1 distance to retract when heating [mm]
20:41:33.976 : EPR:0 254 255 Extr.1 extruder cooler speed [0-255]
20:41:33.979 : EPR:3 246 0.000 Extr.1 advance L [0=off]
~~~~

## These are my personal EEPROM settings:

~~~~
20:41:32.789 : M205
20:41:33.732 : EPR:2 75 250000 Baudrate
20:41:33.735 : EPR:0 1028 0 Language
20:41:33.738 : EPR:3 129 0.000 Filament printed [m]
20:41:33.740 : EPR:2 125 0 Printer active [s]
20:41:33.743 : EPR:2 79 0 Max. inactive time [ms,0=off]
20:41:33.745 : EPR:2 83 360000 Stop stepper after inactivity [ms,0=off]
20:41:33.748 : EPR:3 11 100.0000 Steps per mm
20:41:33.750 : EPR:3 23 200.000 Max. feedrate [mm/s]
20:41:33.753 : EPR:3 35 40.000 Homing feedrate [mm/s]
20:41:33.755 : EPR:3 39 20.000 Max. jerk [mm/s]
20:41:33.758 : EPR:3 133 0.000 X min pos [mm]
20:41:33.760 : EPR:3 137 0.000 Y min pos [mm]
20:41:33.763 : EPR:3 141 0.000 Z min pos [mm]
20:41:33.766 : EPR:3 145 90.000 X max length [mm]
20:41:33.768 : EPR:3 149 90.000 Y max length [mm]
20:41:33.771 : EPR:3 153 300.000 Z max length [mm]
20:41:33.773 : EPR:1 891 70 Segments/s for travel
20:41:33.777 : EPR:1 889 180 Segments/s for printing
20:41:33.780 : EPR:3 59 1000.000 Acceleration [mm/s^2]
20:41:33.782 : EPR:3 71 2000.000 Travel acceleration [mm/s^2]
20:41:33.785 : EPR:3 881 210.000 Diagonal rod length [mm]
20:41:33.787 : EPR:3 885 92.000 Horizontal rod radius at 0,0 [mm]
20:41:33.790 : EPR:3 925 90.000 Max printable radius [mm]
20:41:33.793 : EPR:1 893 100 Tower X endstop offset [steps]
20:41:33.796 : EPR:1 895 100 Tower Y endstop offset [steps]
20:41:33.798 : EPR:1 897 100 Tower Z endstop offset [steps]
20:41:33.801 : EPR:3 901 210.000 Alpha A(210):
20:41:33.805 : EPR:3 905 330.000 Alpha B(330):
20:41:33.808 : EPR:3 909 90.000 Alpha C(90):
20:41:33.810 : EPR:3 913 0.000 Delta Radius A(0):
20:41:33.813 : EPR:3 917 0.000 Delta Radius B(0):
20:41:33.816 : EPR:3 921 0.000 Delta Radius C(0):
20:41:33.819 : EPR:3 933 0.000 Corr. diagonal A [mm]
20:41:33.822 : EPR:3 937 0.000 Corr. diagonal B [mm]
20:41:33.825 : EPR:3 941 0.000 Corr. diagonal C [mm]
20:41:33.827 : EPR:3 1024 0.000 Coating thickness [mm]
20:41:33.831 : EPR:3 808 0.000 Z-probe height [mm]
20:41:33.834 : EPR:3 929 5.000 Max. z-probe - bed dist. [mm]
20:41:33.837 : EPR:3 812 5.000 Z-probe speed [mm/s]
20:41:33.840 : EPR:3 840 40.000 Z-probe x-y-speed [mm/s]
20:41:33.842 : EPR:3 800 0.000 Z-probe offset x [mm]
20:41:33.846 : EPR:3 804 0.000 Z-probe offset y [mm]
20:41:33.849 : EPR:3 816 0.000 Z-probe X1 [mm]
20:41:33.852 : EPR:3 820 0.000 Z-probe Y1 [mm]
20:41:33.855 : EPR:3 824 0.000 Z-probe X2 [mm]
20:41:33.857 : EPR:3 828 0.000 Z-probe Y2 [mm]
20:41:33.861 : EPR:3 832 4.300 Z-probe X3 [mm]
20:41:33.864 : EPR:3 836 0.000 Z-probe Y3 [mm]
20:41:33.867 : EPR:3 1036 0.000 Z-probe bending correction A [mm]
20:41:33.870 : EPR:3 1040 0.000 Z-probe bending correction B [mm]
20:41:33.873 : EPR:3 1044 0.000 Z-probe bending correction C [mm]
20:41:33.876 : EPR:0 880 0 Autolevel active (1/0)
20:41:33.879 : EPR:0 106 1 Bed Heat Manager [0-3]
20:41:33.883 : EPR:0 107 255 Bed PID drive max
20:41:33.885 : EPR:0 124 80 Bed PID drive min
20:41:33.889 : EPR:3 108 196.000 Bed PID P-gain
20:41:33.892 : EPR:3 112 33.020 Bed PID I-gain
20:41:33.895 : EPR:3 116 290.000 Bed PID D-gain
20:41:33.898 : EPR:0 120 255 Bed PID max value [0-255]
20:41:33.901 : EPR:0 1020 0 Enable retraction conversion [0/1]
20:41:33.905 : EPR:3 992 3.000 Retraction length [mm]
20:41:33.908 : EPR:3 1000 40.000 Retraction speed [mm/s]
20:41:33.912 : EPR:3 1004 0.000 Retraction z-lift [mm]
20:41:33.915 : EPR:3 1008 0.000 Extra extrusion on undo retract [mm]
20:41:33.919 : EPR:3 1016 20.000 Retraction undo speed
20:41:33.922 : EPR:3 200 150.000 Extr.1 steps per mm
20:41:33.925 : EPR:3 204 30.000 Extr.1 max. feedrate [mm/s]
20:41:33.928 : EPR:3 208 10.000 Extr.1 start feedrate [mm/s]
20:41:33.932 : EPR:3 212 4000.000 Extr.1 acceleration [mm/s^2]
20:41:33.935 : EPR:0 216 1 Extr.1 heat manager [0-3]
20:41:33.938 : EPR:0 217 150 Extr.1 PID drive max
20:41:33.941 : EPR:0 245 60 Extr.1 PID drive min
20:41:33.944 : EPR:3 218 24.0000 Extr.1 PID P-gain/dead-time
20:41:33.948 : EPR:3 222 0.8800 Extr.1 PID I-gain
20:41:33.951 : EPR:3 226 80.0000 Extr.1 PID D-gain
20:41:33.954 : EPR:0 230 255 Extr.1 PID max value [0-255]
20:41:33.957 : EPR:2 231 0 Extr.1 X-offset [steps]
20:41:33.960 : EPR:2 235 0 Extr.1 Y-offset [steps]
20:41:33.963 : EPR:2 290 0 Extr.1 Z-offset [steps]
20:41:33.966 : EPR:1 239 1 Extr.1 temp. stabilize time [s]
20:41:33.969 : EPR:1 250 150 Extr.1 temp. for retraction when heating [C]
20:41:33.972 : EPR:1 252 0 Extr.1 distance to retract when heating [mm]
20:41:33.976 : EPR:0 254 255 Extr.1 extruder cooler speed [0-255]
20:41:33.979 : EPR:3 246 0.000 Extr.1 advance L [0=off]
~~~~

### Difference between those (diff of two XML files):

~~~~
  <?xml version="1.0" encoding="utf-8"?>

  <Repetier-Firmware-EEPROM>
    <epr pos='75' type='2' value='250000'>Baudrate</epr>
    <epr pos='1028' type='0' value='0'>Language</epr>
-   <epr pos='129' type='3' value='0.000'>Filament printed</epr>
-   <epr pos='125' type='2' value='0'>Printer active</epr>
+   <epr pos='129' type='3' value='2.297'>Filament printed</epr>
+   <epr pos='125' type='2' value='6408'>Printer active</epr>
    <epr pos='79' type='2' value='0'>Max. inactive time</epr>
    <epr pos='83' type='2' value='360000'>Stop stepper after inactivity</epr>
    <epr pos='11' type='3' value='100.0000'>Steps per mm</epr>
    <epr pos='23' type='3' value='200.000'>Max. feedrate</epr>
    <epr pos='35' type='3' value='40.000'>Homing feedrate</epr>
    <epr pos='39' type='3' value='20.000'>Max. jerk</epr>
    <epr pos='133' type='3' value='0.000'>X min pos</epr>
    <epr pos='137' type='3' value='0.000'>Y min pos</epr>
    <epr pos='141' type='3' value='0.000'>Z min pos</epr>
-   <epr pos='145' type='3' value='90.000'>X max length</epr>
-   <epr pos='149' type='3' value='90.000'>Y max length</epr>
-   <epr pos='153' type='3' value='300.000'>Z max length</epr>
+   <epr pos='145' type='3' value='75.000'>X max length</epr>
+   <epr pos='149' type='3' value='75.000'>Y max length</epr>
+   <epr pos='153' type='3' value='329.260'>Z max length</epr>
    <epr pos='891' type='1' value='70'>Segments/s for travel</epr>
    <epr pos='889' type='1' value='180'>Segments/s for printing</epr>
    <epr pos='59' type='3' value='1000.000'>Acceleration</epr>
    <epr pos='71' type='3' value='2000.000'>Travel acceleration</epr>
-   <epr pos='881' type='3' value='210.000'>Diagonal rod length</epr>
-   <epr pos='885' type='3' value='92.000'>Horizontal rod radius at 0,0</epr>
-   <epr pos='925' type='3' value='90.000'>Max printable radius</epr>
-   <epr pos='893' type='1' value='100'>Tower X endstop offset</epr>
-   <epr pos='895' type='1' value='100'>Tower Y endstop offset</epr>
-   <epr pos='897' type='1' value='100'>Tower Z endstop offset</epr>
+   <epr pos='881' type='3' value='228.400'>Diagonal rod length</epr>
+   <epr pos='885' type='3' value='98.630'>Horizontal rod radius at 0,0</epr>
+   <epr pos='925' type='3' value='75.000'>Max printable radius</epr>
+   <epr pos='893' type='1' value='93'>Tower X endstop offset</epr>
+   <epr pos='895' type='1' value='65'>Tower Y endstop offset</epr>
+   <epr pos='897' type='1' value='0'>Tower Z endstop offset</epr>
    <epr pos='901' type='3' value='210.000'>Alpha A(210):</epr>
-   <epr pos='905' type='3' value='330.000'>Alpha B(330):</epr>
+   <epr pos='905' type='3' value='329.650'>Alpha B(330):</epr>
    <epr pos='909' type='3' value='90.000'>Alpha C(90):</epr>
    <epr pos='913' type='3' value='0.000'>Delta Radius A(0):</epr>
    <epr pos='917' type='3' value='0.000'>Delta Radius B(0):</epr>
    <epr pos='921' type='3' value='0.000'>Delta Radius C(0):</epr>
    <epr pos='933' type='3' value='0.000'>Corr. diagonal A</epr>
    <epr pos='937' type='3' value='0.000'>Corr. diagonal B</epr>
    <epr pos='941' type='3' value='0.000'>Corr. diagonal C</epr>
    <epr pos='1024' type='3' value='0.000'>Coating thickness</epr>
    <epr pos='808' type='3' value='0.000'>Z-probe height</epr>
    <epr pos='929' type='3' value='5.000'>Max. z-probe - bed dist.</epr>
    <epr pos='812' type='3' value='5.000'>Z-probe speed</epr>
    <epr pos='840' type='3' value='40.000'>Z-probe x-y-speed</epr>
    <epr pos='800' type='3' value='0.000'>Z-probe offset x</epr>
    <epr pos='804' type='3' value='0.000'>Z-probe offset y</epr>
    <epr pos='816' type='3' value='0.000'>Z-probe X1</epr>
    <epr pos='820' type='3' value='0.000'>Z-probe Y1</epr>
    <epr pos='824' type='3' value='0.000'>Z-probe X2</epr>
    <epr pos='828' type='3' value='0.000'>Z-probe Y2</epr>
-   <epr pos='832' type='3' value='4.300'>Z-probe X3</epr>
+   <epr pos='832' type='3' value='0.000'>Z-probe X3</epr>
    <epr pos='836' type='3' value='0.000'>Z-probe Y3</epr>
    <epr pos='1036' type='3' value='0.000'>Z-probe bending correction A</epr>
    <epr pos='1040' type='3' value='0.000'>Z-probe bending correction B</epr>
    <epr pos='1044' type='3' value='0.000'>Z-probe bending correction C</epr>
-   <epr pos='880' type='0' value='0'>Autolevel active (1/0)</epr>
+   <epr pos='880' type='0' value='1'>Autolevel active (1/0)</epr>
    <epr pos='106' type='0' value='1'>Bed Heat Manager</epr>
    <epr pos='107' type='0' value='255'>Bed PID drive max</epr>
    <epr pos='124' type='0' value='80'>Bed PID drive min</epr>
    <epr pos='108' type='3' value='196.000'>Bed PID P-gain</epr>
    <epr pos='112' type='3' value='33.020'>Bed PID I-gain</epr>
    <epr pos='116' type='3' value='290.000'>Bed PID D-gain</epr>
    <epr pos='120' type='0' value='255'>Bed PID max value</epr>
    <epr pos='1020' type='0' value='0'>Enable retraction conversion</epr>
    <epr pos='992' type='3' value='3.000'>Retraction length</epr>
    <epr pos='1000' type='3' value='40.000'>Retraction speed</epr>
    <epr pos='1004' type='3' value='0.000'>Retraction z-lift</epr>
    <epr pos='1008' type='3' value='0.000'>Extra extrusion on undo retract</epr>
    <epr pos='1016' type='3' value='20.000'>Retraction undo speed</epr>
    <epr pos='200' type='3' value='150.000'>Extr.1 steps per mm</epr>
    <epr pos='204' type='3' value='30.000'>Extr.1 max. feedrate</epr>
    <epr pos='208' type='3' value='10.000'>Extr.1 start feedrate</epr>
    <epr pos='212' type='3' value='4000.000'>Extr.1 acceleration</epr>
    <epr pos='216' type='0' value='1'>Extr.1 heat manager</epr>
-   <epr pos='217' type='0' value='150'>Extr.1 PID drive max</epr>
+   <epr pos='217' type='0' value='140'>Extr.1 PID drive max</epr>
    <epr pos='245' type='0' value='60'>Extr.1 PID drive min</epr>
    <epr pos='218' type='3' value='24.0000'>Extr.1 PID P-gain/dead-time</epr>
    <epr pos='222' type='3' value='0.8800'>Extr.1 PID I-gain</epr>
    <epr pos='226' type='3' value='80.0000'>Extr.1 PID D-gain</epr>
    <epr pos='230' type='0' value='255'>Extr.1 PID max value</epr>
    <epr pos='231' type='2' value='0'>Extr.1 X-offset</epr>
    <epr pos='235' type='2' value='0'>Extr.1 Y-offset</epr>
    <epr pos='290' type='2' value='0'>Extr.1 Z-offset</epr>
    <epr pos='239' type='1' value='1'>Extr.1 temp. stabilize time</epr>
    <epr pos='250' type='1' value='150'>Extr.1 temp. for retraction when heating</epr>
    <epr pos='252' type='1' value='0'>Extr.1 distance to retract when heating</epr>
    <epr pos='254' type='0' value='255'>Extr.1 extruder cooler speed</epr>
    <epr pos='246' type='3' value='0.000'>Extr.1 advance L</epr>
  </Repetier-Firmware-EEPROM>
~~~~
