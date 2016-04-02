//#include <Servo.h>

// Servo
//Servo servo;
int servoPin = 9;
int servoStep = 1;
int servoValue = 0;

// Pressure Sensor
int pressurePin = A5;
int pressureValue = 0;
int pressureThreshold = 0;

void setup() {
  // Serial initialization
  Serial.begin(9600);

  // Init servo
  //servo.attach(servoPin);  
}

void loop() {

  // Read pressure
  pressureValue = analogRead(pressurePin);

  Serial.print("Pressure value: ");
  Serial.println(pressureValue);
  
  /*for(servoValue = 0; servoValue <= 180; servoValue += servoStep) {
    servo.write(servoValue);
    delay(15);
  }
  
  for(servoValue = 180; servoValue >= 0; servoValue -= servoStep) {                           
    servo.write(servoValue);
    delay(15);
  }*/
} 

