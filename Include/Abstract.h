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

		// Pure Virtual
		virtual HRESULT                 Initialize() = 0;                           // Initialize  
		virtual void                    Deinitialize() = 0;                         // Shutdown   

		// Virtual    
		virtual LPCWSTR                 GetClass();                                 // Class type    
		virtual bool                    operator==(Abstract * xAbstract);        // Class type       
		virtual LPCWSTR                 ToString();                                 // Class type 

		virtual bool					isClass(LPCWSTR xClass) final;
	};

}
#endif
