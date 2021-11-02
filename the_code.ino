#include <Servo.h> 
#include <tcs3200.h>
const int trigPin = 10;
const int echoPin = 11;
int red;
int green;
int black;
String sensedColour = "none";
int delayTime = 0;
int leftMotorForward = A2;
int leftMotorBackward = A3;
int rightMotorForward = A4;
int rightMotorBackward = A5;
// Variables for the duration and the distance
long duration;
int distance;
int neardistance = 250;
int lastdistance ;
int targetangle;
int angle;
Servo myServo; // Creates a servo object for controlling the servo motor
tcs3200 sensor(4, 5, 6, 7, 8); //S0, S1, S2, S3, output pin
void setup() { 
  pinMode(leftMotorForward, OUTPUT);
  pinMode(leftMotorBackward, OUTPUT);
  pinMode(rightMotorForward, OUTPUT);
  pinMode(rightMotorBackward, OUTPUT);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600);
  red = sensor.colorRead('r', 20);   //Scaling the sensor to 20%
  myServo.attach(12); // Defines on which pin is the servo motor attached
  myServo.write(90);
}
void loop() {
  searching ();
  readColour();
  checkColour();
}

void searching(){
    // rotates the servo motor from 15 to 165 degrees
  for(int i=15;i<=165;i++){  
  myServo.write(i);
  delay(30);
  distance = getdistance();// Calls a function for calculating the distance measured by the Ultrasonic sensor for each degree
  angle = i;
  compare();  
  }
  // Repeats the previous lines from 165 to 15 degrees
  for(int i=165;i>15;i--){  
  myServo.write(i);
  delay(30);
  distance = getdistance();
  angle = i;
  compare();
  }
  decide();
}
// Function for calculating the distance measured by the Ultrasonic sensor
int getdistance(){   
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
  distance= duration*0.034/2;
  return distance;
}
void compare(){
  if ( distance < neardistance){
    neardistance = distance;
    targetangle = angle;
  }
}     
void decide(){
  if (targetangle >94 ){
    turnright();
    
  }
  if (targetangle < 86){
    turnleft();
  }
  if ( targetangle > 85 ){
    if (targetangle < 96){
    forward();
  }}
  
  
}
void turnright(){
  digitalWrite(leftMotorForward, HIGH);
  digitalWrite(rightMotorBackward, HIGH);
  delay(200);
  digitalWrite(leftMotorForward, LOW);
  digitalWrite(rightMotorBackward, LOW);
}
void turnleft(){
  digitalWrite(leftMotorBackward, HIGH);
  digitalWrite(rightMotorForward, HIGH);
  delay(200);
  digitalWrite(leftMotorBackward, LOW);
  digitalWrite(rightMotorForward, LOW);
}
void forward(){
  digitalWrite(leftMotorForward, HIGH);
  digitalWrite(rightMotorForward, HIGH);

}
//function to read the colour
void readColour() {
  red = sensor.colorRead('r');   //reads colour value for red
  green = sensor.colorRead('g');   //reads colour value for green
  black = sensor.colorRead('b');    //reads colour value for black  
  delay(10);  
}
//sets the colour that is sensed
void checkColour() {
  if (red > green and red > black and red > 8) {   //If the colour is red......
    sensedColour = "red";     //Sets the value of this variable to “red”
  }
  else if (green > red and green > black and green > 8) {   //If the colour is green......
    sensedColour = "green";     //Sets the value of this variable to “green”
    }
  else if (black > green and black > red and black > 8) {   //If the colour is black......
    sensedColour = "black";     //Sets the value of this variable to “black”
  }
}
