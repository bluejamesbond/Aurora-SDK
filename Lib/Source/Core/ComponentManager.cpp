
#include "../../../include/Core/ExtLibs.h"
#include "../../../include/Core/ComponentManager.h"
#include "../../../include/Core/Component.h"
#include "../../../include/Core/AbstractWindow.h"
#include "../../../include/Core/AbstractFrame.h"

using namespace A2D;

ComponentManager::ComponentManager(void * xGraphics, Component * xRoot, AbstractWindow * xWindow)
{
	aGraphics = xGraphics;
	aBackBuffer = static_cast<Graphics*>(aGraphics)->getBackBuffer();
	aBackBufferDims = aBackBuffer->getSizeAsPtr();
	aRoot = xRoot;
	aWindow = xWindow;
}

STATUS ComponentManager::initialize()
{
	Component& root = *aRoot;

	// Set based on camera properties later
	// For now it is hardcoded
	// xGraphics->getCameraProperties();

	root.setDepth(0.0f);
	root.setGraphics(*static_cast<Graphics*>(aGraphics));

	addToDepthTracker(root, 0.0f);

	return STATUS_OK;
}

ComponentManager::~ComponentManager(){}

AbstractWindow * ComponentManager::getWindow()
{
	return aWindow;
}

STATUS ComponentManager::add(Component& xParent, Component& xChild)
{
	float depth = xParent.getDepth();

	if (depth == FLT_MIN)
	{
		return STATUS_FAIL;
	}
	
	xChild.setParent(xParent);
	xChild.setDepth(++depth);
	xChild.setGraphics(xParent.getGraphics());
	
	if (addToDepthTracker(xChild, abs(depth)))
	{
		xParent.add(xChild);
		xParent.revalidate(); // force validation asap

		return STATUS_OK;
	}

	return STATUS_FAIL;
}

bool ComponentManager::addToDepthTracker(Component& xComponent, float xZ)
{
	// Call eventDepthTracker also.
	xComponent.aComponentManager = this;
	Toolkit::getSystemEventQueue(aWindow->getFrame()->id())->addEventDepthTracker(&xComponent, xZ);
	UnorderedList<Component*> * peerComponents;

	int maxZ = aOpaqueDepthTracker.size() - 1;
	int neededZ = INT(xZ);

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


	return 1;
}

void ComponentManager::update()
{
	AbstractBackBuffer * backBuffer = aBackBuffer;

	backBuffer->setActive();
	backBuffer->clear();
//	backBuffer->setZBuffer(false);

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

//	backBuffer->setZBuffer(true);
	backBuffer->swap();
}

void ComponentManager::update_forward()
{
	AbstractBackBuffer * backBuffer = aBackBuffer;

	backBuffer->setActive();
	backBuffer->clear();
	//backBuffer->setZBuffer(false);

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

	//backBuffer->setZBuffer(true);
	backBuffer->swap();
}