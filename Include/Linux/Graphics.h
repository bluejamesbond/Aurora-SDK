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
//#include "TextureBuffer.h"
//#include "Texture.h"
#include "QuadFactory.h"
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

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

    class Graphics
    {
    public:

        Graphics(AbstractBackBuffer * xBackBuffer);
        ~Graphics();


        GLuint                          programID;
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
        AbstractBackBuffer   *			aBackBuffer;
        AbstractWindow       *          aWindow;
/*
        Texture              *          aTexture;
        QuadFactory			 *			aQuadFactory;
        TextureBuffer        *			aTextureBuffer;

        // Shaders
        AbstractShader		 *			aColorShader;
        AbstractTextureShader*			aColoredTextureShader;
        AbstractTextureShader*			aTextureShader;

    public:

        Dims*							getDrawableDimensions();*/
        void							validate();
        void							fillRect(Pipeline ** xPipeline, Rect& xRect,  Paint& xPaint);
        void							setClip(Rect * aRect, float xZ);/*
*/
        AbstractBackBuffer           *          getBackBuffer();
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
