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

#include "../_A2D.h"
#include "OrderedList.h"
#include "UnorderedList.h"
#include "AbstractWindow.h"
#include "AbstractBackBuffer.h"
//#include GRAPHICS__

namespace A2D {

	////////////////////////////////////////////////////////////////////////////////
	// FORWARD DECLARATIONS
	////////////////////////////////////////////////////////////////////////////////

	class Component;

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

	class RepaintManager
	{
		Dims										*  aBackBufferDims;
		OrderedList<UnorderedList<Component*>*>        aOpaqueDepthTracker;
		OrderedList<UnorderedList<Component*>*>        aComponentDepthTracker;

		AbstractBackBuffer						   *   aBackBuffer;
		Component								   *   aRoot;
		AbstractWindow	  						   *   aWindow;
		void									   *   aGraphics;


		// FIXME Just for fun code
		float translationX = 0;
		float translationY = 0;
		float translationXG1 = 10;
		float translationYG1 = 10;
		float translationXDirection = 1;
		float translationYDirection = 1;
		float translationXDirectionG1 = 1;
		float translationYDirectionG1 = 1;
		float width = 300;
		float height = 300;
		float max_width = 800;
		float max_height = 600;

	public:

		RepaintManager(void * xGraphics, Component * xRoot);
		~RepaintManager();

		HRESULT										  add(Component& xParent, Component& xChild);
		bool										  addToDepthTracker(Component& xComponent, float xZ);
		void										  update();
		void										  update_forward();

	public:

		virtual void								  validate();
		virtual HRESULT								  initialize();

	};
}

#endif
