////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __QUADEXPANSIONSHADER_H__
#define __QUADEXPANSIONSHADER_H__

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
#include "Texture.h"
#include "AbstractShader.h"

namespace A2D {

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

	class QuadExpansionShader : public AbstractShader
	{
	public:

		QuadExpansionShader(ID3D10Device ** xDevice);
		virtual ~QuadExpansionShader();
		
	private:

		static ID3D10Effect			*	aQuadEffect;
		static ID3D10EffectShaderResourceVariable*   aTexturePtr;
		static Texture				*	aTexture;

	public:

		void									setTexture(Texture * xTexture);

	protected:

		virtual ID3D10Effect		**	getEffect();
		virtual LPCWSTR					getEffectName();
		virtual HRESULT					getUsableVariablePointers(ID3D10Effect * xEffect);
		virtual HRESULT					createPolygonLayout(D3D10_INPUT_ELEMENT_DESC ** xPolygonLayout);
		virtual unsigned int			getPolygonLayoutElementCount();
		virtual	LPCSTR					getTechniqueName();
	};
}

#endif