int a, b, c;

void setup() {
  //Asignamos pines donde están conectados sensores infrarrojos.
  pinMode(2,INPUT);
  pinMode(3,INPUT);
  pinMode(A0,INPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  /**
   * Bloque para seteo de Timer1 y contar 1's y 0's con el fin de
   * determinar la velocidad de giro de la rueda.
   */
  //Inicializa Timer1
  noInterrupts();          // deshabilitamos interrupciones globalss
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
  
  Serial.begin(9600);
}

void loop() {
  a = digitalRead(2);
  b = digitalRead(3);
  c = analogRead(A0);
  Serial.print(a);
  Serial.println(b);
  Serial.println(c);
  delay(100);
}

/**
 * Funcion que se ejecuta cuando se alcanza el valor en el registro.
 */
ISR(TIMER1_COMPA_vect)
{
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
}
