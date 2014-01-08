////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __COLOREDTEXTUREVERTEX_H__
#define __COLOREDTEXTUREVERTEX_H__

//+-----------------------------------------------------------------------------
//
//  Class:
//      COLOREDTEXTUREVERTEX
//
//  Synopsis:
//      Differentiates which of the two possible arcs could match the given arc
//      parameters.
//
//------------------------------------------------------------------------------

namespace A2D {

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

	struct ColoredTextureVertex
	{
		// Variables
		D3DXVECTOR3 position;
		D3DXVECTOR2 texture;
		D3DXVECTOR4 color;
	};
}

#endif