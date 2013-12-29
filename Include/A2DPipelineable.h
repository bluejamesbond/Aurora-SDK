////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __PIPELINEABLE_H__
#define __PIPELINEABLE_H__

//+-----------------------------------------------------------------------------
//
//  Class:
//      PIPELINEABLE
//
//  Synopsis:
//      Differentiates which of the two possible arcs could match the given arc
//      parameters.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "ExtLibs.h"
#include "Abstract.h"

////////////////////////////////////////////////////////////////////////////////
// DECLARATION
////////////////////////////////////////////////////////////////////////////////

class Pipelineable : public Abstract
{

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
