////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __A2DABSTRACTSHAPE_H__
#define __A2DABSTRACTSHAPE_H__

//+-----------------------------------------------------------------------------
//
//  Class: 
//      A2DABSTRACTSHAPE
//
//  Synopsis:
//      Abstract class for shapes such as quads/triangles.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "A2DExtLibs.h"
#include "A2DPipelineable.h"
#include "A2DVertexData.h"
#include "A2DRect.h"

////////////////////////////////////////////////////////////////////////////////
// FORWARD DECLARATIONS
////////////////////////////////////////////////////////////////////////////////

class A2D;
class A2DAbstract;
class A2DPipelineable;
class A2DBackBuffer;

////////////////////////////////////////////////////////////////////////////////
// DEFINE
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// DECLARATION
////////////////////////////////////////////////////////////////////////////////

class A2DAbstractShape : public A2DPipelineable
{
public:

	A2DAbstractShape(A2DBackBuffer * xBackBuffer, int xVertexCount);

	~A2DAbstractShape();

protected:

	// Variables
	A2DBackBuffer			*		aBackBuffer;


	///////////////////////////////////////////

	int								aVertexCount; // if called from this class, default would be 6
	int								aIndexCount; // same as above

	ID3D10Buffer		*			aVertexBuffer;
	ID3D10Buffer		*			aIndexBuffer;

	///////////////////////////////////////////

	virtual HRESULT					CreateResources(void * xArgs[]);
	virtual void					Update(void * xArgs[]) = 0;
	virtual void					Render(); // Render should be defined seperately but called inside Update
	virtual void					DestroyResources();

protected:

	virtual void					CalculateCoords(A2DRect * xTexRect) = 0; // NEEDS TO CHANGE WILL SHAPES WILL NOT ALWAYS HAVE TEXTURES
	virtual HRESULT					MapCoords() = 0;

public:

	//virtual HRESULT					SetAsTexture() = 0;

public:

	//////////////////////////////////////////////////////////
	// A2DABSTRACT IMPLEMENTATION
	//////////////////////////////////////////////////////////

	virtual HRESULT                 Initialize() = 0;
	virtual void                    Deinitialize() = 0;
	virtual LPCWSTR                 GetClass();
	virtual LPCWSTR                 ToString();
	virtual bool                    operator==(A2DAbstract * A2DAbstract);
	
};



#endif