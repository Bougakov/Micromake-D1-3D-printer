# Manual calibration using Repetier Host

This HOWTO was written for [Micromake users' group on Facebook](https://www.facebook.com/groups/173676226330714/) instead.

For a long time I wasn't able to print something with a footprint larger than 5cm on my Micromake D1. "Auto level" function in CURA never worked for me quite well. This is what I was getting with a (test plate model from Thingiverse)[http://www.thingiverse.com/thing:1549840] even with the best 0.04mm tolerance:

![Full plate test](https://raw.githubusercontent.com/Bougakov/Micromake-D1-3D-printer/master/images/leveling0.png)

And now I've managed to get this quality with 0.15mm layer even with full-plate prints:

![Full plate test](https://raw.githubusercontent.com/Bougakov/Micromake-D1-3D-printer/master/images/leveling1.jpg)

I was inspired by this video from Repetier project. Unfortunately, it relies on some commands that Micromake D1 doesn't support, so I'll be using just the part that describes measuring offsets of each vertical tower.

[![Video from Repetier](http://img.youtube.com/vi/L9URtv2LqKc/0.jpg)](http://www.youtube.com/watch?v=L9URtv2LqKc?t=5)

You will need:

* something long, like 30cm steel ruler or a piece of 30-40cm metal rod
* calculator (Windows #calc.exe# is just fine)
* any software that can send commands to COM port. I was using Repetier Host, but you can even use Arduino's *Serial monitor* - Just set the correct port speed (250 000 baud) and connect.
* [This brilliant online calculator](http://escher3d.com/pages/wizards/wizarddelta.php) (open it in new tab of your browser)
* 5-10 minutes of time

# Some theory

Delta printers have a lot of variables to play with:

![Rods and offsets](https://www.repetier.com/firmware/v092/images/deltacolumnnames2.png)

...and imperfections with lengths and towers misplaced by even a fraction of a degree can cause a lot of trouble:

Basically, calibration means solving an equation with **seven** variables: three endstop corrections, delta radius, two tower angular position corrections, and diagonal rod length. It is some serious math.

To make things worse, all those variables are poorly named. You might have got used with towers named X, Y and Z. To make things worse, the Cartesian axes in which the print head moves, are *also* named X, Y and Z. And, for some reason, towers are sometimes named A, B and C. And to seriously fuck your brain, the angles of tower placement (which are 90, 210 and 330 degrees), are also named A, B, and C. On top of that, some adjustments are measured in millimeters, and some - in motor steps. Don't ask me why.

![Names explained](https://raw.githubusercontent.com/Bougakov/Micromake-D1-3D-printer/master/images/Explainer.png)

## Step one - let's purge all autoleveling data your printer is storing

First, check that the tension of all three belts is satisfactory. If you are printing with ABS, make sure your printer is warmed up and you are conducting the measurements on the hot printer (because metal parts expand and dimensions slightly change). On the LCD screen select #Quick settings# -> #Preheat ABS# to do that.

If you are connected to COM port, fire this command:

~~~~
G28 ; Home
~~~~

It will tell the printer to home the printing head. Then use these:

~~~~
M321 ; Deactivates auto level (adding S2 parameter will make change permanent)
M322 ; Resets auto level matrix  (adding S3 parameter will make change permanent)
G33 R0 ; Resets bump map
~~~~

This will reset the printer completely. 

## Step two - measuring exact offsets of all three endstops:

Now let's bring all pulley to the 20cm height (or, at least, what your printer *believes* is 20cm height). "X0 Y0" tell the head to stay at the point with the coordinates of 0,0 and Z200 tells it to stay 200mm from below.

~~~~
G1 X0 Y0 Z200 ; Move extruder down to 20cm height
~~~~

Now comes the tricky part. Look at the picture above, and relative to the position of the LCD screen, decide which tower is X, which is Y, and which is Z. Put a paper sticker with a letter on each one - it helps.

Let's start with X tower. Place a rod firmly into the slot of the aluminum beam (I used steel ruler):

![Steel ruler](https://raw.githubusercontent.com/Bougakov/Micromake-D1-3D-printer/master/images/leveling1.jpg)

Next, run this command:

~~~~
M99 X0 ; Disables stepper motor for tower X for 10 seconds.
~~~~

Stepper motors for towers Y and Z will still work. But motor for tower X will turn off for 10 seconds and allow you to bring the pulley down, so it touches your metal rod (or ruler). Hold it firmly and wait till the stepper "wakes up". Then gently remove the rod.

Repeat the procedure for remaining towers:

~~~~
M99 Y0 ; Disables stepper motor for tower Y for 10 seconds.
M99 Z0 ; Disables stepper motor for tower Z for 10 seconds.
~~~~

At this step you don't really need to know the length of your rod (or ruler). You just ensured that the distance between each pulley and the bottom is uniform. 

Next, run this command:

~~~~
G132 S1 ; Calculates offsets  and stores them in EEPROM. Wreite them down!
~~~~

It will move all pulleys up, until they reach the endstops, and return something like this:

~~~~
Tower 1:16
Tower 2:0
Tower 3:83
~~~~

These are exact offsets measured by the printer. Write them down.

## Step three: measuring the printer height manually.

I also wanted to have the printer's height measured exactly. My printer has had a value of #329.260 Z max length [mm]# stored in memory. I added 2cm and rounded it up to 340mm and stored the new value in memory. (Use Machine -> Firmware configuration to change printer's settings in CURA)

Run these commands to first home the head and then move it down:

~~~~
G28 ; Home
G1 X0 Y0 Z20 ; Move extruder down to 30mm height
~~~~

The printer will move the print nozzle at what it *thinks* is 3cm distance from the glass. But since we've messed with the height parameter, the actual distance will be smaller. 

On the LCD screen select #Position# -> #Z position#. **Gently** turn the dial counter-clockwise to move the head down. Do it slowly!

Multiple advice on the web suggest using "paper test"

