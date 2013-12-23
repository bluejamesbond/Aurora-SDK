////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __A2DABSTRACT_H__
#define __A2DABSTRACT_H__

//+-----------------------------------------------------------------------------
//
//  Abstract Class:
//      A2DABSTRACT
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

////////////////////////////////////////////////////////////////////////////////
// DECLARATION
////////////////////////////////////////////////////////////////////////////////

class A2DAbstract
{
public:

    // Pure Virtual
    virtual HRESULT                 Initialize() = 0;                           // Initialize  
    virtual void                    Deinitialize() = 0;                         // Shutdown   

    // Virtual    
    virtual LPCWSTR                 GetClass();                                 // Class type    
    virtual bool                    operator==(A2DAbstract * xAbstract);        // Class type       
    virtual LPCWSTR                 ToString();                                 // Class type 

	virtual bool					isClass(LPCWSTR xClass) final;
};

#endif
