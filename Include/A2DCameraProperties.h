////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __A2DCAMERAPROPERTIES_H__
#define __A2DCAMERAPROPERTIES_H__

//+-----------------------------------------------------------------------------
//
//  Struct:
//      A2DCAMERAPROPERTIES
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

class A2DWindow;
class A2DImagePanel;

////////////////////////////////////////////////////////////////////////////////
// DEFINE
////////////////////////////////////////////////////////////////////////////////

#define A2DCAMERAPROPERTIES_LL(str1, str2)                    str1 str2

////////////////////////////////////////////////////////////////////////////////
// DECLARATION
////////////////////////////////////////////////////////////////////////////////

struct A2DCameraProperties : public A2DAbstract
{
public:
    // Constructor
    A2DCameraProperties() :                                   // default values for camera properties
        aPositionX(0.0f),
        aPositionY(0.0f),
        aPositionZ(0.0f),
        aRotationX(0.0f),
        aRotationY(0.0f),
        aRotationZ(0.0f),
        aLookAtX(0.0f),
        aLookAtY(0.0f),
        aLookAtZ(1.0f){}

    A2DCameraProperties(float xPositionX, float xPositionY, float xPositionZ, float xRotationX, float xRotationY, float xRotationZ):
        aPositionX(xPositionX),
        aPositionY(xPositionY),
        aPositionZ(xPositionZ),
        aRotationX(xRotationX),
        aRotationY(xRotationY),
        aRotationZ(xRotationZ),
        aLookAtX(0.0f),
        aLookAtY(0.0f),
        aLookAtZ(1.0f){}
    
    // Deconstructor
    // { NONE }

    // Variables
    float                           aPositionX,
                                    aPositionY,
                                    aPositionZ,
                                    aRotationX,
                                    aRotationY,
                                    aRotationZ,
                                    aLookAtX,
                                    aLookAtY,
                                    aLookAtZ;

    float                           aLookAtXDef = 0.0f;
    float                           aLookAtYDef = 0.0f;
    float                           aLookAtZDef = 1.0f;

    // Accessors
    // { NONE }

    // Mutators
    // { NONE }

    // Builders
    // { NONE }

    // Factory
    // { NONE }

    // Additional
    // { NONE }

    // Pure Virtual
    // { NONE }

    // Virtual
    // { NONE }

public:

    // Implementation
    // { A2DABSTRACT }
    virtual HRESULT                 Initialize();
    virtual void                    Deinitialize();
    virtual LPCWSTR                 GetClass();
    virtual LPCWSTR                 ToString();
    virtual bool                    operator==(A2DAbstract * xAbstract);

};

#endif
