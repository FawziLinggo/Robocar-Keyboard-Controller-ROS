#include <SoftwareSerial.h>
#include <ros.h>
#include <geometry_msgs/Twist.h>

#define BRAKE 0
#define CW    1
#define CCW   2
#define CS_THRESHOLD 15   // Definition of safety current (Check: "1.3 Monster Shield Example").

//MOTOR 1
#define MOTOR_A1_PIN 7
#define MOTOR_B1_PIN 8

//MOTOR 2
#define MOTOR_A2_PIN 4
#define MOTOR_B2_PIN 9

#define PWM_MOTOR_1 5
#define PWM_MOTOR_2 6

#define CURRENT_SEN_1 A2
#define CURRENT_SEN_2 A3

#define EN_PIN_1 A0
#define EN_PIN_2 A1

#define MOTOR_1 0
#define MOTOR_2 1

#define test 13

ros::NodeHandle node;
geometry_msgs::Twist msg;


void Stop()
{
  digitalWrite(MOTOR_A1_PIN, LOW);
  digitalWrite(MOTOR_B1_PIN, LOW);
  digitalWrite(MOTOR_A2_PIN, LOW);
  digitalWrite(MOTOR_B2_PIN, LOW);
}

void Right()
{
  digitalWrite(MOTOR_A1_PIN, LOW);
  digitalWrite(MOTOR_B1_PIN, HIGH);
  analogWrite(PWM_MOTOR_1, 150);
  digitalWrite(MOTOR_A2_PIN, LOW);
  digitalWrite(MOTOR_B2_PIN, LOW);
}

void Left()
{
  digitalWrite(MOTOR_A1_PIN, LOW);
  digitalWrite(MOTOR_B1_PIN, LOW);
  digitalWrite(MOTOR_A2_PIN, LOW);
  digitalWrite(MOTOR_B2_PIN, HIGH);
  analogWrite(PWM_MOTOR_2, 150);
}

void Reverse()
{
  digitalWrite(MOTOR_A1_PIN, HIGH);
  digitalWrite(MOTOR_B1_PIN, LOW);
  analogWrite(PWM_MOTOR_1, 150);
  digitalWrite(MOTOR_A2_PIN, HIGH);
  digitalWrite(MOTOR_B2_PIN, LOW);
  analogWrite(PWM_MOTOR_2, 150);
}

void Forward()
{
  digitalWrite(MOTOR_A1_PIN, LOW);
  digitalWrite(MOTOR_B1_PIN, HIGH);
  analogWrite(PWM_MOTOR_1, 150);
  digitalWrite(MOTOR_A2_PIN, LOW);
  digitalWrite(MOTOR_B2_PIN, HIGH);
  analogWrite(PWM_MOTOR_2, 150);
}

void roverCallBack(const geometry_msgs::Twist& cmd_vel)
{

  if(cmd_vel.linear.x > 0 && cmd_vel.angular.z == 0)
  {
    Forward(); //i
    analogWrite(EN_PIN_1, 255);
    analogWrite(EN_PIN_2, 255);
  }
  else
  {
    if(cmd_vel.linear.x == 0 && cmd_vel.angular.z > 0)
    {
      Left(); //j
      analogWrite(EN_PIN_1, 255);
      analogWrite(EN_PIN_2, 255);
    }
    else
    {
      if(cmd_vel.linear.x == 0 && cmd_vel.angular.z == 0)
      {
        Stop(); //k
        analogWrite(EN_PIN_1, 0);
      }
      else
      {
        if(cmd_vel.linear.x == 0 && cmd_vel.angular.z < 0)
        {
          Right(); //l
	  analogWrite(EN_PIN_1, 255);
	  analogWrite(EN_PIN_2, 255);
        }
        else
        {
          if(cmd_vel.linear.x < 0 && cmd_vel.angular.z == 0)
          {
            Reverse(); //,
            analogWrite(EN_PIN_1, 255);   
            analogWrite(EN_PIN_2, 255);
          }
          else
          {
            Stop(); //default
          }
        }
      }
    }
  }
}

ros::Subscriber <geometry_msgs::Twist> sub("cmd_vel", roverCallBack);


void setup()                         
{
  node.initNode();
  node.subscribe(sub);
  
  pinMode(test, OUTPUT);

  pinMode(MOTOR_A1_PIN, OUTPUT);
  pinMode(MOTOR_B1_PIN, OUTPUT);

  pinMode(MOTOR_A2_PIN, OUTPUT);
  pinMode(MOTOR_B2_PIN, OUTPUT);

  pinMode(PWM_MOTOR_1, OUTPUT);
  pinMode(PWM_MOTOR_2, OUTPUT);

  pinMode(CURRENT_SEN_1, OUTPUT);
  pinMode(CURRENT_SEN_2, OUTPUT);  

  pinMode(EN_PIN_1, OUTPUT);
  pinMode(EN_PIN_2, OUTPUT);

}

void loop()
{
  
  digitalWrite(test, LOW);

//  if(Serial.available())
//  {
//    BT1.print((char)Serial.read());
//  } 
//  if(BT1.available())
//  {
//    Serial.print((char)BT1.read());
//  }
  
  node.spinOnce(); 
  delay(1);
}
