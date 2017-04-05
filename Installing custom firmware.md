# Patching and installing Micromake D1 firmware (Repetier)

***Warning* - I used 1st generation Micromake board as reference. Mine is set to 32-microsteps mode with an onboard jumper. Your settings may differ, pay close attention to that. <!-- В качестве средства для отправки команд принтеру я использую Repetier Host. Если вы используете штатную программу CURA, ваши шаги будут немного отличаться.-->**

Micromake's main board is basically an Arduino with added circuitry - same processor plus drivers for motors and couple of MOSFETs to drive heater and hot bed. As any Arduino it can be reprogrammed using your PC and USB cable.

To reprogram your board, you'd need "Arduino IDE". You can download it for free from  https://www.arduino.cc/en/Main/Software (you will need "Windows installer" link). Download and install it.

Next you'd need source files for firmware itself. Micromake uses "Repetier" firmware from here - https://github.com/repetier/Repetier-Firmware, yet you can't just take it and apply. First, it needs to be tuned to match our printer's hardware. Second, you'd miss patches from Chinese makers of our board.

Your easiest option would be to grab the Chinese sources from official repository and tweak it. Get it from  https://drive.google.com/drive/folders/0B1DQUrzkDP-tNDU0NXhVcGhlc0k - use a file called `Micromake D1.zip`.

Unzip it to any location, but ensure that the target folder is named `Repetier`. Let's assume it is `c:\Repetier`. Lanch file called `Repetier.ino`.

Plug the board using USB-cable to your PC. In Arduino IDE go to the menu called `Tools` - `Board` and choose `Arduino/Genuino MEGA or MEGA 2560`. In `Tools` - `Port` choose the port that Windows has assigned to your printer (verify its name with Windows Device Manager if needed).

To ensure that you have downloaded everything correctly, hit `Ctrl+R`. You'd see commands running in the bottom of the window, and finally you'd see `Done compining` message and a summery like this: 

    Sketch uses 137,236 bytes (54%) of program storage space. Maximum is 253,952 bytes.
    Global variables use 6,984 bytes (85%) of dynamic memory, leaving 1,208 bytes for local variables. Maximum is 8,192 bytes.
    Low memory available, stability problems may occur.

If you got that that means you installed Arduino IDE right and downloaded firmware sources correctly.

## Let's patch the firmware

Main window of Arduino IDE would have many tabs - one per each file in the firmware. Locate the tab with `Commands.cpp` (don't confuse it with `Commands.h`!). Find these lines:

    case 30:
        { // G30 single probe set Z0
            uint8_t p = (com->hasP() ? (uint8_t)com->P : 3);

you will need to change `P : 3` to `P : 2`, so you'd get this:

    case 30:
        { // G30 single probe set Z0
            uint8_t p = (com->hasP() ? (uint8_t)com->P : 2);

This change is enough to make OpenDACT work with Repetier. If you don't want to change anything else, just skip the next section.

## Few more useful changes to the firmware

Once we started editing, we can add more useful tweaks. Switch to `Configuration.h` and use `Ctrl+H` to quickly locate the parts we will be editing:

### STARTUP_GCODE

This parameter lists g-codes that are executed each time you power on or reboot printer. It is empty by default, mine looks like this (commands are separated with `\n` sumbols):

    #define STARTUP_GCODE "M115\nM119\nG28\nM140 S115\nM105 X0\n\n"

I'll explain these one by one:

| Command | What it does: |
| --- | --- |
| `M115` | Prints firmware version to log window |
| `M119` | Checks the status of the endstops |
| `G28` | Homes the effector |
| `M140 S115` | Makes heated bed to warm up to 115 degrees (for ABS). *Warning! Don't leave your printer unattended!*  |
| `M105 X0` | Queries temperature sensors |

Reference with full list of commands can be found here: http://reprap.org/wiki/G-code

### Z_PROBE_REPETITIONS

By default the value of this parameter is `1` - probe checks the bed only once in the given point. Since our z-probe is shitty, change this to `3` to improve measurements. Printer will average the result and use that:

    #define Z_PROBE_REPETITIONS 3 // Repetitions for probing at one point.

### Z_PROBE_X1

Chinese makers of our printer for some reason did not include correct coordinates for default probe points. Replace their incorrect values with right ones (three pairs of coordinates make 6 lines of code):

    #define Z_PROBE_X1 0
    #define Z_PROBE_Y1 65
    #define Z_PROBE_X2 64.95
    #define Z_PROBE_Y2 -37.5
    #define Z_PROBE_X3 -64.95
    #define Z_PROBE_Y3 -37.5


### BEEPER

If you'd like to make your printer quieter, adjust the default beeps of the buzzer:

    #define BEEPER_SHORT_SEQUENCE 1,1
    #define BEEPER_LONG_SEQUENCE 2,2

### Temperature

If you own heated bed module, make sure the following line has one instead of zero::

    #define HAVE_HEATED_BED 1

### Correct value for `Delta diagonal rod`

For some strange reason Micromake comes with wrong value for diagonal rod length. Change it to correct value - from `210`mm to `217`mm:

    // Delta settings
    #if DRIVE_SYSTEM==DELTA
    /** \brief Delta rod length (mm)
    */
    #define DELTA_DIAGONAL_ROD 217 // mm

### Correct microstepping value

As I wrote earlier, my printer is set to 32 microsteps and 200 steps per mm. The following lines in the software match my hardware setup. Adjust yours according to your hardware:

    /** \brief Steps per rotation of stepper motor */
    #define STEPS_PER_ROTATION 200

    /** \brief Micro stepping rate of X, Y and Y tower stepper drivers */
    #define MICRO_STEPS 32

### Change text on welcome splash screen

Instead of "Micromake" you can display whatever you want. I suggest to edit this so you will ensure that your own version indeed replaced factory firmware. Edit these lines accordingly:

    #define UI_PRINTER_NAME "Micromake 2.0.?"
    #define UI_PRINTER_COMPANY "www.micromake.org"

## Uploading your patched firmware to printer

*Warning!* Save or write down your EEPROM settings before proceeding!.

After you've made your edits, press `Ctrl+U`. Your code will compile and will get uploaded to printer in 10-20 seconds. **Please test your printer by making the effector move a bit. If it moves twice faster or twice slower, double-check and fix microstepping settings and `steps per mm` value in EEPROM!** 

## How to revert everything back in case you broke things

Open CURA and upload default firmware - it shoud fix things for you immediately.
    
This article continues in "[Calibrating Micromake D1 using OpenDACT utility](https://github.com/Bougakov/Micromake-D1-3D-printer/blob/master/Calibrating%20Micromake%20D1%20with%20OpenDACT.md)"
