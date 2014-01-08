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

#include "../Core/Common.h"
#include "../Core/Paint.h"
#include "../Core/Color3D.h"
#include "../Core/ImageProperties.h"
#include "../Core/Pipeline.h"
#include "../Core/CameraProperties.h"

#include "TextureVertex.h"
#include "BackBuffer.h"
#include "ColoredTextureShader.h"
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

		ID3D10Device		**			aDevice;

	public:

		Dims*							getDrawableDimensions();
		CameraProperties*				getCameraProperties();
		BackBuffer*						getBackBuffer();
		
		void							validate();

		void							drawImage(Pipeline ** xPipeline, Rect& xRect, LPCWSTR& xSrc, bool xRepeat);
		void							drawImage(Pipeline ** xPipeline, Rect& xRect, LPCWSTR& xSrc, Paint& xPaint, bool xRepeat);
		void							fillRect(Pipeline ** xPipeline, Rect& xRect,  Paint& xPaint);

		void							setClip(Rect * aRect, float xZ);

	public:

		virtual HRESULT                 initialize();

	};
}

#endif
