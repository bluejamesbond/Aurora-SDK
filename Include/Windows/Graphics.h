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

#include "../Core/A2DCOMPONENTRENDERSTYLESET.h"

#include "VertexTypes.h"
#include "BackBuffer.h"
#include "ColoredTextureShader.h"
#include "QuadExpansionShader.h"
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

		ID3D10Device		**			aDevice;
		D3DXMATRIX						m_position_matrix;

	public:

		const Dims*						getDrawableDimensions();
		CameraProperties*				getCameraProperties();
		BackBuffer*						getBackBuffer();
		
		void							drawImage(Pipeline ** xPipeline, Rect& xRect, LPCWSTR& xSrc, bool xRepeat);
		void							drawString(Pipeline ** xPipeline, Rect& xRect);
		// void							drawImage(Pipeline ** xPipeline, Rect& xRect, LPCWSTR& xSrc, Paint& xPaint, bool xRepeat); // This function is now inlined for very fast rendering.
		void							fillRect(Pipeline ** xPipeline, Rect& xRect, Paint& xPaint);
		
		void							drawComponent(Pipeline ** xPipeline, A2DCOMPONENTRENDERSTYLESET& x_renderSet);
		
	public:

		virtual STATUS                 initialize();

		////////////////////////////////////////////////////////////////////////////////
		// INLINE
		////////////////////////////////////////////////////////////////////////////////

		void inline run(void * x_param, int x_thread)
		{
			TextureBindingParameter * parameter = static_cast<TextureBindingParameter*>(x_param);
			Drawable * drawable = parameter->m_drawable;
			
			Texture * texture = new Texture(aDevice, drawable->getSource());
			G_SAFELY(texture->initialize());

			drawable->m_activeTexture = texture;
			drawable->fireChangeListeners();

			DESTROY(parameter);
		}

		void inline resetDrawable(Drawable& x_drawable)
		{
			x_drawable.m_activeTexture = Texture::DEFAULT_TEXTURE;
		}

		void inline unbindDrawable(Drawable& x_drawable)
		{
			Texture * inActiveTexture = static_cast<Texture*>(x_drawable.m_inActiveTexture);
			Texture * activeTexture = static_cast<Texture*>(x_drawable.m_activeTexture);

			DESTROY(inActiveTexture);
			DESTROY(activeTexture);
		}

		void inline	bindDrawable(Drawable& x_drawable)
		{
			// Thread * thread = new Thread(this, new TextureBindingParameter(aDevice, &x_drawable));
			// G_SAFELY(thread->initialize());
			// thread->start();

			run(new TextureBindingParameter(aDevice, &x_drawable), 0);
		}

		inline void Graphics::setClip(Rect * xClip, float xDepth)
		{
			aQuadFactory->setConstraints(aClip = xClip, xDepth);
		}

		void inline	validate()
		{
			DXUtils::updateBorderMatrix(&m_position_matrix, aBackBufferDims);
			aQuadExpansionShader->updatePositionMatrix(&m_position_matrix);
		}
	};
}

#endif
