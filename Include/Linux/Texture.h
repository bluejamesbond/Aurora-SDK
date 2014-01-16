////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __TEXTURE_H__
#define __TEXTURE_H__

//+-----------------------------------------------------------------------------
//
//  Class:  
//      TEXTURE
//
//  Synopsis:
//      Texture container class.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "../Core/Rect.h"
#include "BackBuffer.h"
#include "AbstractTexture.h"
#include "Common.h"
#include "GLImageLoader.h"
#include "TextureBuffer.h"

namespace A2D {

	////////////////////////////////////////////////////////////////////////////////
	// FORWARD DECLARATIONS
	////////////////////////////////////////////////////////////////////////////////

	class AbstractTexture;
	
	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

	class Texture : public AbstractTexture
	{
	public:
		// Constructor
        Texture(LPCWSTR xSrc, GLfloat* tcoords);

		// Deconstructor
		~Texture();

        unsigned char           *       image_data;
        unsigned int                    tex = 0;
        GLint                           State = GL_CLAMP_TO_EDGE;
        GLfloat                   *       texcoords;
        unsigned int                    vt_vbo;

		// Variables
		LPCTSTR							aSrc;
        TextureBuffer           *       tBuffer;

		// Accessors
        LPCTSTR					*		GetSrc();

		// Virtual
		HRESULT							changeTexture(LPCWSTR  xSrc);

		// Virtual
		virtual	bool					hasAlpha();
		virtual void			*		getPlatformCompatibleResource();

	public:
		// Implementation
		// { ABSTRACT }
		virtual HRESULT                 initialize();
        void                            checkSrcDims();
        void                            renderTexture();

	};
}

#endif
