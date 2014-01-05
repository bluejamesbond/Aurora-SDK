#include "../../include/ExtLibs.h"
#include "../../include/AbstractListener.h"
#include "../../include/AbstractEvent.h"

using namespace A2D;

AbstractListener::AbstractListener(int xID) :
aID(xID)
{}

AbstractListener::~AbstractListener(){}

/////////////////////////////////////////////////////////////////////////////
// REQUIRED BY ABSTRACT_AURORA
/////////////////////////////////////////////////////////////////////////////

LPCWSTR AbstractListener::getClass()
{
	return L"AbstractListener";
}

LPCWSTR AbstractListener::toString()
{
	return L"AbstractListener";
}

HRESULT AbstractListener::initialize()
{
	return NULL;
}

bool AbstractListener::operator==(const AbstractListener& xListener)
{
	if (this->aID == xListener.aID)
	{
		return true;
	}
	else return false;
}
