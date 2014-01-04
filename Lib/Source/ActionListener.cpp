#include "../../include/ExtLibs.h"
#include "../../include/ActionListener.h"

using namespace A2D;

ActionListener::ActionListener() :
ActionListener("DefaultActionListener")
{}

ActionListener::ActionListener(string xString) :
AbstractListener(_LISTENER_ACTION), aName(xString)
{}


ActionListener::~ActionListener(){}

void ActionListener::Notify(AbstractEvent * xEvent)
{
	Notify((ActionEvent*)xEvent);
}

void ActionListener::Notify(ActionEvent * xEvent)
{
	ActionPerformed(xEvent);
}

void ActionListener::ActionPerformed(ActionEvent * xEvent)
{
	// FILL THIS OUT
	SYSOUT_STR("Handling action performed");
}

void ActionListener::Print() const
{
	cout << aName.c_str();

}


/////////////////////////////////////////////////////////////////////////////
// REQUIRED BY Abstract
/////////////////////////////////////////////////////////////////////////////

LPCWSTR ActionListener::getClass()
{
	return L"ActionListener";
}

LPCWSTR ActionListener::toString()
{
	return L"ActionListener";
}

HRESULT ActionListener::initialize(){

	return NULL;
}