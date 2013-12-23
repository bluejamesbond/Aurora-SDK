////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __A2DTEXTURESHADER_H__
#define __A2DTEXTURESHADER_H__

//+-----------------------------------------------------------------------------
//
//  Class: 
//      A2DTEXTURESHADER
//
//  Synopsis:
//      Texture quad.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "A2DExtLibs.h"
#include "A2DAbstractShader.h"
#include "A2DTexture.h"

////////////////////////////////////////////////////////////////////////////////
// FORWARD DECLARATIONS
////////////////////////////////////////////////////////////////////////////////

class A2D;
class A2DAbstract;

////////////////////////////////////////////////////////////////////////////////
// DEFINE
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// DECLARATION
////////////////////////////////////////////////////////////////////////////////

class A2DTextureShader : public A2DAbstractShader
{
public:
	A2DTextureShader(A2DBackBuffer * xBackBuffer);
	~A2DTextureShader();

	ID3D10EffectMatrixVariable	*	aWorldMatrixPtr;
	ID3D10EffectMatrixVariable	*	aViewMatrixPtr;
	ID3D10EffectMatrixVariable	*	aProjectionMatrixPtr;
	ID3D10EffectShaderResourceVariable	*	aTexturePtr;
	ID3D10EffectScalarVariable	*	aScreenHeightPtr;
	ID3D10EffectScalarVariable	*	aScreenWidthPtr;

	virtual HRESULT					CreateResources(void * xArgs[]);
	virtual void					Update(void * xArgs[]);
	virtual void					DestroyResources();

public:

	//////////////////////////////////////////////////////////
	// A2DABSTRACT IMPLEMENTATION
	//////////////////////////////////////////////////////////

	virtual LPCWSTR                 GetClass();
	virtual LPCWSTR                 ToString();
	virtual bool                    operator==(A2DAbstract * xAbstract);
};



#endif