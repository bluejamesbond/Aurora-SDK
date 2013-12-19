////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __A2DBACKBUFFER_H__
#define __A2DBACKBUFFER_H__

//+-----------------------------------------------------------------------------
//
//  Class:
//      A2DBACKBUFFER
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
#include "A2DAbstract.h"
#include "A2DAbstractBackBuffer.h"

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
            
#define A2DBACKBUFFER_LL(str1, str2)                              str1 str2

////////////////////////////////////////////////////////////////////////////////
// DECLARATION
////////////////////////////////////////////////////////////////////////////////

class A2DBackBuffer : public A2DAbstract, public A2DAbstractBackBuffer
{

public:

    // Constructor
	A2DBackBuffer(A2DWindow * xWindow, A2DWindowProperties * xWindowProps);

    // Deconstructor
    ~A2DBackBuffer();

    // Variables
    IDXGISwapChain            *     aDXGISwapChain;
    ID3D10Device              *     aDXDevice;
    ID3D10RenderTargetView    *     aDXRenderTargetView;
    ID3D10Texture2D           *     aDXDepthStencilBuffer;
    ID3D10DepthStencilState   *     aDXDepthStencilState;
    ID3D10DepthStencilView    *     aDXDepthStencilView;
    ID3D10RasterizerState     *     aDXRasterState;
	ID3D10DepthStencilState   *     aDXDepthDisabledStencilState;
	char							aVideoCardDescription[128];
	int								aVideoCardMemory;

private:
	// Variables
	A2DWindowProperties       *     aWindowProps;
	A2DWindow				  *     aWindow;

public:
    // Accessors
    ID3D10Device              *     GetDevice();

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
