int DC_Motor_Pin = 9;    // DC Connect the motor to digital pin 9 times
int fadeValue;           // Speed Control

void setup() {
  Serial.begin(9600); // Serial initialization
  while(!Serial);         
  Serial.println("Init DC Motor example");
}

void loop() {
  
  for (int fadeValue = 0 ; fadeValue <= 255; fadeValue += 5) {
    analogWrite(DC_Motor_Pin, fadeValue);
    delay(30);
    Serial.print("To RIGHT - DC value : ");
    Serial.println(fadeValue);
  }

  for (int fadeValue = 255 ; fadeValue >= 0; fadeValue -= 5) {

    analogWrite(DC_Motor_Pin, fadeValue);
    delay(30);
    Serial.print("To LEFT - DC value : ");
    Serial.println(fadeValue);
  }
}

