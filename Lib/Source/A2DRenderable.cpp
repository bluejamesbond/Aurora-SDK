
#include "../../include/ExtLibs.h"
#include "../../include/Renderable.h"

Renderable::Renderable(){}
Renderable::~Renderable(){}

LPCWSTR Renderable::GetClass()
{
	return L"Renderable";
}

LPCWSTR Renderable::ToString()
{
	return L"Renderable";
}

bool Renderable::operator==(Abstract * xAbstract)
{
	return false;
}

HRESULT Renderable::Initialize(){

	return NULL;
}

void Renderable::Deinitialize(){}