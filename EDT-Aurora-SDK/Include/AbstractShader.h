////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __ABSTRACTSHADER_H__
#define __ABSTRACTSHADER_H__

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

#include "GLXExtLibs.h"
#include "GLShaderUtils.h"
//#include "Texture.h"

namespace A2D {

	////////////////////////////////////////////////////////////////////////////////
	// FORWARD DECLARATIONS
	////////////////////////////////////////////////////////////////////////////////

	class Abstract;

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

	class AbstractShader
	{
	public:

		AbstractShader(ID3D10Device ** xDevice);
		virtual ~AbstractShader();

	protected:

		// Pull out and cache device
		ID3D10Device				**	aDevice;
		ID3D10EffectTechnique		*	aTechnique;
		ID3D10InputLayout			*	aLayout;
		bool							aHasAlpha = false;


	private:
		
		static ID3D10BlendState		*	aBlendState;
		static ID3D10BlendState		*	aBlendDisabledState;
		
	public:

		void							renderShader();

	protected:

		virtual HRESULT					createPolygonLayout(D3D10_INPUT_ELEMENT_DESC * xPolygonLayout) = 0;
		virtual unsigned int			getPolygonLayoutElementCount() = 0;
		virtual	LPCSTR					getTechniqueName() = 0;
		virtual ID3D10Effect		**	getEffect() = 0;
		virtual LPCWSTR					getEffectName() = 0;
		virtual HRESULT					getUsableVariablePointers(ID3D10Effect * xEffect) = 0;

	public:

		//////////////////////////////////////////////////////////
		// ABSTRACT IMPLEMENTATION
		//////////////////////////////////////////////////////////

		virtual HRESULT	                initialize();
		virtual LPCWSTR                 getClass() = 0;
		virtual LPCWSTR                 toString() = 0;
	};
}

#endif
