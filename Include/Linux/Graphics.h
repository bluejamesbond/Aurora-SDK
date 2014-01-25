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
//#include "TextureVertex.h"
#include "BackBuffer.h"
//#include "ColoredTextureShader.h"
#include "TextureBuffer.h"
#include "Texture.h"
#include "QuadFactory.h"
#include "../Core/Pipeline.h"
#include "../Core/Paint.h"
// FIXME Fix the type and make subclasses
#include "GenericShader.h"
//#include "ImageProperties.h"
//#include "Pipeline.h"
//#include "Paint.h"
//#include "Color3D.h"
//#include "TextureShader.h"
//#include "ColorShader.h"
#include "GLShaderUtils.h"
#include "XWindow.h"

namespace A2D {

	////////////////////////////////////////////////////////////////////////////////
	// FORWARD DECLARATIONS
	////////////////////////////////////////////////////////////////////////////////

    struct CameraProperties;
    class BackBuffer;;
	class Texture;
	class TextureBuffer;
    class XWindow;
    class AbstractBackBuffer;
    class QuadFactory;
    class GenericShader;

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

    class Graphics
    {
    public:

        Graphics(AbstractBackBuffer * xBackBuffer);
        ~Graphics();

        AbstractBackBuffer   *			aBackBuffer;
        AbstractWindow       *          aWindow;
        Texture              *          aTexture;
        QuadFactory			 *			aQuadFactory;
        TextureBuffer        *			aTextureBuffer;
        Rect                 *          aClip;
        GenericShader		 *			aTextureShader;

/*        // Shaders
        AbstractShader		 *			aColorShader;
        AbstractTextureShader*			aColoredTextureShader;
        AbstractTextureShader*			aTextureShader;

    public:

        Dims*							getDrawableDimensions();*/
        void							validate();
        void							fillRect(Pipeline ** xPipeline, Rect& xRect,  Paint& xPaint);

        AbstractBackBuffer       *      getBackBuffer();
        void                            setClip(Rect * xClip, float xDepth);

        void                            setWindow(AbstractWindow* xWindow);
        void                            setBackBuffer(BackBuffer* xBackBuffer);
//        void							drawImage(Rect& xRect, LPCWSTR& xSrc, bool xRepeat);
        void                            drawImage(Pipeline ** xPipeline, Rect& aRect, LPCWSTR& xSrc, bool xRepeat);
        void                            swap();
    public:

        virtual HRESULT                 initialize();

    };
}

#endif
