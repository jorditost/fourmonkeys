#include <Servo.h>

// Servo
Servo servo;
int servoPin = 9;
int servoStep = 1;
int servoValue = 0;

// Pressure Sensor
int pressurePin = A5;
int pressureValue = 0;
int pressureThreshold = 950;

// Smoothing
const int numReadings = 10;

int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;

int servoReadings[numReadings];      // the readings from the analog input
int servoReadIndex = 0;              // the index of the current reading
int servoTotal = 0;                  // the running total
int servoAverage = 0;

void setup() {
  // Serial initialization
  Serial.begin(9600);

  // initialize all the readings to 0:
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
    servoReadings[thisReading] = 0;
  }
  
  // Init servo
  servo.attach(servoPin);
}

void loop() {

  Serial.print("Sensure value: ");
  Serial.print(analogRead(pressurePin));
  
  // Read pressure
  pressureValue = normalizePressure(analogRead(pressurePin));
  
  // Map it to the servo range
  servoValue = map(pressureValue, 0, 1023, 0, 180);
  //servoValue = normalizeServo(servoValue);

  Serial.print(" / Pressure value: ");
  Serial.print(pressureValue);
  Serial.print(" / servo value: ");
  Serial.println(servoValue);

  // Change servo value
  servo.write(servoValue);

  delay(1);
}

int normalizePressure(int value) {
  
  // Check that we are above the threshold
  value = map(value, pressureThreshold, 1023-2, 0, 1023);
  value = (value < 0) ? 0 : value;

  // subtract the last reading:
  total = total - readings[readIndex];
  // read from the sensor:
  readings[readIndex] = value;
  // add the reading to the total:
  total = total + readings[readIndex];
  // advance to the next position in the array:
  readIndex = readIndex + 1;

  // if we're at the end of the array...
  if (readIndex >= numReadings) {
    // ...wrap around to the beginning:
    readIndex = 0;
  }

  // calculate the average:
  average = total / numReadings;

  return average;
}

int normalizeServo(int value) {
  
  // subtract the last reading:
  servoTotal = servoTotal - servoReadings[servoReadIndex];
  // read from the sensor:
  servoReadings[servoReadIndex] = servoValue;
  // add the reading to the total:
  servoTotal = servoTotal + servoReadings[servoReadIndex];
  // advance to the next position in the array:
  servoReadIndex = servoReadIndex + 1;

  // if we're at the end of the array...
  if (servoReadIndex >= numReadings) {
    // ...wrap around to the beginning:
    servoReadIndex = 0;
  }

  // calculate the average:
  servoAverage = servoTotal / numReadings;

  return servoAverage;
}

void bounceServo() {
  for(servoValue = 0; servoValue <= 180; servoValue += servoStep) {
    servo.write(servoValue);
    delay(15);
  } 
  for(servoValue = 180; servoValue >= 0; servoValue -= servoStep) {                           
    servo.write(servoValue);
    delay(15);
  }
}

