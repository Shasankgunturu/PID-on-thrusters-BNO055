#include <ros.h>
#include <calypso_msgs/gypseas.h>
#include <Wire.h>
#include <Servo.h>

#define upper_limit 2000
#define lower_limit 1540
#define stop_sign 1500

Servo top_right_ser;
Servo bottom_right_ser; 
Servo top_left_ser;
Servo bottom_left_ser;

int bottom_right, bottom_left, top_right, top_left;

void pub_rpm(calypso_msgs::gypseas& rpms) {
  bottom_right = rpms.t3;
  bottom_left = rpms.t4;
  top_left = rpms.t1;
  top_right = rpms.t2;
}

ros::NodeHandle get_rpm;
ros::Subscriber<calypso_msgs::gypseas> rpm_sub("/thruster_gypsea", &pub_rpm);

void setup() {
  // put your setup code here, to run once:
  top_right_ser.attach(3);
  bottom_right_ser.attach(5);
  top_left_ser.attach(6);
  bottom_left_ser.attach(9);  

  get_rpm.initNode();
  
  top_right_ser.writeMicroseconds(stop_sign);
  bottom_right_ser.writeMicroseconds(stop_sign);
  top_right_ser.writeMicroseconds(stop_sign);
  bottom_left_ser.writeMicroseconds(stop_sign); 

  delay(5000);
}

void loop() {
  
  
  get_rpm.subscribe(rpm_sub);
  get_rpm.spinOnce();

  
  bottom_right_ser.writeMicroseconds(bottom_right);
  top_right_ser.writeMicroseconds(top_right);
  bottom_left_ser.writeMicroseconds(bottom_left);
  top_left_ser.writeMicroseconds(top_left);


}
