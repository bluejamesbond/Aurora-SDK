
#include "../../include/A2DExtLibs.h"
#include "../../include/A2DRenderable.h"

A2DRenderable::A2DRenderable(){}
A2DRenderable::~A2DRenderable(){}

LPCWSTR A2DRenderable::GetClass()
{
	return L"A2DRenderable";
}

LPCWSTR A2DRenderable::ToString()
{
	return L"A2DRenderable";
}

bool A2DRenderable::operator==(A2DAbstract * xAbstract)
{
	return false;
}

HRESULT A2DRenderable::Initialize(){

	return NULL;
}

void A2DRenderable::Deinitialize(){}