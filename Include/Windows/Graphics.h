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

	struct VS_CONSTANT_BUFFER
	{
		D3DXMATRIX m_borderCalculationMatrix;
	};


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

		ID3D10Buffer*					m_constantBuffer10 = NULL;
		ID3D10Device		**			aDevice;
		D3DXMATRIX						m_borderCalculationMatrix;
		VS_CONSTANT_BUFFER				m_constantBuffer;

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

		inline void Graphics::setClip(Rect * xClip, float xDepth)
		{
			aQuadFactory->setConstraints(aClip = xClip, xDepth);
		}

		void inline	validate()
		{
			DXUtils::updateBorderMatrix(&m_constantBuffer.m_borderCalculationMatrix, aBackBufferDims);

			//void * mappedVertices = 0;

			//m_constantBuffer10->Map(D3D10_MAP_WRITE_DISCARD, 0, static_cast<void**>(&mappedVertices));
			//memcpy(static_cast<VS_CONSTANT_BUFFER*>(mappedVertices), &m_constantBuffer, sizeof(VS_CONSTANT_BUFFER));
			//m_constantBuffer10->Unmap();
			//
			//// aQuadExpansionShader->setConstantBuffer(m_constantBuffer10);

			//(*aDevice)->GSSetConstantBuffers(0, 1, &m_constantBuffer10);

		}
	};
}

#endif
