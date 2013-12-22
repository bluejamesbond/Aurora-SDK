
#include "../../include/A2DExtLibs.h"
#include "../../include/A2DPipelineComponent.h"

A2DPipelineComponent::A2DPipelineComponent(A2DBackBuffer * xBackBuffer) :
aBackBuffer(xBackBuffer){}

HRESULT A2DPipelineComponent::Initialize()
{
	return S_OK;
}

void A2DPipelineComponent::Deinitialize()
{
	aBackBuffer = 0;
}

LPCWSTR A2DPipelineComponent::GetClass()
{
	return L"A2DAbstractPipelineComponent";
}

LPCWSTR A2DPipelineComponent::ToString()
{
	return L"A2DAbstractPipelineComponent";
}

bool A2DPipelineComponent::operator==(A2DAbstract * xAbstract)
{
	return false;
}