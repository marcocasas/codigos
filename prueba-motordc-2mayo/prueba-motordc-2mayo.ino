#include <Servo.h>
Servo myservo;

int adelante = 9;
int atras = 10;
int enable = 8;
int servoMotor = 6;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(adelante,OUTPUT);
  pinMode(atras,OUTPUT);
  pinMode(enable,OUTPUT);
  myservo.attach(servoMotor);
}

void loop() {
  // put your main code here, to run repeatedly:
  myservo.write(45);
  digitalWrite(enable,HIGH);
  delay(10);
  Serial.println(digitalRead(8));
  analogWrite(adelante,250);
  delay(10);
  Serial.println(analogRead(9));
  analogWrite(atras,0);
  delay(10);
  Serial.println(analogRead(10));
  //digitalWrite(enable,LOW);
  delay(2000);
  myservo.write(0);
  Serial.println(digitalRead(8));
  analogWrite(atras,250);
  analogWrite(adelante,0);
  
  delay(2000);

  myservo.write(90);
  Serial.println(analogRead(9));
}
