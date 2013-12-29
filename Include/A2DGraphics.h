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
#include "VertexData.h"
#include "BackBuffer.h"
#include "TextureShader.h"
#include "TextureBuffer.h"
#include "Texture.h"
#include "QuadFactory.h"
#include "ImageProperties.h"
#include "AbstractComponent.h"
#include "Pipeline.h"

////////////////////////////////////////////////////////////////////////////////
// FORWARD DECLARATIONS
////////////////////////////////////////////////////////////////////////////////

class ;
class Abstract;
class Renderable;
class AbstractComponent;
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
// DEFINE
////////////////////////////////////////////////////////////////////////////////                               

////////////////////////////////////////////////////////////////////////////////
// DECLARATION
////////////////////////////////////////////////////////////////////////////////

class Graphics : public RenderData, public Abstract
{
	
private:

	ID3D10Device		**			aDXDevice;
	Rect				 *			aClip;
	QuadFactory		 *			aQuadFactory;
	TextureShader	 *			aTextureShader;

public:

	// Additional
	void							setClip(Rect * aRect);

	void							DrawImage(Pipeline ** xPipeline, LPCWSTR * xSrc, Rect * aRect, ImageProperties * xImageProps);
	void							DrawImage(Pipeline * xPipeline, Texture * xTexture, float xImageLeft, float xImageTop, float xImageWidth, float xImageHeight, ImageProperties * xImageProps, int xBlur);
	
	void							validate();

public:

////////////////////////////////////////////////////////////////////////////////
// ABSTRACT
////////////////////////////////////////////////////////////////////////////////

	virtual HRESULT                 Initialize();
	virtual void                    Deinitialize();
	virtual LPCWSTR                 GetClass();
	virtual LPCWSTR                 ToString();
	virtual bool                    operator==(Abstract * xAbstract);

};


#endif
