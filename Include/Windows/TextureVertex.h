////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __TEXTUREVERTEX_H__
#define __TEXTUREVERTEX_H__

//+-----------------------------------------------------------------------------
//
//  Class:
//      VERTEXDATA
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

	struct TextureVertex
	{
		// Variables
		D3DXVECTOR3 position;
		D3DXVECTOR2 texture;

		static void  TextureVertex::memcpySSE2(TextureVertex * xDest, const TextureVertex * xSrc);
	};
}
#endif