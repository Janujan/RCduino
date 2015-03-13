#include "commandHandler.h"
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h"

//Define where your motors are located on motor shield
#define FMOTOR 4
#define LMOTOR 1

#define maxSpeed 150
#define turnSpeed 150
#define turnDelay 500
#define stopDelay 500

//Singleton Class
CommandHandler::CommandHandler()
{

}

//Empty Deconstructor
CommandHandler::~CommandHandler()
{

}

void CommandHandler::begin( )
{
	//Serial.println("making commandhandler");
    afms = Adafruit_MotorShield();
     //default frequency of 1600 Hz
    //exists = true;
    forwardMotor = afms.getMotor(FMOTOR);
    lateralMotor = afms.getMotor(LMOTOR);
    afms.begin();

}
void CommandHandler::sendCommand(int motor, char direct, int delayTime)
{

	_motor = motor;
	_direct = direct;
	_delayTime = delayTime;
      
	//Select whether to move forward or back
	switch(motor)
	{
		case 1:
			moveForward( direct, delayTime );
			Serial.println("moving forward");
			break;
		case 4:
			moveLateral( direct, delayTime);
			Serial.println("moving lateral");
			break;
		default:
			Serial.println("Motor not valid");
			break;
	};

}

//----------------------------------------MOVEMENT COMMANDS--------------------------------------------
void CommandHandler::moveForward(char direct, int delayTime)
{
	switch(direct)
	{
		case 'f':
			forwardMotor->run(FORWARD);
			break;

		case 'b':
			forwardMotor->run(BACKWARD);
			break;

		case 's':
			break;

		default:
			Serial.println("ERROR: direction is not valid");
			return;
	}

	if(direct == 's')
	{	
		//Ramp to a stop
		for(int i = currentSpeed; i > 0; i--)
		{
			forwardMotor->setSpeed(i);
		}
		currentSpeed=0;
	}

	else
	{
		//Ramp the speed
		for (currentSpeed = 0; currentSpeed < maxSpeed; currentSpeed++)
		{
      		forwardMotor->setSpeed(currentSpeed);
    	}
	}

}

void CommandHandler::moveLateral(char direct, int delayTime)
{

	switch(direct)
	{
		case 'r':
			lateralMotor->run(FORWARD);
			break;
		case 'l':
			lateralMotor->run(BACKWARD);
			break;

		case 's':
			break;

		default:
			//Serial.print("ERROR: direction is not valid");
			return;
	}

	//Ramp turning speed
	for (int i = 0; currentSpeed < turnSpeed; currentSpeed++)
	{
      lateralMotor->setSpeed(i);
    }

}

