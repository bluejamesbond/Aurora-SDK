#include "../../../include/Core/ExtLibs.h"
#include "../../../include/Core/ActionListener.h"

using namespace A2D;

ActionListener::ActionListener() :
ActionListener("DefaultActionListener")
{}

ActionListener::ActionListener(string xString) :
AbstractListener(A2D_LISTENER_ACTION), aName(xString)
{}


ActionListener::~ActionListener(){}

STATUS ActionListener::notify(AbstractEvent * xEvent)
{
	return notify((ActionEvent*)xEvent);
}

STATUS ActionListener::notify(ActionEvent * xEvent)
{
	actionPerformed(xEvent);
	if (xEvent->isConsumed()) { return STATUS_OK; }
	else return STATUS_FAIL;
}

void ActionListener::actionPerformed(ActionEvent * xEvent)
{
	// FILL THIS OUT
	SYSOUT_STR("Handling action performed");
}

void ActionListener::print() const
{
	SYSOUT_F("%s", aName.c_str());

}
