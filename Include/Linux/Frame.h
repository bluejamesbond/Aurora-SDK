////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __FRAME_H__
#define __FRAME_H__

//+-----------------------------------------------------------------------------
//
//  Class:
//      FRAME
//
//  Synopsis:
//      Differentiates which of the two possible arcs could match the given arc
//      parameters.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "../Core/AbstractFrame.h"
//#include "Thread.h"
#include "Graphics.h"

namespace A2D {

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

    class Frame : public AbstractFrame
    {

		////////////////////////////////////////////////////////////////////////////////
		// PLATFORM COMPATIBLE IMPLEMENTATION
		////////////////////////////////////////////////////////////////////////////////

	public:

        Frame();

        virtual ~Frame();

	protected:

        virtual HRESULT		createPlatformCompatibleEventQueue(AbstractEventQueue ** xEventQueue);
        virtual HRESULT		createPlatformCompatibleWindow(AbstractWindow ** xWindow);
        virtual HRESULT		createPlatformCompatibleBackBuffer(AbstractBackBuffer ** xBackBuffer, AbstractWindow * xWindow, GXSettings * xSettings);
        virtual HRESULT		createAndInitPlatformCompatibleGraphics(void ** xGraphics, AbstractBackBuffer * xBackbuffer);
    };
}
#endif
