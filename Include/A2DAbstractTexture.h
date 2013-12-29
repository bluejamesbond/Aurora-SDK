////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __A2DABSTRACTTEXTURE_H__
#define __A2DABSTRACTTEXTURE_H__

//+-----------------------------------------------------------------------------
//
//  Class:  
//      A2DABSTRACTTEXTURE
//
//  Synopsis:
//      Texture container class.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "A2DRect.h"
#include "A2DPipelineable.h"

////////////////////////////////////////////////////////////////////////////////
// FORWARD DECLARATIONS
////////////////////////////////////////////////////////////////////////////////

class A2D;
class A2DAbstract;
class A2DAbstractTexture;

////////////////////////////////////////////////////////////////////////////////
// DECLARATION
////////////////////////////////////////////////////////////////////////////////

class A2DAbstractTexture : public A2DPipelineable
{

protected:

	// Variables
	A2DDims							aDims;
	A2DRect							aClip;

public:

	// Accessors
	A2DDims			*		GetSize();
	A2DRect			*		GetClip(int xIndex = 0);

	// Mutators
	void					SetClip(A2DRect * xClip, int xIndex = 0);
	
	// Virtual
	virtual void			*		getPlatformCompatibleResource() = 0;
	virtual	bool					hasAlpha() = 0;
	
public:

	// Implementation
	// { A2DABSTRACT }
	virtual HRESULT                 Initialize() = 0;
	virtual void                    Deinitialize() = 0;
	virtual LPCWSTR                 GetClass() = 0;
	virtual LPCWSTR                 ToString() = 0;
	virtual bool                    operator==(A2DAbstract * xAbstract) = 0;

};



#endif