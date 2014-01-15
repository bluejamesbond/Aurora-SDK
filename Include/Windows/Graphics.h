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

#include "../Core/../_A2DCommon.h"
#include "../Core/Paint.h"
#include "../Core/Color3D.h"
#include "../Core/ImageProperties.h"
#include "../Core/Pipeline.h"
#include "../Core/CameraProperties.h"
#include "../Core/BorderSet.h"

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

	class Graphics
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
		Dims				 *			aBackBufferDims;
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

	public:

		Dims*							getDrawableDimensions();
		CameraProperties*				getCameraProperties();
		BackBuffer*						getBackBuffer();
		
		void							drawImage(Pipeline ** xPipeline, Rect& xRect, LPCWSTR& xSrc, bool xRepeat);
		void							drawString(Pipeline ** xPipeline, Rect& xRect);
		// void							drawImage(Pipeline ** xPipeline, Rect& xRect, LPCWSTR& xSrc, Paint& xPaint, bool xRepeat); // This function is now inlined for very fast rendering.
		void							fillRect(Pipeline ** xPipeline, Rect& xRect, Paint& xPaint);
		
		inline void Graphics::drawComponent(Pipeline ** xPipeline, Rect& xRect, LPCWSTR& xSrc, BorderSet& xBorderSet, Paint& xPaint, bool xRepeat)
		{
			Rect * clip = aClip;

			if (xRect.aX >= clip->aWidth || xRect.aY >= clip->aHeight || clip->aWidth <= 0 || clip->aHeight <= 0)	return;

			Texture * texture;
			QuadData<QuadExpansionVertex, 1> * quadData;

			if (*xPipeline == NULL)
			{
				// Intialize the pipeline

				*xPipeline = new Pipeline();

				texture = new Texture(aDevice, xSrc);
				quadData = new QuadData<QuadExpansionVertex, 1>();

				DXUtils::CreateDefaultDynamicVertexBuffer<QuadExpansionVertex>(*aDevice, &quadData->aVertexBuffer, 1);

				texture->initialize();

				(*xPipeline)->aPipelineComps[0] = texture;
				(*xPipeline)->aPipelineComps[1] = quadData;

				(*xPipeline)->aLength = 2;

				return;
			}

			texture = static_cast<Texture*>((*xPipeline)->aPipelineComps[0]);
			quadData = static_cast<QuadData<QuadExpansionVertex, 1>*>((*xPipeline)->aPipelineComps[1]);

			// texture->Update(textureArgs); <<<<+++ ADD LATER
			if (aQuadFactory->updateVertexBuffer(quadData, &xRect, texture, &xBorderSet, &xPaint, xRepeat))
			{
				aQuadExpansionShader->setTexture(texture);
				aQuadFactory->renderQuad(quadData->aVertexBuffer, sizeof(QuadExpansionVertex));
				aQuadExpansionShader->renderShader();
			}
		}

	public:

		virtual STATUS                 initialize();

		////////////////////////////////////////////////////////////////////////////////
		// INLINE
		////////////////////////////////////////////////////////////////////////////////

		inline void Graphics::setClip(Rect * xClip, float xDepth)
		{
			aQuadFactory->setConstraints(aClip = xClip, xDepth);
		}
	};
}

#endif
