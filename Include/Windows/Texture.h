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

		friend class Graphics;

	public:
		// Constructor
		Texture(ID3D10Device ** xDevice, LPCWSTR xFilename);

		// Deconstructor
		virtual ~Texture();

		ID3D10Device			**		aDevice;
		ID3D10ShaderResourceView*		aResource;

		// Variables
		LPCTSTR							aSrc;

		// Accessors
		LPCTSTR					*		GetSrc();

		// Virtual
		STATUS							changeTexture(LPCWSTR xSrc);
		
		// Virtual
		virtual	bool					hasAlpha();
		
		static Texture*					DEFAULT_TEXTURE;

		inline void * Texture::getPlatformCompatibleResource()
		{
			return aResource;
		}

		inline bool update(LPCWSTR xSrc)
		{
			if (wcscmp(aSrc, xSrc) != 0)
			{
				aSrc = xSrc;

				Texture::~Texture();

				initialize();

				return true;
			}

			return false;
		}

	public:
		// Implementation
		// { ABSTRACT }
		virtual STATUS                 initialize();

	};
}

#endif
