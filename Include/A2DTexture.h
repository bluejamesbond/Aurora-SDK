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
	A2DTexture(A2DBackBuffer * xBackBuffer, LPCWSTR * xFilename);

	// Deconstructor
	~A2DTexture();

	// Variables
	LPCTSTR					*		aSrc;

	// Accessors
	LPCTSTR					*		GetSrc();

	// Mutators
	// { NONE }

	// Builders
	// { NONE }

	// Factory
	// { NONE }

	// Additional

	// Pure Virtual
	// { NONE }

	// Virtual
	virtual	bool					HasAlpha();

public:

	// Implementation
	// { A2DABSTRACTTEXTURE }
	virtual HRESULT					CreateResources(void * xArgs[]);
	virtual void					Update(void * xArgs[]);
	virtual void					DestroyResources() {};

public:
	// Implementation
	// { A2DABSTRACT }
	virtual LPCWSTR                 GetClass();
	virtual LPCWSTR                 ToString();
	virtual bool                    operator==(A2DAbstract * xAbstract);

};



#endif
