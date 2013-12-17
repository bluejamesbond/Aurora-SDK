////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __A2DTEXTURE_H__
#define __A2DTEXTURE_H__

//+-----------------------------------------------------------------------------
//
//  Class:  
//      A2DTEXTURE
//
//  Synopsis:
//      Texture container class.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "A2DRenderData.h"
#include "A2DBackBuffer.h"

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
class A2DMatrixFactory;
class A2DModelFactory;
class A2DRootPane;
struct A2DWindowProperties;
class A2DWindow;
struct A2DVertexData;
struct A2DQuadData;
struct A2DBufferData;
class A2DTexture;
class A2DImagePanel;

////////////////////////////////////////////////////////////////////////////////
// DEFINE
////////////////////////////////////////////////////////////////////////////////

#define FILENAME_LL(str1, str2)                               str1 str2

////////////////////////////////////////////////////////////////////////////////
// DECLARATION
////////////////////////////////////////////////////////////////////////////////

class A2DTexture
{
public:
	// Constructor
	A2DTexture();
	A2DTexture(A2DBackBuffer * xBackBuffer, LPCWSTR * xFilename);

	// Deconstructor
	~A2DTexture();

	// Variables
	float aHeight = 0;
	float aWidth = 0;
	A2DBackBuffer * aBackBuffer;
	LPCWSTR * aSrc;
	ID3D10ShaderResourceView	*	aResource;
	bool loaded = false;

	// Accessors

	// Mutators
	// { NONE }

	// Builders
	// { NONE }

	// Factory
	// { NONE }

	// Additional
	// { NONE }

	// Pure Virtual
	// { NONE }

	// Virtual
	virtual ID3D10ShaderResourceView	*	GetResource();
	virtual float GetHeight();
	virtual float GetWidth();

	// Implementations
	// { NONE}

	// Implementation
	// { A2DABSTRACT }
	virtual HRESULT                 Initialize();
	virtual void                    Deinitialize();
	virtual LPCWSTR                 GetClass();
	virtual LPCWSTR                 ToString();
	virtual bool                    operator==(A2DAbstract * xAbstract);

};



#endif
