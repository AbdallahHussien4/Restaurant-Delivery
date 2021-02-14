#pragma once
#include "Event.h"
class PromotionEvent :public Event
{
private:
	double extraMoney;
public:
	PromotionEvent(int eTime, int oID, double extra);
	virtual void Execute(Restaurant* pRest);
};

