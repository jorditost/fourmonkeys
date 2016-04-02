#include <Servo.h>  

Servo servo;
int servoPin = 9;
int step = 4;
int pos = 0;

void setup() { 
  servo.attach(servoPin);  
} 
 
void loop() {
  
  for(pos = 0; pos <= 180; pos += step) {
    servo.write(pos);
    delay(15);
  }
  
  for(pos = 180; pos >= 0; pos -= step) {                           
    servo.write(pos);
    delay(15);
  }
} 

