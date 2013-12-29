
#include "../../include/ExtLibs.h"
#include "../../include/Abstract.h"

using namespace A2D;

LPCWSTR Abstract::GetClass()
{
	return L"Abstract";
}

LPCWSTR Abstract::ToString()
{
	return L"Abstract";
}

bool Abstract::operator==(Abstract * xAbstract)
{
	return this == xAbstract;
}

bool Abstract::isClass(LPCWSTR xClass)
{
	return wcscmp(GetClass(), xClass) == 0;
}