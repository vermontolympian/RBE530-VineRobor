#include <math.h>

/*---------------Module Defines-----------------------------*/
#define OFF               0
#define FORWARD           HIGH
#define REVERSE           LOW
#define GROWTH            HIGH
#define RETRACT           LOW

/*---------------Pin Declares-------------------------------*/
int motorPin    = 13;  // PWM output pin for rewinding motor
int motorDirPinA = 8;
int motorDirPinB = 9;

/*---------------Motor Dependent Parameters-----------------*/
int minGrowthSpeed  = 0; // Minimum speed required to allow growth
int minGrowthStop   = 0; // Minimum speed required to stop growth
int minRetractSpeed = 0; // Minimum speed required to start retraction

/*---------------Control Variables--------------------------*/
int motorSpeed   = 0;      // Controls the motor's speed from 0-255
int speedDelta   = 5;      // Controls the change in speed

bool vineState  = GROWTH; // Is the motor growing or retracting?
 



unsigned char key = ' ';

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(motorPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  key = Serial.read();

  if(key == 'W' || key == 'w'){
    motorSpeed = minGrowthSpeed;
    setEffort(motorSpeed);
    vineState = GROWTH;
    Serial.println("Growing");
  }

    if (key == 'S' || key == 's'){               //RETRACT, MOVE BACK  "RETREAT! WE'RE OUTNUMBERED"
    motorSpeed = minRetractSpeed;
    setEffort(-1 * motorSpeed);
    vineState = RETRACT;
     Serial.println("Retracting");
  }

  if (key == 'D' || key == 'd'){               //INCREASE SPEED      "MOAH SPEEEED!"
    motorSpeed += speedDelta;
    Serial.println(motorSpeed);
  }
  
  if (key == 'A' || key == 'a'){               //DECREASE SPEED      "WHOA, SLOW DOWN DUDE!"
    motorSpeed -= speedDelta;
    Serial.println(motorSpeed);
  }

  if (key == ' '){               //STOP                "DID YOU JUST MISS THE STOP SIGN, BUDDY?"
    halt();
    Serial.println("Hit the BRAKES!!!!");
  }
}

unsigned char TestForKey(void) {
  unsigned char KeyEventOccurred;
  
  KeyEventOccurred = Serial.available();
  return KeyEventOccurred;
}

// Tells the vine robot to grow at a particular motor speed
void grow(int motorSpeed){
    analogWrite(motorPin,motorSpeed); 
    digitalWrite(motorDirPin, FORWARD); 
}

// Tells the vine robot to retract at a particular motor speed
void retract(int motorSpeed){
    analogWrite(motorPin,motorSpeed); 
    digitalWrite(motorDirPin, REVERSE);
}

void halt(){
  digitalWrite(motorDirPinA, LOW);
  digitalWrite(motorDirPinB, LOW);
  analogWrite(motorPin, minGrowthStop)
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
    analogWrite(motorPin,motorSpeed)
  }
  else{
    digitalWrite(motorDirPinA, LOW);
    digitalWrite(motorDirPinB, HIGH);
    analogWrite(motorPin,motorSpeed)
  }
}
