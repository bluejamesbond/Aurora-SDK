////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __REPAINTMANAGER_H__
#define __REPAINTMANAGER_H__

//+-----------------------------------------------------------------------------
//
//  Abstract Class:
//      COMPONENTMANAGER
//
//  Synopsis:
//      Differentiates which of the two possible arcs could match the given arc
//      parameters.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "UnorderedList.h"
#include "Container.h"
#include "Component.h"
#include "AbstractWindow.h"
#include "RootPane.h"
#include "AbstractWindow.h"
#include "Camera.h"

namespace A2D {

	////////////////////////////////////////////////////////////////////////////////
	// FORWARD DECLARATIONS
	////////////////////////////////////////////////////////////////////////////////

	class Abstract;
	class Graphics;

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

	class RepaintManager
	{
		Dims										*  aWindowDims;
		Graphics									*  aFrameGraphics;
		OrderedList<UnorderedList<Component*>*>        aOpaqueDepthTracker;
		OrderedList<UnorderedList<Component*>*>        aComponentDepthTracker;

		BackBuffer			   *     aBackBuffer;
		Component			   *     aRoot;
		AbstractWindow	  	   * 	 aWindow;
		Graphics			   *	 aGraphics;

	public:

		RepaintManager(Graphics * xGraphics, Component * xRoot)
		{
			aGraphics = xGraphics;
			aBackBuffer = aGraphics->getBackBuffer();
			aRoot = xRoot;
		}

		~RepaintManager();

		HRESULT add(Component& xParent, Component& xChild)
		{
			float depth = xParent.getDepth();

			if (depth == FLT_MIN)
			{
				return E_FAIL;
			}

			xChild._setDepth(++depth);
			
			xChild._setGraphics(xParent.getGraphics());

			if (addToDepthTracker(xChild, depth))
			{
				xParent._add(xChild);

				return S_OK;
			}

			return E_FAIL;
		}

		HRESULT addToDepthTracker(Component& xComponent, float xZ)
		{
			UnorderedList<Component*> * peerComponents;

			int maxTrackerZ = aOpaqueDepthTracker.size();
			int listsToAdd = xZ;

			while (maxTrackerZ < listsToAdd)
			{
				aOpaqueDepthTracker.push_back(peerComponents = new UnorderedList<Component*>());
			}
			
			peerComponents->push(&xComponent);

			return S_OK;
		}

		void update()
		{
			BackBuffer * backBuffer = aBackBuffer;

			backBuffer->setActive();
			backBuffer->clear();
			backBuffer->setZBuffer(false);
			
			int i, heapSize = 0;
			OrderedList<UnorderedList<Component*>*>::Iterator<UnorderedList<Component*>*>& iterator = aOpaqueDepthTracker.reverse_iterator();
			Component * component;

			while (iterator.has_previous())
			{
				UnorderedList<Component*> * containers = iterator.previous();
				
				if (containers->size() > 0)
				{
					heapSize = containers->heap_size();

					for (i = 0; i < heapSize; i++)
					{
						if ((component = containers->get(heapSize)) == NULL)
						{
							break;
						}
						else
						{
							component->update();
						}
					}
				}
			}

			backBuffer->setZBuffer(true);
			backBuffer->swap();
		}

	public:

		virtual void validate()
		{

		}

		virtual HRESULT initialize()
		{
			Component& root = *aRoot;

			// Set based on camera properties later
			// For now it is hardcoded
			// xGraphics->getCameraProperties();

			root._setDepth(0.0f);
			root._setGraphics(*aGraphics);

			addToDepthTracker(root, 0.0f);
		}

		virtual LPCWSTR                 getClass();
		virtual LPCWSTR                 toString();

	};
}

#endif
