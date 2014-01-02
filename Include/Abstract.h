////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __ABSTRACT_H__
#define __ABSTRACT_H__

//+-----------------------------------------------------------------------------
//
//  Abstract Class:
//      ABSTRACT
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

namespace A2D {

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

	class Abstract
	{

	public:

		virtual HRESULT                 initialize() = 0;                           // initialize  
		virtual LPCWSTR                 getClass();                                 // Class type    
		virtual LPCWSTR                 toString();                                 // Class type 
		static bool						isClass(Abstract& xAbstract, LPCWSTR xClass);
	};

}
#endif
