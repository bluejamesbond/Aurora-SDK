///////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __A2DPANEL_H__
#define __A2DPANEL_H__

//+-----------------------------------------------------------------------------
//
//  Struct:
//      A2DPANEL
//
//  Synopsis:
//      Differentiates which of the two possible arcs could match the given arc
//      parameters.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "A2DComponent.h"
#include "A2DImageProperties.h"

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

#define A2DCOMPONENT_LL(str1, str2)                           str1 str2

////////////////////////////////////////////////////////////////////////////////
// DECLARATION
////////////////////////////////////////////////////////////////////////////////

class A2DPanel : public A2DComponent
{
public:

	// Constructor
	A2DPanel(){}

	// Deconstructor
	~A2DPanel(){}

	// Variables
	float translationX = 0;
	float translationXG1 = 10;
	float translationYG1 = 10;
	float translationY = 0;
	float translationYDirection = 1;
	float translationXDirection = 1;
	float translationXDirectionG1 = 1;
	float translationYDirectionG1 = 1;

protected:

	// Variables
	A2DImageProperties	*			aOptBackgroundProps;					// background-size/background-repeat
	LPCWSTR			*				aOptBackgroundSrc = NULL;				// background-image  (CSS)
	int								aOptBackgroundColor = 0xFF000000;       // background-color  (CSS)
	int								aOptBackgroundPosX = 0;					// background-position-x  (CSS)
	int								aOptBackgroundPosY = 0;					// background-position-x  (CSS)

public:

	// Accessors
	// { NONE }

	// Mutators
	// { NONE }

	// Builders
	// { NONE }

	// Factory
	// { NONE }

public:

	// Additional
	virtual void                    RenderComponent(A2DRenderData * xRenderData);

	// Pure Virtual
	// { NONE }

	// Virtual
	// { NONE }

public:

	// Implementation
	// { A2DABSTRACT }
	virtual LPCWSTR                 GetClass();
	virtual LPCWSTR                 ToString();
};

#endif
