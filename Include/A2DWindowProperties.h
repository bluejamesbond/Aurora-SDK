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
	A2DWindowProperties(int xPadding, int xShadowPadding);
    
    // Deconstructor
    ~A2DWindowProperties();

private:

    // Variables
	int								aPadding;
	int								aShadowPadding;

	A2DRect					        aRealRect;
	A2DRect					        aRelativeRect;
	A2DDims					        aRealDims;
	A2DDims					        aRelativeDims;

    bool                            aWinActive;

    LPCWSTR                         aName;

	A2DWindow				  *		aWindow;

public:

    // Accessors
	A2DRect                   *     GetRealBounds();
	A2DRect                   *     GetRelativeBounds();
	A2DDims					  *     GetRealSize();
	A2DDims					  *     GetRelativeSize();
	float					        GetPadding();
	float					        GetShadowPadding();
	LPCWSTR					  *		GetName();
	void					  *		SetWindow(A2DWindow * xWindow);

    // Mutators
	void                            SetRealBounds(A2DRect * xRect);
	void                            SetRelativeBounds(A2DRect * xRect);

    // Builders
    // { NONE }

    // Factory
    // { NONE }

    // Additional
	void                            CenterBounds();

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