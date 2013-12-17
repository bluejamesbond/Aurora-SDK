////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __A2DWINDOWPROPERTIES_H__
#define __A2DWINDOWPROPERTIES_H__

//+-----------------------------------------------------------------------------
//
//  Struct:
//      A2DWINDOWPROPERTIES
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
#include "A2DAbstract.h"
#include "A2DWindow.h"

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

////////////////////////////////////////////////////////////////////////////////
// DEFINE
////////////////////////////////////////////////////////////////////////////////

#define A2DWINDOWPROPERTIES_LL(str1, str2)                         str1 str2

////////////////////////////////////////////////////////////////////////////////
// DECLARATION
////////////////////////////////////////////////////////////////////////////////

struct A2DWindowProperties : public A2DAbstract
{

public:
    
    // Constructor
	A2DWindowProperties();
	A2DWindowProperties(HINSTANCE * xHInstance);
	A2DWindowProperties(A2DWindowProperties * aWindowProps);
    A2DWindowProperties(HINSTANCE * xHInstance, A2DWindow * xFrontWin, A2DWindow * xBackWin);
    
    // Deconstructor
    ~A2DWindowProperties();

    // Variables
	float                             aRealWidth;
	float                             aRealHeight;
	float                             aRealLeft;
	float                             aRealRight;
	float                             aRealTop;
	float                             aRealBottom;
	float                             aPadding;
	float                             aShadowPadding;
    const float                           aScreenNear = 0.1f;
	const float                           aScreenDepth = 1000.0f;
    bool                            aWinActive;
    bool                            aVsync;
    bool                            aFullScreen;
    A2DWindow                 *     aWindow;                  
    LPCWSTR                         aWindowTitle;             // The title bar text
    LPCWSTR                         aWindowClass;             // the main window class name
	LPCWSTR							aWindowTitleP;
	LPCWSTR							aWindowTitleC;
	LPCWSTR							aWindowClassP;                   // the main window class name
	LPCWSTR							aWindowClassC;
    HINSTANCE                 *     aHInstance;

    // Accessors
	float                             GetRelativeLeft();
	float                             GetRelativeRight();
	float                             GetRelativeTop();
	float                             GetRelativeBottom();
	float                             GetRelativeWidth();
	float                             GetRelativeHeight();

    // Mutators
	void                            SetRealPos(float xRealLeft, float xRealTop, float xRealWidth, float xRealHeight);

    // Builders
    // { NONE }

    // Factory
    // { NONE }

    // Additional
    void                            Center();

    // Pure Virtual
    // { NONE }

    // Virtual
    // { NONE }

    // Implementations
    // { NONE}

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