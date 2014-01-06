
#include "../../include/ExtLibs.h"
#include "../../include/Abstract.h"

using namespace A2D;

LPCWSTR Abstract::getClass()
{
	return L"Abstract";
}

LPCWSTR Abstract::toString()
{
	return L"Abstract";
}

bool Abstract::isClass(Abstract& xAbstract, LPCWSTR xClass)
{
	return wcscmp(xAbstract.getClass(), xClass) == 0;
}