#include "Slingshot.h"

#include "Arduino.h"

#include "measure.h"

//initialize the hardware of slingshot(HX711, button, wireless radio)
void Slingshot::init(int bPin, int global_length_offset, int baud_rate)
{
	slingStatus = wait;
	length_offset = global_length_offset;
	
	Serial.begin(baud_rate);
	pinMode(bPin, INPUT);
	
	sensor.initHX711(35000, 39000);
	
	sensor.initnRF24L01();
	Mouse.begin();
	attachInterrupt(0,special_act, FALLING);
}

//check if the slingshot is in invalid status
bool Slingshot::test()
{
	return (slingStatus != invalid);
}

bool Slingshot::update()
{
	force_last = force;
	force = sensor.getForce();
	length = sensor.force2length(force);
	angle = sensor.getAngle();
}

//set status
void Slingshot::setStatus(SlingStatus _s)
{
	slingStatus = _s;
}

//return the current status
SlingStatus Slingshot::getStatus()
{
	return slingStatus;
}

//whether the string is released from tight to relax
bool Slingshot::suddenFall()
{
	/*force = getForce();
        Serial.print(force_last);
        Serial.print("-------");
        Serial.println(force);
	*/
	if(force_last - force > suddenForce)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//whether the string is pulled from relax to tight
bool Slingshot::tight()
{
	if(force > tightenForce*2)
	{
		length_offset = sensor.force2length(force);
		return true;
	}
	else
	{
		return false;
	}
}

bool Slingshot::isFirstMove()
{
	return firstmove;
}
void Slingshot::setFirstMove()
{
	firstmove = true;
}
void Slingshot::clearFirstMove()
{
	firstmove = false;
}
double Slingshot::getLengthOffset()
{
	return length_offset;
}
double Slingshot::getAngle()
{
	return angle;
}
double Slingshot::getForce()
{
	return force;
}
double Slingshot::getLength()
{
	return length;
}

//single click to trigger the bird's special tricks
void special_act()
{
	Mouse.click();
}