////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __A2DTEXTUREBUFFER_H__
#define __A2DTEXTUREBUFFER_H__

//+-----------------------------------------------------------------------------
//
//  Struct:
//      A2DTEXTUREBUFFER
//
//  Synopsis:
//      Differentiates which of the two possible arcs could match the given arc
//      parameters.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "A2DCommon.h"
#include "A2DWindowProperties.h"
#include "A2DVertexData.h"
#include "A2DBackBuffer.h"
#include "A2DTexture.h"
#include "A2DImageProperties.h"

////////////////////////////////////////////////////////////////////////////////
// FORWARD DECLARATIONS
////////////////////////////////////////////////////////////////////////////////

class A2D;
class A2DTexture;

////////////////////////////////////////////////////////////////////////////////
// DEFINE
////////////////////////////////////////////////////////////////////////////////                               

////////////////////////////////////////////////////////////////////////////////
// DECLARATION
////////////////////////////////////////////////////////////////////////////////

class A2DTextureBuffer : public A2DTexture
{

public:

	// Constructor
	A2DTextureBuffer(A2DBackBuffer * xBackBuffer, float xWidth, float xHeight);

	// Deconstructor
	~A2DTextureBuffer();
	
	// Variables
	A2DBackBuffer * aBackBuffer;
	ID3D10Texture2D* aDXRenderTargetTexture;
	ID3D10RenderTargetView* aDXRenderTargetView;
	ID3D10DepthStencilState   *     aDXDepthStencilState;
	D3D10_VIEWPORT m_viewport;

	// Accessors
	// { NONE }

	// Mutators
	// { NONE }

	// Additional
	void                            SetActive();
	void                            Clear();

public:

	//////////////////////////////////////////////////////////
	// A2DTEXTURE IMPLEMENTATION
	//////////////////////////////////////////////////////////

	virtual ID3D10ShaderResourceView   *	GetResource();

public:

	//////////////////////////////////////////////////////////
	// A2DABSTRACT IMPLEMENTATION
	//////////////////////////////////////////////////////////

	virtual HRESULT                 Initialize();
	virtual void                    Deinitialize();
	virtual LPCWSTR                 GetClass();
	virtual LPCWSTR                 ToString();
	virtual bool                    operator==(A2DAbstract * xAbstract);

};


#endif
