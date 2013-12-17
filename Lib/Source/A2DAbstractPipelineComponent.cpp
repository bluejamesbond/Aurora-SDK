
#include "../../include/A2DExtLibs.h"
#include "../../include/A2DAbstractPipelineComponent.h"

A2DAbstractPipelineComponent::A2DAbstractPipelineComponent(A2DBackBuffer * xBackBuffer) :
aBackBuffer(xBackBuffer){}

HRESULT A2DAbstractPipelineComponent::Initialize()
{
	return S_OK;
}

void A2DAbstractPipelineComponent::Deinitialize()
{
	aBackBuffer = 0;
}

LPCWSTR A2DAbstractPipelineComponent::GetClass()
{
	return L"A2DAbstractPipelineComponent";
}

LPCWSTR A2DAbstractPipelineComponent::ToString()
{
	return L"A2DAbstractPipelineComponent";
}

bool A2DAbstractPipelineComponent::operator==(A2DAbstract * xAbstract)
{
	return false;
}