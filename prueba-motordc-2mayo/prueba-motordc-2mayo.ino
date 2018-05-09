//#include <Servo.h>
//Servo myservo;

int adelante = 9;
int atras = 10;
int enable = 8;
//int servoMotor = 6;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(adelante,OUTPUT);
  pinMode(atras,OUTPUT);
  pinMode(enable,OUTPUT);
//  myservo.attach(servoMotor);
//  myservo.write(10);
//  delay(350);//Let system settle
//  myservo.write(47); //47 es nuestro centro.
  delay(350);
}

void loop() {
  // put your main code here, to run repeatedly:
  //myservo.write(47);
  digitalWrite(enable,HIGH);
  delay(100);
  Serial.println(digitalRead(8));
  analogWrite(adelante,250);
  delay(1000);
//  Serial.println(analogRead(9));
//  analogWrite(atras,0);
//  delay(100);
//  Serial.println(analogRead(10));
//  digitalWrite(enable,LOW);
//  delay(200);
//  //myservo.write(0);
//  Serial.println(digitalRead(8));
//  analogWrite(atras,250);
//  analogWrite(adelante,0);
//  delay(200);
//  //myservo.write(80);
//  Serial.println(analogRead(9));
}

void turnServo() {
}

