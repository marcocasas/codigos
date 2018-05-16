volatile float velocidadRueda = 0;
volatile float contador;

void setup() {
    Serial.begin(9600);
    pinMode(LED_BUILTIN, OUTPUT); //Indicamos que el LED del Arduino será pin de salida.
    pinMode(5,INPUT);
    // Inicializa Timer1
    noInterrupts();          // deshabilitamos interrupciones globales
    TCCR1A = 0;     //Se asigna 0 a TCCR1A
    TCCR1B = 0;     //Lo mismo para TCCR1B
    TCNT1 = 0;
 
    //Se asigna la comparacion para el registro a la cuenta de reloj deseada (en este caso, para lograr contar un segundo).
    OCR1A = 15624; //en vez de 15624 = 1 segundo
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

/*
 * Con 1.23 volts y delay=200 funciona relativamente bien;
 */
void loop() {
  Serial.println(digitalRead(5));
  if(digitalRead(5) == 1) {
    //Serial.println(digitalRead(5));
    contador++;
  }
  //delay(200);
  Serial.println(contador);
  Serial.println(velocidadRueda);
}

ISR(TIMER1_COMPA_vect)
{
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    velocidadRueda = (contador/16);
    contador = 0;
}

//float determinaVelocidad() {
//  return 1.28;
//}

