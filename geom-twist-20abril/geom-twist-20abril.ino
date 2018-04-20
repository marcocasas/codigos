#include <ros.h>
//#include <std_msgs/String.h>
#include <geometry_msgs/Twist.h>

ros::NodeHandle nh;

std_msgs::Twist vel;

 void motorServoVel( const std_msgs::Twist& vel){
  ServoAngulo(vel.angular.x);

ros::Publisher chatter("Sensores", &vel);
ros::Subscriber<std_msgs::Twist> sub("motorCPU", &motorServoVel );
//char hello[13] = "hello world!";


void setup()
{
  nh.initNode();
  nh.advertise(chatter);
  nh.subscribe(sub);
}

void loop()
{
  //codigo de sensores
  vel.linear.x= temperatura;
  vel.linear.y= humedad;
  vel.linear.z= luz;

  chatter.publish( &vel );
  nh.spinOnce(); //garantiza que se ejecute el suscriber
  delay(100);
}

//vel  x,y,z
//Angulx,y,z
