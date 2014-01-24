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

#include "../Core/Common.h"
//#include "../Core/ImageProperties.h"
#include "../Core/Rect.h"

//#include "TextureVertex.h"
//#include "BackBuffer.h"
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
//        TextureBuffer(Dims * xSize);
        TextureBuffer();

		// Deconstructor
		~TextureBuffer();

		// Variables

		// Accessors
		virtual	bool					hasAlpha() { return false; };

		// Mutators
//		void							SetActive();
        void                            genBuffer(unsigned int vt_vbo, float*texcoords);

		// Additional
//		void							Clear();
		virtual void			   *	getPlatformCompatibleResource(){ return NULL; };

	public:

		// Implementation
		// { ABSTRACT }
		virtual HRESULT                 initialize();

	};
}

#endif
