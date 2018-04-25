#include <ros.h>
//#include <std_msgs/String.h>
#include <geometry_msgs/Twist.h>
#include <Servo.h>
Servo myservo;

int fotoresistencia = 0;

int pin = 7;
int Te;
int H;
int L;
int pos;
uint8_t bits[5];  // buffer to receive data

#define TIMEOUT 10000

//Varibales globales para NodeHandle, mensajes utilizados y publicador.
ros::NodeHandle nh;
geometry_msgs::Twist vel;
ros::Publisher chatter("Sensores", &vel);

//Declaracion de la funcion callback.
 void motorServoVel(const geometry_msgs::Twist& vel) {
  ServoAngulo();
  //ServoAngulo(vel.angular.x);
 }

//Declaracion del suscriptor.
ros::Subscriber <geometry_msgs::Twist> sub("motorCPU", &motorServoVel);

void setup()
{
  Serial.begin(9600);
  //Necesario iniciar nodo y publicador aquí, así como suscribirse.
  nh.initNode();
  nh.advertise(chatter);
  nh.subscribe(sub);
}

void loop()
{
  //codigo de sensores
  Temperatura();
  vel.linear.x= bits[0]; //temperatura
  vel.linear.y= bits[2];
  vel.linear.z= bits[5];

  chatter.publish( &vel );
  nh.spinOnce(); //garantiza que se ejecute el suscriber
  delay(100);
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

void ServoAngulo() {
  Serial.print("hola");
}

//vel  x,y,z
//Angulx,y,z
