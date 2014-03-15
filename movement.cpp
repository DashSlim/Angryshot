#include "Arduino.h"
//include above is essential
#include "movement.h"

int singleMoveLimit = 20;
int MStep = 2;

int x = 0;
int y = 0;

int totalX = 0;
int totalY = 0;

void moveBack()
{
        //Mouse.move(0-totalX, totalY);
        moveTo(0, 0);
        totalX = 0;
        totalY = 0;
}

int limitSingleMove(int move)
{
	if(move < (0 - singleMoveLimit) )
		move = 0 - singleMoveLimit;
	if(move > singleMoveLimit)
		move = singleMoveLimit;
	return move;
}

void p2c(double l,double a,int* x,int* y)
{
	*x = l*cos(a);
	*y = l*sin(a);
}

void moveTo(int xNew, int yNew)
{
	int moveX = 0;
	int moveY = 0;
	
	bool lockX = false;
	bool lockY = false;
	
	moveX = x-xNew;
	moveY = yNew - y;
	
	//record every step we make
	totalX += moveX;
	totalY += moveX;
	
	while(1)
	{
		if(!lockX)
		{
			if (moveX > MStep)
			{
				Mouse.move(MStep, 0);
				moveX -= MStep;
			}
			else if (moveX < (0-MStep))
			{
				Mouse.move(0-MStep, 0);
				moveX += MStep;
			}
			else
			{
				lockX = true;
			}
		}
		
		if(!lockY)
		{
			if (moveY > MStep)
			{
				Mouse.move(0, MStep);
				moveY -= MStep;
			}
			else if (moveY < (0-MStep))
			{
				Mouse.move(0, 0-MStep);
				moveY += MStep;
			}
			else
			{
				lockY = true;
			}
		}
		if(lockX && lockY)
		{
			break;
		}
	}
	
	Mouse.move(moveX, moveY);
	
}

void moveWithSlingshot(double length, double angle)
{
	int xNew;
	int yNew;

	/*
	//get position
	length = getLength(force) - length_offset;
    angle = getAngleRadius(angle);
	*/
	//calculate coordinate
	p2c(length, angle, &xNew, &yNew);
	
	xNew = x + limitSingleMove(xNew - x);
	yNew = y + limitSingleMove(yNew - y);
	
	//move to (xNew,yNew)
	moveTo(xNew, yNew);
	//update current coordinate
	x = xNew;
	y = yNew;
}

void resetOrigin()
{
  x = 0;
  y = 0;
}
