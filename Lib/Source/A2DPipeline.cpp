
#include "../../include/A2DPipeline.h"

A2DPipeline::A2DPipeline() : aLifeCycle(A2DPipeline::aGlobalLifeCycle - 1) {} // Offset by 1

A2DPipeline::A2DPipeline(A2DPipeline * xPipeline){}

// Initialize to value
int A2DPipeline::aGlobalLifeCycle = 0;

void A2DPipeline::nextLifeCycle()
{
	aGlobalLifeCycle++;
}

/////////////////////////////////////////////////////////////////////////////
// REQUIRED BY A2D_ABSTRACT
////////////////////////////////////////////////////////////////////////////

LPCWSTR A2DPipeline::GetClass()
{
	return L"A2DPipeline";
}

LPCWSTR A2DPipeline::ToString()
{
	return L"A2DPipeline";
}

bool A2DPipeline::operator==(A2DAbstract * xAbstract)
{
	return false;
}

HRESULT A2DPipeline::Initialize()
{
	return NULL;
}

void A2DPipeline::Deinitialize()
{
	for (int i = 0; i < aLength; i++)
	{
		if (aPipelineComps[i])
		{
			aPipelineComps[i]->Deinitialize();
			delete aPipelineComps[i];
			aPipelineComps[i] = 0;
		}
	}
}