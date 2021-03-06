
#include "../../../Include/Core/ExtLibs.h"
#include "../../../Include/Core/AbstractFrame.h"

using namespace A2D;

int AbstractFrame::aClassInstances = -1;

AbstractFrame::AbstractFrame(){}

AbstractFrame::~AbstractFrame()
{
	DESTROY(aBackBuffer);
	DESTROY(aComponentManager);
	DESTROY(aGraphics);
}

void AbstractFrame::setName(wchar_t * xName)
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

void AbstractFrame::run(void * x_param, int xThreadId)
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

const ComponentManager * AbstractFrame::getComponentManager()
{
	return aComponentManager;
}

STATUS AbstractFrame::initialize()
{
	aId = ++aClassInstances;

	SAFELY(aRootPane.initialize());

	SAFELY(createPlatformCompatibleEventQueue(&aEventQueue));
	SAFELY(aEventQueue->initialize());	
	
	aEventQueue->startDispatchingThread();
	
	return STATUS_OK;
}

Panel& AbstractFrame::getRootPane()
{
	return aRootPane;
}

STATUS AbstractFrame::createResources()
{	
	SAFELY(createPlatformCompatibleWindow(&aWindow));
	SAFELY(aWindow->initialize());	

	SAFELY(createPlatformCompatibleBackBuffer(&aBackBuffer, aWindow, &aGXSettings));
	SAFELY(aBackBuffer->initialize());

	SAFELY(createAndInitPlatformCompatibleGraphics(&aGraphics, aBackBuffer));
	
	aComponentManager = new ComponentManager(aGraphics, &aRootPane, aWindow);
	SAFELY(aComponentManager->initialize());
	
	return STATUS_OK;
}

void AbstractFrame::invalidate()
{
	aValidatedContents = false;
}

void AbstractFrame::validated()
{
	aValidatedContents = true;
}

STATUS AbstractFrame::addListener(AbstractListener * xListener)
{
	OrderedList<EventSource*> * sourceList = &Toolkit::getSystemEventQueue(aId)->aEventSourcesList;
	OrderedList<EventSource*>::Node<EventSource*> * node = sourceList->_end();
	while (node)
	{
		if (node->value == this) // may be broken, need to overload ==operator
		{
			break; // don't have to add, so do nothing.
		}
		node = node->left;
	}

	sourceList->push_back(this, &aRemoveTicket);

	return EventSource::addListener(xListener);
}

STATUS AbstractFrame::removeListener(AbstractListener * xListener)
{
	OrderedList<EventSource*> sourceList = Toolkit::getSystemEventQueue(aId)->aEventSourcesList;
	OrderedList<EventSource*>::Node<EventSource*> * node = sourceList._end();
	while (node)
	{
		if (node->value == this) // may be broken, need to overload ==operator
		{
			if (sourceList.remove_request(&aRemoveTicket))
			{
				break;
			}
			else
			{
				return STATUS_FAIL;
			}
		}
		node = node->left;
	}

	return EventSource::removeListener(xListener);
}

Rect * AbstractFrame::getEventRegion()
{
	return &aWindow->getBounds();
}

void AbstractFrame::update()
{
	if (!aValidatedContents)
	{
		aComponentManager->validate();
		
		aValidatedContents = true;
	}

	// NVIDIA wants us to use bottom to top
	// and remove depth buffer testing
	aComponentManager->updateBottomToTop();
}
