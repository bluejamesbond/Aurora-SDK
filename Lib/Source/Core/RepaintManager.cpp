
#include "../../../Include/Core/ExtLibs.h"
#include "../../../Include/Core/RepaintManager.h"
#include "../../../Include/Core/Component.h"

using namespace A2D;

RepaintManager::RepaintManager(void * xGraphics, Component * xRoot)
{
    aGraphics = xGraphics;
	aBackBufferDims = aBackBuffer->getSizeAsPtr();
	aRoot = xRoot;
}

HRESULT RepaintManager::initialize()
{
	Component& root = *aRoot;

	// Set based on camera properties later
	// For now it is hardcoded
	// xGraphics->getCameraProperties();

	addToDepthTracker(root, 0.0f);

	return S_OK;
}

void RepaintManager::validate()
{
	return;

    aBackBuffer->validate();
}

RepaintManager::~RepaintManager(){}

HRESULT RepaintManager::add(Component& xParent, Component& xChild)
{
    float depth = 0.0f;

    if (depth == 0.0)
	{
		return E_FAIL;
	}

	static float val = -0.01f;

	
	if (addToDepthTracker(xChild, abs(depth)))
    {

		return S_OK;
	}

	return E_FAIL;
}

bool RepaintManager::addToDepthTracker(Component& xComponent, float xZ)
{
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

void RepaintManager::update()
{
	AbstractBackBuffer * backBuffer = aBackBuffer;

	return;

	backBuffer->setActive();
	backBuffer->clear();
	backBuffer->setZBuffer(false);

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
                    //component->update();
				}
			}
		}
	}

	backBuffer->setZBuffer(true);
	backBuffer->swap();
}

void RepaintManager::update_forward()
{
	AbstractBackBuffer * backBuffer = aBackBuffer;

	return;

	backBuffer->setActive();
	backBuffer->clear();
	backBuffer->setZBuffer(false);

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
                    //component->update();
				}
			}
		}
	}


	backBuffer->setZBuffer(true);
	backBuffer->swap();
}
