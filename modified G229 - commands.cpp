/* This is replacement code section for Micromake's firmware - "commands.cpp" file.
   Micromake have modified Repetier firmware and added custom "G229" command.
   Their (also) modified CURA program sends this command to printer with parameter
   telling to perform auto-level on certain radius (for example, "G229 S50" tells it to
   probe 50mm circle).
   If you are not using CURA (by switching to OctoPrint or Repetier host), you don't need
   this custom command in its original form anymore. But you can replace it with this block
   of code and greatly simplify the manual calibration with Escher3d calculator
   https://github.com/Bougakov/Micromake-D1-3D-printer/blob/master/calibrating.md 
   Just send the command with radius parameter and printer will perform the series of
   measurements by itself. All you will be left to do is to write down 10 numbers and
   paste them in Escher3d.
   Look into the log and check for a line like this:

   Z-probe distance: 35.37 35.39 35.32 35.37 35.56 35.65 35.66 35.58 35.50 35.57

   These three numbers are "probe points" from 0 to 9.
   Before using double-check that the "Z-probe offset" is correctly entered into EEPROM in 
   case you have custom Z-probe.
   
   Be prepared that measurements will be well off in single direction (like mine 
   that are all 35mm off). I gave up fixing it - it is a flaw buried deep in the firmware.
   Escher3d handles it well, so it is easier to leave it be.   
   
   If you want to trade speed for more consistent results, change Z_PROBE_REPETITIONS in the 
   "configuration.h"   from 1 to about 3.
*/

    case 229: {
        long radius = 50; // Default radius. If you have custom Z-probe, feel free to use max radius
        float offset = 0;
        if (com->hasS() && com->S)
        {
          radius = com->S;
        }
        Printer::homeAxis(true, true, true); // First we home the extruder
        GCode::executeFString(Com::tZProbeStartScript);
        bool oldAutolevel = Printer::isAutolevelActive();
        Printer::setAutolevelActive(false);
        float oldFeedrate = Printer::feedrate;
        // I reverse-engineered the JavaScript on Esher3D to find out how it calculates the suggested probe points
        // Still, some of them are couple of mm off (rounding errors?) but I didn't investigate why.
        const float position[10][2] = {
            {radius * sin((2 * M_PI * 0) / 6), radius * cos((2 * M_PI * 0) / 6)}, // Point 0 
            {radius * sin((2 * M_PI * 1) / 6), radius * cos((2 * M_PI * 1) / 6)}, // Point 1 
            {radius * sin((2 * M_PI * 2) / 6), radius * cos((2 * M_PI * 2) / 6)}, // Point 2 
            {radius * sin((2 * M_PI * 3) / 6), radius * cos((2 * M_PI * 3) / 6)}, // Point 3 
            {radius * sin((2 * M_PI * 4) / 6), radius * cos((2 * M_PI * 4) / 6)}, // Point 4 
            {radius * sin((2 * M_PI * 5) / 6), radius * cos((2 * M_PI * 5) / 6)}, // Point 5 
            {radius / 2 * sin((2 * M_PI * (6 - 6)) / 3), radius / 2 * cos((2 * M_PI * (6 - 6))/3)}, // Point 6
            {radius / 2 * sin((2 * M_PI * (7 - 6)) / 3), radius / 2 * cos((2 * M_PI * (7 - 6))/3)}, // Point 7
            {radius / 2 * sin((2 * M_PI * (8 - 6)) / 3), radius / 2 * cos((2 * M_PI * (8 - 6))/3)}, // Point 8
            {0, 0} // Point 9 
        };
        float distance[10];
        Printer::moveTo(0, 0, Z_PROBE_BED_DISTANCE * 3 + EEPROM::zProbeHeight() , IGNORE_COORDINATE, oldFeedrate); // We want the nozzle to get to the bed faster so we travel most of the distance at normal speed and slow down when close
        offset = Printer::runZProbe(false, false, 1, false); // + Z_PROBE_BED_DISTANCE; // For some reason the first measurement returns bogus results so we discard it 
        if(offset == ILLEGAL_Z_PROBE)
          return false; // Without this firmware sometimes crashes with no apparent reason
        // Initial call to Printer::runZProbe is supposed to be with "TRUE" as first argument. But it crashes, so I call it with "false, false"        
        Printer::moveTo(position[0][0], position[0][1], Z_PROBE_BED_DISTANCE * 3 + EEPROM::zProbeHeight() , IGNORE_COORDINATE, oldFeedrate);
        Printer::moveTo(position[0][0], position[0][1], Z_PROBE_BED_DISTANCE * 3 + EEPROM::zProbeHeight() , IGNORE_COORDINATE, EEPROM::zProbeXYSpeed());
        distance[0] = Printer::runZProbe(false, false, Z_PROBE_REPETITIONS, false); 
        for (uint8_t i = 1; i < 9; i++)
        {
          Printer::moveTo(position[i][0], position[i][1], Z_PROBE_BED_DISTANCE * 3 + EEPROM::zProbeHeight() , IGNORE_COORDINATE, oldFeedrate);
          Printer::moveTo(position[i][0], position[i][1], Z_PROBE_BED_DISTANCE * 3 + EEPROM::zProbeHeight() , IGNORE_COORDINATE, EEPROM::zProbeXYSpeed());
          distance[i] = Printer::runZProbe(false, false, Z_PROBE_REPETITIONS, false);
        }
        Printer::moveTo(position[9][0], position[9][1], Z_PROBE_BED_DISTANCE * 3 + EEPROM::zProbeHeight() , IGNORE_COORDINATE, oldFeedrate);
        Printer::moveTo(position[9][0], position[9][1], Z_PROBE_BED_DISTANCE * 3 + EEPROM::zProbeHeight() , IGNORE_COORDINATE, EEPROM::zProbeXYSpeed());
        distance[9] = Printer::runZProbe(false, true, Z_PROBE_REPETITIONS, false); // Note "true" as 2nd argument
        Printer::updateCurrentPosition();
        // distance[9] = Printer::zLength - Printer::currentPosition[Z_AXIS];
        Com::printArrayFLN(Com::tZProbeDistance, distance, 10, 2);
        Printer::feedrate = oldFeedrate;
        Printer::setAutolevelActive(oldAutolevel);
        Printer::updateCurrentPosition(true);
        printCurrentPosition(PSTR("229 "));
        GCode::executeFString(Com::tZProbeEndScript);
        Printer::homeAxis(true, true, true);
      }
      break;
