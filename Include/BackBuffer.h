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
	class AbstractComponent;
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

		// Constructor
		BackBuffer(AbstractWindow * xWindow, GXSettings * xGXSettings);

		// Deconstructor
		~BackBuffer();

		// Variables
		IDXGISwapChain            *     aDXGISwapChain;
		ID3D10Device              *     aDXDevice;
		ID3D10RenderTargetView    *     aDXRenderTargetView;
		ID3D10Texture2D           *     aDXDepthStencilBuffer;
		ID3D10DepthStencilState   *     aDXDepthStencilState;
		ID3D10DepthStencilView    *     aDXDepthStencilView;
		ID3D10RasterizerState     *     aDXRasterState;
		ID3D10DepthStencilState   *     aDXDepthDisabledStencilState;
		char							aVideoCardDescription[128];
		int								aVideoCardMemory;

	private:
		// Variables
		AbstractWindow		  *     aWindow;
		GXSettings			  *     aGXSettings;

	public:
		// Accessors
		ID3D10Device              *     GetDevice();
		void							validate();

	public:
		// Mutators
		void                            SetZBuffer(bool val);

		// Builders
		// { NONE }

		// Factory
		// { NONE }

	public:
		// Additional
		void                            SetActive();
		void                            Swap();
		void                            Clear();

		// Pure Virtual
		// { NONE }

		// Virtual
		// { NONE }

	public:

		// Implementation
		// { ABSTRACT }
		virtual HRESULT                 Initialize();
		virtual void                    Deinitialize();
		virtual LPCWSTR                 GetClass();
		virtual LPCWSTR                 ToString();
		virtual bool                    operator==(Abstract * xAbstract);

	};
}
#endif
