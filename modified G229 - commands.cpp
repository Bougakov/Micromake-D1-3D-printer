    case 229: {
        long radius = 50; // Default radius. If you have custom Z-probe, feel free to use max radius
        float offset = 0;
        int p = com->hasP() ? com->P : 0;
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
        int array_size = 0;
        if (com->hasP()) {
          array_size = 6; // elements
          const float position[array_size][2] = {
              {radius * sin((2 * M_PI * 4) / 6), radius * cos((2 * M_PI * 4) / 6)}, // Point 4 - X
              {radius * sin((2 * M_PI * 1) / 6), radius * cos((2 * M_PI * 1) / 6)}, // Point 1 - X opposite
              {radius * sin((2 * M_PI * 2) / 6), radius * cos((2 * M_PI * 2) / 6)}, // Point 2 - Y
              {radius * sin((2 * M_PI * 5) / 6), radius * cos((2 * M_PI * 5) / 6)}, // Point 5 - Y opposite
              {radius * sin((2 * M_PI * 0) / 6), radius * cos((2 * M_PI * 0) / 6)}, // Point 0 - Z
              {radius * sin((2 * M_PI * 3) / 6), radius * cos((2 * M_PI * 3) / 6)}  // Point 3 - Z opposite
          };
          float distance[array_size];
          Printer::moveTo(0, 0, Z_PROBE_BED_DISTANCE * 3 + EEPROM::zProbeHeight() , IGNORE_COORDINATE, oldFeedrate); // We want the nozzle to get to the bed faster so we travel most of the distance at normal speed and slow down when close
          offset = Printer::runZProbe(false, false, 1, false); // + Z_PROBE_BED_DISTANCE; // For some reason the first measurement returns bogus results so we discard it 
          if(offset == ILLEGAL_Z_PROBE)
            return false; // Without this firmware sometimes crashes with no apparent reason
          // Initial call to Printer::runZProbe is supposed to be with "TRUE" as first argument. But it crashes, so I call it with "false, false"        
          Printer::moveTo(position[0][0], position[0][1], Z_PROBE_BED_DISTANCE * 3 + EEPROM::zProbeHeight() , IGNORE_COORDINATE, oldFeedrate);
          Printer::moveTo(position[0][0], position[0][1], Z_PROBE_BED_DISTANCE * 3 + EEPROM::zProbeHeight() , IGNORE_COORDINATE, EEPROM::zProbeXYSpeed());
          distance[0] = Printer::runZProbe(false, false, Z_PROBE_REPETITIONS, false); 
          for (uint8_t i = 1; i < (array_size - 1); i++)
          {
            Printer::moveTo(position[i][0], position[i][1], Z_PROBE_BED_DISTANCE * 3 + EEPROM::zProbeHeight() , IGNORE_COORDINATE, oldFeedrate);
            Printer::moveTo(position[i][0], position[i][1], Z_PROBE_BED_DISTANCE * 3 + EEPROM::zProbeHeight() , IGNORE_COORDINATE, EEPROM::zProbeXYSpeed());
            distance[i] = Printer::runZProbe(false, false, Z_PROBE_REPETITIONS, false);
          }
          Printer::moveTo(position[(array_size - 1)][0], position[(array_size - 1)][1], Z_PROBE_BED_DISTANCE * 3 + EEPROM::zProbeHeight() , IGNORE_COORDINATE, oldFeedrate);
          Printer::moveTo(position[(array_size - 1)][0], position[(array_size - 1)][1], Z_PROBE_BED_DISTANCE * 3 + EEPROM::zProbeHeight() , IGNORE_COORDINATE, EEPROM::zProbeXYSpeed());
          distance[(array_size - 1)] = Printer::runZProbe(false, true, Z_PROBE_REPETITIONS, false); // Note "true" as 2nd argument
          Printer::updateCurrentPosition();
          // distance[(array_size - 1)] = Printer::zLength - Printer::currentPosition[Z_AXIS];
          Com::printArrayFLN(Com::tZProbeDistance, distance, array_size, 2);
        } else {        
          array_size = 10; // elements
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
          float distance[array_size];
          Printer::moveTo(0, 0, Z_PROBE_BED_DISTANCE * 3 + EEPROM::zProbeHeight() , IGNORE_COORDINATE, oldFeedrate); // We want the nozzle to get to the bed faster so we travel most of the distance at normal speed and slow down when close
          offset = Printer::runZProbe(false, false, 1, false); // + Z_PROBE_BED_DISTANCE; // For some reason the first measurement returns bogus results so we discard it 
          if(offset == ILLEGAL_Z_PROBE)
            return false; // Without this firmware sometimes crashes with no apparent reason
          // Initial call to Printer::runZProbe is supposed to be with "TRUE" as first argument. But it crashes, so I call it with "false, false"        
          Printer::moveTo(position[0][0], position[0][1], Z_PROBE_BED_DISTANCE * 3 + EEPROM::zProbeHeight() , IGNORE_COORDINATE, oldFeedrate);
          Printer::moveTo(position[0][0], position[0][1], Z_PROBE_BED_DISTANCE * 3 + EEPROM::zProbeHeight() , IGNORE_COORDINATE, EEPROM::zProbeXYSpeed());
          distance[0] = Printer::runZProbe(false, false, Z_PROBE_REPETITIONS, false); 
          for (uint8_t i = 1; i < (array_size - 1); i++)
          {
            Printer::moveTo(position[i][0], position[i][1], Z_PROBE_BED_DISTANCE * 3 + EEPROM::zProbeHeight() , IGNORE_COORDINATE, oldFeedrate);
            Printer::moveTo(position[i][0], position[i][1], Z_PROBE_BED_DISTANCE * 3 + EEPROM::zProbeHeight() , IGNORE_COORDINATE, EEPROM::zProbeXYSpeed());
            distance[i] = Printer::runZProbe(false, false, Z_PROBE_REPETITIONS, false);
          }
          Printer::moveTo(position[(array_size - 1)][0], position[(array_size - 1)][1], Z_PROBE_BED_DISTANCE * 3 + EEPROM::zProbeHeight() , IGNORE_COORDINATE, oldFeedrate);
          Printer::moveTo(position[(array_size - 1)][0], position[(array_size - 1)][1], Z_PROBE_BED_DISTANCE * 3 + EEPROM::zProbeHeight() , IGNORE_COORDINATE, EEPROM::zProbeXYSpeed());
          distance[(array_size - 1)] = Printer::runZProbe(false, true, Z_PROBE_REPETITIONS, false); // Note "true" as 2nd argument
          Printer::updateCurrentPosition();
          // distance[(array_size - 1)] = Printer::zLength - Printer::currentPosition[Z_AXIS];
          Com::printArrayFLN(Com::tZProbeDistance, distance, array_size, 2);
        };
        Printer::feedrate = oldFeedrate;
        Printer::setAutolevelActive(oldAutolevel);
        Printer::updateCurrentPosition(true);
        printCurrentPosition(PSTR("229 "));
        GCode::executeFString(Com::tZProbeEndScript);
        Printer::homeAxis(true, true, true);
      }
      break;
