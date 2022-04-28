#include <math.h>
#include <arduino.h>

//Test

/*---------------Module Defines-----------------------------*/
#define OFF               0
#define FORWARD           HIGH
#define REVERSE           LOW
#define GROWTH            HIGH
#define RETRACT           LOW

/*---------------Pin Declares-------------------------------*/
int motorPin    = 11;  // PWM output pin for rewinding motor
int motorDirPinA = 8;
int motorDirPinB = 9;

/*---------------Motor Dependent Parameters-----------------*/
int minGrowthSpeed  = 0; // Minimum speed required to allow growth
int minGrowthStop   = 0; // Minimum speed required to stop growth
int minRetractSpeed = 0; // Minimum speed required to start retraction

/*---------------Control Variables--------------------------*/
int motorSpeed   = 0;      // Controls the motor's speed from 0-255
int speedDelta   = 10;      // Controls the change in speed

unsigned char key = ' ';

void setup() {
  Serial.begin(9600);

  pinMode(motorPin, OUTPUT);
  pinMode(motorDirPinA, OUTPUT);
  pinMode(motorDirPinB, OUTPUT);
}

void loop() {  
  key = Serial.read();

  if(key == 'W' || key == 'w'){
    motorSpeed = abs(motorSpeed);
    setEffort(motorSpeed);
    Serial.println("Growing");
  }

  if (key == 'S' || key == 's'){
    motorSpeed = abs(motorSpeed) * -1;
    setEffort(motorSpeed);
    Serial.println("Retracting");
  }

  if (key == 'D' || key == 'd'){
    motorSpeed += speedDelta;
    setEffort(motorSpeed);
    Serial.println(motorSpeed);
  }
  
  if (key == 'A' || key == 'a'){
    motorSpeed -= speedDelta;
    setEffort(motorSpeed);
    Serial.println(motorSpeed);
  }

  if (key == '0'){
    motorSpeed = 0;
    setEffort(motorSpeed);
    Serial.println("Speed = 0");
  }

  if (key == ' '){
    halt();
    Serial.println("Hit the BRAKES!!!!");
  }
}



//******FUNCTIONS******//

unsigned char TestForKey(void) {
  unsigned char KeyEventOccurred;
  
  KeyEventOccurred = Serial.available();
  return KeyEventOccurred;
}

void halt(){
  digitalWrite(motorDirPinA, LOW);
  digitalWrite(motorDirPinB, LOW);
  analogWrite(motorPin, minGrowthStop);
}


void setEffort(int motorSpeed){
  if(motorSpeed == 0){
    digitalWrite(motorDirPinA, LOW);
    digitalWrite(motorDirPinB, LOW);
    analogWrite(motorPin, minGrowthStop);
  }
  else if(motorSpeed > 0){
    digitalWrite(motorDirPinA, HIGH);
    digitalWrite(motorDirPinB, LOW);
    analogWrite(motorPin,motorSpeed);
  }
  else if(motorSpeed < 0){
    digitalWrite(motorDirPinA, LOW);
    digitalWrite(motorDirPinB, HIGH);
    analogWrite(motorPin,abs(motorSpeed));
  }
}




// OLD FUNCTIONS

/* // Tells the vine robot to grow at a particular motor speed
void grow(int motorSpeed){
    analogWrite(motorPin,motorSpeed); 
    digitalWrite(motorDirPin, FORWARD); 
}

// Tells the vine robot to `` at a particular motor speed
void retract(int motorSpeed){
    analogWrite(motorPin,motorSpeed); 
    digitalWrite(motorDirPin, REVERSE);
} */
