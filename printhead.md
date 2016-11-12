# Proper assembly of the printing head

Today I decided to clean the hot end of my printer, for the first time since I bought Micromake D1. I found out that molten ABS leaked in every connection and I had to soak everything in acetone for hours to clean it. So I decided to study the subject and assemble the hot end properly this time.

The physics is like this: cold ABS filament has uniform diameter of 1.75mm:

![Cross-section of the hot end](https://raw.githubusercontent.com/Bougakov/Micromake-D1-3D-printer/master/images/printhead_3_prut1.jpg )

When warmed up, it expands slightly and becomes soft:

![Cross-section of the hot end](https://raw.githubusercontent.com/Bougakov/Micromake-D1-3D-printer/master/images/printhead_3_prut2.jpg )

When it reaches the temperature of about 245 degrees Celsius, it melts and goes off from the nozzle. **Basically, the expanded warm part of the filament works like a piston that fills entire diameter of the tube and pushes the molten ABS out**:

![Cross-section of the hot end](https://raw.githubusercontent.com/Bougakov/Micromake-D1-3D-printer/master/images/printhead_4_csection.png)

This **piston** is important for retract function to work properly. If the warm section of the filament inside the hot end tube is too long, printer can't retract the filament when necessary and leaves ugly traces like this:

![Tears of ABS](http://3dtoday.ru/upload/blog/377/41750f2cc979fef852661dcb5a4e1e95.jpeg)

So the goal is to make the distance where the ABS melts very **abupt**.

Here are the parts of the printing head. ABS melts on the short end of the threaded tube (on the inside it is made from Teflon, which makes the movement of ABS super smooth), and expands in the long end. Aluminum fins help to dissipate heat - dedicated fan cools them down with air all the time. **Our goal is to protect the thermal barrier tube from getting excessive heat and help it to cool down more efficiently.**

![Components](https://raw.githubusercontent.com/Bougakov/Micromake-D1-3D-printer/master/images/printhead_0_components.jpg)

Go to the nearest DIY store and buy a spool of the sandard Teflon tape used in plumbing (it costs less than $1). Teflon can easily withstand heat, it is a good insulator and it makes screwing and unscrewing super easy:

![Teflon tape](http://s.leroymerlin.ru/upload/catalog/img/7/4/11457225/800x800/11457225_1.jpg?v=3)

Wrap the short end of the tube in the 4cm of Teflon tape:

![Teflon wrap](https://raw.githubusercontent.com/Bougakov/Micromake-D1-3D-printer/master/images/printhead_1_teflon.jpg)

Gently apply some heatsink paste (the one that is used on computer CPUs) on the longer part. Make sure that the paste doesn't get inside the channel that delivers ABS:

![Heatsink paste](https://raw.githubusercontent.com/Bougakov/Micromake-D1-3D-printer/master/images/printhead_2_paste.jpg)

You can also apply the paste on the thread of the nozzle, and fill the chamber of thermal sensor and heating element with it. 

## Results:

* you have sealed all connections with Teflon and paste, molten ABS won't leak. *It will be very easy to disassemble later.*
* you have improved *retraction*
* you gave the thermal sensor *better reaction time* - thanks to the paste it will notice the changes in the temperature faster, giving you more stable flow of plastic
* heater will also work more efficiently - *temperature will be less volatile*, so fewer visual differences between layers
* nozzle itself will become hotter - *improving the emission of ABS*
