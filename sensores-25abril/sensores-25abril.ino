int a, b, c;

void setup() {
  //declaramos los pines
  pinMode(2,INPUT);
  pinMode(3,INPUT);
  pinMode(4,INPUT);
  Serial.begin(9600);
}

void loop() {
  //leemos la información de los pines y la imprimimos.
  a = digitalRead(2);
  b = digitalRead(3);
  c = digitalRead(4);
//delay(1000);
//  Serial.println(a);
//  Serial.println(b);
  //falta probar este sensor 
  Serial.println(c);
  delay(100);

  int i = 0;
  time1 = milis();
  if
  time2 = milis() - time1;
}
