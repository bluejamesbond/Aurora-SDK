////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __ABSTRACTBACKBUFFER_H__
#define __ABSTRACTBACKBUFFER_H__

//+-----------------------------------------------------------------------------
//
//  Class:
//      BACKBUFFER
//
//  Synopsis:
//      Differentiates which of the two possible arcs could match the given arc
//      parameters.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "GXSettings.h"
#include "AbstractWindow.h"

namespace A2D {

	////////////////////////////////////////////////////////////////////////////////
	// FORWARD DECLARATIONS
	////////////////////////////////////////////////////////////////////////////////

	class Abstract;
	class Container;
	struct CameraProperties;
	class RootPane;

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

	class AbstractBackBuffer
	{

	public:

		AbstractBackBuffer(AbstractWindow * xWindow, GXSettings * xGXSettings);
		virtual ~AbstractBackBuffer();

	protected:

		Dims					  	   aDims;
		AbstractWindow			  *    aWindow;
		GXSettings				       aSettings;

	public:

		Dims					  *		getSizeAsPtr();
		Dims							getSize();
		GXSettings				  *		getSettings();

		virtual void                    setActive() = 0;
		virtual void                    swap() = 0;
		virtual void                    clear() = 0;
		virtual void                    setZBuffer(bool val) = 0;
		virtual void					validate() = 0;

	public:

		virtual HRESULT                 initialize() = 0;

	};
}
#endif
