int a, b, c;

void setup() {
  // put your setup code here, to run once:
  pinMode(2,INPUT);
  pinMode(2,INPUT);
  pinMode(2,INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  a.digitalRead(2);
  a.digitalRead(2);
  a.digitalRead(2);
  Serial.print(a);
  Serial.print(b);
  Serial.print(c);
  delay(100);
}
