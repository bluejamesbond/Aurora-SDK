////////////////////////////////////////////////////////////////////////////////
// GUARDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __A2DGLCAMERA_H__
#define __A2DGLCAMERA_H__

//+-----------------------------------------------------------------------------
//
//  Class:
//      A2DGLCAMERA
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
class A2DGLCamera;
struct A2DCameraProperties;
struct A2DRenderData;
class A2DBackBuffer;
class A2DMatrixFactory;
class A2DModelFactory;
class A2DRootPane;

class A2DXWindow;

////////////////////////////////////////////////////////////////////////////////
// DEFINE
////////////////////////////////////////////////////////////////////////////////

#define HRESULT int 
#define S_OK 0
#define E_FAIL 1
#define FAILED(x) !x

////////////////////////////////////////////////////////////////////////////////
// DECLARATION
////////////////////////////////////////////////////////////////////////////////

class A2DGLCamera : public A2DAbstract //need an abstract camera class..or perhaps not
{

public:

    // Constructor
    A2DGLCamera();
    A2DGLCamera(A2DGLCameraProperties * xCameraProps);

    // Deconstructor
    ~A2DGLCamera();

private:

    // Variables
    A2DCameraProperties       *     aCameraProps;
    
    float                           aViewMatrix[16];
    
    struct VectorType 
    { 
        float x, y, z;
    };

public:

    // Accesors
    float                     *     GetViewMatrix();
    A2DCameraProperties       *     GetProperties();          // returns the camera properties by pointer

    //Mutators
    void                            SetViewMatrix(float* matrix);
    void                            SetPosition(float x, float y, float z);
    void                            SetRotation(float x, float y, float z);

private:

    // Builders
    void                            BuildViewMatrix(VectorType position, VectorType lookAt, VectorType up);
    void                            TransformCoord(VectorType& vector, float* matrix);
    void                            MatrixRotationYawPitchRoll(float* matrix, float yaw, float pitch, float roll);
    // Factory
    // { NONE }

public:
    // Additional
    void                            CreateResources();

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