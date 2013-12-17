
#include "../../Include/A2DExtLibs.h"
#include "../../Include/A2D.h"
#include "../../Include/A2DTextureBuffer.h"

A2D::A2D(A2DWindow * xWindow, A2DWindowProperties * xWindowProp) :
aWindowProps(xWindowProp),
aWindow(xWindow){}

A2D::~A2D(){}

A2DRootPane * A2D::GetRootPane()
{
	return aRootPane;
}

A2DCamera * A2D::GetCamera()
{
	return aCamera;
}

A2DRenderData * A2D::GetRenderData()
{
	return aRenderData;
}

HRESULT A2D::CreateResources()
{
	
	HRESULT hr;

	// Adjust camera settings and then create its resources.
	A2DCameraProperties * cameraProperties = aCamera->GetProperties();

	cameraProperties->aPositionX = 0.0f;
	cameraProperties->aPositionY = 0.0f;
	cameraProperties->aPositionZ = -10.0f;

	aCamera->CreateResources();

	// Set the RenderData and pass it into RootPane to inialize the render process.
	aRenderData->aBackBuffer = aBackBuffer;
	aRenderData->aTextureBuffer = aTextureBuffer;
	aRenderData->aBlurBuffer = aBlurBuffer;
	aRenderData->aWindowProps = aWindowProps;
	aRenderData->aCameraProps = aCamera->GetProperties();
	aRenderData->aViewMatrix = aCamera->GetViewMatrix();
	aRenderData->aWorldMatrix = A2DMatrixFactory::createDefaultWorldMatrix();
	aRenderData->aProjectionMatrix = A2DMatrixFactory::createDefaultProjectionMatrix(aWindowProps);
	aRenderData->aOrthogonalMatrix = A2DMatrixFactory::createDefaultOrthogonalMatrix(aWindowProps);

	// Create children resources; This also calls all subsequent children and
	// creates their resources.
	hr = aRootPane->CreateResources(aRenderData);

	return hr;
}

LRESULT A2D::PumpWindowMsg(HWND * xHwnd, UINT * xMessage, WPARAM * xWParam, LPARAM * xLParam)
{
	return aRootPane->WindowMsg(xHwnd, xMessage,xWParam, xLParam);
}

void A2D::Update()
{
	aRenderData->aBackBuffer->SetActive();

	aRenderData->aBackBuffer->Clear();

	aRenderData->aBackBuffer->SetZBuffer(false);

	aRootPane->Update();
	
	aRenderData->aBackBuffer->SetZBuffer(true);

	aRenderData->aBackBuffer->Swap();
}

/////////////////////////////////////////////////////////////////////////////
// REQUIRED BY A2D_ABSTRACT
/////////////////////////////////////////////////////////////////////////////

LPCWSTR A2D::GetClass()
{
	return L"A2D";
}

LPCWSTR A2D::ToString()
{
	return L"A2D";
}

bool A2D::operator==(A2DAbstract * xAbstract)
{
	return false;
}

HRESULT A2D::Initialize()
{
	HRESULT hr;

	aWindow->SetAurora2D(this);

	// -----------------------------------------------------
	
	aRootPane = new A2DRootPane(aWindowProps);
	aBackBuffer = new A2DBackBuffer(aWindow, aWindowProps);
	aCamera = new A2DCamera();
	aRenderData = new A2DRenderData();
	aTextureBuffer = new A2DTextureBuffer(aBackBuffer, aWindowProps->aRealWidth, aWindowProps->aRealHeight);
	aBlurBuffer = new A2DTextureBuffer(aBackBuffer, aWindowProps->aRealWidth, aWindowProps->aRealHeight);

	// -----------------------------------------------------

	hr = aBackBuffer->Initialize();
	hr = aRootPane->Initialize();
	hr = aCamera->Initialize();
	hr = aTextureBuffer->Initialize();
	hr = aBlurBuffer->Initialize();

	aRootPane->SetBounds(0, 0, aWindowProps->aRealWidth, aWindowProps->aRealHeight);

	// -----------------------------------------------------
	
	return hr;
}

void A2D::Deinitialize()
{
	// Release the D3D object.
	if (aBackBuffer)
	{
		aBackBuffer->Deinitialize();
		delete aBackBuffer;
		aBackBuffer = 0;
	}

	// Release the Camera object.
	if (aCamera)
	{
		aCamera->Deinitialize();
		delete aCamera;
		aCamera = 0;
	}

	// Release the D3D object.
	if (aRootPane)
	{
		aRootPane->Deinitialize();
		delete aRootPane;
		aRootPane = 0;
	}

	// Release the RenderData object.
	if (aRenderData)
	{
		aRenderData->Deinitialize();
		delete aRenderData;
		aRenderData = 0;
	}
}