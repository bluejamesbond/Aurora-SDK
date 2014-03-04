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

		friend class AbstractFrame;

	private:

		const Dims								   *   aBackBufferDims;
		Pipeline*									   m_pipeline = NULL;
		OrderedList<UnorderedList<Component*>*>        aOpaqueDepthTracker;
		OrderedList<UnorderedList<Component*>*>        aComponentDepthTracker;

		AbstractBackBuffer						   *   aBackBuffer;
		Component								   *   aRoot;
		AbstractWindow	  						   *   aWindow;
		Graphics								   *   aGraphics;
		AbstractEventQueue						   *   m_eventQueue;
		Bufferable*									   m_textureBuffer;
		Bufferable*									   m_sandbox;

	public:

		AbstractWindow							   *   getWindow();

	public:

		ComponentManager(void * xGraphics, Component * xRoot, AbstractWindow * xWindow);
		~ComponentManager();

		STATUS										  add(Component& xParent, Component& xChild) const;

	private:

		bool										  addToDepthTracker(Component& xComponent);
		void										  updateTopToBottom();
		void										  updateBottomToTop();

	public:

		virtual STATUS								  initialize();
		
		inline void ComponentManager::validate()
		{
			// FIX ME ... use scrollLeft and variables like that to find offset

			aBackBuffer->validate();
			aGraphics->validate();

			/*A2DPIXELDISTANCESETUINT4& borderWidths = aRoot->m_styleSet.m_borders.m_precalculatedBorderWidths;

			aRoot->setBounds(SFLOAT(borderWidths.m_left),
							 SFLOAT(borderWidths.m_top),
							 aBackBufferDims->m_width - SFLOAT(borderWidths.m_left + borderWidths.m_right),
							 aBackBufferDims->m_height - SFLOAT(borderWidths.m_top + borderWidths.m_bottom));*/

			aRoot->setBounds(0,0, aBackBufferDims->m_width, aBackBufferDims->m_height);
			aRoot->m_componentTreeValidationRequest = true;
		}

	};
}

#endif
