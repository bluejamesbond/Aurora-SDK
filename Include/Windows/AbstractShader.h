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


#include "ExtLibs.h"
#include "DXUtils.h"
#include "Texture.h"
#include "VertexTypes.h"

namespace A2D {

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
		int								aIndexCount = 6;


	private:
		
		static ID3D10BlendState		*	aBlendState;
		static ID3D10BlendState		*	aBlendDisabledState;
		
	public:

		void							renderShader();
		void							renderShader(int xIndexCount);

	protected:

		virtual STATUS					createPolygonLayout(D3D10_INPUT_ELEMENT_DESC ** xPolygonLayout) = 0;
		virtual unsigned int			getPolygonLayoutElementCount() = 0;
		virtual	LPCSTR					getTechniqueName() = 0;
		virtual ID3D10Effect		**	getEffect() = 0;
		virtual LPCWSTR					getEffectName() = 0;
		virtual STATUS					getUsableVariablePointers(ID3D10Effect * xEffect) = 0;

	public:

		//////////////////////////////////////////////////////////
		// ABSTRACT IMPLEMENTATION
		//////////////////////////////////////////////////////////

		virtual STATUS	                initialize();
	};
}

#endif