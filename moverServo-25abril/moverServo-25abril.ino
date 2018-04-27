void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
 
    noInterrupts();          // deshabilitamos interrupciones globalss
    TCCR3A = 0;     //Se asigna 0 a TCCR1A
    TCCR3B = 0;     //Lo mismo para TCCR1B
    TCNT3 = 0;
  
    //Se asigna la comparacion para el registro a la cuenta de reloj deseada (en este caso, para contar un segundo).
    OCR3A = 15624;
    //Modo CTC:
    TCCR3B |= (1 << WGM32);
    //CS10 and CS12 bits para preescalar 1024:
    TCCR3B |= (1 << CS30);
    TCCR3B |= (1 << CS32);
    //Habilitar interrupcion de comparacion de timer:
    TIMSK3 |= (1 << OCIE3A);
    //Permitir interrupciones globales:
    interrupts();
    
    Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:

}

ISR(TIMER3_OVF_vect)
{
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
}
