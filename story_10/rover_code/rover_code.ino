#include <NewPing.h>

#define ECHO_PIN     5
#define TRIGGER_PIN  4
#define MAX_DISTANCE_IN_CM  200
<<<<<<< HEAD
#define MAX_DISTANCE_TO_GROUND 15
=======
#define MAX_DISTANCE_TO_GROUND 16
>>>>>>> 145e800d2d5dadf3b0efc2a828f11c6331fe1010
#define TRIGGER_DOWN 13
#define ECHO_DOWN 17

const int LEFT_FEEDBACK = 2; // Pin numbers on Rover
const int RIGHT_FEEDBACK = 3;

volatile int leftMotorCounter = 0; // initiate counter to zero for start
volatile int rightMotorCounter = 0; // counter could always be reset
volatile int rightTurn = 130;
volatile int leftTurn = 130;
volatile int turns = 0;

const int RIGHT_FORWARD = 12;
const int RIGHT_REVERSE = 11;
const int RIGHT_ENABLE = 10;
const int LEFT_ENABLE = 9;
const int LEFT_FORWARD = 8;
const int LEFT_REVERSE = 7;

const int FORWARD_IN_MILLISECONDS = 5000;
const int STOP_IN_MILLISECONDS = 1000;
const int REVERSE_IN_MILLISECONDS = 2000;

const int DELAY_TURN = 2000;

const int COUNTS_PER_METRE = 435;

const int LEFT_TURN_SPEED = 130;
const int RIGHT_TURN_SPEED = 130;
const int NINETY_DEGREE_TURN_IN_MS = 1300;

const int AIRWAVE_DELAY = 50;

NewPing frontSonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE_IN_CM);
NewPing downSonar(TRIGGER_DOWN, ECHO_DOWN, MAX_DISTANCE_IN_CM);

void setup()
{
  Serial.begin(115200);
  attachInterrupt(digitalPinToInterrupt(LEFT_FEEDBACK),LeftMotorISR,RISING);
  attachInterrupt(digitalPinToInterrupt(RIGHT_FEEDBACK),RightMotorISR,RISING);
  
  pinMode(RIGHT_FORWARD, OUTPUT);
  pinMode(LEFT_FORWARD, OUTPUT);
  
  pinMode(RIGHT_ENABLE, OUTPUT);
  pinMode(LEFT_ENABLE, OUTPUT);
  
  pinMode(RIGHT_REVERSE, OUTPUT);
  pinMode(LEFT_REVERSE, OUTPUT);

  frontSonar.ping_cm();
}

void loop()
{
  delay(AIRWAVE_DELAY);
  int downDistance = downSonar.ping_cm();
  /*
  int frontDistance = frontSonar.ping_cm();
  if (frontDistance <= 13) {
    TurnOffMotors();
    delay(500);
    Reverse();
    delay(1000);
    QuickLeft();
    delay(NINETY_DEGREE_TURN_IN_MS);
  }
<<<<<<< HEAD
=======
  */
>>>>>>> 145e800d2d5dadf3b0efc2a828f11c6331fe1010
  if (downDistance >= MAX_DISTANCE_TO_GROUND)
  {
    TurnOffMotors();
    delay(500);
    Reverse();
<<<<<<< HEAD
    delay(500);
    QuickLeft();
    delay(7800);
=======
    delay(1000);
    TurnOffMotors();
    exit(0);
>>>>>>> 145e800d2d5dadf3b0efc2a828f11c6331fe1010
  }
  MoveForward();
  delay(1000);
  QuickLeft();
  delay(NINETY_DEGREE_TURN_IN_MS);
}


//Adjustment of the speed of each motor to make the Rover be able to go forwards straight
void AdjustSpeed()
{
  if (leftMotorCounter > rightMotorCounter){
    rightTurn = rightTurn + 1;
    analogWrite(RIGHT_ENABLE, rightTurn);
    leftTurn = leftTurn - 1;
    analogWrite(LEFT_ENABLE, leftTurn);
    
    Serial.print("Right Counter: ");
    Serial.println(rightMotorCounter);
    Serial.println("---------------");
    Serial.print("Right Turn: ");
    Serial.println(rightTurn);
  }
  else if (rightMotorCounter > leftMotorCounter){
    leftTurn = leftTurn + 1;
    analogWrite(LEFT_ENABLE,leftTurn);
    rightTurn = rightTurn - 1;
    analogWrite(RIGHT_ENABLE,rightTurn);
    
    Serial.print("Left Counter: ");
    Serial.println(leftMotorCounter);
    Serial.println("---------------");
    Serial.print("Left Turn: ");
    Serial.println(leftTurn);
  }
}
// Void for Moving Forwards
void MoveForward()
{
  TurnOnMotors();
  digitalWrite(RIGHT_REVERSE, LOW);
  digitalWrite(LEFT_REVERSE, LOW);
  
  digitalWrite(RIGHT_FORWARD, HIGH);
  digitalWrite(LEFT_FORWARD, HIGH);
}
// Void for going in Reverse
void Reverse()
{ 
  TurnOnMotors();
  
  digitalWrite(RIGHT_FORWARD, LOW);
  digitalWrite(LEFT_FORWARD, LOW);
  
  digitalWrite(RIGHT_REVERSE, HIGH);
  digitalWrite(LEFT_REVERSE, HIGH);
}
//Turns Off the Motors, full halt
void TurnOffMotors()
{  
  analogWrite(RIGHT_ENABLE, 0);
  analogWrite(LEFT_ENABLE, 0);
  
  digitalWrite(RIGHT_FORWARD,LOW);
  digitalWrite(LEFT_FORWARD,LOW);
  
  digitalWrite(RIGHT_REVERSE,LOW);
  digitalWrite(LEFT_REVERSE,LOW);
}
//Turns right at a slight angle
void TurnRight()
{
  analogWrite(LEFT_ENABLE,200);
  analogWrite(RIGHT_ENABLE,160);
  
  //digitalWrite(RIGHT_FORWARD, HIGH);
  //digitalWrite(LEFT_FORWARD, LOW);
}

//Turns Left  at a slight angle
void TurnLeft()
{
  analogWrite(RIGHT_ENABLE,200);
  analogWrite(LEFT_ENABLE,160);
  //digitalWrite(LEFT_FORWARD, HIGH);
  //digitalWrite(RIGHT_FORWARD, LOW);
}

//Turns on the Motors via analog to set Turn Speed
void TurnOnMotors()
{
  analogWrite(LEFT_ENABLE, LEFT_TURN_SPEED);
  analogWrite(RIGHT_ENABLE, RIGHT_TURN_SPEED);
  
  //digitalWrite(RIGHT_ENABLE, HIGH);
  //digitalWrite(LEFT_ENABLE, HIGH);
}

void LeftMotorISR(){
  // adds one to the counter on each motor revolution
  leftMotorCounter++;
}
void RightMotorISR() {
  // adds one to the counter on each motor revolution
  rightMotorCounter++;
}
//Void turn Quickly To Left
void QuickLeft(){
  digitalWrite(LEFT_FORWARD, LOW);
  digitalWrite(RIGHT_REVERSE, LOW);
  
  digitalWrite(LEFT_REVERSE, HIGH);
  digitalWrite(RIGHT_FORWARD, HIGH);  
}
