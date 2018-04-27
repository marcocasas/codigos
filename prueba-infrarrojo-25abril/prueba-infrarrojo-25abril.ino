int a, b, c;

void setup() {
  // put your setup code here, to run once:
  pinMode(2,INPUT);
  pinMode(3,INPUT);
  pinMode(A0,INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  a = digitalRead(2);
  b = digitalRead(3);
  c = analogRead(A0);
  Serial.print(a);
  Serial.println(b);
  Serial.println(c);
  delay(100);
}
