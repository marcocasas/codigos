#include <Servo.h>
Servo myservo;

int fotoresistencia = 0;

int pin = 7;
double humidity;
double temperature;
double light;
int Te;
int H;
int L;
int pos;
uint8_t bits[5];  // buffer to receive data

#define TIMEOUT 10000

void setup() {
  Serial.begin(9600);
  myservo.attach(6);
  Serial.println("Primera ejecucion");
  myservo.write(10);
  pos = 0;
  delay(350);//Let system settle
  Serial.println("Humidity and temperature\n\n");
  delay(700);//Wait rest of 1000ms recommended delay before
  //accessing sensor
}

void loop() {
  Temperatura();
  humidity	= bits[0];  // bit[1] == 0;
  temperature = bits[2];  // bits[3] == 0;
  light = analogRead(fotoresistencia);
  Serial.print("Current humidity = ");
  Serial.print(humidity);
  Serial.print("%  ");
  Serial.print("temperature = ");
  Serial.print(temperature);
  Serial.print("C  ");
  Serial.print("light = ");
  Serial.println(light);
  delay(1500);//Don't try to access too frequently... in theory
  //should be once per two seconds, fastest,
  //but seems to work after 0.8 second.

  turnServo();
}

void Temperatura(){
  uint8_t cnt = 7;
  uint8_t idx = 0;
  // EMPTY BUFFER
  for (int i=0; i< 5; i++) bits[i] = 0;

  // REQUEST SAMPLE
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
  delay(20);
  digitalWrite(pin, HIGH);
  delayMicroseconds(40);
  pinMode(pin, INPUT);

  // GET ACKNOWLEDGE or TIMEOUT
  unsigned int loopCnt = TIMEOUT;
  while(digitalRead(pin) == LOW)
	if (loopCnt-- == 0)
  	Serial.print("reini");
 	 
  loopCnt = TIMEOUT;
  while(digitalRead(pin) == HIGH)
	if (loopCnt-- == 0)  
  	Serial.print("reiniciar sens");
 
  for (int i=0; i<40; i++)
  {
	loopCnt = TIMEOUT;
	while(digitalRead(pin) == LOW)
  	if (loopCnt-- == 0)
    	Serial.print ("reiniciar sensor");
    
	unsigned long t = micros();
	loopCnt = TIMEOUT;
    
	while(digitalRead(pin) == HIGH)
  	if (loopCnt-- == 0)
    	Serial.print ("reiniciar");

	if ((micros() - t) > 40)
  	bits[idx] |= (1 << cnt);
	if (cnt == 0)   // next byte?
	{
  	cnt = 7;   
  	idx++; 	 
	}
	else cnt--;
  }
}

void turnServo() {
  if (temperature > 30) {
	Te = 1;
  } else {
	Te = 0;
  }

  if (humidity > 45) {
	H = 1;
  } else {
	H = 0;
  }

  if (light > 50) {
	L = 1;
  } else {
	L = 0;
  }
 
  if (Te == 1 && pos != 90) {
 	myservo.write(85);
 	pos = 90;
  }
  if(Te == 1 && pos == 90){
	pos = 90;
  } else {
	if (L==1 && H==1) {
  	if (pos == 90) {
    	pos = 90;
  	} else {
    	myservo.write(85);
    	pos = 90;
  	}
	} else {
  	if (pos == 0) {
    	pos = 0;
  	} else {
    	myservo.write(10);
    	pos = 0;
  	}
	}
  }
}




