
#include "../../include/Pipeline.h"

Pipeline::Pipeline() : aLifeCycle(Pipeline::aGlobalLifeCycle - 1) {} // Offset by 1

Pipeline::Pipeline(Pipeline * xPipeline){}

// Initialize to value
int Pipeline::aGlobalLifeCycle = 0;

void Pipeline::nextLifeCycle()
{
	aGlobalLifeCycle++;
}

/////////////////////////////////////////////////////////////////////////////
// REQUIRED BY _ABSTRACT
////////////////////////////////////////////////////////////////////////////

LPCWSTR Pipeline::GetClass()
{
	return L"Pipeline";
}

LPCWSTR Pipeline::ToString()
{
	return L"Pipeline";
}

bool Pipeline::operator==(Abstract * xAbstract)
{
	return false;
}

HRESULT Pipeline::Initialize()
{
	return NULL;
}

void Pipeline::Deinitialize()
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