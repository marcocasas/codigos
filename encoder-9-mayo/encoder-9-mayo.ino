const byte ledPin = 13;
const byte interruptPin = 2; //Colocar el pin de la interrupcion.
volatile byte state = LOW;
volatile float velocidad;

/*
 * Variable volatil para contar cuantas veces leemos 1.
 */
volatile int contadorEncoder = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(interruptPin, INPUT_PULLUP);
  pinMode(A0,INPUT); //A0 es el pin del sensor encoder.
  
  attachInterrupt(digitalPinToInterrupt(interruptPin), obtenerVelocidad, CHANGE)

    /**
   * Bloque para seteo de Timer1 y contar 1's y 0's con el fin de
   * determinar la velocidad de giro de la rueda.
   * 
   * Usar el dos.
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
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(ledPin, state);

  /**
   * Rutina para contar las veces que es uno
   * 
   * Revisar que con ese valor funcione.
   */
   if(analogRead(A0) > 500) {
    contadorEncoder++;
   }
}

void obtenerVelocidad() {
  velocidad = contadorEncoder * (360/16) * 60 / 360;

  contadorEncoder = 0;
}
