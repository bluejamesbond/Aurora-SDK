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
#include "AbstractShader.h"

namespace A2D {

	////////////////////////////////////////////////////////////////////////////////
	// FORWARD DECLARATIONS
	////////////////////////////////////////////////////////////////////////////////

	class Abstract;

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

	class AbstractTextureShader : public AbstractShader
	{
	public:

		AbstractTextureShader(ID3D10Device ** xDevice);
		virtual ~AbstractTextureShader();

	private:

		static Texture						*	aTexture;
		static float						**	aProjectionMatrix;
		static ID3D10Effect					*	aTextureEffect;
		static ID3D10EffectMatrixVariable	*	aWorldMatrixPtr;
		static ID3D10EffectMatrixVariable	*	aViewMatrixPtr;
		static ID3D10EffectMatrixVariable	*	aProjectionMatrixPtr;
		static ID3D10EffectShaderResourceVariable*   aTexturePtr;

	public:

		void									setTexture(Texture * xTexture);
		static void								setViewMatrix(float ** xMatrix);
		static void								setWorldMatrix(float ** xMatrix);
		static void								setProjectionMatrix(float ** xMatrix);
		static void								reloadProjectionMatrix();

	protected:

		virtual ID3D10Effect				**	getEffect();
		virtual LPCWSTR							getEffectName();
		virtual HRESULT							getUsableVariablePointers(ID3D10Effect * xEffect);
		virtual HRESULT							createPolygonLayout(D3D10_INPUT_ELEMENT_DESC * xPolygonLayout) = 0;
		virtual unsigned int					getPolygonLayoutElementCount() = 0;
		virtual	LPCSTR							getTechniqueName() = 0;

	public:

		//////////////////////////////////////////////////////////
		// ABSTRACT IMPLEMENTATION
		//////////////////////////////////////////////////////////

		virtual LPCWSTR                 getClass() = 0;
		virtual LPCWSTR                 toString() = 0;
	};
}

#endif