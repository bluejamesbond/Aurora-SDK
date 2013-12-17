#ifndef __A2DTEXTURESHADER_H__
#define __A2DTEXTURESHADER_H__

//+-----------------------------------------------------------------------------
//
//  Class: 
//      A2DTEXTURESHADER
//
//  Synopsis:
//      Shader class for textures.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"



////////////////////////////////////////////////////////////////////////////////
// FORWARD DECLARATIONS
////////////////////////////////////////////////////////////////////////////////

using namespace std;
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
class A2DTextureShader;

////////////////////////////////////////////////////////////////////////////////
// DEFINE
////////////////////////////////////////////////////////////////////////////////

#define FILENAME_LL(str1, str2)                               str1 str2

////////////////////////////////////////////////////////////////////////////////
// DECLARATION
////////////////////////////////////////////////////////////////////////////////

class A2DTextureShader
{
public:
	// Constructor
	A2DTextureShader();

	// Deconstructor
	~A2DTextureShader();

	// Variables
	// { NONE }

	// Accessors
	// { NONE }

	// Mutators
	// { NONE }

	// Builders
	bool Initialize(ID3D10Device*, HWND);
	void Shutdown();
	

	// Factory
	// { NONE }

	// Additional
	void Render(ID3D10Device*, int, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX, ID3D10ShaderResourceView*);

	// Pure Virtual
	// { NONE }

	// Virtual
	// { NONE }

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
