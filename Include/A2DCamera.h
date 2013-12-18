////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __A2DCAMERA_H__
#define __A2DCAMERA_H__

//+-----------------------------------------------------------------------------
//
//  Class:
//      A2DCAMERA
//
//  Synopsis:
//      Differentiates which of the two possible arcs could match the given arc
//      parameters.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "A2DCameraProperties.h"
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
struct A2DWindowProperties;
class A2DWindow;

////////////////////////////////////////////////////////////////////////////////
// DEFINE
////////////////////////////////////////////////////////////////////////////////

#define A2DCAMERA_LL(str1, str2)                              str1 str2

////////////////////////////////////////////////////////////////////////////////
// DECLARATION
////////////////////////////////////////////////////////////////////////////////

class A2DCamera : public A2DAbstract
{

public:

    // Constructor
    A2DCamera();
    A2DCamera(A2DCameraProperties * xCameraProps);

    // Deconstructor
    ~A2DCamera();

private:

    // Variables
    A2DCameraProperties       *     aCameraProps;
    D3DXMATRIX                *     aViewMatrix;

public:

    // Accesors
    D3DXMATRIX                *     GetViewMatrix();
    A2DCameraProperties       *     GetProperties();          // returns the camera properties by pointer

private:

    // Builders
    // { NONE }

    // Factory
    // { NONE }

public:
    // Additional
	void						   CreateResources();

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
