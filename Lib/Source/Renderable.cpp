
#include "../../include/ExtLibs.h"
#include "../../include/Renderable.h"

Renderable::Renderable(){}
Renderable::~Renderable(){}

LPCWSTR Renderable::getClass()
{
	return L"Renderable";
}

LPCWSTR Renderable::toString()
{
	return L"Renderable";
}

bool Renderable::operator==(Abstract * xAbstract)
{
	return false;
}

HRESULT Renderable::initialize(){

	return NULL;
}

void Renderable::Deinitialize(){}