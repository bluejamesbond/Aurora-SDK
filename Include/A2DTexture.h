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

#include "RenderData.h"
#include "BackBuffer.h"
#include "AbstractTexture.h"
#include "Rect.h"

////////////////////////////////////////////////////////////////////////////////
// FORWARD DECLARATIONS
////////////////////////////////////////////////////////////////////////////////

class ;
class Abstract;
class AbstractTexture;

////////////////////////////////////////////////////////////////////////////////
// DEFINE
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// DECLARATION
////////////////////////////////////////////////////////////////////////////////

class Texture : public AbstractTexture
{
public:
	// Constructor
	Texture(ID3D10Device ** xDXDevice, LPCWSTR * xFilename);

	// Deconstructor
	~Texture();

	ID3D10Device			**		aDXDevice;
	ID3D10ShaderResourceView*		aResource;

	static			ID3D10ShaderResourceView* aStaticResource;

	// Variables
	LPCTSTR					*		aSrc;

	// Accessors
	LPCTSTR					*		GetSrc();

	// Virtual
	HRESULT							changeTexture(LPCWSTR * xSrc);

	// Virtual
	virtual	bool					hasAlpha();
	virtual void			*		getPlatformCompatibleResource();
	
public:
	// Implementation
	// { ABSTRACT }
	virtual HRESULT                 Initialize();
	virtual void	                Deinitialize();
	virtual LPCWSTR                 GetClass();
	virtual LPCWSTR                 ToString();
	virtual bool                    operator==(Abstract * xAbstract);

};



#endif
