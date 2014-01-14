
#include "../../../include/Core/ExtLibs.h"
#include "../../../include/Core/ComponentEventSource.h"

using namespace A2D;

ComponentEventSource::ComponentEventSource(){}

ComponentEventSource::~ComponentEventSource(){}

STATUS ComponentEventSource::processFocusEvent(FocusEvent * xEvent)
{
	return fireListener(xEvent, A2D_LISTENER_FOCUS);
}

STATUS ComponentEventSource::addFocusListener(FocusListener * xListener)
{
	if (xListener == NULL)
	{
		int ID = A2D_LISTENER_FOCUS;
		AbstractListener * listener = findListener(ID);
		if (listener)
		{
			return removeListener(listener);
		}
		else
		{
			return STATUS_FAIL;
		}
	}
	return addListener(xListener);
}

