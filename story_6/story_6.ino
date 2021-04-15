/*
  This program blinks pin 13 of the Arduino (the
  built-in LED)
*/

// help

const int LEFT_FEEDBACK = 2; // Pin numbers on Rover
const int RIGHT_FEEDBACK = 3;

volatile int leftMotorCounter = 0; // initiate counter to zero for start
volatile int rightMotorCounter = 0; // counter could always be reset
volatile int RightTurn = 130;
volatile int LeftTurn = 130;
volatile int Turns = 0;

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
  
}

void loop()
{
  // Print out left counter value until the motors reach 2 metres
  
  //if (millis() > 13,360){
    //TurnOffMotors();
  //}
  if (Turns == 4) {
    TurnOffMotors();
  }
  else
  {
    MoveForward();
    delay(2000);
    QuickLeft();
    delay(1335);
    Turns += 1;
  }
}

void AdjustSpeed()
{
  if (leftMotorCounter > rightMotorCounter){
    RightTurn = RightTurn + 1;
    analogWrite(RIGHT_ENABLE,RightTurn);
    LeftTurn = LeftTurn - 1;
    analogWrite(LEFT_ENABLE,LeftTurn);
    
    Serial.print("Right Counter: ");
    Serial.println(rightMotorCounter);
    Serial.println("---------------");
    Serial.print("Right Turn: ");
    Serial.println(RightTurn);
  }
  else if (rightMotorCounter > leftMotorCounter){
    LeftTurn = LeftTurn + 1;
    analogWrite(LEFT_ENABLE,LeftTurn);
    RightTurn = RightTurn - 1;
    analogWrite(RIGHT_ENABLE,RightTurn);
    
    Serial.print("Left Counter: ");
    Serial.println(leftMotorCounter);
    Serial.println("---------------");
    Serial.print("Left Turn: ");
    Serial.println(LeftTurn);
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
  
  //digitalWrite(RIGHT_FORWARD, HIGH);
  //digitalWrite(LEFT_FORWARD, LOW);
}

void TurnLeft()
{
  analogWrite(RIGHT_ENABLE,200);
  analogWrite(LEFT_ENABLE,160);
  //digitalWrite(LEFT_FORWARD, HIGH);
  //digitalWrite(RIGHT_FORWARD, LOW);
}

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
void QuickLeft(){
  digitalWrite(LEFT_FORWARD, LOW);
  digitalWrite(RIGHT_REVERSE, LOW);
  
  digitalWrite(LEFT_REVERSE, HIGH);
  digitalWrite(RIGHT_FORWARD, HIGH);  
}
