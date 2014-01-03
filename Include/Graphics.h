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
#include "ColoredTextureShader.h"
#include "TextureBuffer.h"
#include "Texture.h"
#include "QuadFactory.h"
#include "ImageProperties.h"
#include "Pipeline.h"
#include "MatrixFactory.h"
#include "GradientPaint.h"
#include "Color3D.h"
#include "TextureShader.h"

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
		AbstractTextureShader*			aColoredTextureShader;
		AbstractTextureShader*			aTextureShader;
		TextureBuffer        *			aTextureBuffer;
		TextureBuffer        *			aBlurBuffer;

		ID3D10Device		**			aDXDevice;

	public:

		Dims*							getDrawableDimensions();
		CameraProperties*				getCameraProperties();
		void							setClip(Rect * aRect, float xZ);
		void							validate();
		BackBuffer*						getBackBuffer();

		void							setBackground(Color3D& xColor);
		void							setBackground(GradientPaint& xGradientPaint);
		void							fillRect();
		void							drawImage(Pipeline ** xPipeline, LPCWSTR xSrc, Rect& aRect);
		void							drawImage(Pipeline ** xPipeline, LPCWSTR xSrc, Rect& aRect, bool xRepeat);
		void							drawImage();
		void							drawRect();
		void							drawLine();

	public:

		virtual HRESULT                 initialize();
		virtual LPCWSTR                 getClass();
		virtual LPCWSTR                 toString();

	};
}

#endif
