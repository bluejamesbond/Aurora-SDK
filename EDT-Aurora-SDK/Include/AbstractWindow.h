////////////////////////////////////////////////////////////////////////////////
// GUARDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __ABSTRACTWINDOW_H__
#define __ABSTRACTWINDOW_H__

//+-----------------------------------------------------------------------------
//
//  Abstract Class:
//      ABSTRACTWINDOW
//
//  Synopsis:
//      Abstract Class to allow cross-patform implementation of AbstractWindow. 
//      Currently compatible with Windows and Linux.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

//#include "ExtLibs.h"
#include "GLXExtLibs.h"
//#include "Abstract.h"
#include "Rect.h"
#include "Color.h"
#include "Common.h"
//#include "AbstractEventQueue.h"

namespace A2D {

	////////////////////////////////////////////////////////////////////////////////
	// FORWARD DECLARATIONS
	////////////////////////////////////////////////////////////////////////////////

	class AbstractFrame;

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

    class AbstractWindow //: public Abstract
	{

    public:
        Display*                        aDis;
        Window                          aWin;

		AbstractWindow(AbstractFrame * xFrame);
        virtual Window                          createCompatibleWindow(bool isParent) = 0;
        virtual HRESULT                         createBackgroundResources() = 0;

//    protected:

        virtual void render() = 0;

    };
}

#endif
