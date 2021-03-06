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
//      Texure and colored vertices shader.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////


#include "ExtLibs.h"
#include "AbstractTextureShader.h"

namespace A2D {
	
	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

	class ColoredTextureShader : public AbstractTextureShader
	{
	public:

		ColoredTextureShader(ID3D10Device ** xDevice);

	protected:

		virtual STATUS					createPolygonLayout(D3D10_INPUT_ELEMENT_DESC ** xPolygonLayout);
		virtual unsigned int			getPolygonLayoutElementCount();
		virtual	LPCSTR					getTechniqueName();		

	};
}

#endif