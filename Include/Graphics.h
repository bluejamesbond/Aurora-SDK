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

#include "Common.h"
#include "TextureVertex.h"
#include "BackBuffer.h"
#include "TextureShader.h"
#include "TextureBuffer.h"
#include "Texture.h"
#include "QuadFactory.h"
#include "ImageProperties.h"
#include "Pipeline.h"
#include "MatrixFactory.h"

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
	class BackBuffer;
	class MatrixFactory;
	class RootPane;
	class Window;
	struct VertexData;
	class Texture;
	class TextureBuffer;

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

	class Graphics : public RenderData, public Abstract
	{
	public:

		Graphics(BackBuffer * xBackBuffer);
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
		TextureShader		 *			aTextureShader;
		TextureBuffer        *			aTextureBuffer;
		TextureBuffer        *			aBlurBuffer;

		ID3D10Device		**			aDXDevice;

	public:

		Dims*							getDrawableDimensions();
		CameraProperties*				getCameraProperties();
		void							setClip(Rect * aRect);
		void							validate();
		BackBuffer*						getBackBuffer();

		void							drawImage(Pipeline ** xPipeline, LPCWSTR xSrc, Rect& aRect, ImageProperties& xImageProps);
	
	public:

		virtual HRESULT                 initialize();
		virtual LPCWSTR                 getClass();
		virtual LPCWSTR                 toString();

	};
}

#endif
