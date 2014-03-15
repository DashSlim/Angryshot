/*
 * measure.h
 *
 *  Created on: Apr 2, 2013
 *      Author: dash
 */

#ifndef MEASURE_H_
#define MEASURE_H_

//define the pin configuration of the main board
//nRF24L01+ SPI configuration:
#define CE	12
#define CSN	13
//HX711--01 UART configuration:
#define SCK1	4
#define DOUT1	5
//HX711--02 UART configuration:
#define SCK2	6
#define DOUT2	7

#include <nRF24L01.h>
#include <RF24.h>
#include <HX711.h>

class Sensors
{
public:
	//initialize 2 HX711 and 1 nRF24L01+ on main board
	void initHX711(int bias1, int bias2);
	void initnRF24L01();

	//get the force data, update force_last
	double getForce();
	//get the angle data from wireless radio
	double getAngle();

	double force2length(double force);
	double getLength(double force);
	double getLength_offset();
	double getAngleRadius(double angle);
private:
	RF24 radio;
	HX711 hx1;
	HX711 hx2;
};

#endif /* MEASURE_H_ */
