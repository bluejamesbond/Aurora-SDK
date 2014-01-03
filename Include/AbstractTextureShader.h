////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __ABSTRACTTEXTURESHADER_H__
#define __ABSTRACTTEXTURESHADER_H__

//+-----------------------------------------------------------------------------
//
//  Class: 
//      ABSTRACTTEXTURESHADER
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

namespace A2D {

	////////////////////////////////////////////////////////////////////////////////
	// FORWARD DECLARATIONS
	////////////////////////////////////////////////////////////////////////////////

	class Abstract;

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

	class AbstractTextureShader
	{
	public:

		AbstractTextureShader(ID3D10Device ** xDXDevice);
		~AbstractTextureShader();

	private:

		// Pull out and cache device
		ID3D10Device				**	aDXDevice;


		ID3D10EffectShaderResourceVariable	*	aTexturePtr;

		ID3D10EffectTechnique		*	aTextureTechnique;
		ID3D10EffectTechnique		*	aTechnique;
		ID3D10InputLayout			*	aLayout;

		Texture						*	aTexture;

		static ID3D10EffectMatrixVariable	*	aWorldMatrixPtr;
		static ID3D10EffectMatrixVariable	*	aViewMatrixPtr;
		static ID3D10EffectMatrixVariable	*	aProjectionMatrixPtr;
		static ID3D10Effect			*	aTextureEffect;
		static ID3D10BlendState		*	aBlendState;
		static ID3D10BlendState		*	aBlendDisabledState;

		static float				**	aProjectionMatrix;

	public:

		void							setTexture(Texture * xTexture);
		void							renderTexture();
		static void						setViewMatrix(float ** xMatrix);
		static void						setWorldMatrix(float ** xMatrix);
		static void						setProjectionMatrix(float ** xMatrix);
		static void						reloadProjectionMatrix();

	protected:

		virtual HRESULT					createPolygonLayout(D3D10_INPUT_ELEMENT_DESC * xPolygonLayout) = 0;
		virtual unsigned int			getPolygonLayoutElementCount() = 0;
		virtual	LPCSTR					getTechniqueName() = 0;

	public:

		//////////////////////////////////////////////////////////
		// ABSTRACT IMPLEMENTATION
		//////////////////////////////////////////////////////////

		virtual HRESULT	                initialize();
		virtual LPCWSTR                 getClass();
		virtual LPCWSTR                 toString();
	};
}

#endif