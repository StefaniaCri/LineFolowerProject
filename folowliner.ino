#include <QTRSensors.h>

// Motor pins
const int m11Pin = 7;
const int m12Pin = 6;
const int m21Pin = 5;
const int m22Pin = 4;
const int m1Enable = 11;
const int m2Enable = 10;

// Motor speed
int m1Speed = 0;
int m2Speed = 0;

// PID variables
float kp = 15;
float ki = 0;
float kd = 30;


int p = 0;
int i = 0;
int d = 0;

float error = 0;
float lastError = 0;

const int maxSpeed = 255;
const int minSpeed = -255;

const int baseSpeed = 255;

QTRSensors qtr;

const int sensorCount = 6;
int sensorValues[sensorCount];
int sensors[sensorCount] = {0, 0, 0, 0, 0, 0};

int contorCalibration = 0;
unsigned long calibrationTime = 0;
// if selfCalibrateMood is true the robot use 
// selfCalibrate() for calibration,
// otherwise the calibration is made by human interaction
bool selfCalibrateMood = true; 
// selfCalibrate is a function that calibrates the Robot by moving left right through the black line
void selfCalibrate();
void manualCalibrate();

void pidControl(float kp, float ki, float kd);
void setMotorSpeed(int motor1Speed, int motor2Speed);

void setup() {
  // pinMode setup
  pinMode(m11Pin, OUTPUT);
  pinMode(m12Pin, OUTPUT);
  pinMode(m21Pin, OUTPUT);
  pinMode(m22Pin, OUTPUT);
  pinMode(m1Enable, OUTPUT);
  pinMode(m2Enable, OUTPUT);
  
  qtr.setTypeAnalog();
  qtr.setSensorPins((const uint8_t[]){A0, A1, A2, A3, A4, A5}, sensorCount);

  delay(500);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH); // turn on Arduino's LED to indicate we are in calibration mode
  // calibrate the sensor.
  if(selfCalibrateMood){
    selfCalibrate();
  }
  else{    
    manualCalibrate();
  }
  digitalWrite(LED_BUILTIN, LOW);

  Serial.begin(9600);   
}

void loop() {
  pidControl(kp, ki, kd);
}

// calculate PID value based on error, kp, kd, ki, p, i and d.
void pidControl(float kp, float ki, float kd) {
  int error = map(qtr.readLineBlack(sensorValues), 0, 5000, -30, 30);

  p = error;
  i = i + error;
  d = error - lastError;
  lastError = error;

  int motorSpeed = kp * p + ki * i + kd * d; // = error in this case
  
  m1Speed = baseSpeed;
  m2Speed = baseSpeed;

  // a bit counter intuitive because of the signs
  // basically in the first if, you substract the error from m1Speed (you add the negative)
  // in the 2nd if you add the error to m2Speed (you substract the negative)
  // it's just the way the values of the sensors and/or motors lined up
  if (error < 0) {
    m1Speed += motorSpeed;
  }
  else if (error > 0) {
    m2Speed -= motorSpeed;
  }
  // make sure it doesn't go past limits. You can use -255 instead of 0 if calibrated programmed properly.
  // making sure we don't go out of bounds
  // maybe the lower bound should be negative, instead of 0? This of what happens when making a steep turn
  m1Speed = constrain(m1Speed, m1Speed, maxSpeed);
  m2Speed = constrain(m2Speed, m2Speed, maxSpeed);


  setMotorSpeed(m1Speed, m2Speed);

  
//  DEBUGGING
//  Serial.print("Error: ");
//  Serial.println(error);
//  Serial.print("M1 speed: ");
//  Serial.println(m1Speed);
//
//  Serial.print("M2 speed: ");
//  Serial.println(m2Speed);
//
//  delay(250);
}


// each arguments takes values between -255 and 255. The negative values represent the motor speed in reverse.
void setMotorSpeed(int motor1Speed, int motor2Speed) {
  // remove comment if any of the motors are going in reverse 
  //  motor1Speed = -motor1Speed;
  //  motor2Speed = -motor2Speed;
  if (motor1Speed == 0) {
    digitalWrite(m11Pin, LOW);
    digitalWrite(m12Pin, LOW);
    analogWrite(m1Enable, motor1Speed);
  }
  else {
    if (motor1Speed > 0) {
      digitalWrite(m11Pin, HIGH);
      digitalWrite(m12Pin, LOW);
      analogWrite(m1Enable, motor1Speed);
    }
    if (motor1Speed < 0) {
      digitalWrite(m11Pin, LOW);
      digitalWrite(m12Pin, HIGH);
      analogWrite(m1Enable, -motor1Speed);
    }
  }
  if (motor2Speed == 0) {
    digitalWrite(m21Pin, LOW);
    digitalWrite(m22Pin, LOW);
    analogWrite(m2Enable, motor2Speed);
  }
  else {
    if (motor2Speed > 0) {
      digitalWrite(m21Pin, HIGH);
      digitalWrite(m22Pin, LOW);
      analogWrite(m2Enable, motor2Speed);
    }
    if (motor2Speed < 0) {
      digitalWrite(m21Pin, LOW);
      digitalWrite(m22Pin, HIGH);
      analogWrite(m2Enable, -motor2Speed);
    }
  }
}

void manualCalibrate()
{
  for (uint16_t i = 0; i < 400; i++){
    qtr.calibrate();
  }
}

void selfCalibrate()
{
   while (true) {
    qtr.calibrate();
    if(contorCalibration > 12){
      return; 
    }

    if(contorCalibration % 2 == 0)
    { // right left
      // setMotorSpeed(220, -240);
      setMotorSpeed(230, -250);
    }
    else{
      // setMotorSpeed(-255, 220);
      setMotorSpeed(-250, 240);
    }
    if(millis() - calibrationTime > 220)
    {
      contorCalibration ++;
      calibrationTime = millis();
    }
  }
}