# Adding physical "shutdown" button to Orange Pi Zero

I use tiny $8.5 Linux computer called [Orange Pi Zero](http://ali.ski/0UX_QL) to manage my Micromake 3D printer. It is standalone and allows me to print without the need to have my PC left connected to printer all the time.

It has LAN and WiFi, and USB port that Micromake printer is plugged into. Tiny computer uses "DietPI" Linux distribution and runs [Repetier Server](https://www.repetier.com/repetier-server-download/).

![Board](https://images-na.ssl-images-amazon.com/images/I/71iiAjj4NYL._SX466_.jpg)

The only inconvenience is to shut this tiny computer off after each print. Usually I had to connect to it over SSH, type in my `root` password and send it `shutdown -t now` command. 

I decided I need a physical button to turn it off.

## Parts needed:

  * 100uF electrolytic capacitor
  * 10K resistor
  * pushbutton
  * few wires
  
## Wiring

![Pushbutton wiring]()

## Software - prerequisites

Connect to Pi Zero over SSH and run these commands:

```
git clone https://github.com/vladikoms/WiringOP-Zero.git
```
