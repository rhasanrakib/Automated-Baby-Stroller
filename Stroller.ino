#include <NewPing.h>
#define power 9
#define front_trig_pin 7
#define front_echo_pin 8

#define left_trig_pin 2
#define left_echo_pin 4

#define right_trig_pin 12
#define right_echo_pin 13

#define MAX_DISTANCE 200
NewPing sonar(front_trig_pin, front_echo_pin, MAX_DISTANCE);
NewPing sonarL(left_trig_pin, left_echo_pin, MAX_DISTANCE);
NewPing sonarR(right_trig_pin, right_echo_pin, MAX_DISTANCE);

//Servo myservo;
boolean GoForward = false;
int distance = 100;
int speedSet = 0;
//Motor A
const int motorRightForward = 11;
const int motorRightBackward = 10;
//Motor B
const int motorLeftForward = 6;
const int motorLeftBackward = 5;
void setup() {
  pinMode(motorRightForward,OUTPUT);
  pinMode(motorRightBackward,OUTPUT);
  pinMode(motorLeftForward,OUTPUT);
  pinMode(motorLeftBackward,OUTPUT);
  pinMode(power,INPUT);
  distance = readPing(3);
  delay(100);
  Serial.begin(9600);
}
void loop() {
  int distanceR = 0;
  int distanceL = 0;
  int distanceF = 0;
  delay(40);
  if (distance <= 20)
  {
    moveStop();
    delay(100);
    moveBackward();
    delay(200);
    moveStop();
    delay(200);
    distanceR = lookRight();
    distanceL = lookLeft();
    distanceF = lookF();

    int RLdiff = distanceR - distanceL;
    if (RLdiff < 0)
      RLdiff = -1 * RLdiff;
    if(RLdiff<=5)
    {
      moveBackward();
      delay(500);
      if(distanceR>distanceL)
      {
        turnRight();
        delay(400);
      }
      else
      {
        turnRight();
        delay(400);
      }
    }


    if (distanceR >= distanceL)
    {
      turnRight();
      moveStop();
    }
    else
    {
      turnLeft();
      moveStop();
    }
  }
  else
  {
    moveForward();
  }
  distance = readPing(3);
}
int lookF()
{
  int distance = readPing(0);
  delay(50);
  return distance;
}
int lookRight()
{

  int distance = readPing(2);
  return distance;
}
int lookLeft()
{
  int distance = readPing(1);
  delay(50);
  return distance;
}
int readPing(int x) {
  int cm = 0;

  if (x == 1)
  {
    cm = sonarL.ping_cm();
    if (cm == 0)
    {
      cm = 250;
    }
  }
  else if (x == 2)
  {

    cm = sonarR.ping_cm();
    if (cm == 0)
    {
      cm = 250;
    }
  }
  else if (x == 0)
  {
    cm = sonar.ping_cm();
    if (cm == 0)
    {
      cm = 250;
    }
  }
  else if (x == 3)
  {

    int cmL = sonarL.ping_cm();
    if (cmL == 0)
    {
      cmL = 200;
    }
    int cmR = sonarR.ping_cm();
    if (cmR == 0)
    {
      cmR = 200;
    }
    int cmM = sonar.ping_cm();
    if (cmM == 0)
    {
      cmM = 200;
    }

    if (cmM <= 20 || cmL <= 20 || cmR <= 20)
    {
      cm = 10;
    }
    else
      cm = 200;
  }

  return cm;
}
void moveStop() {
  analogWrite(motorRightForward, 0);
  analogWrite(motorRightBackward, 0);
  analogWrite(motorLeftForward, 0);
  analogWrite(motorLeftBackward, 0);
}
void moveForward() {
  analogWrite(motorRightForward, 90);
  analogWrite(motorRightBackward, 0);
  analogWrite(motorLeftForward, 90);
  analogWrite(motorLeftBackward, 0);
}
void moveBackward() {
  analogWrite(motorRightForward, 0);
  analogWrite(motorRightBackward, 90);
  analogWrite(motorLeftForward, 0);
  analogWrite(motorLeftBackward, 90);
  delay(100);
}
void turnLeft() {
  analogWrite(motorRightForward, 90);
  analogWrite(motorRightBackward, 0);
  analogWrite(motorLeftForward, 0);
  analogWrite(motorLeftBackward, 90);
  delay(300);
  //moveBackward();
}
void turnRight() {
  analogWrite(motorRightForward, 0);
  analogWrite(motorRightBackward, 90);
  analogWrite(motorLeftForward, 90);
  analogWrite(motorLeftBackward, 0);
  delay(300);
  //moveBackward();
}
