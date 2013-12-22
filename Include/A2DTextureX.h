////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __A2DTEXTUREX_H__
#define __A2DTEXTUREX_H__

//+-----------------------------------------------------------------------------
//
//  Class:  
//      A2DTEXTUREX
//
//  Synopsis:
//      Texture container class.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "A2DRenderData.h"
#include "A2DTexture.h"
#include "A2DBackBuffer.h"
#include "A2DRect.h"

////////////////////////////////////////////////////////////////////////////////
// FORWARD DECLARATIONS
////////////////////////////////////////////////////////////////////////////////

class A2D;
class A2DAbstract;
class A2DRenderable;
class A2DAbstractComponent;
class A2DCamera;
struct A2DCameraProperties;
class A2DMatrixFactory;
struct A2DRenderData;
class A2DBackBuffer;
class A2DModelFactory;
class A2DRootPane;

class A2DWindow;
struct A2DVertexData;
struct A2DQuadData;
struct A2DBufferData;
class A2DTexture;

////////////////////////////////////////////////////////////////////////////////
// DEFINE
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// DECLARATION
////////////////////////////////////////////////////////////////////////////////

class A2DTextureX : public A2DTexture
{
public:
	// Constructor
	A2DTextureX(A2DBackBuffer * xBackBuffer, LPCWSTR * xFilename);

	// Deconstructor
	~A2DTextureX();

	// Variables
	A2DRect							aClips[20];

	// Accessors
	virtual A2DRect			*		GetClip(int xIndex = 0);

	// Mutators
	virtual void					SetClip(A2DRect * xClip, int xIndex = 0);

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
	// { A2DABSTRACT }
	virtual LPCWSTR                 GetClass();
	virtual LPCWSTR                 ToString();
	virtual bool                    operator==(A2DAbstract * xAbstract);

};



#endif
