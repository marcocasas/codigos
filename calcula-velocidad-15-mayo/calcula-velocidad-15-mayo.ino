//Gracias, Alexander!

#include <avr/io.h>
const int ADELANTE = 9;
const int ATRAS = 10;
const int ENABLE = 8;
int vueltas = 0;
unsigned long tiempo1;
unsigned long tiempo2;

void setup() {
  cli();
  TCCR5B = B00001111;
  TCNT5 = 240;
  TCCR5B |= (1 << WGM01); //Esto hace que vuelva a su valor de 240
  TIMSK5 |= (1 << OCIE0A); // enable timer compare interrupt
  pinMode(47,INPUT); //PIN QUE DISPARA RUTINA DE TIMER5 de ATMEGA
  //pinMode(18, INPUT); //previamente era 8.
  Serial.begin(9600);
  sei();
  pinMode(ADELANTE, OUTPUT);
  pinMode(ATRAS, OUTPUT);
  pinMode(ENABLE, OUTPUT);
  delay(2000);
  tiempo1 = millis();
}

ISR(TIMER5_COMPA_vect){  
   vueltas++;
   //Serial.println(TCNT5);
   TCNT5 = 240;
}
void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(ENABLE, 255);  
  adelante();
  tiempo2 = millis();
  if(tiempo2-tiempo1>= 1000)
  {
      double vel = vueltas + (TCNT5-240.0)/16.0;
      Serial.print("La velocidad es de: ");
      Serial.print(vel);
      Serial.println(" rev/s");
      vueltas = 0;
      tiempo1 = tiempo2;
      TCNT5 = 240;
  }
}
void adelante()
{
  digitalWrite(ATRAS, LOW);
  digitalWrite(ADELANTE, HIGH);
}
void atras()
{
  digitalWrite(ADELANTE, LOW);
  digitalWrite(ATRAS, HIGH);
}
