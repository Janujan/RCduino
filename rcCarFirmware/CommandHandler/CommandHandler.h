/*
  commandHand;er.h - Library for handling commands for ArdPiCar
  Uses the Adafruit Motor Shield Library.
  v1.0: Control 2 motors( one for turning, the other for moving forward and back)
  Created by Janujan Selvaratnam, February 14, 2015.
  Released into the public domain.
*/

#ifndef commandHandler_h
#define commandHandler_h
#include <Adafruit_MotorShield.h>
#include <Arduino.h>
#include "utility/Adafruit_PWMServoDriver.h"
class CommandHandler
{
	public:
		CommandHandler();
		~CommandHandler();
		void sendCommand(int motor, char direct, int delayTime);
		void begin();
	private:
		int _motor;
		char _direct;
		int _delayTime;
		int currentSpeed;
		Adafruit_MotorShield afms;
		Adafruit_DCMotor *forwardMotor;
		Adafruit_DCMotor *lateralMotor;
		//bool exists = false;
		void moveForward( char direct, int delayTime);
		void moveLateral( char direct, int delayTime);

};

#endif
