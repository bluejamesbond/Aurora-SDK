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
#include "../Include/Dims.h"

namespace A2D {

	////////////////////////////////////////////////////////////////////////////////
	// FORWARD DECLARATIONS
	////////////////////////////////////////////////////////////////////////////////

	struct RenderData;
	class BackBuffer;
	class RootPane;
	class Texture;
	class TextureBuffer;
    class XWindow;
    class Dims;

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

    class Graphics// : public Abstract
	{
	public:

		Graphics(BackBuffer * xBackBuffer);
		~Graphics();

        //variables
        GLuint                          programID;
        unsigned char       *           image_data;
        int                             x;
        int                             y;
        int                             n;
        char                *           file_name;

        glm::mat4                       MVP;
		BackBuffer			 *			aBackBuffer;
        AbstractWindow       *          aWindow;
        Dims                 *          aBackBufferDims;

        //Future Quadfactory
        Rect                 *          aConstraints; //(aClip in Quad)
        float                           aDepth;

/*
        QuadFactory			 *			aQuadFactory;
		TextureBuffer        *			aTextureBuffer;
		TextureBuffer        *			aBlurBuffer;

		// Shaders
		AbstractShader		 *			aColorShader;
		AbstractTextureShader*			aColoredTextureShader;
		AbstractTextureShader*			aTextureShader;

	public:

		void							validate();
        void							fillRect(Pipeline ** xPipeline, Rect& xRect,  Paint& xPaint);
        void							setClip(Rect * aRect, float xZ);
        void							drawImage(Rect& xRect, LPCWSTR& xSrc, bool xRepeat);

*/
        BackBuffer           *          getBackBuffer();
        Dims                 *          getDrawableDimensions();
        void                            setWindow(AbstractWindow * xWindow);
        void                            setBackBuffer(BackBuffer * xBackBuffer);
        void                            validate();
        void                            drawImage();

		virtual HRESULT                 initialize();
		virtual LPCWSTR                 getClass();
		virtual LPCWSTR                 toString();

        //Future Quadfactory
        void                            setClip(Rect * xClip, float xDepth);

	};
}

#endif
