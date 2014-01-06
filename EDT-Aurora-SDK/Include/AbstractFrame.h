////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __ABSTRACTFRAME_H__
#define __ABSTRACTFRAME_H__

//+-----------------------------------------------------------------------------
//
//  Class:
//      ABSTRACTFRAME
//
//  Synopsis:
//      Differentiates which of the two possible arcs could match the given arc
//      parameters.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

//#include "Abstract.h"
#include "Graphics.h"
//#include "Renderable.h"
//#include "AbstractTexture.h"
//#include "RootPane.h"
//#include "CameraProperties.h"
//#include "RenderData.h"
#include "BackBuffer.h"
//#include "MatrixFactory.h"
#include "AbstractWindow.h"
#include "GXSettings.h"
//#include "RepaintManager.h"
#include "Rect.h"

namespace A2D {
	
	////////////////////////////////////////////////////////////////////////////////
	// FORWARD DECLARATIONS
	////////////////////////////////////////////////////////////////////////////////

	class	Abstract;
	class	Renderable;
	class	Container;
	class	Camera;
	struct	CameraProperties;
	struct	RenderData;
	class	MatrixFactory;
	class	BackBuffer;
	struct	BufferData;
	class	MatrixFactory;
	class	RootPane;
    class   AbstractFrame;
    class   Graphics;
	
	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

    class AbstractFrame //: public Abstract//, public Runnable
	{

	public:

		AbstractFrame();
        virtual ~AbstractFrame();

    private:
        AbstractWindow	  	   *		aWindow;

		bool							aValidatedContents;

	public:

        HRESULT                         createResources();

	protected:

        virtual void                    createPlatformCompatibleWindow(AbstractWindow ** xWindow) = 0;


	};
}

#endif
