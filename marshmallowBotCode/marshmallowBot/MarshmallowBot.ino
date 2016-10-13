
const int buttonPin = 8;     // the number of the pushbutton pin
const int catapultpin = 10; //catapult motor pin
const int encoderA = 9; //Encoder pin

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status
int encoderValue; //current value of motor encoder
int lastA; //Last encoder value
int currentA; //Current encoder value

int rightDirPinA = 5;
int rightDirPinB = 6;
int rightSpeedPin = 7;

int leftDirPinA = 3;
int leftDirPinB = 4;
int leftSpeedPin = 2;

void setup() {
  //set baud rate
  Serial.begin(9600);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  pinMode(catapultpin, OUTPUT);
  pinMode(encoderA, INPUT);
  //Initialize variables
  lastA = digitalRead(encoderA);
  encoderValue = 0;
}

void loop() {
  if (Serial.available() > 0) {
    char input = Serial.read();
    

    switch (input) {
      case 'a':
        Serial.print("turning left\n");
        rightMotorInstruct(1);
        leftMotorInstruct(-1);
        break;
      case 's':
        Serial.print("driving forwards\n");
        rightMotorInstruct(1);
        leftMotorInstruct(1);
        break;
        
      case 'd':
        Serial.print("turning right\n");
        rightMotorInstruct(-1);
        leftMotorInstruct(1);
        break;
      case 'w':
        Serial.print("reverse\n");
        rightMotorInstruct(-1);
        leftMotorInstruct(-1);
        break;
      case '0':
      case ' ':
        Serial.print("stop\n");
        rightMotorInstruct(0);
        leftMotorInstruct(0);
        break;
      case 'f':
        // read the state of the pushbutton value:
        while (encoderValue < 428) { //Until the encoder has gone through 200 ticks
          digitalWrite(catapultpin, HIGH);
          updateEncoder();
        }
        digitalWrite(catapultpin, LOW); //Stop
        encoderValue = 0; //Reset encoder
        break;
    }
  }
  //else{
  //  rightMotorInstruct(0);
  //  leftMotorInstruct(0);
  //  }

  /*// read the state of the pushbutton value:
    buttonState = digitalRead(buttonPin);
    if (buttonState == LOW) { //button is pressed
    while (encoderValue < 428) { //Until the encoder has gone through 200 ticks
      digitalWrite(catapultpin, HIGH);
      updateEncoder();
    }
    digitalWrite(catapultpin, LOW); //Stop
    encoderValue = 0; //Reset encoder
    }*/
}

//Update encoder value
void updateEncoder() {
  currentA = digitalRead(encoderA); //Get current value

  if (currentA != lastA) { //if last and current value don't agree
    encoderValue++; //Add one tick
    Serial.print(encoderValue); //Debugging
    Serial.print("\n");
  }

  //Update last value
  lastA = currentA;
}

//dir is -1, 0, 1, for backwards stop and forwards respectively
void rightMotorInstruct(int dir) {
  analogWrite(rightSpeedPin, abs(dir) * 255);
  if (dir == -1) {
    digitalWrite(rightDirPinA, HIGH);
    digitalWrite(rightDirPinB, LOW);
  }
  else {
    digitalWrite(rightDirPinA, LOW);
    digitalWrite(rightDirPinB, HIGH);
  }
}

void leftMotorInstruct(int dir) {
  analogWrite(leftSpeedPin, abs(dir) * 255);
  if (dir == -1) {
    digitalWrite(leftDirPinA, HIGH);
    digitalWrite(leftDirPinB, LOW);
  }
  else {
    digitalWrite(leftDirPinA, LOW);
    digitalWrite(leftDirPinB, HIGH);
  }
}
