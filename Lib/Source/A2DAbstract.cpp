
#include "../../include/A2DExtLibs.h"
#include "../../include/A2DAbstract.h"

A2DAbstract::A2DAbstract(){}

A2DAbstract::~A2DAbstract(){}

LPCWSTR A2DAbstract::GetClass()
{
	return L"A2DAbstract";
}

LPCWSTR A2DAbstract::ToString()
{
	return L"A2DAbstract";
}

bool A2DAbstract::operator==(A2DAbstract * xAbstract)
{
	return this == xAbstract;
}

bool A2DAbstract::isClass(LPCWSTR xClass)
{
	return wcscmp(GetClass(), xClass) == 0;
}