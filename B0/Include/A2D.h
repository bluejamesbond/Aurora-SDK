////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __A2D_H__
#define __A2D_H__

//+-----------------------------------------------------------------------------
//
//  Class:
//      A2D
//
//  Synopsis:
//      Differentiates which of the two possible arcs could match the given arc
//      parameters.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "A2DGraphics.h"
#include "A2DAbstract.h"
#include "A2DRenderable.h"
#include "A2DWindowProperties.h"
#include "A2DAbstractComponent.h"
#include "A2DComponent.h"
#include "A2DPanel.h"
#include "A2DCamera.h"
#include "A2DCameraProperties.h"
#include "A2DRenderData.h"
#include "A2DBackBuffer.h"
#include "A2DMatrixFactory.h"
#include "A2DRootPane.h"
#include "A2DWindow.h"

////////////////////////////////////////////////////////////////////////////////
// FORWARD DECLARATIONS
////////////////////////////////////////////////////////////////////////////////

class	A2D;
class	A2DAbstract;
class	A2DRenderable;
class	A2DAbstractComponent;
class	A2DCamera;
struct	A2DCameraProperties;
struct	A2DRenderData;
class	A2DMatrixFactory;
class	A2DBackBuffer;
struct	A2DBufferData;
class	A2DMatrixFactory;
class	A2DRootPane;
struct	A2DWindowProperties;
class	A2DWindow;
class	A2DTextureBuffer;

////////////////////////////////////////////////////////////////////////////////
// DEFINE
////////////////////////////////////////////////////////////////////////////////

#define A2D_LL(str1, str2)                                    str1 str2

////////////////////////////////////////////////////////////////////////////////
// DECLARATION
////////////////////////////////////////////////////////////////////////////////

class A2D : public A2DAbstract
{

public:
    
    // Constructor
	A2D(A2DWindow * xWindow, A2DWindowProperties * xWindowProp);

    // Deconstructor
    ~A2D();

private:

    // Variables
    A2DRootPane               *     aRootPane;
	A2DBackBuffer             *     aBackBuffer;
	A2DTextureBuffer          *     aTextureBuffer;
	A2DTextureBuffer          *     aBlurBuffer;
	A2DWindow                 *     aWindow;
    A2DCamera                 *     aCamera;
    A2DRenderData             *     aRenderData;
    A2DWindowProperties       *     aWindowProps;

    // Accessors
    // { NONE }

    // Mutators
    // { NONE }

public:

    // Builders
    // { NONE }

    // Factory
    // { NONE }

public:
	// Additional
	LRESULT							PumpWindowMsg(HWND * xHwnd, UINT * xMessage, WPARAM * xWParam, LPARAM * xLParam);

public:

    // Accessors
    A2DRootPane               *     GetRootPane();
    A2DCamera                 *     GetCamera();
    A2DRenderData             *     GetRenderData();

public:

    // Additional
	HRESULT                         CreateResources();
	void                            Update();

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
