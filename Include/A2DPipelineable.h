////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __A2DPIPELINEABLE_H__
#define __A2DPIPELINEABLE_H__

//+-----------------------------------------------------------------------------
//
//  Class:
//      A2DPIPELINEABLE
//
//  Synopsis:
//      Differentiates which of the two possible arcs could match the given arc
//      parameters.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "A2DExtLibs.h"
#include "A2DAbstract.h"

////////////////////////////////////////////////////////////////////////////////
// DECLARATION
////////////////////////////////////////////////////////////////////////////////

class A2DPipelineable : public A2DAbstract
{

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
