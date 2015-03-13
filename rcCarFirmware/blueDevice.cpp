#include "bluedevice.h"


Bluetooth::Bluetooth( int Rx, int Tx)
{

	ss = SoftwareSerial(Rx,Tx);
	_baudRate = 38400;
	_pin = "0000";
	_name = "Example";


}

Bluetooth::~Bluetooth()
{

}

void Bluetooth::begin()
{
	ss.begin(_baudRate);
  	ss.print("\r\n+STWMOD=0\r\n"); //set the bluetooth work in slave mode
  	ss.print("STNA=Example"); //set the bluetooth name as "CrowBTSlave"
  	//blueToothSerial.flush();
  	ss.print("\r\n");//Set SLAVE pincode"0000"
  	ss.print(_pin);
  	ss.print("\r\n");
  	ss.print("\r\n+STOAUT=1\r\n"); // Permit Paired device to connect me
  	ss.print("\r\n+STAUTO=0\r\n"); // Auto-connection should be forbidden here
  	delay(2000); // This delay is required.
  	ss.print("\r\n+INQ=1\r\n"); //make the slave bluetooth inquirable 
  	Serial.println("The slave bluetooth is inquirable!");
  	delay(2000); // This delay is required.
  	ss.flush();
}

void Bluetooth::send( char* message )
{
	ss.print(message);
}
/*
char* Bluetooth::read()
{

}
*/