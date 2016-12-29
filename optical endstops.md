# Replacing pushbuttons with optical endstops

Work in progress. Check [Facebook group on Micromake](https://www.facebook.com/groups/173676226330714/) instead.

State | Optical endstop
--- | ---
Slit is clear | High (4V out of 5V)
Slit blocked | Low (0V)

Voltage changes across `VCC` and either `D0` or `A0`.

State | Caret pushbutton
--- | ---
Caret isn't touching the endstop button | Circuit is closed
Caret is homed (presses the button) | Connection is broken

State | Autolevel pushbutton probe
--- | ---
Effector touches the glass | Circuit is closed
Effector is in the air | Connection is broken
