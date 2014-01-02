
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

bool Abstract::operator==(Abstract * xAbstract)
{
	return this == xAbstract;
}

bool Abstract::isClass(LPCWSTR xClass)
{
	return wcscmp(getClass(), xClass) == 0;
}