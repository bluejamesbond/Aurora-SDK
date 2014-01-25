#include "../../../Include/Core/ExtLibs.h"
#include "../../../Include/Core/AbstractFrame.h"

using namespace A2D;

int AbstractFrame::aClassInstances = -1;

AbstractFrame::AbstractFrame() : aRepaintManager(NULL) {}

AbstractFrame::~AbstractFrame()
{
	DESTROY(aBackBuffer);
	DESTROY(aRepaintManager);
	DESTROY(aGraphics);
}

void AbstractFrame::setName(LPCWSTR xName)
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

void AbstractFrame::setSize(float xWidth, float xHeight)
{
	aWindow->setSize(xWidth, xHeight);

	aWindow->invalidate();

	if (aWindow->isVisible())
	{
		aWindow->update();
	}
}

void AbstractFrame::setSize(Dims * xDims)
{
	aWindow->setSize(xDims);

	aWindow->invalidate();

	if (aWindow->isVisible())
	{
		aWindow->update();
	}
}

void AbstractFrame::setUndecorated(bool xDecorated)
{
	aWindow->setUndecorated(xDecorated);

	aWindow->invalidate();

	if (aWindow->isVisible())
	{
		aWindow->update();
	}
}

void AbstractFrame::setLocationRelativeTo(AbstractFrame * xFrame)
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

void AbstractFrame::setVsync(bool xVsync)
{
	// Window doesn't have vsync yet.
}

void AbstractFrame::setDefaultCloseOperation(int xOperation)
{
	aWindow->setDefaultCloseOperation(xOperation);
}

AbstractWindow* AbstractFrame::getWindow()
{
	return aWindow;
}

void AbstractFrame::setVisible(bool xVisible)
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
	this->update();
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

RepaintManager* AbstractFrame::getRepaintManager()
{
	return aRepaintManager;
}

HRESULT AbstractFrame::initialize()
{
	aId = ++aClassInstances;


	SAFELY(createPlatformCompatibleEventQueue(&aEventQueue));
	SAFELY(aEventQueue->initialize());	
	
	aEventQueue->startDispatchingThread();
	
	return S_OK;
}


HRESULT AbstractFrame::createResources()
{	
	SYSOUT_STR("[AbstractFrame] CreateResources started.");

	SAFELY(createPlatformCompatibleWindow(&aWindow));
	SAFELY(aWindow->initialize());

	SYSOUT_STR("[AbstractFrame] CreatePlatformCompatibleWindow - Window.");

	SAFELY(createPlatformCompatibleBackBuffer(&aBackBuffer, aWindow, &aGXSettings));
	SAFELY(aBackBuffer->initialize());

	SYSOUT_STR("[AbstractFrame] CreatePlatformCompatibleBackBuffer - Backbuffer.");

	SAFELY(createAndInitPlatformCompatibleGraphics(&aGraphics, aBackBuffer));
	
    aRepaintManager = new RepaintManager(aGraphics, NULL);
	SAFELY(aRepaintManager->initialize());

	aWindowDims = aWindow->getSizeAsPtr();

	SYSOUT_STR("[AbstractFrame] CreateResources successfully completed.");

	return S_OK;
}

void AbstractFrame::invalidate()
{
	aValidatedContents = false;
}

void AbstractFrame::validated()
{
	aValidatedContents = true;
}

void AbstractFrame::update()
{
    SYSOUT_STR("[AbstractFrame] Updating per-frame content.");

    if(!aRepaintManager) return;

    if (!aValidatedContents)
	{
    	aRepaintManager->validate();

		aRepaintManager->update_forward();

    	aValidatedContents = true;

		return;
	}

    aRepaintManager->update();
}
