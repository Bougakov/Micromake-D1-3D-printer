# Adding physical "shutdown" button to Orange Pi Zero

I use tiny $8.5 Linux computer called [Orange Pi Zero](http://ali.ski/0UX_QL) to manage my Micromake 3D printer. It is standalone and allows me to print without the need to have my PC left connected to printer all the time.

It has LAN and WiFi, and USB port that Micromake printer is plugged into. Tiny computer uses "DietPI" Linux distribution and runs [Repetier Server](https://www.repetier.com/repetier-server-download/).

![Board](https://images-na.ssl-images-amazon.com/images/I/71iiAjj4NYL._SX466_.jpg)

The only inconvenience is to shut this tiny computer off after each print. Usually I had to connect to it over SSH, type in my `root` password and send it `shutdown -t now` command. 

I decided I need a physical button to turn it off.

## Parts needed:

  * 100uF electrolytic capacitor
  * 10K to 100K resistor
  * pushbutton
  * few wires
  
## Wiring

![Pushbutton wiring](https://github.com/Bougakov/Micromake-D1-3D-printer/blob/master/Orange%20PI%20Zero/Pushbutton%20wiring.jpg?raw=true)

Use `GND`, `3.3V` and `GPIO 3` (number 15 on the schematics below) to wire parts to your board:

![Pinout](https://i.stack.imgur.com/O03j0.jpg)

Make sure everything is soldered properly, you don't want your board to shut down due to random spark in your circuit and ruin your 3D print!

## Software - prerequisites

Connect to Pi Zero over SSH and run these commands:

```
cd ~
git clone https://github.com/vladikoms/WiringOP-Zero.git
cd WiringOP-Zero
chmod +x ./build
./build
```

To test your setup, run `gpio mode 3 input && gpio read 3`. It shoud output `1`. Push the button, hold it, and repeat the command. It shoud output zero this time.

## Write a program to check the button state

Open `nano` editor and create a file called `~/zerobutton.c`. Copy and paste this code:

```
#include <stdio.h>
#include <wiringPi.h>
#include <stdlib.h>
int system(const char *command);
// Button connects between GPIO 3 (pin 15) and 3.3V
// as in pic #1 here: https://www.raspberrypi.org/forums/download/file.php?id=13147
int main (void)
{
        wiringPiSetup () ;
        pinMode (3, INPUT);
        // system("gpio mode 3 input");

        if (digitalRead (3) == LOW) {
                system("logger Something is wrong with button!");
                exit(0);
        }

        for (;;) {
                if (digitalRead (3) == LOW) {
                        system("logger Initiated shutdown from button");
                        system("shutdown -h now");
                        exit(0);
                } else {
                        // wait
                }
        }
        return 0 ;
}

/*
        Save this file as zerobutton.c
        Run "gcc -lwiringPi -lwiringPiDev -o zerobutton zerobutton.c"
        to compile and run "chmod +x ./zerobutton" to make it executable.
        To excute it in background run "sudo ./zerobutton &"
*/
```

Next, run the following commands to compile this little program into an executable file:

```
gcc -lwiringPi -lwiringPiDev -o zerobutton zerobutton.c
chmod +x ./zerobutton
```

To test it, run:

```
~/zerobutton &
tail -f /var/log/syslog
```

Once you'd press the button you will see a message `Initiated shutdown from button` appear and then SSH will disconnect as your board will shut down gracefully.

## Make the button checking program run automatically on each boot

Run `nano /etc/rc.local` to open boot script for editing. Add the following line to the bottom of it (notice the trailing `&` symbol!):

```
~/zerobutton &
```


