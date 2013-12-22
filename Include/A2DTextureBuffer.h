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

#include "A2DVertexData.h"
#include "A2DBackBuffer.h"
#include "A2DAbstractTexture.h"
#include "A2DImageProperties.h"
#include "A2DRect.h"

////////////////////////////////////////////////////////////////////////////////
// FORWARD DECLARATIONS
////////////////////////////////////////////////////////////////////////////////

class A2D;
class A2DTexture;
class A2DAbstractTexture;

////////////////////////////////////////////////////////////////////////////////
// DEFINE
////////////////////////////////////////////////////////////////////////////////                               

////////////////////////////////////////////////////////////////////////////////
// DECLARATION
////////////////////////////////////////////////////////////////////////////////

class A2DTextureBuffer : public A2DAbstractTexture
{

public:

	// Constructor
	A2DTextureBuffer(A2DBackBuffer * xBackBuffer, A2DDims * xSize);

	// Deconstructor
	~A2DTextureBuffer();
	
	// Variables
	ID3D10Texture2D				*	aDXRenderTargetTexture;
	ID3D10RenderTargetView		*	aDXRenderTargetView;
	ID3D10DepthStencilState		*   aDXDepthStencilState;

	// Accessors
	virtual	bool					hasAlpha();

	// Mutators
	void							SetActive();

	// Additional
	void							Clear();

public:

	// Implementation
	// { A2DABSTRACTTEXTURE }
	virtual HRESULT					CreateResources(void * xArgs[]);
	virtual void					Update(void * xArgs[]);
	virtual void					Render(); // Render should be defined seperately but called inside Update
	virtual void					DestroyResources();
	
public:
	// Implementation
	// { A2DABSTRACT }
	virtual LPCWSTR                 GetClass();
	virtual LPCWSTR                 ToString();
	virtual bool                    operator==(A2DAbstract * xAbstract);

};


#endif
