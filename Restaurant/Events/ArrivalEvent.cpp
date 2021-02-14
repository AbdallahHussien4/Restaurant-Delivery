#include "ArrivalEvent.h"
#include "..\Rest\Restaurant.h"


ArrivalEvent::ArrivalEvent(int eTime, int oID, ORD_TYPE oType, REGION reg):Event(eTime, oID)
{
	OrdType = oType;
	OrdRegion = reg;
}
ArrivalEvent::ArrivalEvent(int eTime, int oID, ORD_TYPE oType, REGION reg, double money, int distance):Event(eTime, oID)
{
	OrdType = oType;
	OrdRegion = reg;
	OrdDistance=distance;
	OrdMoney=money;
}

void ArrivalEvent::Execute(Restaurant* pRest)
{
	//This function should create and order and and fills its data 
	// Then adds it to normal, frozen, or VIP order lists that you will create in phase1
	Order*pord=new Order(OrderID,OrdType,OrdRegion);
	pord->SetDistance(OrdDistance);
	pord->SetMoney(OrdMoney);
	pord->SetArrTime(EventTime);
	if(OrdType==TYPE_VIP)
		pRest->AddVOrder(pord);
	else if (OrdType==TYPE_FROZ)
		pRest->AddFOrder(pord);
	else if (OrdType==TYPE_NRM)
		pRest->AddNOrder(pord);
	
	
	///For the sake of demo, this function will just create an order and add it to DemoQueue
	///Remove the next code lines in phase 1&2
	
	/*Order* pOrd = new Order(OrderID,OrdType,OrdRegion);
	pRest->AddtoDemoQueue(pOrd);*/
}
