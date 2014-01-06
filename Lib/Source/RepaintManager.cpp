
#include "../../include/ExtLibs.h"
#include "../../include/RepaintManager.h"
#include "../../include/Component.h"
#include "../../include/Graphics.h"

using namespace A2D;

RepaintManager::RepaintManager(Graphics * xGraphics, Component * xRoot)
{
	aGraphics = xGraphics;
	aBackBuffer = aGraphics->getBackBuffer();
	aRoot = xRoot;
}

RepaintManager::~RepaintManager(){}

HRESULT RepaintManager::add(Component& xParent, Component& xChild)
{
	float depth = xParent.getDepth();

	if (depth == FLT_MIN)
	{
		return E_FAIL;
	}

	static float val = -0.01f;

	xChild.setParent(xParent);
	xChild.setDepth(--depth);
	xChild.setGraphics(xParent.getGraphics());
	
	if (addToDepthTracker(xChild, abs(depth)))
	{
		xParent.add(xChild);
		xParent.revalidate(); // force validation asap

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
	BackBuffer * backBuffer = aBackBuffer;

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

void RepaintManager::update_forward()
{
	BackBuffer * backBuffer = aBackBuffer;

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

void RepaintManager::validate()
{
	// aRoot->setBounds(0, 0, aBackBufferDims->aWidth, aBackBufferDims->aHeight);
}

HRESULT RepaintManager::initialize()
{
	Component& root = *aRoot;

	// Set based on camera properties later
	// For now it is hardcoded
	// xGraphics->getCameraProperties();

	root.setDepth(0.0f);
	root.setGraphics(*aGraphics);

	addToDepthTracker(root, 0.0f);

	return S_OK;
}

LPCWSTR RepaintManager::getClass()
{
	return L"RepaintManager";
}

LPCWSTR RepaintManager::toString()
{
	return L"RepaintManager";
}