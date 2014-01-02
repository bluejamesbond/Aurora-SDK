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

namespace A2D {

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

	class Pipelineable : public Abstract
	{

	public:

		// Implementation
		// { ABSTRACT }
		virtual HRESULT                 initialize() = 0;
		virtual void                    Deinitialize() = 0;
		virtual LPCWSTR                 getClass() = 0;
		virtual LPCWSTR                 toString() = 0;
		virtual bool                    operator==(Abstract * xAbstract) = 0;
	};
}

#endif
