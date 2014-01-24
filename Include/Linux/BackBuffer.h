////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __BACKBUFFER_H__
#define __BACKBUFFER_H__

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

#include "../Core/GXSettings.h"
#include "../Core/AbstractWindow.h"
#include "ExtLibs.h"
#include "../Core/AbstractBackBuffer.h"
#include "Texture.h"
#include "XWindow.h"

namespace A2D {

	////////////////////////////////////////////////////////////////////////////////
	// FORWARD DECLARATIONS
	////////////////////////////////////////////////////////////////////////////////

	struct CameraProperties;
    class Texture;
    class Graphics;
    class XWindow;

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

    class BackBuffer: public AbstractBackBuffer
	{

	public:

        BackBuffer(AbstractWindow * xWindow, GXSettings * xGXSettings);
        BackBuffer(AbstractWindow * xWindow);
        ~BackBuffer();

	private:

    public:

		Dims					 	   aDims;
		XWindow					  *    aWindow;
        GLuint                         vao;
        Graphics                  *    aGraphics;
        GLXContext*					   m_context;

        //functions
		void							validate();
		Dims					  *		getSize();
        AbstractWindow            *     getWindow();
//		GXSettings				  *		getSettings();
		void                            setActive();
		void                            swap();
		void                            clear();
		void                            setZBuffer(bool val);
        void                            setGraphics(Graphics* xGraphics);

	public:

		virtual HRESULT                 initialize();
		virtual LPCWSTR                 getClass();
		virtual LPCWSTR                 toString();

	};
}
#endif
