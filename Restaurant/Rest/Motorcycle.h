#ifndef __MOTORCYCLE_H_
#define __MOTORCYCLE_H_


#include "..\Defs.h"

#pragma once
class Motorcycle	
{
	int ID;
	ORD_TYPE type;	//for each order type there is a corresponding motorcycle type 
	int speed;		//meters it can move in one clock tick (in one timestep)
	REGION	region;	//region of the motorcycle
	STATUS	status;	//idle or in-service
	int BackTime;

public:
	Motorcycle();
	Motorcycle(int, ORD_TYPE, int);
	void setRegion(REGION);
	REGION getRegion();
	void SetStatus(STATUS);
	STATUS GetStatus();
	int getspeed();
	void SetBackTime(int);
	int GetBackTime();
	ORD_TYPE gettype();
	virtual ~Motorcycle();
};

#endif