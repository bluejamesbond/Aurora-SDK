
#include "../../../include/Core/ExtLibs.h"
#include "../../../include/Core/ComponentManager.h"
#include "../../../include/Core/Component.h"
#include "../../../include/Core/AbstractWindow.h"
#include "../../../include/Core/AbstractFrame.h"

using namespace A2D;

ComponentManager::ComponentManager(void * xGraphics, Component * xRoot, AbstractWindow * xWindow)
{
	aGraphics = static_cast<Graphics*>(xGraphics);
	aBackBuffer = static_cast<Graphics*>(aGraphics)->getBackBuffer();
	m_textureBuffer = aGraphics->createTextureBuffer(aBackBuffer->getSize());
	aBackBufferDims = aBackBuffer->getSizeAsPtr();
	aRoot = xRoot;
	aWindow = xWindow;
	m_eventQueue = Toolkit::getSystemEventQueue(aWindow->getFrame()->id());
}

STATUS ComponentManager::initialize()
{
	Component& root = *aRoot;

	// Set based on camera properties later
	// For now it is hardcoded
	// xGraphics->getCameraProperties();
	//------------------------------------------------------------------------------
	root.setGraphics(*aGraphics);
	root.setComponentManager(*this);
	root.setDepth(0);
	root.setEventQueue(*m_eventQueue);

	addToDepthTracker(root);

	return STATUS_OK;
}

ComponentManager::~ComponentManager(){}

AbstractWindow * ComponentManager::getWindow()
{
	return aWindow;
}

STATUS ComponentManager::add(Component& xParent, Component& xChild) const
{
	int depth = xParent.getDepth();

	if (depth == INT_MIN)
	{
		return STATUS_FAIL;
	}
	
	xChild.setParent(xParent);
	xChild.setDepth(++depth);
	xChild.setGraphics(xParent.getGraphics());
	xChild.setComponentManager(*unconst__(ComponentManager*));
	xChild.setEventQueue(*m_eventQueue);
	xChild.initialize();

	if (unconst__(ComponentManager*)->addToDepthTracker(xChild))
	{
		xParent.add(xChild);
		xParent.revalidate(); // force validation asap

		return STATUS_OK;
	}

	return STATUS_FAIL;
}

bool ComponentManager::addToDepthTracker(Component& xComponent)
{
	// Call eventDepthTracker also.
	m_eventQueue->addEventDepthTracker(&xComponent, xComponent.getDepth());
	UnorderedList<Component*> * peerComponents = NULL;

	int maxZ = aOpaqueDepthTracker.size() - 1;
	int neededZ = xComponent.getDepth();

	if (maxZ <= neededZ)
	{
		while (maxZ++ <= neededZ)
		{
			aOpaqueDepthTracker.push_back(peerComponents = new UnorderedList<Component*>(), NULL);
		}

		peerComponents->push(&xComponent);
	}
	else
	{
		aOpaqueDepthTracker.get(neededZ)->push(&xComponent);
	}


	return true;
}

void ComponentManager::updateTopToBottom()
{
	AbstractBackBuffer * backBuffer = aBackBuffer;

	backBuffer->setActive();
	backBuffer->clear();
	backBuffer->setZBuffer(true);

	int i, heapSize = 0, size = 0;
	OrderedList<UnorderedList<Component*>*>::Iterator<UnorderedList<Component*>*>& iterator = aOpaqueDepthTracker.reverse_iterator();
	Component * component;

	while (iterator.has_previous())
	{
		UnorderedList<Component*> * containers = iterator.previous();

		if (containers->size() > 0)
		{
			heapSize = containers->heap_size();
			size = containers->size();

			for (i = 0; i < size; i++)
			{
				if ((component = containers->get(i)) != NULL)
				{
					component->update();
				}
			}
		}
	}

	backBuffer->swap();
}

void ComponentManager::updateBottomToTop()
{
	AbstractBackBuffer * backBuffer = aBackBuffer;
	Bufferable * cacheBuffer = m_textureBuffer;

	backBuffer->setActive();
//	cacheBuffer->setActive();

	int i, heapSize = 0, size = 0;
	OrderedList<UnorderedList<Component*>*>::Iterator<UnorderedList<Component*>*>& iterator = aOpaqueDepthTracker.iterator();
	Component * component;

	while (iterator.has_next())
	{
		UnorderedList<Component*> * containers = iterator.next();

		if (containers->size() > 0)
		{
			heapSize = containers->heap_size();
			size = containers->size();

			for (i = 0; i < size; i++)
			{
				if ((component = containers->get(i)) != NULL)
				{
					component->update();
				}
			}
		}
	}

//	backBuffer->setActive();
	backBuffer->swap();
}