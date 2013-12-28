////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __A2DQUADDATA_H__
#define __A2DQUADDATA_H__


//+-----------------------------------------------------------------------------
//
//  Class:  
//      A2DQUADDATA
//
//  Synopsis:
//      Texture container class.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "A2DExtLibs.h"
#include "A2DVertexData.h"
#include "A2DImageProperties.h"
#include "A2DRect.h"
#include "A2DPipelineable.h"

////////////////////////////////////////////////////////////////////////////////
// DECLARATION
////////////////////////////////////////////////////////////////////////////////

struct A2DQuadData : public A2DPipelineable
{
	// Before adjusting the ID3D10Buffer
	// check if any of these values are different
	// Do a memcompare(ptr1, ptr2) of these with the new ones
	A2DRect aPreviousRect; // cached
	A2DRect aPreviousContraints; // cached
	A2DRect	aPreviousTextureClip; // cached
	A2DDims	aPreviousTextureSize; // cached
	A2DImageProperties aPreviousImageProperties; // cached

	// Do not delete only adjust the values! 
	A2DVertexData					aVertices[6];

	// Vertex buffer can change (but change only as needed)
	ID3D10Buffer		*			aVertexBuffer;

	// This pretty much stays constant
	// so it will be stored inside A2DQuads instance.
	// ID3D10Buffer		*			aIndexBuffer;

	virtual HRESULT                 Initialize(){ return S_OK;  };
	virtual void                    Deinitialize(){};
	virtual LPCWSTR                 GetClass(){ return L"A2DQuadData"; };
	virtual LPCWSTR                 ToString(){ return L"A2DQuadData";  };
	virtual bool                    operator==(A2DAbstract * xAbstract){ return false; };
};

#endif