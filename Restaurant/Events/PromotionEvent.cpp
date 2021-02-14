#include "PromotionEvent.h"
#include "..\Rest\Restaurant.h"

PromotionEvent::PromotionEvent(int eTime, int oID, double extra):Event(eTime,oID), extraMoney(extra){}

void PromotionEvent::Execute(Restaurant* pRest) {
	Order* pOrd;
	
	if (pRest->getNOrdbyId(pOrd, OrderID))
	{
		pOrd->SetMoney(pOrd->getmoney() + extraMoney);
		pOrd->SetOrdType(TYPE_VIP);
		pRest->AddVOrder(pOrd);
	}
}