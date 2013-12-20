////////////////////////////////////////////////////////////////////////////////

#ifndef __A2DLINBACKBUFFER_H__
#define __A2DLINBACKBUFFER_H__

//+-----------------------------------------------------------------------------
//
//  Class:
//      A2DLINBACKBUFFER
//
//  Synopsis:
//      Custom LINUX/UNIX implementation of A2DAbstractBackBuffer to allow a 
//		Cross-Platform SDK Implementation
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////
#include "OpenGlClass.h"
#include "InputClass.h"
#include "GraphicsClass.h"
#include "A2DAbstractBackBuffer.h"
#include "A2DCPResultHandle.h"
#include "A2DCPWindowHandle.h"
#include "A2DCPDevice.h"
#include "A2DCPInstanceHandle.h"
#include "A2DCPString.h"
#include "OpenGlClass.h"
#include "InputClass.h"
#include "GraphicsClass.h"

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
class A2DMatrixFactory;
class A2DModelFactory;
class A2DRootPane;
struct A2DWindowProperties;
class A2DWindow;
class A2DImagePanel;
class A2DAbstractBackBuffer;

////////////////////////////////////////////////////////////////////////////////
// DEFINE
////////////////////////////////////////////////////////////////////////////////
class A2DLinBackBuffer: public A2DAbstract, public A2DAbstractBackBuffer
{

public:
	// Constructor
	A2DLinBackBuffer(A2DWindow * xWindow, A2DWindowProperties * xWindowProps);

    // Deconstructor
    ~A2DLinBackBuffer();

    // Variables
    								aVertexBuffer;
    								aIndexBuffer;

    
    //Windows Variables
    IDXGISwapChain            *     aDXGISwapChain;
    A2DCPDevice               *     aDXDevice;

private:
	// Variables
	A2DWindowProperties       *     aWindowProps;
	A2DWindow				  *     aWindow;

public:
    // Accessors
    A2DCPDevice              *     GetDevice();

public:
    // Mutators
    void                            SetZBuffer(bool val);
    
    // Builders
    // { NONE }

    // Factory
    // { NONE }

public:
    // Additional
    void                            SetActive();
    void                            Swap();
    void                            Clear();

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