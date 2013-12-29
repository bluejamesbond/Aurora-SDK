////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __ABSTRACTTEXTURE_H__
#define __ABSTRACTTEXTURE_H__

//+-----------------------------------------------------------------------------
//
//  Class:  
//      ABSTRACTTEXTURE
//
//  Synopsis:
//      Texture container class.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "Rect.h"
#include "Pipelineable.h"

////////////////////////////////////////////////////////////////////////////////
// FORWARD DECLARATIONS
////////////////////////////////////////////////////////////////////////////////

class ;
class Abstract;
class AbstractTexture;

////////////////////////////////////////////////////////////////////////////////
// DECLARATION
////////////////////////////////////////////////////////////////////////////////

class AbstractTexture : public Pipelineable
{

protected:

	// Variables
	Dims							aDims;
	Rect							aClip;

public:

	// Accessors
	Dims			*		GetSize();
	Rect			*		GetClip(int xIndex = 0);

	// Mutators
	void					SetClip(Rect * xClip, int xIndex = 0);
	
	// Virtual
	virtual void			*		getPlatformCompatibleResource() = 0;
	virtual	bool					hasAlpha() = 0;
	
public:

	// Implementation
	// { ABSTRACT }
	virtual HRESULT                 Initialize() = 0;
	virtual void                    Deinitialize() = 0;
	virtual LPCWSTR                 GetClass() = 0;
	virtual LPCWSTR                 ToString() = 0;
	virtual bool                    operator==(Abstract * xAbstract) = 0;

};



#endif
