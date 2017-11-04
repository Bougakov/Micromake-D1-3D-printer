# Using piezo disc as z-probe

![Schematics](http://3dtoday.ru/upload/main/0aa/0aa029e2c5641ebff3a33ed71cb2e249.png)

## Arduino sketch:

~~~~
#include <Average.h> // Source - https://github.com/MajenkoLibraries/Average 
Average<int> ave1(2); // We use an array of last N measurements and average them
Average<int> ave2(2);
Average<int> ave3(2);
Average<int> ave(2); // extra one to store xor of readings
Average<int> ave4(12); // Nozzle piezo is subject to extra noise because of movements, so more measurements are needed

#define DEBUG 0 // Comment out for production

#ifdef DEBUG
  const int interval = 100; // Microseconds between reading the value of the piezo sensor
#else
  const int interval = 1; 
#endif

const int ledPin = 13;      // LED is connected to digital pin 13
const int relayPin = 19;    // Optocoupler output is connected to digital pin 19 (marked as A5 on Arduino Nano)
const int piezoPin1 = A1;   // the piezos are connected to analog pins
const int piezoPin2 = A2; 
const int piezoPin3 = A3;
const int piezoPin4 = A4;

const bool useNozzlePiezo = 0; // Enables or ignores 4th piezo


const int threshold = 8;    // threshold value to decide when the detected sound is a knock or not
const int displayMax = 20;  // limits the upper reading in Serial monitor

int sensorReading1 = 0;     // variable to store the value read from the sensor pin
int sensorReading2 = 0; 
int sensorReading3 = 0;
int sensorReading4 = 0;

void setup() {
  pinMode(ledPin, OUTPUT); 
  pinMode(relayPin, OUTPUT);
  digitalWrite(ledPin, LOW); 
  digitalWrite(relayPin, LOW); 
  if (DEBUG == 1){
    Serial.begin(250000); // We send values to serial for debugging. Use Arduino's SERIAL PLOTTER feature 
  }
}

void loop() {
  sensorReading1 = analogRead(piezoPin1);
  sensorReading2 = analogRead(piezoPin2);
  sensorReading3 = analogRead(piezoPin3);
  if (useNozzlePiezo == 1) {
    sensorReading4 = analogRead(piezoPin4);
  } else {
    sensorReading4 = 0;    
  }
  ave1.push(sensorReading1); // We push fresh measurements to an array. Oldest measure gets discarded
  ave2.push(sensorReading2); 
  ave3.push(sensorReading3); 
  ave4.push(sensorReading4); 
  if (
      ( sensorReading1 >= threshold ) ||
      ( sensorReading2 >= threshold ) ||
      ( sensorReading3 >= threshold )  
    ) {
      ave.push(threshold);
    } else {
      ave.push(0);
    }
  if (DEBUG == 1){
    Serial.print(displayMax); // Dummy constant to keep the chart in SERIAL PLOTTER to scale
    Serial.print(",");  
    Serial.print(threshold); // Dummy - to show threshold on chart
    Serial.print(",");  
    if (sensorReading1 <= displayMax) {
      Serial.print(sensorReading1);
    } else {
      Serial.print(displayMax);
    }
    Serial.print(",");  
    if (sensorReading2 <= displayMax) {
      Serial.print(sensorReading2);
    } else {
      Serial.print(displayMax);
    }
    Serial.print(",");  
    if (sensorReading3 <= displayMax) {
      Serial.print(sensorReading3);
    } else {
      Serial.print(displayMax);
    }
    Serial.print(",");  
    if (sensorReading4 <= displayMax) {
      Serial.print(sensorReading4);
    } else {
      Serial.print(displayMax);
    }
    Serial.print(",");  
  }
  if (
      ( ave1.mean() >= threshold ) ||
      ( ave2.mean() >= threshold ) ||
      ( ave3.mean() >= threshold ) ||
//    (useNozzlePiezo != 0 && ( ave4.mean() >= threshold*20 )) // Nozzle pin is extra sensitive... 
      ( ave.mean() >= threshold )
    ) {
    if (DEBUG == 1){
      Serial.println(displayMax + 5); // for debugging. Once sensor value is over threshold over given time, output gets triggered and this fact is displayed on chart with separate line.
    }
    digitalWrite(ledPin, HIGH);
    digitalWrite(relayPin, HIGH);
    delayMicroseconds(50000); // waits 0.05 sec to make printer notice 
  } else {
    if (DEBUG == 1){
      Serial.println("0");
    }
    digitalWrite(ledPin, LOW);
    digitalWrite(relayPin, LOW);
  }
  if (DEBUG == 1){
    Serial.print(" "); 
  }
  sensorReading1 = 0;
  sensorReading2 = 0;
  sensorReading3 = 0;
  
  delayMicroseconds(interval); 
}
~~~~
