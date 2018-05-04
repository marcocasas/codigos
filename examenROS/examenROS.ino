/*
 * Implementacion de codigo examen en ROS.
 */
 
#include <ros.h>
//#include <iostream>
#include <geometry_msgs/Twist.h>
#include <std_msgs/Int32.h>
#include <Servo.h>
Servo myservo;

int fotoresistencia = 0;
int pin = 7;
uint8_t bits[5];  // buffer to receive data

#define TIMEOUT 10000
#define RATE_HZ 2

ros::NodeHandle nh;
geometry_msgs::Twist lecturas_msg;

void motorServoVel(const geometry_msgs::Twist &lecturas_msg) {
  if  (lecturas_msg.angular.x == 0) {
    myservo.write(90);
  } else {
    myservo.write(0);
  }
}

ros::Publisher chatter("/Sensores", &lecturas_msg);
ros::Subscriber <geometry_msgs::Twist> sub("/motorCPU", 1000, &motorServoVel);
//ros::Rate rate(RATE_HZ);

void setup() {
  Serial.begin(9600);
  myservo.attach(6);
  delay(700);

  nh.initNode();
  nh.advertise(chatter);
  nh.subscribe(sub);
}

void loop() {
  Temperatura();

  lecturas_msg.linear.x = bits[0];
  lecturas_msg.linear.y = bits[2];
  lecturas_msg.linear.z = analogRead(fotoresistencia);
  
  chatter.publish(&lecturas_msg);
  nh.spinOnce();
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
