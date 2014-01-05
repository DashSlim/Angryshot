/*
 * movement.h
 *
 *  Created on: Apr 2, 2013
 *      Author: dash
 */

#ifndef MOVEMENT_H_
#define MOVEMENT_H_

//convert Polar coordinates to Cartesian coordinates
void p2c(double l,double a,int* x,int* y);
//move to the following point (ref. origin)
void moveTo(int xNew, int yNew);
//move to origin
void moveBack();
//relocate the coordination system
void resetOrigin();
//move as the player want (Polar coordinates)
void moveWithSlingshot(double length, double angle);

#endif /* MOVEMENT_H_ */