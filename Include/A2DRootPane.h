////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __A2DROOTPANE_H__
#define __A2DROOTPANE_H__

//+-----------------------------------------------------------------------------
//
//  Class:
//      A2DROOTPANE
//
//  Synopsis:
//      Differentiates which of the two possible arcs could match the given arc
//      parameters.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////


#include "A2DRenderData.h"
#include "A2DVertexData.h"
#include "A2DBackBuffer.h"
#include "A2DTexture.h"
#include "A2DPanel.h"

////////////////////////////////////////////////////////////////////////////////
// FORWARD DECLARATIONS
////////////////////////////////////////////////////////////////////////////////

class A2D;
class A2DAbstract;
class A2DRenderable;
class A2DCamera;
struct A2DCameraProperties;
class A2DBackBuffer;

class A2DWindow;
class A2DAbstractComponent;

////////////////////////////////////////////////////////////////////////////////
// DEFINE
////////////////////////////////////////////////////////////////////////////////

#define A2DROOTPANE_LL(str1, str2)                            str1 str2

////////////////////////////////////////////////////////////////////////////////
// DECLARATION
////////////////////////////////////////////////////////////////////////////////

class A2DRootPane : public A2DPanel
{
	
public:

	// Constructor
	// { NONE }

	// Deconstructor
	// { NONE }

private:

	// Variables
	bool							aLockDimensions = false;

	// Accessors
	// { NONE }

	// Mutators
	// { NONE }

	// Additional
	// { NONE }

	// Pure Virtual
	// { NONE }

	// Virtual
	// { NONE }

public:

	// Implementation
	// { A2DABSTRACTCOMPONENT }
	virtual void                    RenderComponent(A2DRenderData * xRenderData);
	virtual void                    RenderComponentBorder(A2DRenderData * xRenderData);
	virtual LRESULT                 WindowMsg(HWND * xHwnd, UINT * xMessage, WPARAM * xWParam, LPARAM * xLParam);
	virtual void					SetBounds(float xOptLeft, float xOptTop, float xOptWidth, float xOptHeight) final;

public:

	// Implementation
	// { A2DABSTRACT }
	virtual LPCWSTR                 GetClass();
	virtual LPCWSTR                 ToString();
	virtual bool                    operator==(A2DAbstract * xAbstract);

};

#endif
