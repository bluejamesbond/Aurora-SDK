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

//#include "GXSettings.h"
#include "../Core/AbstractWindow.h"
//#include "Graphics.h"

namespace A2D {

	////////////////////////////////////////////////////////////////////////////////
	// FORWARD DECLARATIONS
	////////////////////////////////////////////////////////////////////////////////

	class Abstract;
	class Container;
	struct CameraProperties;
//	struct RenderData;
	class MatrixFactory;
	class RootPane;
    class Graphics;
	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

    class BackBuffer //: public Abstract
	{

	public:

//		BackBuffer(AbstractWindow * xWindow, GXSettings * xGXSettings);
        BackBuffer(AbstractWindow * xWindow);
        ~BackBuffer();

	private:
/*
		D3D10_VIEWPORT					aViewport;
		D3D10_TEXTURE2D_DESC			aDepthBufferDesc;
		IDXGISwapChain            *     aDXGISwapChain;
		ID3D10Device              *     aDXDevice;
		ID3D10RenderTargetView    *     aDXRenderTargetView;
		ID3D10Texture2D           *     aDXDepthStencilBuffer;
		ID3D10DepthStencilState   *     aDXDepthStencilState;
		ID3D10DepthStencilView    *     aDXDepthStencilView;
		ID3D10RasterizerState     *     aDXRasterState;
		ID3D10DepthStencilState   *     aDXDepthDisabledStencilState;
*/
    public:

		Dims					 	   aDims;
		AbstractWindow			  *    aWindow;
//		GXSettings				       aSettings;
        GLuint                         vertexbuffer;
        unsigned int                   vt_vbo;
        GLuint                         vao;
        GLuint                         TextureID;
        unsigned int                   tex = 0;
        Graphics                  *    aGraphics;

        //functions

		void							validate();
		Dims					  *		getSize();
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
