
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

	xChild._setDepth(++depth);
	xChild._setGraphics(xParent.getGraphics());

	xChild.invalidate();

	if (addToDepthTracker(xChild, depth))
	{
		xParent._add(xChild);

		return S_OK;
	}

	return E_FAIL;
}

HRESULT RepaintManager::addToDepthTracker(Component& xComponent, float xZ)
{
	UnorderedList<Component*> * peerComponents;

	int maxZ = aOpaqueDepthTracker.size() - 1;
	int neededZ = static_cast<int>(xZ);

	if (maxZ <= neededZ)
	{
		while (maxZ++ <= neededZ)
		{
			aOpaqueDepthTracker.push_back(peerComponents = new UnorderedList<Component*>());
		}

		peerComponents->push(&xComponent);
	}
	else
	{
		aOpaqueDepthTracker.get(neededZ)->push(&xComponent);
	}


	return S_OK;
}

void RepaintManager::update()
{
	BackBuffer * backBuffer = aBackBuffer;

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
					component->update();
				}
			}
		}
	}

	backBuffer->setZBuffer(true);
	backBuffer->swap();
}

void RepaintManager::validate()
{

}

HRESULT RepaintManager::initialize()
{
	Component& root = *aRoot;

	// Set based on camera properties later
	// For now it is hardcoded
	// xGraphics->getCameraProperties();

	root._setDepth(0.0f);
	root._setGraphics(*aGraphics);

	addToDepthTracker(root, 0.0f);
	root.setBounds(0, 0, 500, 500);
	root.invalidate();

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