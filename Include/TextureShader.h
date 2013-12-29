////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __TEXTURESHADER_H__
#define __TEXTURESHADER_H__

//+-----------------------------------------------------------------------------
//
//  Class: 
//      TEXTURESHADER
//
//  Synopsis:
//      Texture quad.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "ExtLibs.h"
#include "DXShaderUtils.h"
#include "Texture.h"

////////////////////////////////////////////////////////////////////////////////
// FORWARD DECLARATIONS
////////////////////////////////////////////////////////////////////////////////

class ;
class Abstract;

////////////////////////////////////////////////////////////////////////////////
// DECLARATION
////////////////////////////////////////////////////////////////////////////////

class TextureShader : public DXShaderUtils
{
public:
	TextureShader(ID3D10Device ** xDXDevice, float ** xWorldMatrixPtr, float ** xViewMatrix, float ** xProjectionMatrix);
	~TextureShader();

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

	Texture					*	aTexture;

public:

	void							setTexture(Texture * xTexture);
	void							loadMatrices();
	void							renderTexture();

public:

	//////////////////////////////////////////////////////////
	// ABSTRACT IMPLEMENTATION
	//////////////////////////////////////////////////////////

	virtual HRESULT	                Initialize();
	virtual void	                Deinitialize();
	virtual LPCWSTR                 GetClass();
	virtual LPCWSTR                 ToString();
	virtual bool                    operator==(Abstract * xAbstract);
};



#endif