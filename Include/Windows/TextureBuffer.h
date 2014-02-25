////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __TEXTUREBUFFER_H__
#define __TEXTUREBUFFER_H__

//+-----------------------------------------------------------------------------
//
//  Struct:
//      TEXTUREBUFFER
//
//  Synopsis:
//      Differentiates which of the two possible arcs could match the given arc
//      parameters.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////


#include "../Core/../_A2DCommon.h"
#include "../Core/ImageProperties.h"
#include "../Core/Rect.h"

#include "BackBuffer.h"
#include "AbstractTexture.h"

namespace A2D {

	////////////////////////////////////////////////////////////////////////////////
	// FORWARD DECLARATIONS
	////////////////////////////////////////////////////////////////////////////////

	class Texture;
	class AbstractTexture;

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

	class TextureBuffer : public AbstractTexture
	{

	public:

		// Constructor
		TextureBuffer(ID3D10Device ** xDevice, ID3D10DepthStencilView ** xBackBufferaDXDepthStencilView, Dims * xSize);

		// Deconstructor
		virtual ~TextureBuffer();

		// Variables
		ID3D10Device				**	aDevice;
		ID3D10DepthStencilView		**	aBackBufferaDXDepthStencilView;

		ID3D10Texture2D				*	aDXRenderTargetTexture;
		ID3D10RenderTargetView		*	aDXRenderTargetView;
		ID3D10DepthStencilState		*   aDXDepthStencilState;
		ID3D10ShaderResourceView*		aResource;

		// Accessors
		virtual	bool					hasAlpha();

		// Mutators
		void							SetActive();

		// Additional
		void							Clear();
		virtual void			   *	getPlatformCompatibleResource();

	public:

		// Implementation
		// { ABSTRACT }
		virtual STATUS                 initialize();

	};
}

#endif
