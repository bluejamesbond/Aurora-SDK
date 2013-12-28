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
#include "A2DDXShaderUtils.h"
#include "A2DTexture.h"

////////////////////////////////////////////////////////////////////////////////
// FORWARD DECLARATIONS
////////////////////////////////////////////////////////////////////////////////

class A2D;
class A2DAbstract;

////////////////////////////////////////////////////////////////////////////////
// DECLARATION
////////////////////////////////////////////////////////////////////////////////

class A2DTextureShader : public A2DDXShaderUtils
{
public:
	A2DTextureShader(ID3D10Device ** xDXDevice, float ** xWorldMatrixPtr, float ** xViewMatrix, float ** xProjectionMatrix);
	~A2DTextureShader();

private:

	// Pull out and cache device
	ID3D10Device				**	aDXDevice;
	
	float						**	aWorldMatrix;
	float						**	aViewMatrix;
	float						**	aProjectionMatrix;

	ID3D10EffectMatrixVariable	*	aWorldMatrixPtr;
	ID3D10EffectMatrixVariable	*	aViewMatrixPtr;
	ID3D10EffectMatrixVariable	*	aProjectionMatrixPtr;
	ID3D10EffectShaderResourceVariable	*	aTexturePtr;

	ID3D10Effect				*	aEffect;
	ID3D10EffectTechnique		*	aTechnique;
	ID3D10InputLayout			*	aLayout;
	ID3D10BlendState			*	aBlendState;
	ID3D10BlendState			*	aBlendDisabledState;

	A2DTexture					*	aTexture;

public:

	void							setTexture(A2DTexture * xTexture);
	void							loadMatrices();
	void							renderTexture();

public:

	//////////////////////////////////////////////////////////
	// A2DABSTRACT IMPLEMENTATION
	//////////////////////////////////////////////////////////

	virtual HRESULT	                Initialize();
	virtual void	                Deinitialize();
	virtual LPCWSTR                 GetClass();
	virtual LPCWSTR                 ToString();
	virtual bool                    operator==(A2DAbstract * xAbstract);
};



#endif