////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __A2DRENDERDATA_H__
#define __A2DRENDERDATA_H__

//+-----------------------------------------------------------------------------
//
//  Struct:
//      A2DRENDERDATA
//
//  Synopsis:
//      Differentiates which of the two possible arcs could match the given arc
//      parameters.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "A2DAbstract.h"
#include "A2DAbstractWindow.h"

////////////////////////////////////////////////////////////////////////////////
// FORWARD DECLARATIONS
////////////////////////////////////////////////////////////////////////////////

class A2D;
class A2DAbstract;
class A2DRenderable;
class A2DAbstractComponent;
class A2DCamera;
struct A2DRenderData;
class A2DBackBuffer;
class A2DTextureBuffer;

////////////////////////////////////////////////////////////////////////////////
// DEFINE
////////////////////////////////////////////////////////////////////////////////
            
#define A2DRENDERDATA_LL(str1, str2)                          str1 str2                                        

////////////////////////////////////////////////////////////////////////////////
// DECLARATION
////////////////////////////////////////////////////////////////////////////////

struct A2DRenderData : public A2DAbstract
{

public:

    // Constructor
	A2DRenderData();
	A2DRenderData(A2DRenderData * xRenderData);

    // Deconstructor
    // { NONE }

    // Variables
    D3DXMATRIX                *     aViewMatrix;
    D3DXMATRIX                *     aWorldMatrix;
    D3DXMATRIX                *     aOrthogonalMatrix;
    D3DXMATRIX                *     aProjectionMatrix;

	A2DAbstractWindow		  *		aWindow;
    A2DCamera				  *     aCamera;
    A2DBackBuffer             *     aBackBuffer;
	A2DTextureBuffer          *     aTextureBuffer;
	A2DTextureBuffer          *     aBlurBuffer;

    // Accessors
    // { NONE }

    // Mutators
    // { NONE }

    // Additional
    // { NONE }

public:

    //////////////////////////////////////////////////////////
    // A2DABSTRACT IMPLEMENTATION
    //////////////////////////////////////////////////////////

    virtual HRESULT                 Initialize();
    virtual void                    Deinitialize();
    virtual LPCWSTR                 GetClass();
    virtual LPCWSTR                 ToString();
    virtual bool                    operator==(A2DAbstract * xAbstract);

};


#endif
