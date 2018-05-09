#include <Servo.h>
Servo myservo;

void setup() {
  // put your setup code here, to run once:
  //Serial.begin(9600);
  myservo.attach(6);
  myservo.write(10);
  delay(350);//Let system settle
  myservo.write(47); //47 es nuestro centro.
  delay(350);
}

void loop() {
  // put your main code here, to run repeatedly:
 
}
