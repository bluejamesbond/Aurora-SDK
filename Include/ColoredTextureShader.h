////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __COLOREDTEXTURESHADER_H__
#define __COLOREDTEXTURESHADER_H__

//+-----------------------------------------------------------------------------
//
//  Class: 
//      COLOREDTEXTURESHADER
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
#include "AbstractTextureShader.h"

namespace A2D {

	////////////////////////////////////////////////////////////////////////////////
	// FORWARD DECLARATIONS
	////////////////////////////////////////////////////////////////////////////////

	class Abstract;

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

	class ColoredTextureShader : public AbstractTextureShader
	{
	public:

		ColoredTextureShader(ID3D10Device ** xDevice);

	protected:

		virtual HRESULT					createPolygonLayout(D3D10_INPUT_ELEMENT_DESC * xPolygonLayout);
		virtual unsigned int			getPolygonLayoutElementCount();
		virtual	LPCSTR					getTechniqueName();

	public:

		//////////////////////////////////////////////////////////
		// ABSTRACT IMPLEMENTATION
		//////////////////////////////////////////////////////////

		virtual LPCWSTR                 getClass();
		virtual LPCWSTR                 toString();
		

	};
}

#endif