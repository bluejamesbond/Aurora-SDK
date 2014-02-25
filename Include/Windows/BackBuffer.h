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
//      Creates a renderable context based on the device context of a window.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////


#include "../Core/AbstractBackBuffer.h"
#include "../Core/GXSettings.h"
#include "../Core/AbstractWindow.h"

namespace A2D {

	////////////////////////////////////////////////////////////////////////////////
	// FORWARD DECLARATIONS
	////////////////////////////////////////////////////////////////////////////////

	class Container;
	struct CameraProperties;
	class DXUtils;
	class RootPane;

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

	class BackBuffer : public AbstractBackBuffer
	{

	public:

		BackBuffer(AbstractWindow * xWindow, GXSettings * xGXSettings);
		virtual ~BackBuffer();

	private:

		D3D10_VIEWPORT					aViewport;
		D3D10_TEXTURE2D_DESC			aDepthBufferDesc;
		IDXGISwapChain            *     aDXGISwapChain;
		ID3D10Device              *     aDevice;
		ID3D10RenderTargetView    *     aDXRenderTargetView;
		ID3D10Texture2D           *     aDXDepthStencilBuffer;
		ID3D10DepthStencilState   *     aDXDepthStencilState;
		ID3D10DepthStencilView    *     aDXDepthStencilView;
		ID3D10RasterizerState     *     aDXRasterState;
		ID3D10DepthStencilState   *     aDXDepthDisabledStencilState;

	public:

		ID3D10Device              **    getDevice();
		virtual void					validate();
		virtual void                    setActive();
		virtual void                    swap();
		virtual void                    clear();
		virtual void                    setZBuffer(bool val);

	public:

		virtual STATUS                 initialize();

	};
}
#endif
