# Manual calibration using Repetier Host

This HOWTO was written for [Micromake users' group on Facebook](https://www.facebook.com/groups/173676226330714/) instead.

For a long time I wasn't able to print something with a footprint larger than 5cm on my Micromake D1. "Auto level" function in CURA never worked for me quite well. This is what I was getting with a (test plate model from Thingiverse)[http://www.thingiverse.com/thing:1549840] even with the best 0.04mm tolerance:

![Full plate test](https://raw.githubusercontent.com/Bougakov/Micromake-D1-3D-printer/master/images/leveling0.jpg)

And now I've managed to get this quality with 0.15mm layer even with full-plate prints:

![Full plate test](https://raw.githubusercontent.com/Bougakov/Micromake-D1-3D-printer/master/images/leveling1.jpg)

I was inspired by this video from Repetier project. Unfortunately, it relies on some commands that Micromake D1 doesn't support, so I'll be using just the part that describes measuring offsets of each vertical tower.

[![Video from Repetier](http://img.youtube.com/vi/L9URtv2LqKc/0.jpg)](http://www.youtube.com/watch?v=L9URtv2LqKc?t=5)

You will need:

* something long, like 30cm steel ruler or a piece of 30-40cm metal rod
* calculator (Windows #calc.exe# is just fine)
* any software that can send commands to COM port. I was using Repetier Host, but you can even use Arduino's *Serial monitor* - Just set the correct port speed (250 000 baud) and connect.
* [This brilliant online calculator)[http://escher3d.com/pages/wizards/wizarddelta.php]
* 5-10 minutes of time

# Some theory



# Step one - let's purge all autoleveling data your printer is storing



