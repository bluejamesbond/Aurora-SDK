
#include "../../include/Pipeline.h"

using namespace A2D;

// initialize to value
int Pipeline::aGlobalLifeCycle = 0;

Pipeline::Pipeline()
{ 
	// Offset by 1
	aLifeCycle = aGlobalLifeCycle - 1;
}

void Pipeline::nextLifeCycle()
{
	aGlobalLifeCycle++;
}

Pipeline::~Pipeline()
{
	for (int i = 0; i < aLength; i++)
	{
		DESTROY(aPipelineComps[i]);
	}
}

LPCWSTR Pipeline::getClass()
{
	return L"Pipeline";
}

LPCWSTR Pipeline::toString()
{
	return L"Pipeline";
}
HRESULT Pipeline::initialize()
{
	return NULL;
}