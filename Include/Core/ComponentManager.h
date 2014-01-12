////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __COMPONENTMANAGER_H__
#define __COMPONENTMANAGER_H__

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

#include "../_A2DLinkers.h"
#include "OrderedList.h"
#include "UnorderedList.h"
#include "AbstractWindow.h"
#include "AbstractBackBuffer.h"
#include "Component.h"
#include GRAPHICS__

namespace A2D {

	////////////////////////////////////////////////////////////////////////////////
	// FORWARD DECLARATIONS
	////////////////////////////////////////////////////////////////////////////////

	class Component;

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

	class ComponentManager
	{

	private:

		Dims										*  aBackBufferDims;
		OrderedList<UnorderedList<Component*>*>        aOpaqueDepthTracker;
		OrderedList<UnorderedList<Component*>*>        aComponentDepthTracker;

		AbstractBackBuffer						   *   aBackBuffer;
		Component								   *   aRoot;
		AbstractWindow	  						   *   aWindow;
		void									   *   aGraphics;

	public:

		AbstractWindow							   *   getWindow();

	public:

		ComponentManager(void * xGraphics, Component * xRoot, AbstractWindow * xWindow);
		~ComponentManager();

		HRESULT										  add(Component& xParent, Component& xChild);
		bool										  addToDepthTracker(Component& xComponent, float xZ);
		void										  update();
		void										  update_forward();

	public:

		virtual HRESULT								  initialize();
		
		inline void ComponentManager::validate()
		{
			aBackBuffer->validate();
			aRoot->setBounds(0, 0, aBackBufferDims->aWidth, aBackBufferDims->aHeight);
		}

	};
}

#endif
