#include <Servo.h>
Servo myservo;

void setup() {
  // put your setup code here, to run once:
  //Serial.begin(9600);
  myservo.attach(52);
  myservo.write(10);
  delay(350);//Let system settle
  myservo.write(45); //47 es nuestro centro.
  delay(350);
  myservo.write(90);
  delay(350);
}

void loop() {
}
