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

HRESULT ActionListener::notify(AbstractEvent * xEvent)
{
	return notify((ActionEvent*)xEvent);
}

HRESULT ActionListener::notify(ActionEvent * xEvent)
{
	actionPerformed(xEvent);
	if (xEvent->isConsumed()) return S_OK;
	else return S_FALSE;
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
