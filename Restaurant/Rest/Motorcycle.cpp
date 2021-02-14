#include "Motorcycle.h"


Motorcycle::Motorcycle()
{
}

Motorcycle::Motorcycle(int a, ORD_TYPE b, int c)
{
	ID = a;
	type = b;
	speed = c;
}
void Motorcycle::setRegion(REGION r) {
	region = r;
}
REGION Motorcycle::getRegion() {
	return region;
}
void Motorcycle:: SetStatus(STATUS s)
{
	status=s;
}
STATUS Motorcycle:: GetStatus()
{
	return status;
}
int Motorcycle:: getspeed()
{
	return speed;
}
void Motorcycle:: SetBackTime(int c)
{
	BackTime=c;
}
int Motorcycle::GetBackTime()
{
	return BackTime;
}
ORD_TYPE Motorcycle::gettype()
{
	return type;
}

Motorcycle::~Motorcycle()
{
}

