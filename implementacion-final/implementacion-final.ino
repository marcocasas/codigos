#include <Servo.h>
//Gracias, Alexander!

#include <avr/io.h>
#include <ros.h>
#include <std_msgs/Float64.h>
////////
Servo myservo;

int a, b;
int estado = 10; //empieza en 10°
/*
 * Negro es uno
 * Blanco es cero
 */
//////////

const int ADELANTE = 9;
const int ATRAS = 10;
const int ENABLE = 8;
int vueltas = 0;
unsigned long tiempo1;
unsigned long tiempo2;
double vel = 0;
double error = 0;
double ki = 0.6833; //kt
double kp = 3.85;//1.0589;kb
double velDeseada = 2.8; //YA NO Esto se logra con 2.4 volts si se saca de la fuente 
double senalControl = 0;
double sumaErrores = 0;

/*
 * Xbee & ROS
 */
ros::NodeHandle  nh;
std_msgs::Float64 str_msg;
ros::Publisher chatter("chatter", &str_msg);

//Para ver a qué dirección se dirige.
std_msgs::Float64 dir;
ros::Publisher direccion("direccion", &dir);
 
void setup() {
  cli();
  TCCR5B = B00001111;
  TCNT5 = 240;
  TCCR5B |= (1 << WGM01); //Esto hace que vuelva a su valor de 240
  TIMSK5 |= (1 << OCIE0A); // enable timer compare interrupt
  pinMode(47,INPUT); //PIN QUE DISPARA RUTINA DE TIMER5 de ATMEGA
  //pinMode(18, INPUT); //previamente era 8.
  Serial.begin(9600);
  sei();
  pinMode(ADELANTE, OUTPUT); //ESTE SERA EL PIN PWM PARA INYECTAR VOLTAJE VARIABLE
  pinMode(ATRAS, OUTPUT);
  pinMode(ENABLE, OUTPUT);
  delay(2000);
  tiempo1 = millis();
  
  ////////////////
  //parte de los sensores infrarrojos
  Serial.begin(9600);
  myservo.attach(52);
  myservo.write(10);
  delay(200);//Let system settle
  myservo.write(45); //47 es nuestro centro.
  delay(200);
  myservo.write(90);
  delay(200);

  pinMode(2,INPUT);
  pinMode(3,INPUT);
  ////////////////////

  /*
   * ROS NODE HANDLER SETUP
   */
  nh.initNode();
  nh.advertise(chatter);
  nh.advertise(direccion);
}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(ENABLE, 255);  //controlar velocidad
  adelante();
  tiempo2 = millis();
  if(tiempo2-tiempo1>= 300)
  {
      vel = vueltas + (TCNT5-240.0)/16.0;
      if(vel>=0){
        Serial.print("La velocidad es de: ");
        Serial.print(vel); //vel*10 ??
        Serial.println(" rev/s");
        vueltas = 0;
        tiempo1 = tiempo2;
        TCNT5 = 240;
  
        //VelDeseada es el max de velocidad que nosotros queremos que tenga
        error = velDeseada - vel;
        sumaErrores += error;
        senalControl = kp*error + ki*sumaErrores;
        Serial.print("error: ");
        Serial.println(error);
  
        Serial.print("señalControl: ");
        Serial.println(senalControl);

        /*
        * PUBLISH ROS TOPIC
        */
        str_msg.data = vel;
        chatter.publish( &str_msg );
        nh.spinOnce();
      }
      else{
        vueltas = 0;
        tiempo1 = tiempo2;
        TCNT5 = 240;
      }

  }
  
  //////////////////
  //parte de la logica del servo
  a = digitalRead(2); //derecho
  b = digitalRead(3); //izquierdo
  
  Serial.print(a);
  Serial.println(b);
  //delay(70);
  LogicaServo(a,b);
  ///////////////////
}

void adelante()
{
  digitalWrite(ATRAS, LOW);
  analogWrite(ADELANTE,senalControl);
}

void atras()
{
  analogWrite(ADELANTE, senalControl);
  digitalWrite(ATRAS, HIGH);
}

void LogicaServo(int a,int b){
  
      if(a == 1) {
    if (b == 1) {
      if(estado != 45) {
        myservo.write(45);
        //delay(100);
        estado = 45;
        velDeseada = 2.8;

        dir.data = 0;
        direccion.publish( &dir );
        nh.spinOnce();
      }
    } else {
      if (estado != 10) {
        myservo.write(19);
        //delay(100);
        estado = 10;
        velDeseada = 1.0;

        dir.data = -1.0;
        direccion.publish( &dir );
        nh.spinOnce();
      }
    }
  } else {
    if (b == 1) {
        if(estado != 85) {
        myservo.write(75);
        //delay(100);
        estado = 85;
        velDeseada = 1.0;

        
        dir.data = 1.0;
        direccion.publish( &dir );
        nh.spinOnce();
      }
    } else {
      myservo.write(75);
      //delay(100);
      estado = 85;
      velDeseada = 1.0;
      
      
      dir.data = 1.0;
      direccion.publish( &dir );
      nh.spinOnce();
    }
  }
  
}

ISR(TIMER5_COMPA_vect){  
   vueltas++;
   //Serial.println(TCNT5);
   TCNT5 = 240;
}
