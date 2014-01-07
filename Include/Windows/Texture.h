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
	public:
		// Constructor
		Texture(ID3D10Device ** xDevice, LPCWSTR xFilename);

		// Deconstructor
		~Texture();

		ID3D10Device			**		aDevice;
		ID3D10ShaderResourceView*		aResource;

		static			ID3D10ShaderResourceView* aStaticResource;

		// Variables
		LPCTSTR							aSrc;

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

	};
}

#endif
