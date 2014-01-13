#include "../../../include/Core/ExtLibs.h"
#include "../../../include/Core/AbstractListener.h"
#include "../../../include/Core/AbstractEvent.h"

using namespace A2D;

AbstractListener::AbstractListener(int xID) :
aID(xID)
{}

AbstractListener::~AbstractListener(){}

bool AbstractListener::operator==(const AbstractListener& xListener)
{
	if (this->aID == xListener.aID)
	{
		return true;
	}
	else return false;
}
