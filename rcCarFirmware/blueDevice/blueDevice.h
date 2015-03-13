#ifndef BLUEDEVICE_H
#define BLUEDEVICE_H

#include <Arduino.h>
#include <SoftwareSerial.h>

class Bluetooth 
{
	public:
		Bluetooth( int Rx, int Tx);
		~Bluetooth();
		void begin();
		void send( char* message );
		char* read();
		void setBaudRate(int baud);
		int getBaudRate();
		void setName(char* name);
		char* getName();
		void setPin( char* pin );
		char* getPin();

	private:
		SoftwareSerial ss;
		int _baudRate;
		char* _pin;
		char* _name;

};

#endif