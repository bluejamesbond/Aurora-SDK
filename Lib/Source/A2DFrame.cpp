
#include "../../Include/A2DExtLibs.h"
#include "../../Include/A2DFrame.h"
#include "../../Include/A2DTextureBuffer.h"

A2DFrame::A2DFrame(HINSTANCE * xHInstance) : aHInstance(xHInstance) {}

A2DFrame::~A2DFrame(){}

A2DRootPane * A2DFrame::GetRootPane()
{
	return aRootPane;
}

A2DCamera * A2DFrame::GetCamera()
{
	return aCamera;
}

A2DRenderData * A2DFrame::GetRenderData()
{
	return aRenderData;
}

HRESULT A2DFrame::CreateResources()
{
	
	HRESULT hr;

	// Adjust camera settings and then create its resources.
	A2DCameraProperties * cameraProperties = aCamera->GetProperties();

	cameraProperties->aPositionX = 0.0f;
	cameraProperties->aPositionY = 0.0f;
	cameraProperties->aPositionZ = -10.0f;

	// Create properties once the properties have been set
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

LRESULT A2DFrame::PumpWindowMsg(HWND * xHwnd, UINT * xMessage, WPARAM * xWParam, LPARAM * xLParam)
{
	return aRootPane->WindowMsg(xHwnd, xMessage,xWParam, xLParam);
}

void A2DFrame::Update()
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

LPCWSTR A2DFrame::GetClass()
{
	return L"A2DFrame";
}

LPCWSTR A2DFrame::ToString()
{
	return L"A2DFrame";
}

bool A2DFrame::operator==(A2DAbstract * xAbstract)
{
	return false;
}

HRESULT A2DFrame::Initialize()
{
	HRESULT hr;	

	// -----------------------------------------------------

	aWindow = new A2DWindow(aHInstance, aWindowProps);

	hr = aWindow->Initialize();
	if (FAILED(hr))	return hr;

	// -----------------------------------------------------

	aRootPane = new A2DRootPane(aWindowProps);

	hr = aRootPane->Initialize();
	if (FAILED(hr))	return hr;

	// -----------------------------------------------------

	aBackBuffer = new A2DBackBuffer(aWindow, aWindowProps);

	hr = aBackBuffer->Initialize();
	if (FAILED(hr))	return hr;

	// -----------------------------------------------------

	aCamera = new A2DCamera();

	hr = aCamera->Initialize();
	if (FAILED(hr))	return hr;

	// -----------------------------------------------------

	aTextureBuffer = new A2DTextureBuffer(aBackBuffer, aWindowProps->GetRealSize());

	hr = aTextureBuffer->Initialize();
	if (FAILED(hr))	return hr;

	// -----------------------------------------------------

	aBlurBuffer = new A2DTextureBuffer(aBackBuffer, aWindowProps->GetRealSize());

	hr = aBlurBuffer->Initialize();
	if (FAILED(hr))	return hr;

	// -----------------------------------------------------

	aRenderData = new A2DRenderData();

	hr = aRenderData->Initialize();
	if (FAILED(hr))	return hr;

	// -----------------------------------------------------

	aRootPane->SetBounds(0, 0, aWindowProps->GetRealSize()->aWidth, aWindowProps->GetRealSize()->aHeight);
	aWindow->SetFrame(this);

	// -----------------------------------------------------
	
	return hr;
}

void A2DFrame::Deinitialize()
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