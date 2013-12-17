////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __A2DMATRIXFACTORY_H__
#define __A2DMATRIXFACTORY_H__

//+-----------------------------------------------------------------------------
//
//  Class:
//      A2DMATRIXFACTORY
//
//  Synopsis:
//      Differentiates which of the two possible arcs could match the given arc
//      parameters.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "A2DWindowProperties.h"

////////////////////////////////////////////////////////////////////////////////
// FORWARD DECLARATIONS
////////////////////////////////////////////////////////////////////////////////

class A2D;
class A2DAbstract;
class A2DRenderable;
class A2DAbstractComponent;
class A2DCamera;
struct A2DCameraProperties;
struct A2DRenderData;
class A2DBackBuffer;
class A2DMatrixFactory;
class A2DModelFactory;
class A2DRootPane;
struct A2DWindowProperties;
class A2DWindow;
class A2DImagePanel;

////////////////////////////////////////////////////////////////////////////////The 
// DEFINE
////////////////////////////////////////////////////////////////////////////////

#define A2DMATRIXFACTORY_LL(str1, str2)                       str1 str2

////////////////////////////////////////////////////////////////////////////////
// DECLARATION
////////////////////////////////////////////////////////////////////////////////

class A2DMatrixFactory
{

public:

    // Constructor
    // { NONE }
    
    // Deconstructor
    // { NONE }

    // Variables
    // { NONE }

    // Accessors
    // { NONE }

    // Mutators
    // { NONE }

    // Builders
    // { NONE }

    // Factory
    static D3DXMATRIX         *     createDefaultWorldMatrix();
    static D3DXMATRIX         *     createDefaultProjectionMatrix(A2DWindowProperties * xWindowProps);
    static D3DXMATRIX         *     createDefaultOrthogonalMatrix(A2DWindowProperties * xWindowProps);
    
    // Additional
    // { NONE }

    // Pure Virtual
    // { NONE }

    // Virtual
    // { NONE }

    // Implementations
    // { NONE}

};

#endif
