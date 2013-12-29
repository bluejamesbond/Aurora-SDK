////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __TEXTUREX_H__
#define __TEXTUREX_H__

//+-----------------------------------------------------------------------------
//
//  Class:  
//      TEXTUREX
//
//  Synopsis:
//      Texture container class.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "RenderData.h"
#include "Texture.h"
#include "BackBuffer.h"
#include "Rect.h"

////////////////////////////////////////////////////////////////////////////////
// FORWARD DECLARATIONS
////////////////////////////////////////////////////////////////////////////////

class ;
class Abstract;
class Renderable;
class AbstractComponent;
class Camera;
struct CameraProperties;
class MatrixFactory;
struct RenderData;
class BackBuffer;
class ModelFactory;
class RootPane;

class Window;
struct VertexData;
struct QuadData;
struct BufferData;
class Texture;

////////////////////////////////////////////////////////////////////////////////
// DEFINE
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// DECLARATION
////////////////////////////////////////////////////////////////////////////////

class TextureX : public Texture
{
public:
	// Constructor
	TextureX(BackBuffer * xBackBuffer, LPCWSTR * xFilename);

	// Deconstructor
	~TextureX();

	// Variables
	Rect							aClips[20];

	// Accessors
	virtual Rect			*		GetClip(int xIndex = 0);

	// Mutators
	virtual void					SetClip(Rect * xClip, int xIndex = 0);

	// Builders
	// { NONE }

	// Factory
	// { NONE }

	// Additional

	// Pure Virtual
	// { NONE }

	// Virtual
	// { NONE }

public:
	// Implementation
	// { ABSTRACT }
	virtual LPCWSTR                 GetClass();
	virtual LPCWSTR                 ToString();
	virtual bool                    operator==(Abstract * xAbstract);

};



#endif
