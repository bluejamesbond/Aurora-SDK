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

#include "Abstract.h"
#include "GXSettings.h"
#include "AbstractWindow.h"

namespace A2D {

	////////////////////////////////////////////////////////////////////////////////
	// FORWARD DECLARATIONS
	////////////////////////////////////////////////////////////////////////////////

	class Abstract;
	class Renderable;
	class Container;
	class Camera;
	struct CameraProperties;
	struct RenderData;
	class MatrixFactory;
	class ModelFactory;
	class RootPane;

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

	class BackBuffer : public Abstract
	{

	public:

		BackBuffer(AbstractWindow * xWindow, GXSettings * xGXSettings);
		~BackBuffer();

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

		Dims					 	   aDims;
		AbstractWindow			  *    aWindow;
		GXSettings				       aSettings;

	public:

		ID3D10Device              **    getDevice();
		void							validate();
		Dims					  *		getSize();
		GXSettings				  *		getSettings();
		void                            setActive();
		void                            swap();
		void                            clear();
		void                            setZBuffer(bool val);

	public:

		virtual HRESULT                 initialize();
		virtual LPCWSTR                 getClass();
		virtual LPCWSTR                 toString();

	};
}
#endif
