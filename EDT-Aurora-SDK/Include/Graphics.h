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
#include "GLImageLoader.h"
//#include "TextureVertex.h"
#include "BackBuffer.h"
//#include "ColoredTextureShader.h"
//#include "TextureBuffer.h"
//#include "Texture.h"
//#include "QuadFactory.h"
//#include "ImageProperties.h"
//#include "Pipeline.h"
//#include "MatrixFactory.h"
//#include "Paint.h"
//#include "Color3D.h"
//#include "TextureShader.h"
//#include "ColorShader.h"
#include "GLShaderUtils.h"
#include "../Include/Windows/XWindow.h"

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
	class Texture;
	class TextureBuffer;
    class XWindow;

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

    class Graphics// : public Abstract
	{
	public:

		Graphics(BackBuffer * xBackBuffer);
		~Graphics();


        GLuint                          programID;
        GLuint                          MatrixID;
        unsigned char       *           image_data;
        int                             x;
        int                             y;
        int                             n;
        char                *           file_name;

//    private:
/*
		float                *			aViewMatrix;
		float                *			aWorldMatrix;
		float                *			aProjection2DMatrix;
		float                *			aProjection3DMatrix;
*/
        glm::mat4                       MVP;
		BackBuffer			 *			aBackBuffer;
        AbstractWindow              *          aWindow;
/*
        QuadFactory			 *			aQuadFactory;
		TextureBuffer        *			aTextureBuffer;
		TextureBuffer        *			aBlurBuffer;

		// Shaders
		AbstractShader		 *			aColorShader;
		AbstractTextureShader*			aColoredTextureShader;
		AbstractTextureShader*			aTextureShader;

	public:

		Dims*							getDrawableDimensions();
		BackBuffer*						getBackBuffer();
		void							validate();
        void							fillRect(Pipeline ** xPipeline, Rect& xRect,  Paint& xPaint);
        void							setClip(Rect * aRect, float xZ);
*/
        BackBuffer           *          getBackBuffer();
        void                            setWindow(AbstractWindow* xWindow);
        void                            setBackBuffer(BackBuffer* xBackBuffer);
//        void							drawImage(Rect& xRect, LPCWSTR& xSrc, bool xRepeat);
        void                            drawImage();
	public:

		virtual HRESULT                 initialize();
		virtual LPCWSTR                 getClass();
		virtual LPCWSTR                 toString();

	};
}

#endif
