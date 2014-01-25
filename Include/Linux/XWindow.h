////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __XWINDOW_H__
#define __XWINDOW_H__

//+-----------------------------------------------------------------------------
//
//  Class:
//      XWindow
//
//  Synopsis:
//      Differentiates which of the two possible arcs could match the given arc
//      parameters.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

//#include "ExtLibs.h"
#include "ExtLibs.h"
//#include "EventQueue.h"
#include "Common.h"
#include "../Core/Rect.h"
#include "../Core/Dims.h"
#include "../Core/AbstractWindow.h"
#include "../Core/AbstractFrame.h"

namespace A2D {

	////////////////////////////////////////////////////////////////////////////////
	// FORWARD DECLARATIONS
	////////////////////////////////////////////////////////////////////////////////

	class Frame;
	class Abstract;
  //  class AbstractFrame;

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

    class XWindow : public AbstractWindow
	{

		////////////////////////////////////////////////////////////////////////////////
		// PLATFORM COMPATIBLE IMPLEMENTATION
		////////////////////////////////////////////////////////////////////////////////
//    protected:
    public:

        bool                            aParent;
        LPCWSTR                         aName = NULL;
        XSetWindowAttributes            winAttr;
        GLXContext                      hRC;
        GLXContext                      render_context;
        Display      *                  aDis;
        unsigned long int               aWin = NULL;

    public:

        XWindow(AbstractFrame * xFrame);

        virtual void                    render();
        virtual void              *     getPlatformCompatibleWindowHandle();
        virtual void			  		initPlatformCompatibleEventDispatcher(AbstractEventQueue * xEventQueue);


        unsigned long int      			createCompatibleWindow(bool isParent);
        void                            destroyResources();
        HRESULT                 		createGLXContext();
        void                            destroyBackgroundResources();
        HRESULT                         isExtensionSupported(const char *extList, const char *extension);
        virtual	HRESULT					initialize();

	};
}
#endif
