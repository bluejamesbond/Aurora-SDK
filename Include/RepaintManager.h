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

#include "OrderedList.h"
#include "UnorderedList.h"
#include "BackBuffer.h"

namespace A2D {

	////////////////////////////////////////////////////////////////////////////////
	// FORWARD DECLARATIONS
	////////////////////////////////////////////////////////////////////////////////

	class Abstract;
	class Graphics;
	class Component;
	class Window;
	class AbstractFrame;

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

	class RepaintManager
	{

	public:

		Dims										*  aWindowDims;
		Graphics									*  aFrameGraphics;
		OrderedList<UnorderedList<Component*>*>        aOpaqueDepthTracker;
		OrderedList<UnorderedList<Component*>*>        aComponentDepthTracker;

		BackBuffer			   *     aBackBuffer;
		Component			   *     aRoot;
		AbstractWindow	  	   * 	 aWindow;
		Graphics			   *	 aGraphics;

	public:

		RepaintManager(Graphics * xGraphics, Component * xRoot, AbstractWindow * xWindow);

		~RepaintManager();

		HRESULT add(Component& xParent, Component& xChild);

		HRESULT addToDepthTracker(Component& xComponent, float xZ);

		void update();

	public:

		virtual void validate();

		virtual HRESULT initialize();

		virtual LPCWSTR                 getClass();
		virtual LPCWSTR                 toString();

	};
}

#endif
