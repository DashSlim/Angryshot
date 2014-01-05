//#include "Angryshot.h"

//include below is due to the quirk of Arduino platform
#include "Slingshot.h"
#include <HX711.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "movement.h"
//#include "printf.h"

//include above is due to the quirk of Arduino platform

//button pin to trigger the special trick of certain birds(simulate the single click)
int button = 3;
int move_cnt = 0;
double first_move_bias = 0;

Slingshot leo;

void setup()
{
	//initialize the hardware
	//using the UART in baud rate 9600 for debugging
	leo.init(button, 0, 9600);
	
	//set the initial status as "wait"
	leo.setStatus(wait);
}

void loop()
{

	//three PHASES used:
	
	//PHASE #1-----------------------------------
	
	//UART output the current status of leo (unnecessary, debug only)
	Serial.println( leo.getStatus() );
	
	//END OF PHASE #1
	
	//PHASE #2-----------------------------------
	
	//update data (force and angle)
	leo.update();
	
	//END OF PHASE #2
	
	//PHASE #3-----------------------------------
	
	//transition of status based on status and motion
	
	if(leo.getStatus() == wait)
	{
		//mouse should be released when "wait"
		if(Mouse.isPressed())
		{
			Mouse.release();
		}
		
		//enter "aim" when the string is tight
		if(leo.tight())
		{
			//reset the origin  to the current point
			resetOrigin();
			//hold the mouse button till "fire"
			Mouse.press();
			//set the flag to ignore the first N moves
			leo.setFirstMove();
			//enter status "aim"
			leo.setStatus(aim);
		}
	}
	else if(leo.getStatus() == aim)
	{
		//player release the rope
		if(leo.suddenFall())
		{
			Mouse.release();
			//delay a little before the mouse is relocated
			delay(20);
			leo.setFirstMove();
			leo.setStatus(fire);
		}
		else
		//move the mouse as player want
		{
			//using the flag to identify the 1st move
			if(leo.isFirstMove())
			{
			  //Serial.println("1st");
			  
			  moveWithSlingshot(leo.getLength() - first_move_bias, leo.getAngle());//ACTION  4
			  move_cnt ++;
			  if(move_cnt > 10)
			  {
				move_cnt = 0;
				first_move_bias = leo.getLength();
				leo.clearFirstMove();
			  }
			  //moveWithSlingshot(0);//ACTION  4
			  //Serial.println(getLength_offset());
			  //delay(1000);
			}
			else
			{
				//Serial.println("after");
				moveWithSlingshot(leo.getLength() - first_move_bias, leo.getAngle());
				//Serial.println(getLength_offset());
				//delay(1000);
			}
		}
	}
	else if(leo.getStatus() == fire)
	{
		leo.setFirstMove();
		//get the mouse pointer to the virtual slingshot for the next round
		moveBack();
		//get back to "wait"
		leo.setStatus(wait);
	}
	else
	//something nasty happening
	{
		if ( leo.test() )
		{
			leo.setStatus(invalid);
			Serial.println("Slingshot test successful!Resume to Work");
		}
		else
		{
			Serial.println("Invalid Status detected, Halt Now...");
			Serial.println("Please rest Arduino using the \"reset\" button!");
			while(1);
		}
	}
	
	//END OF PHASE #3
	//return to the beginning of the loop	
}