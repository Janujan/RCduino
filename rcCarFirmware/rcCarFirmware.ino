#include <blueDevice.h>
#include <CommandHandler.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <SoftwareSerial.h>

#define turnSpeed 150
#define turnDelay 500
#define stopDelay 500
#define debug
int currentSpeed = 0;
#define maxSpeed 150
#define FORWARDMOTOR 4
#define TURNMOTOR 1

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61);

// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *myMotor = AFMS.getMotor(1);
Adafruit_DCMotor *backMotor = AFMS.getMotor(4);
// You can also make another motor on port M2
//Adafruit_DCMotor *myOtherMotor = AFMS.getMotor(2);

CommandHandler ch;
Bluetooth bt = Bluetooth(6,7);

void setup() {
  Serial.begin(9600); 
  ch.begin();  
  bt.start();

}

void loop() {
  // put your main code here, to run repeatedly:
  //readCommand();
  Serial.println("I am ready");
  while(Serial.available()){
    //parseCommand();
    readCommand();
  }
  
}

//--------------------------Turning Motor-------------------------------
//Green left, blue right
//Default for turning right

void turn( char direct )
{
  if ( direct == 'r' )
  {
    myMotor->run(FORWARD);
  }
  else {
    myMotor->run(BACKWARD);
  }
  myMotor->setSpeed(turnSpeed);
}


//Stop Turning
void stopTurn() {
  myMotor->run(RELEASE);
  delay(stopDelay);
}

//----------------------Movement Motor---------------------------------

//Move forward while ramping speed
void moveForward( char direct ) {
  if (direct == 'f')
  {
    backMotor->run(FORWARD);

    for (currentSpeed = 0; currentSpeed < maxSpeed; currentSpeed++) {
      backMotor->setSpeed(currentSpeed);
    }
  }
  else
  {
    backMotor->run(BACKWARD);

    for (currentSpeed = 0;  currentSpeed < maxSpeed; currentSpeed++) {
      backMotor->setSpeed(currentSpeed);
    }

  }

}


//Stop moving the back motor
void stopMovement( ) {

  for ( currentSpeed = maxSpeed; currentSpeed > 0; currentSpeed--) {
    backMotor->setSpeed(currentSpeed);
  }

  delay(stopDelay);

}


//---------------------------------Communicating with the Arduino using commands--------------------------------------
//LEGACY CODE DONT TOUCH
void readCommand( ) {

  char command = Serial.read( );

  switch (command) {
    case 'f':
      moveForward(command);
      break;

    case 'b':
      //moveBackward(command);
      break;

    case 'r':
      //turnRight();
      break;

    case 'l':
      //turnLeft();
      break;

    case 's':
      stopMovement();
      break;

    case 'i':
      stopTurn();
      break;
  }

}


//------------------------FLOW---------------------------------
/*
  1. Read the Serial through parseCommand
  2. Parse the motor, direction and delay
  3. Send to commandHandler
  4. commandHandler executes the program.


*/

//Parse the command sent in to the appropriate motor
/*
  Pattern:
  "#/x/time."
  # is for motor number (1 is turn, 4 is back)
  x is for command: [f,b,r,l]
  time is in milliseconds, 4 digits

*/
void parseCommand( )
{
  String command = Serial.readString();

  if (command == NULL) {
    return;
  }

  //String command = "1f1000";
  //End of the char array is always the null character \0
  char actualCommands[7];
  command.toCharArray(actualCommands, 7);
  int motor = actualCommands[0] - '0';
  char direct = actualCommands[1];
  String delayTime;

  for (int i = 2; i < 7; i++)
  {
    delayTime.concat(actualCommands[i]);
  }
   int parsedTime = delayTime.toInt();
  //commandHandler(motor, direct, delayTime.toInt());

  #ifdef debug
    Serial.print("Motor: ");
    Serial.print(motor);
    Serial.print(" Direction: ");
    Serial.print(direct);
    Serial.print(" Delay :");
    Serial.println(parsedTime);
  #endif
  
  ch.sendCommand( motor, direct, parsedTime);
}


/* LEGACY CODE DO NOT TOUCH
void commandHandler( int motor, char direct, int delayTime )
{
  if ( direct == 's' )
  {
    stopMovement();
  }
  else {
    if (motor == FORWARDMOTOR)
    {
      moveForward(direct);
      delay(delayTime);
    }
    else if (motor == TURNMOTOR)
    {
      turn(direct);
      delay(delayTime);

    }
    else {
      Serial.println("error in commandHandler");
      return;
    }
  }

}
*/
