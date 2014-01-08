
#include "../../include/ExtLibs.h"
#include "../../include/ComponentEventSource.h"

using namespace A2D;

ComponentEventSource::ComponentEventSource(){}

ComponentEventSource::~ComponentEventSource(){}

HRESULT ComponentEventSource::processFocusEvent(FocusEvent * xEvent)
{
	int ID = A2D_LISTENER_FOCUS;
	return fireListener(xEvent, ID);
}

HRESULT ComponentEventSource::addFocusListener(FocusListener * xListener)
{
	if (xListener == NULL)
	{
		int ID = A2D_LISTENER_FOCUS;
		AbstractListener * listener = findListener(ID);
		if (listener) return removeListener(listener);
		else return S_FALSE;
	}
	return addListener(xListener);
}

/////////////////////////////////////////////////////////////////////////////
// REQUIRED BY ABSTRACT_AURORA
/////////////////////////////////////////////////////////////////////////////

LPCWSTR ComponentEventSource::getClass()
{
	return L"ComponentEventSource";
}

LPCWSTR ComponentEventSource::toString()
{
	return L"ComponentEventSource";
}

HRESULT ComponentEventSource::initialize()
{

	return NULL;
}

