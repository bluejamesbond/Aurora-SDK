
#include "../../Include/ExtLibs.h"
#include "../../Include/AbstractFrame.h"
#include "../../Include/TextureBuffer.h"

using namespace A2D;

/////////////////////////////////////////////////////////////////////////////
// REQUIRED BY A@D_ABSTRACT_FRAME
/////////////////////////////////////////////////////////////////////////////

int AbstractFrame::aClassInstances = -1;

void AbstractFrame::SetName(LPCWSTR xName)
{
	aWindow->setName(xName);
}

void AbstractFrame::setBounds(Rect * xRect)
{
	aWindow->setBounds(xRect);

	aWindow->invalidate();
	
	if (aWindow->isVisible())
	{
		aWindow->update();
	}
}

void AbstractFrame::setBounds(float xLeft, float xTop, float xWidth, float xHeight)
{
	aWindow->setBounds(xLeft, xTop, xWidth, xHeight);

	aWindow->invalidate();

	if (aWindow->isVisible())
	{
		aWindow->update();
	}
}

void AbstractFrame::SetSize(float xWidth, float xHeight)
{
	aWindow->setSize(xWidth, xHeight);

	aWindow->invalidate();

	if (aWindow->isVisible())
	{
		aWindow->update();
	}
}

void AbstractFrame::SetSize(Dims * xDims)
{
	aWindow->setSize(xDims);

	aWindow->invalidate();

	if (aWindow->isVisible())
	{
		aWindow->update();
	}
}

void AbstractFrame::SetUndecorated(bool xDecorated)
{
	aWindow->setUndecorated(xDecorated);

	aWindow->invalidate();

	if (aWindow->isVisible())
	{
		aWindow->update();
	}
}

void AbstractFrame::SetLocationRelativeTo(AbstractFrame * xFrame)
{
	aWindow->setLocationRelativeTo(xFrame ? xFrame->aWindow : NULL); //        WTF IS THIS INPUT FRAME BUT NEED WINDOW WTF

	aWindow->invalidate();

	if (aWindow->isVisible())
	{
		aWindow->update();
	}
}

void AbstractFrame::setBackground(byte xRed, byte xGreen, byte xBlue)
{
	Color color;

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

void AbstractFrame::setBorder(byte xAlpha, byte xRed, byte xGreen, byte xBlue, float xWidth)
{
	Color color;

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

void AbstractFrame::setShadow(byte xAlpha, byte xRed, byte xGreen, byte xBlue, float xRadius)
{
	Color color;

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

void AbstractFrame::SetVsync(bool xVsync)
{
	// Window doesn't have vsync yet.
}

void AbstractFrame::SetDefaultCloseOperation(int xOperation)
{
	aWindow->setDefaultCloseOperation(xOperation);
}

AbstractWindow* AbstractFrame::getWindow()
{
	return aWindow;
}

void AbstractFrame::SetVisible(bool xVisible)
{	
	if (xVisible)
	{
		if (!AbstractEventQueue::isDispatchingThread(this->id()) && aEventQueue)
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

void AbstractFrame::run(int xThreadId)
{
	this->Update();
}

/////////////////////////////////////////////////////////////////////////////
// REQUIRED BY _ABSTRACT
/////////////////////////////////////////////////////////////////////////////

LPCWSTR AbstractFrame::GetClass()
{
	return L"Frame";
}

LPCWSTR AbstractFrame::ToString()
{
	return L"Frame";
}

bool AbstractFrame::operator==(Abstract * xAbstract)
{
	return false;
}

int AbstractFrame::id()
{
	return aId;
}

void AbstractFrame::dispose()
{
	if (aEventQueue)
	{
		aWindow->setVisible(false);
		aEventQueue->stopDispatchingThread();
	}
}

HRESULT AbstractFrame::Initialize()
{
	HRESULT hr;	

	aId = ++aClassInstances;

	aEventQueue = createPlatformCompatibleEventQueue();

	hr = aEventQueue->Initialize();
	if (FAILED(hr))	return hr;
	
	// -----------------------------------------------------

	aRootPane = new RootPane;

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
//HRESULT AbstractFrame::initialize_()
//{
//	HRESULT hr;
//
//	aId = ++aClassInstances;
//
//	// -----------------------------------------------------
//
//	aRenderData = new RenderData();
//
//	hr = aRenderData->Initialize();
//	if (FAILED(hr))	return hr;
//
//	// -----------------------------------------------------
//
//	aRootPane = new RootPane;
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

void AbstractFrame::Deinitialize()
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


RootPane * AbstractFrame::GetRootPane()
{
	return aRootPane;
}

HRESULT AbstractFrame::CreateResources()
{
	HRESULT hr;
	
	// -----------------------------------------------------

	aWindow = createPlatformCompatibleWindow();

	hr = aWindow->Initialize();
	if (FAILED(hr))	return hr;

	// -----------------------------------------------------

	aBackBuffer = new BackBuffer(aWindow, &aGXSettings);

	hr = aBackBuffer->Initialize();
	if (FAILED(hr))	return hr;

	// -----------------------------------------------------

	aCamera = new Camera();

	hr = aCamera->Initialize();
	if (FAILED(hr))	return hr;

	// -----------------------------------------------------
	
	// Adjust camera settings and then create its resources.
	CameraProperties * cameraProperties = aCamera->GetProperties();

	cameraProperties->aPositionX = 0.0f;
	cameraProperties->aPositionY = 0.0f;
	cameraProperties->aPositionZ = -10.0f;

	// Create properties once the properties have been set
	aCamera->CreateResources();

	// Create graphics
	aGraphics = new Graphics();

	// Set the RenderData and pass it into RootPane to inialize the render process.
	aGraphics->aBackBuffer = aBackBuffer;
	aGraphics->aBlurBuffer = aBlurBuffer;
	aGraphics->aWindowDims = aWindow->_getSize();
	aGraphics->aCamera = aCamera;
	aGraphics->aViewMatrix = reinterpret_cast<float*>(aCamera->GetViewMatrix());
	aGraphics->aWorldMatrix = reinterpret_cast<float*>(MatrixFactory::createDefaultWorldMatrix());
	aGraphics->aProjection3DMatrix = reinterpret_cast<float*>(MatrixFactory::createDefaultProjectionMatrix(&aWindow->getSize(), &aGXSettings));
	aGraphics->aProjection2DMatrix = reinterpret_cast<float*>(MatrixFactory::createDefaultOrthogonalMatrix(&aWindow->getSize(), &aGXSettings));

	aRootPane->setBounds(0, 0, aWindow->getBounds().aWidth, aWindow->getBounds().aHeight);

	// Create graphics
	aGraphics->Initialize();

	return hr;
}

void AbstractFrame::validate()
{
	aBackBuffer->validate();

	delete aGraphics->aProjection2DMatrix;

	aGraphics->aProjection2DMatrix = reinterpret_cast<float*>(MatrixFactory::createDefaultOrthogonalMatrix(&aWindow->getSize(), &aGXSettings));

	aGraphics->validate();

	aValidatedContents = true;
}

void AbstractFrame::invalidate()
{
	aValidatedContents = false;
}

void AbstractFrame::validated()
{
	aValidatedContents = true;
}

void AbstractFrame::Update()
{
	if (!aValidatedContents)
	{
		validate();

		if (!aValidatedContents)	return;
	}

	aBackBuffer->SetActive();
	aBackBuffer->Clear();
	aBackBuffer->SetZBuffer(false);

	aRootPane->Update(aGraphics);

	aBackBuffer->SetZBuffer(true);
	aBackBuffer->Swap();
}
