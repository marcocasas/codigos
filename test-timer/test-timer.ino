volatile float velocidadRueda;

void setup() {
    pinMode(LED_BUILTIN, OUTPUT); //Indicamos que el LED del Arduino será pin de salida.
 
    // Inicializa Timer1
    noInterrupts();          // deshabilitamos interrupciones globalss
    TCCR1A = 0;     //Se asigna 0 a TCCR1A
    TCCR1B = 0;     //Lo mismo para TCCR1B
    TCNT1 = 0;
 
    //Se asigna la comparacion para el registro a la cuenta de reloj deseada (en este caso, para lograr contar un segundo).
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
  
}

ISR(TIMER1_COMPA_vect)
{
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    velocidadRueda = determinaVelocidad();
}

float determinaVelocidad() {
  return 1.28;
}

