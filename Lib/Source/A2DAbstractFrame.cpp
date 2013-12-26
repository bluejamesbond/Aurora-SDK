
#include "../../Include/A2DExtLibs.h"
#include "../../Include/A2DAbstractFrame.h"
#include "../../Include/A2DTextureBuffer.h"

/////////////////////////////////////////////////////////////////////////////
// REQUIRED BY A@D_ABSTRACT_FRAME
/////////////////////////////////////////////////////////////////////////////

void A2DAbstractFrame::SetName(LPCWSTR xName)
{
	aWindow->setName(xName);
}

void A2DAbstractFrame::SetBounds(A2DRect * xRect)
{
	aWindow->setBounds(xRect);

	aWindow->invalidate();
	aWindow->update();
}

void A2DAbstractFrame::SetBounds(float xLeft, float xTop, float xWidth, float xHeight)
{
	aWindow->setBounds(xLeft, xTop, xWidth, xHeight);

	aWindow->invalidate();
	aWindow->update();
}

void A2DAbstractFrame::SetSize(float xWidth, float xHeight)
{
	aWindow->setSize(xWidth, xHeight);

	aWindow->invalidate();
	aWindow->update();
}

void A2DAbstractFrame::SetSize(A2DDims * xDims)
{
	aWindow->setSize(xDims);

	aWindow->invalidate();
	aWindow->update();
}

void A2DAbstractFrame::SetUndecorated(bool xDecorated)
{
	aWindow->setUndecorated(xDecorated);

	aWindow->invalidate();
	aWindow->update();
}

void A2DAbstractFrame::SetLocationRelativeTo(A2DAbstractFrame * xFrame)
{
	aWindow->setLocationRelativeTo(xFrame ? xFrame->aWindow : NULL); //        WTF IS THIS INPUT FRAME BUT NEED WINDOW WTF

	aWindow->invalidate();
	aWindow->update();
}

void A2DAbstractFrame::setBackground(short xRed, short xGreen, short xBlue)
{
	A2DColor color;

	color.aAlpha = 0xFF;
	color.aRed = xRed;
	color.aGreen = xGreen;
	color.aBlue = xBlue;

	aWindow->setBackgroundColor(&color);
}

void A2DAbstractFrame::setBorder(short xAlpha, short xRed, short xGreen, short xBlue, float xWidth)
{
	A2DColor color;

	color.aAlpha = xAlpha;
	color.aRed = xRed;
	color.aGreen = xGreen;
	color.aBlue = xBlue;

	aWindow->setBorder(&color, xWidth);
}

void A2DAbstractFrame::setShadow(short xAlpha, short xRed, short xGreen, short xBlue, float xRadius)
{
	A2DColor color;

	color.aAlpha = xAlpha;
	color.aRed = xRed;
	color.aGreen = xGreen;
	color.aBlue = xBlue;

	aWindow->setShadow(&color, xRadius);
}

void A2DAbstractFrame::SetVsync(bool xVsync)
{
	// A2DWindow doesn't have vsync yet.
}

void A2DAbstractFrame::SetDefaultCloseOperation(int xOperation)
{
	aWindow->setDefaultCloseOperation(xOperation);
}

void A2DAbstractFrame::SetVisible(bool xVisible)
{
	aWindow->setVisible(xVisible);
}

/////////////////////////////////////////////////////////////////////////////
// REQUIRED BY A2D_ABSTRACT
/////////////////////////////////////////////////////////////////////////////

LPCWSTR A2DAbstractFrame::GetClass()
{
	return L"A2DFrame";
}

LPCWSTR A2DAbstractFrame::ToString()
{
	return L"A2DFrame";
}

bool A2DAbstractFrame::operator==(A2DAbstract * xAbstract)
{
	return false;
}

HRESULT A2DAbstractFrame::Initialize()
{
	HRESULT hr;	

	// -----------------------------------------------------

	aWindow = createPlatformCompatibleWindow();

	hr = aWindow->Initialize();
	if (FAILED(hr))	return hr;

	aWindow->setFrame(this);

	// -----------------------------------------------------

	aRootPane = new A2DRootPane;

	hr = aRootPane->Initialize();
	if (FAILED(hr))	return hr;

	// -----------------------------------------------------

	aBackBuffer = new A2DBackBuffer(aWindow, &aGXSettings);

	hr = aBackBuffer->Initialize();
	if (FAILED(hr))	return hr;

	// -----------------------------------------------------

	aCamera = new A2DCamera();

	hr = aCamera->Initialize();
	if (FAILED(hr))	return hr;

	// -----------------------------------------------------

	aTextureBuffer = new A2DTextureBuffer(aBackBuffer, static_cast<A2DDims *>(&aWindow->getBounds()));

	hr = aTextureBuffer->Initialize();
	if (FAILED(hr))	return hr;

	// -----------------------------------------------------

	aBlurBuffer = new A2DTextureBuffer(aBackBuffer, static_cast<A2DDims *>(&aWindow->getBounds()));

	hr = aBlurBuffer->Initialize();
	if (FAILED(hr))	return hr;

	// -----------------------------------------------------

	aRenderData = new A2DRenderData();

	hr = aRenderData->Initialize();
	if (FAILED(hr))	return hr;

	// -----------------------------------------------------
		
	return hr;
}

void A2DAbstractFrame::Deinitialize()
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


A2DRootPane * A2DAbstractFrame::GetRootPane()
{
	return aRootPane;
}

HRESULT A2DAbstractFrame::CreateResources()
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
	aRenderData->aWindow = aWindow;
	aRenderData->aCamera = aCamera;
	aRenderData->aViewMatrix = aCamera->GetViewMatrix();
	aRenderData->aWorldMatrix = A2DMatrixFactory::createDefaultWorldMatrix();
	aRenderData->aProjectionMatrix = A2DMatrixFactory::createDefaultProjectionMatrix(static_cast<A2DDims *>(&aWindow->getBounds()), &aGXSettings);
	aRenderData->aOrthogonalMatrix = A2DMatrixFactory::createDefaultOrthogonalMatrix(static_cast<A2DDims *>(&aWindow->getBounds()), &aGXSettings);

	aRootPane->SetBounds(0, 0, aWindow->getBounds().aWidth/2, aWindow->getBounds().aHeight);

	// Create children resources; This also calls all subsequent children and
	// creates their resources.
	hr = aRootPane->CreateResources(aRenderData);

	return hr;
}

void A2DAbstractFrame::Update()
{
	aBackBuffer->SetActive();
	aBackBuffer->Clear();
	aBackBuffer->SetZBuffer(false);

	aRootPane->Update();

	aBackBuffer->SetZBuffer(true);
	aBackBuffer->Swap();
}
