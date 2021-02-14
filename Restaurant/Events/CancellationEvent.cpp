#include "CancellationEvent.h"
#include "..\Rest\Restaurant.h"


CancellationEvent::CancellationEvent(int eTime, int oID) :Event(eTime, oID){}

void CancellationEvent::Execute(Restaurant* pRest)//,GUI* p) 
{
	Order* pOrd;
	if (pRest->getNOrdbyId(pOrd, OrderID)) {
		//p->RemoveOrderByID(OrderID);
		delete pOrd;
	}
		
	
}



