
#include "../../Include/A2DExtLibs.h"
#include "../../Include/A2DAbstractFrame.h"
#include "../../Include/A2DTextureBuffer.h"

/////////////////////////////////////////////////////////////////////////////
// REQUIRED BY A@D_ABSTRACT_FRAME
/////////////////////////////////////////////////////////////////////////////

int A2DAbstractFrame::aClassInstances = -1;

void A2DAbstractFrame::SetName(LPCWSTR xName)
{
	aWindow->setName(xName);
}

void A2DAbstractFrame::SetBounds(A2DRect * xRect)
{
	aWindow->setBounds(xRect);

	aWindow->invalidate();
	
	if (aWindow->isVisible())
	{
		aWindow->update();
	}
}

void A2DAbstractFrame::SetBounds(float xLeft, float xTop, float xWidth, float xHeight)
{
	aWindow->setBounds(xLeft, xTop, xWidth, xHeight);

	aWindow->invalidate();

	if (aWindow->isVisible())
	{
		aWindow->update();
	}
}

void A2DAbstractFrame::SetSize(float xWidth, float xHeight)
{
	aWindow->setSize(xWidth, xHeight);

	aWindow->invalidate();

	if (aWindow->isVisible())
	{
		aWindow->update();
	}
}

void A2DAbstractFrame::SetSize(A2DDims * xDims)
{
	aWindow->setSize(xDims);

	aWindow->invalidate();

	if (aWindow->isVisible())
	{
		aWindow->update();
	}
}

void A2DAbstractFrame::SetUndecorated(bool xDecorated)
{
	aWindow->setUndecorated(xDecorated);

	aWindow->invalidate();

	if (aWindow->isVisible())
	{
		aWindow->update();
	}
}

void A2DAbstractFrame::SetLocationRelativeTo(A2DAbstractFrame * xFrame)
{
	aWindow->setLocationRelativeTo(xFrame ? xFrame->aWindow : NULL); //        WTF IS THIS INPUT FRAME BUT NEED WINDOW WTF

	aWindow->invalidate();

	if (aWindow->isVisible())
	{
		aWindow->update();
	}
}

void A2DAbstractFrame::setBackground(byte xRed, byte xGreen, byte xBlue)
{
	A2DColor color;

	color.aAlpha = 0xFF;
	color.aRed = xRed;
	color.aGreen = xGreen;
	color.aBlue = xBlue;

	aWindow->setBackgroundColor(&color);

	aWindow->invalidate();

	if (aWindow->isVisible())
	{
		aWindow->update();
	}
}

void A2DAbstractFrame::setBorder(byte xAlpha, byte xRed, byte xGreen, byte xBlue, float xWidth)
{
	A2DColor color;

	color.aAlpha = xAlpha;
	color.aRed = xRed;
	color.aGreen = xGreen;
	color.aBlue = xBlue;

	aWindow->setBorder(&color, xWidth);


	aWindow->invalidate();

	if (aWindow->isVisible())
	{
		aWindow->update();
	}
}

void A2DAbstractFrame::setShadow(byte xAlpha, byte xRed, byte xGreen, byte xBlue, float xRadius)
{
	A2DColor color;

	color.aAlpha = xAlpha;
	color.aRed = xRed;
	color.aGreen = xGreen;
	color.aBlue = xBlue;

	aWindow->setShadow(&color, xRadius);

	aWindow->invalidate();

	if (aWindow->isVisible())
	{
		aWindow->update();
	}
}

void A2DAbstractFrame::SetVsync(bool xVsync)
{
	// A2DWindow doesn't have vsync yet.
}

void A2DAbstractFrame::SetDefaultCloseOperation(int xOperation)
{
	aWindow->setDefaultCloseOperation(xOperation);
}

A2DAbstractWindow* A2DAbstractFrame::getWindow()
{
	return aWindow;
}

void A2DAbstractFrame::SetVisible(bool xVisible)
{	
	if (xVisible)
	{
		if (!A2DAbstractEventQueue::isDispatchingThread(this->id()) && aEventQueue)
		{
			aEventQueue->invokeLater(this);
			aEventQueue->resumeDispatchingThread();
		}

		aWindow->setVisible(xVisible);
	}
	else
	{
		aWindow->setVisible(xVisible);
		
		if (aEventQueue)
		{
			aEventQueue->interruptDispatchingThread();
		}
	}
}

void A2DAbstractFrame::run(int xThreadId)
{
	this->Update();
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

int A2DAbstractFrame::id()
{
	return aId;
}

void A2DAbstractFrame::dispose()
{
	if (aEventQueue)
	{
		aWindow->setVisible(false);
		aEventQueue->stopDispatchingThread();
	}
}

HRESULT A2DAbstractFrame::Initialize()
{
	HRESULT hr;	

	aId = ++aClassInstances;

	aEventQueue = createPlatformCompatibleEventQueue();

	hr = aEventQueue->Initialize();
	if (FAILED(hr))	return hr;
	
	// -----------------------------------------------------

	aRootPane = new A2DRootPane;

	hr = aRootPane->Initialize();
	if (FAILED(hr))	return hr;

	// -----------------------------------------------------

	aEventQueue->startDispatchingThread();

	// -----------------------------------------------------

	return hr;
}

// Window is created here.
// Note: We will not continue support development
// outside of EDT. We might come back to it in the future.
//HRESULT A2DAbstractFrame::initialize_()
//{
//	HRESULT hr;
//
//	aId = ++aClassInstances;
//
//	// -----------------------------------------------------
//
//	aRenderData = new A2DRenderData();
//
//	hr = aRenderData->Initialize();
//	if (FAILED(hr))	return hr;
//
//	// -----------------------------------------------------
//
//	aRootPane = new A2DRootPane;
//
//	hr = aRootPane->Initialize();
//	if (FAILED(hr))	return hr;
//
//	// -----------------------------------------------------
//
//	hr = createWindow();
//
//	// -----------------------------------------------------
//
//	return hr;
//}

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
	if (aGraphics)
	{
		aGraphics->Deinitialize();
		delete aGraphics;
		aGraphics = 0;
	}
}


A2DRootPane * A2DAbstractFrame::GetRootPane()
{
	return aRootPane;
}

HRESULT A2DAbstractFrame::CreateResources()
{
	HRESULT hr;
	
	// -----------------------------------------------------

	aWindow = createPlatformCompatibleWindow();

	hr = aWindow->Initialize();
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
	
	// Adjust camera settings and then create its resources.
	A2DCameraProperties * cameraProperties = aCamera->GetProperties();

	cameraProperties->aPositionX = 0.0f;
	cameraProperties->aPositionY = 0.0f;
	cameraProperties->aPositionZ = -10.0f;

	// Create properties once the properties have been set
	aCamera->CreateResources();

	// Create graphics
	aGraphics = new A2DGraphics();

	// Set the RenderData and pass it into RootPane to inialize the render process.
	aGraphics->aBackBuffer = aBackBuffer;
	aGraphics->aBlurBuffer = aBlurBuffer;
	aGraphics->aWindowDims = aWindow->_getSize();
	aGraphics->aCamera = aCamera;
	aGraphics->aViewMatrix = reinterpret_cast<float*>(aCamera->GetViewMatrix());
	aGraphics->aWorldMatrix = reinterpret_cast<float*>(A2DMatrixFactory::createDefaultWorldMatrix());
	aGraphics->aProjection3DMatrix = reinterpret_cast<float*>(A2DMatrixFactory::createDefaultProjectionMatrix(&aWindow->getSize(), &aGXSettings));
	aGraphics->aProjection2DMatrix = reinterpret_cast<float*>(A2DMatrixFactory::createDefaultOrthogonalMatrix(&aWindow->getSize(), &aGXSettings));

	aRootPane->SetBounds(0, 0, aWindow->getBounds().aWidth, aWindow->getBounds().aHeight);

	// Create graphics
	aGraphics->Initialize();

	return hr;
}

void A2DAbstractFrame::validate()
{
	// aBackBuffer->validate();

	delete aGraphics->aProjection2DMatrix;

	aGraphics->aProjection2DMatrix = reinterpret_cast<float*>(A2DMatrixFactory::createDefaultOrthogonalMatrix(&aWindow->getSize(), &aGXSettings));

	aGraphics->validate();

	aValidatedContents = true;
}

void A2DAbstractFrame::invalidate()
{
	aValidatedContents = false;
}

void A2DAbstractFrame::validated()
{
	aValidatedContents = true;
}

void A2DAbstractFrame::Update()
{
	if (!aValidatedContents)
	{
		validate();
	}

	aBackBuffer->SetActive();
	aBackBuffer->Clear();
	aBackBuffer->SetZBuffer(false);

	aRootPane->Update(aGraphics);

	aBackBuffer->SetZBuffer(true);
	aBackBuffer->Swap();
}
