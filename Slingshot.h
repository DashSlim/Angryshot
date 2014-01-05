#ifndef Slingshot_H_
#define Slingshot_H_

#include "measure.h"

typedef enum SlingStatus {invalid, wait, aim, fire};

class Slingshot
{
public:
	//default constructor
	Slingshot()
	{
		slingStatus = invalid;
	}
	
	Slingshot(SlingStatus _s)
	{
		slingStatus = _s;
	}
	
	//initialize the hardware of slingshot(HX711, button, wireless radio)
	void init(int bPin, int global_length_offset, int baud_rate);
	
	//see if the slingshot is in "invalid" status
	bool test();
	
	//update data acquired
	bool update();
	
	//set slingshot status
	void setStatus(SlingStatus _s);
	//get slingshot status
	SlingStatus getStatus();
	
	//sudden fall detect
	bool suddenFall();
	//tight detect
	bool tight();
	
	//test 1st move
	bool isFirstMove();	
	//set 1st move to true
	void setFirstMove();
	//set 1st move to false
	void clearFirstMove();
	
	//get Length Offset
	double getLengthOffset();
	//get angle
	double getAngle();
	//get Length
	double getLength();
	
private:
	//virtually integrated sensor
	Sensors sensor;
	
	//current status
	SlingStatus slingStatus;
	//flag for 1st move
	bool firstmove;
	//move times counter
	int move_cnt;
	
	double init_length_offset;
	double first_move_bias;
	
	//current force
	double force;
	//last force
	double force_last;
	//current length
	double length;
	////current force offset
	double length_offset;
	//current angle
	double angle;
	
	//a fall in the value of strength greater than this would be considered as releasing of the string
	static const double suddenForce = 130000;

	//a rise in the value of strength greater than this would be considered as pulling of the string
	static const double tightenForce = 300000;
	
};

//some bird need a single click to toggle special effect
void special_act();

#endif /* Slingshot_H_ */