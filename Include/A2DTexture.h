////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __A2DTEXTURE_H__
#define __A2DTEXTURE_H__

//+-----------------------------------------------------------------------------
//
//  Class:  
//      A2DTEXTURE
//
//  Synopsis:
//      Texture container class.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "A2DRenderData.h"
#include "A2DBackBuffer.h"
#include "A2DAbstractTexture.h"
#include "A2DRect.h"

////////////////////////////////////////////////////////////////////////////////
// FORWARD DECLARATIONS
////////////////////////////////////////////////////////////////////////////////

class A2D;
class A2DAbstract;
class A2DAbstractTexture;

////////////////////////////////////////////////////////////////////////////////
// DEFINE
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// DECLARATION
////////////////////////////////////////////////////////////////////////////////

class A2DTexture : public A2DAbstractTexture
{
public:
	// Constructor
	A2DTexture(ID3D10Device ** xDXDevice, LPCWSTR * xFilename);

	// Deconstructor
	~A2DTexture();

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
	// { A2DABSTRACT }
	virtual HRESULT                 Initialize();
	virtual void	                Deinitialize();
	virtual LPCWSTR                 GetClass();
	virtual LPCWSTR                 ToString();
	virtual bool                    operator==(A2DAbstract * xAbstract);

};



#endif
