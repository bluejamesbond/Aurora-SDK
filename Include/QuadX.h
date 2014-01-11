////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __QUADX_H__
#define __QUADX_H__

//+-----------------------------------------------------------------------------
//
//  Class: 
//      QUADX
//
//  Synopsis:
//      Class for multiple quads.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "ExtLibs.h"
#include "Abstract.h"
#include "Pipelineable.h"
#include "Rect.h"
#include "VertexData.h"
#include "BackBuffer.h"
#include "Quad.h"

////////////////////////////////////////////////////////////////////////////////
// FORWARD DECLARATIONS
////////////////////////////////////////////////////////////////////////////////

class ;
class Abstract;

////////////////////////////////////////////////////////////////////////////////
// DEFINE
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// DECLARATION
////////////////////////////////////////////////////////////////////////////////

class QuadX : public Quad
{
public:
	QuadX(BackBuffer * xBuffer, Rect xConstraints, int xQuadCount);
	~QuadX();

	int								aQuadCount; // number of quads

	const int						QUADX_HORIZONTAL_MODE = 0x04215; // horizontal quad
	const int						QUADX_VERTICAL_MODE = 0x02414;

	///////////////////////////////////////////

	bool							aRepeatX;
	bool							aRepeatY;
	bool							aHorizontal;
	bool							aVertical;

	///////////////////////////////////////////

	virtual HRESULT CreateResources(void * xArgs[]);

	///////////////////////////////////////////

	// 0: a2drect
	// 1: a2dtexture
	// 2: a2dwinprops
	// 3: orientation (horizontal/vertical) (?)
	// 4: repeat direction x or y (?)
	virtual void					Update(void* Args[]);
	virtual HRESULT					Map();

protected:

	virtual HRESULT					MapCoords();
	virtual void					BuildVertex();

public:

	//////////////////////////////////////////////////////////
	// ABSTRACT IMPLEMENTATION
	//////////////////////////////////////////////////////////

	virtual HRESULT                 initialize() = 0;
	virtual void                    Deinitialize() = 0;
	virtual LPCWSTR                 getClass();
	virtual LPCWSTR                 toString();
	virtual bool                    operator==(Abstract * Abstract);
	
};



#endif