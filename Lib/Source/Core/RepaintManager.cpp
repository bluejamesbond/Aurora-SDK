
#include "../../../Include/Core/ExtLibs.h"
#include "../../../Include/Core/RepaintManager.h"
#include "../../../Include/Core/Component.h"
#include "../../../Include/Linux/GLShaderUtils.h"

using namespace A2D;

RepaintManager::RepaintManager(void * xGraphics, Component * xRoot)
{
    aGraphics = xGraphics;
    aBackBuffer = static_cast<Graphics*>(aGraphics)->getBackBuffer();
	aBackBufferDims = aBackBuffer->getSizeAsPtr();
	aRoot = xRoot;
}

HRESULT RepaintManager::initialize()
{
	Component& root = *aRoot;

	// Set based on camera properties later
	// For now it is hardcoded
	// xGraphics->getCameraProperties();

	 root.setGraphics(*static_cast<Graphics*>(aGraphics));
	 //root.setRepaintManager(*this);
	 root.setDepth(0);

	 addToDepthTracker(root, 0.0f);

	return S_OK;
}

void RepaintManager::validate()
{
    aBackBuffer->validate();

    translationX += (translationX + width) >= max_width || translationX < 0.0f ? ((translationXDirection*=-1) * translationXG1) : (translationXDirection * translationXG1);
    translationY += (translationY + height) >= max_height || translationY < 0.0f? ((translationYDirection*=-1) * translationYG1) : (translationYDirection * translationYG1);

    // FIXME Forced in root size
    aRoot->forceBounds(true);
    aRoot->setBounds(translationX,translationY,width,height);
}

RepaintManager::~RepaintManager(){}

HRESULT RepaintManager::add(Component& xParent, Component& xChild)
{
    float depth = xParent.getDepth();

    if (depth == FLT_MIN)
	{
		return E_FAIL;
	}

	xChild.setParent(xParent);
	xChild.setDepth(++depth);
	xChild.setGraphics(xParent.getGraphics());

	if (addToDepthTracker(xChild, abs(depth)))
    {
		SYSOUT_STR("[RepaintManager] Component added");

        xParent.add(xChild);
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

	return true;
}

void RepaintManager::update()
{
	GLShaderUtils * check;
	AbstractBackBuffer * backBuffer = aBackBuffer;

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
                	check->check_gl_error();

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
	GLShaderUtils * check;

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
					check->check_gl_error();

                    component->update();
                	check->check_gl_error();

				}
			}
		}
	}


	backBuffer->setZBuffer(true);
	backBuffer->swap();
}
