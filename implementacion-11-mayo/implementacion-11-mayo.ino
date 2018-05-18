#include <SD.h>

#include <Servo.h>
Servo myservo;

int a, b;
int estado = 10;

/*
 * Negro es uno
 * Blanco es cero
 */

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  myservo.attach(52);
  myservo.write(10);
  delay(200);//Let system settle
  myservo.write(45); //47 es nuestro centro.
  delay(200);
  myservo.write(90);
  delay(200);

  pinMode(2,INPUT);
  pinMode(3,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  a = digitalRead(2); //derecho
  b = digitalRead(3); //izquierdo
  //c = analogRead(A0);
  Serial.print(a);
  Serial.println(b);
  //Serial.println(c);
  delay(200);

    if(a == 1) {
    if (b == 1) {
      if(estado != 45) {
        myservo.write(45);
        delay(100);
        estado = 45; 
      }
    } else {
      if (estado != 85) {
        myservo.write(85);
        delay(100);
        estado = 85;
      }
    }
  } else {
    if (b == 1) {
        if(estado != 10) {
        myservo.write(10);
        delay(100);
        estado = 10;
      }
    } else {
      myservo.write(85);
      delay(100);
      estado = 85;
    }
  }
}
