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

		STATUS										  add(Component& xParent, Component& xChild);
		bool										  addToDepthTracker(Component& xComponent, float xZ);
		void										  update();
		void										  update_forward();

	public:

		virtual STATUS								  initialize();
		
		inline void ComponentManager::validate()
		{
			// FIX ME ... use scrollLeft and variables like that to find offset

			BorderSet& borderSet = aRoot->m_borderSet;

			aBackBuffer->validate();
			aRoot->setBounds(borderSet.m_left.m_width,
							 borderSet.m_top.m_width,
							 aBackBufferDims->aWidth - (borderSet.m_left.m_width + borderSet.m_right.m_width),
							 aBackBufferDims->aHeight - (borderSet.m_top.m_width + borderSet.m_bottom.m_width));
		}

	};
}

#endif
