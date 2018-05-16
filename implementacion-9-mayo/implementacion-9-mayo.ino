#include <Servo.h>
Servo myservo;

int a, b, c;
//a izq (provisional: derecho)
//b der
int enable = 8;
int adelante = 9;
int atras = 10;
int servoPin = 52;
int estado = 10;

void setup() {
  //Asignamos pines donde están conectados sensores infrarrojos.
  pinMode(2,INPUT);
  pinMode(3,INPUT);
  pinMode(5,INPUT);
  pinMode(adelante,OUTPUT);
  pinMode(atras,OUTPUT);
  pinMode(enable,OUTPUT);
  
  pinMode(LED_BUILTIN, OUTPUT);

  delay(350);

  /**
   * Bloque para seteo de Timer1 y contar 1's y 0's con el fin de
   * determinar la velocidad de giro de la rueda.
   */
  //Inicializa Timer1
  noInterrupts();          // deshabilitamos interrupciones globales
  TCCR1A = 0;     //Se asigna 0 a TCCR1A
  TCCR1B = 0;     //Lo mismo para TCCR1B
  TCNT1 = 0;

  //Se asigna la comparacion para el registro a la cuenta de reloj deseada (en este caso, para contar un segundo).
  OCR1A = 15624;
  //Modo CTC:
  TCCR1B |= (1 << WGM12);
  //CS10 and CS12 bits para preescalar 1024:
  TCCR1B |= (1 << CS10);
  TCCR1B |= (1 << CS12);
  //Habilitar interrupcion de comparacion de timer:
  TIMSK1 |= (1 << OCIE1A);
  //Permitir interrupciones globales:
  interrupts();

  /*
  * Bloque para asignacion del servo motor. 
  */
  myservo.attach(servoPin);
  
  Serial.begin(9600);
}

void loop() {
  a = digitalRead(2);
  b = digitalRead(3);

  if(a == 1) {
    if (b == 1) {
      if(estado != 45) {
        myservo.write(45);
        estado = 45; 
      }
    } else {
      if (estado != 10) {
        myservo.write(10);
        estado = 10;
      }
    }
  } else {
    if (b == 1) {
      if(estado != 85) {
        myservo.write(85);
        estado = 85;
      }
    } else {
      myservo.write(85);
    }
  }
  
  c = digitalRead(5);
  Serial.print(a);
  Serial.println(b);
  Serial.println(c);
  delay(10);

//  //1 = veo la cinta (blanca)
//  
//  if (a==1) {
//    if(b == 0){
//    giraServoDerecha();
//    } else {
//      quedate();
//    }
//  } else {
//    if(b == 0) {
//      giraDerecha();
//    } else {
//      giraIzquierda();
//    }
//  }

    /*
   * Código del motor DC.
   */
  digitalWrite(enable,HIGH);
  delay(100);
  analogWrite(adelante,150);
  delay(1000);
//  Serial.println(analogRead(9));
//  analogWrite(atras,0);
//  delay(10);
//  Serial.println(analogRead(10));
//  digitalWrite(enable,LOW);
//  delay(2000);
//  Serial.println(digitalRead(8));
//  analogWrite(atras,250);
//  analogWrite(adelante,0);
//  delay(2000);
//  Serial.println(analogRead(9));
}

/**
 * Funcion que se ejecuta cuando se alcanza el valor en el registro.
 */
ISR(TIMER1_COMPA_vect)
{
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
}

//void giraServoDerecha() {
//  //Que gire a la derecha
//}

