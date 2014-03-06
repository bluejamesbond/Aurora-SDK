////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __VERTICALBLURSHADER_H__
#define __VERTICALBLURSHADER_H__

//+-----------------------------------------------------------------------------
//
//  Class: 
//      HORIZONTALBLURSHADER
//
//  Synopsis:
//      Texture quad.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////


#include "ExtLibs.h"
#include "AbstractTextureShader.h"

namespace A2D {

	////////////////////////////////////////////////////////////////////////////////
	// FORWARD DECLARATIONS
	////////////////////////////////////////////////////////////////////////////////

	class Abstract;

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

	class VerticalBlurShader : public AbstractTextureShader
	{
	public:

		VerticalBlurShader(ID3D10Device ** xDevice);

		void							setTexelSize(float x_size);

	protected:

		ID3D10EffectScalarVariable   *  m_texelSize = NULL;

		virtual STATUS                  getUsableVariablePointers(ID3D10Effect * xEffect);
		virtual LPCWSTR                 getEffectName();
		virtual STATUS					createPolygonLayout(D3D10_INPUT_ELEMENT_DESC ** xPolygonLayout);
		virtual unsigned int			getPolygonLayoutElementCount();
		virtual	LPCSTR					getTechniqueName();

	};
}

#endif