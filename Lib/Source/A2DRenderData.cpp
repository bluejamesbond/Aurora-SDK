
#include "../../include/A2DExtLibs.h"
#include "../../include/A2DRenderData.h"

A2DRenderData::A2DRenderData() :
aViewMatrix(NULL),
aWorldMatrix(NULL),
aOrthogonalMatrix(NULL),
aProjectionMatrix(NULL),
aCameraProps(NULL),
aBackBuffer(NULL),
aWindowProps(NULL)
{}

A2DRenderData::A2DRenderData(A2DRenderData * xRenderData) :
aViewMatrix (xRenderData->aViewMatrix), 
aWorldMatrix (xRenderData->aWorldMatrix), 
aOrthogonalMatrix (xRenderData->aOrthogonalMatrix), 
aProjectionMatrix (xRenderData->aProjectionMatrix), 
aCameraProps (xRenderData->aCameraProps), 
aBackBuffer (xRenderData->aBackBuffer), 
aTextureBuffer(xRenderData->aTextureBuffer),
aBlurBuffer(xRenderData->aBlurBuffer),
aWindowProps(xRenderData->aWindowProps)
{}

/////////////////////////////////////////////////////////////////////////////
// REQUIRED BY A2D_ABSTRACT
////////////////////////////////////////////////////////////////////////////

LPCWSTR A2DRenderData::GetClass()
{
	return L"A2DRenderData";
}

LPCWSTR A2DRenderData::ToString()
{
	return L"A2DRenderData";
}

bool A2DRenderData::operator==(A2DAbstract * xAbstract)
{
	return false;
}

HRESULT A2DRenderData::Initialize()
{
	return NULL;
}

void A2DRenderData::Deinitialize(){}