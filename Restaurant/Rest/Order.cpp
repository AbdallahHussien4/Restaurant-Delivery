#include "Order.h"

Order::Order(int id, ORD_TYPE r_Type, REGION r_region)
{
	ID = (id>0&&id<1000)?id:0;	//1<ID<999
	type = r_Type;
	Region = r_region;	
}

Order::~Order()
{
}

int Order::GetID()
{
	return ID;
}


int Order::GetType() const
{
	return type;
}

REGION Order::GetRegion() const
{
	return Region;
}

void Order::SetDistance(int d)
{
	Distance = d>0?d:0;
}

int Order::GetDistance() const
{
	return Distance;
}
void Order:: SetMoney(double money)
{
	totalMoney=money;
}
double Order:: getmoney()
{
	return totalMoney;
}
int Order:: getArrTime()
{
	return ArrTime;
}

void Order:: SetArrTime(int t)
{
	ArrTime=t;
}
int Order:: getWaitTime()
{
	return WaitTime;
}

void Order:: SetWaitTime(int t)
{
	WaitTime=t;
}
int Order:: getServTime()
{
	return ServTime;
}

void Order:: SetServTime(int t)
{
	ServTime=t;
}
int Order:: getFinishTime()
{
	return FinishTime;
}

void Order:: SetFinishTime(int t)
{
	FinishTime=t;
}

int Order:: getpriorty()
{
	return totalMoney/(Distance*ArrTime);
}
void Order::SetOrdType(ORD_TYPE t)
{
	type = t;
}