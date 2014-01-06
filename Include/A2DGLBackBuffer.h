////////////////////////////////////////////////////////////////////////////////

#ifndef __A2DGLBACKBUFFER_H__
#define __A2DGLBACKBUFFER_H__

//+-----------------------------------------------------------------------------
//
//  Class:
//      A2DGLBackBuffer
//
//  Synopsis:
//      Custom LINUX/UNIX implementation of A2DAbstractBackBuffer to allow a 
//		Cross-Platform SDK Implementation
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "A2DBackBuffer.h"
#include "A2DExtLibs.h"

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
class A2DMatrixFactory;
class A2DModelFactory;
class A2DRootPane;
class A2DXWindow;
class A2DImagePanel;
class A2DBackBuffer;

////////////////////////////////////////////////////////////////////////////////
// DEFINE
////////////////////////////////////////////////////////////////////////////////

//////////////
// TYPEDEFS //
//////////////

////////////////////////////////////////////////////////////////////////////////
// Class name: A2DGLBackBuffer
////////////////////////////////////////////////////////////////////////////////

class A2DGLBackBuffer: public A2DBackBuffer
{

public:
	// Constructor
	A2DGLBackBuffer(A2DWindow * xWindow, A2DGXSettings * xGXSettings);

    // Deconstructor
    ~A2DGLBackBuffer();

    //GL Variables
    
    //Windows Variables
//

private:
	// Variables
	A2DGXSettings             *     aGXSettings
	A2DWindow				  *     aWindow;
    HDC                             m_deviceContext;
    HGLRC                           m_renderingContext;
    float                           m_worldMatrix[16];
    float                           m_projectionMatrix[16];
    char                            m_videoCardDescription[128];

public:
    // Accessors
    A2DCPDevice              *     GetDevice();
    void                           GetVideoCardInfo(char* xcardName);

    // Mutators
    virtual void                   SetZBuffer(bool val); //sets depth buffer since always enabled for us
    
    // Builders
    // { NONE }

    // Factory
    // { NONE }

public:
    // Additional
    virtual void                   SetActive();
    virtual void                   Swap();
    virtual void                   Clear();

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

private:
    
    bool                            A2DGLBackBuffer::LoadExtensionList();
};


#endif