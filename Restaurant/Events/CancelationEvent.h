#pragma once
#include "\Events\Event.h"
class CancelationEvent :
	public Event
{
public:
	CancelationEvent(void);
	~CancelationEvent(void);
};

