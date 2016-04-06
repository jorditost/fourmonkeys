#include <Servo.h>

// Servo
Servo servo;
int servoPin = 9;
int servoStep = 1;
int servoValue = 0;

int sensorValue = 0;     // here we store the current value from the pin
int ledpin = 13;         // build in LED
int piezopin = A0;       // the analog input pin
int threshold = 10;      // the knock threshold

int state;
int current;               // Current state of the button
byte previous = HIGH;
unsigned long firstTime; // how long since the button was first pressed

long millisBetweenKnocks = 0;
//long millis_held;        // How long the button was held (milliseconds)
//long secs_held;          // How long the button was held (seconds)
//long prev_secs_held;     // How long the button was held in the previous check

void setup(){

  pinMode(ledpin, OUTPUT); // set the pin 13 as output
  digitalWrite(ledpin, LOW); // turn it off
  Serial.begin(9600); // this is for seeing what values come in

  // Init servo
  servo.attach(servoPin);
}

void loop(){

  // Read knock
  sensorValue = analogRead(piezopin); // read the pieso
  //Serial.println(sensorValue); // write the result to the serial monitor
  
  // we check if the value is higher than our threshold
  if (sensorValue >= threshold) {
    current = HIGH;
    digitalWrite(ledpin, HIGH);

  } else {
    current = LOW;
    digitalWrite(ledpin, LOW);
  }

  // If the button state changes to pressed, remember the start time 
  if (current == LOW && previous == HIGH && (millis() - firstTime) > 200) {
    millisBetweenKnocks = (millis() - firstTime);
    firstTime = millis();
    Serial.print("KNOCK");
    updateServo(millisBetweenKnocks);
  }
  
  //millis_held = (millis() - firstTime);
  //secs_held = millis_held / 1000;

  previous = current;
  //prev_secs_held = secs_held;
}

void updateServo(long value) {

  value = (value > 3000) ? 0 : value;

  Serial.print(" - time: " + value);

  // Map it to the servo range
  servoValue = map(value, 0, 3000, 0, 180);

  Serial.print(" / servo value: ");
  Serial.println(servoValue);

  // Change servo value
  servo.write(servoValue);
}

