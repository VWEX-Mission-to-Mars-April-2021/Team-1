#include <NewPing.h>

#define ECHO_PIN     5
#define TRIGGER_PIN  4
#define MAX_DISTANCE_IN_CM  200
#define MAX_DISTANCE_TO_GROUND 15
#define TRIGGER_DOWN 13
#define ECHO_DOWN 17

const int LEFT_FEEDBACK = 2; 
const int RIGHT_FEEDBACK = 3;

volatile int leftMotorCounter = 0; // initiate counter to zero for start
volatile int rightMotorCounter = 0; // counter could always be reset
volatile int rightTurn = 130;
volatile int leftTurn = 130;


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
  int frontDistance = frontSonar.ping_cm();
  if (frontDistance <= 13) {
    TurnOffMotors();
    delay(500);
    Reverse();
    delay(2000);
    QuickLeft();
    delay(6500);
    QuickLeft();
    delay(NINETY_DEGREE_TURN_IN_MS);
    MoveForward();
    delay(1000);
    QuickLeft();
    delay(6500);
    exit(0);
    
  }
  
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

void MoveForward()
{
  TurnOnMotors();
  digitalWrite(RIGHT_REVERSE, LOW);
  digitalWrite(LEFT_REVERSE, LOW);
  
  digitalWrite(RIGHT_FORWARD, HIGH);
  digitalWrite(LEFT_FORWARD, HIGH);
}

void Reverse()
{ 
  TurnOnMotors();
  
  digitalWrite(RIGHT_FORWARD, LOW);
  digitalWrite(LEFT_FORWARD, LOW);
  
  digitalWrite(RIGHT_REVERSE, HIGH);
  digitalWrite(LEFT_REVERSE, HIGH);
}

void TurnOffMotors()
{  
  analogWrite(RIGHT_ENABLE, 0);
  analogWrite(LEFT_ENABLE, 0);
  
  digitalWrite(RIGHT_FORWARD,LOW);
  digitalWrite(LEFT_FORWARD,LOW);
  
  digitalWrite(RIGHT_REVERSE,LOW);
  digitalWrite(LEFT_REVERSE,LOW);
}

void TurnRight()
{
  analogWrite(LEFT_ENABLE,200);
  analogWrite(RIGHT_ENABLE,160);
}

void TurnLeft()
{
  analogWrite(RIGHT_ENABLE,200);
  analogWrite(LEFT_ENABLE,160);
}

void TurnOnMotors()
{
  analogWrite(LEFT_ENABLE, LEFT_TURN_SPEED);
  analogWrite(RIGHT_ENABLE, RIGHT_TURN_SPEED);
  
}

void LeftMotorISR(){
  leftMotorCounter++;
}
void RightMotorISR() {
  rightMotorCounter++;
}
//Void turn Quickly To Left
void QuickLeft(){
  digitalWrite(LEFT_FORWARD, LOW);
  digitalWrite(RIGHT_REVERSE, LOW);
  
  digitalWrite(LEFT_REVERSE, HIGH);
  digitalWrite(RIGHT_FORWARD, HIGH);  
}
