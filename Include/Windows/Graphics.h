////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

//+-----------------------------------------------------------------------------
//
//  Struct:
//      GRAPHICS
//
//  Synopsis:
//      Differentiates which of the two possible arcs could match the given arc
//      parameters.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "../_A2DCommon.h"

#include "../Core/Paint.h"
#include "../Core/Color3D.h"
#include "../Core/ImageProperties.h"
#include "../Core/Pipeline.h"
#include "../Core/CameraProperties.h"
#include "../Core/Drawable.h"
#include "../Core/Bufferable.h"

#include "../Core/A2DCOMPONENTRENDERSTYLESET.h"

#include "VertexTypes.h"
#include "BackBuffer.h"
#include "ColoredTextureShader.h"
#include "QuadExpansionShader.h"
#include "VerticalBlurShader.h"
#include "HorizontalBlurShader.h"
#include "TextureBuffer.h"
#include "Texture.h"
#include "QuadFactory.h"
#include "DXUtils.h"
#include "TextureShader.h"
#include "ColorShader.h"
#include "Thread.h"

namespace A2D {

	////////////////////////////////////////////////////////////////////////////////
	// FORWARD DECLARATIONS
	////////////////////////////////////////////////////////////////////////////////

	class Abstract;
	class Container;
	struct CameraProperties;
	class BackBuffer;
	class DXUtils;
	class RootPane;
	class Window;
	class Texture;
	class TextureBuffer;

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

	class TextureBindingParameter
	{

	public:

		ID3D10Device ** m_device;
		Drawable * m_drawable;

		TextureBindingParameter(ID3D10Device ** x_device, Drawable * x_drawable) :
			m_device(x_device),
			m_drawable(x_drawable)
		{
		}
	};

	class Graphics : public Runnable
	{
	public:

		Graphics(AbstractBackBuffer * xBackBuffer);
		~Graphics();

	private:

		float                *			aViewMatrix;
		float                *			aWorldMatrix;
		float                *			aProjection2DMatrix;
		float                *			aProjection3DMatrix;

		BackBuffer			 *			aBackBuffer;
		const Dims			 *			aBackBufferDims;
		GXSettings			 *			aBackBufferSettings;

		CameraProperties				aCameraProperties;
		Rect				 *			aClip;
		QuadFactory			 *			aQuadFactory;
		TextureBuffer        *			aTextureBuffer;
		TextureBuffer        *			aBlurBuffer;

		// Shaders
		AbstractShader		 *			aColorShader;
		AbstractTextureShader*			aColoredTextureShader;
		AbstractTextureShader*			aTextureShader;
		QuadExpansionShader  *			aQuadExpansionShader;
		VerticalBlurShader   *			aVerticalBlurShader;
		HorizontalBlurShader *			aHorizontalBlurShader;


		ID3D10Device		**			aDevice;
		D3DXMATRIX						m_position_matrix;

	public:
		
		const Dims*						getDrawableDimensions();
		CameraProperties*				getCameraProperties();
		BackBuffer*						getBackBuffer();
		
		void							bitBlitFixed(Pipeline ** xPipeline, Rect& xRect, Bufferable * x_bufferable);
		void							drawImage(Pipeline ** xPipeline, Rect& xRect, LPCWSTR& xSrc, bool xRepeat);
		void							bitBlitComponentBlurred(Pipeline ** x_pipeline, A2DCOMPONENTRENDERSTYLESET& x_renderSet, Bufferable * x_cache, Bufferable * x_sandbox);
		// void							drawString(Pipeline ** xPipeline, Rect& xRect);
		// void							drawImage(Pipeline ** xPipeline, Rect& xRect, LPCWSTR& xSrc, Paint& xPaint, bool xRepeat); // This function is now inlined for very fast rendering.
		void							fillRect(Pipeline ** xPipeline, Rect& xRect, Paint& xPaint);
		
		void							drawComponent(Pipeline ** xPipeline, A2DCOMPONENTRENDERSTYLESET& x_renderSet);


		void run(void * x_param, int x_thread);
		void resetDrawable(Drawable& x_drawable);
		void unbindDrawable(Drawable& x_drawable);
		void bindDrawable(Drawable& x_drawable);
		void setClip(Rect * xClip, float xDepth);
		void validate();
	
		inline STATUS createTextureBuffer(Bufferable** x_bufferable, Dims& x_dims)
		{
			TextureBuffer * texBuffer =  new TextureBuffer(aDevice, aBackBuffer->getDepthStencilViewAsPtr(), &x_dims);
			SAFELY(texBuffer->initialize());
			*x_bufferable = texBuffer;
			return STATUS_OK;
		}

	public:

		virtual STATUS                 initialize();
	};
}

#endif
