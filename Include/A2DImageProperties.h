////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __A2DIMAGEPROPERTIES_H__
#define __A2DIMAGEPROPERTIES_H__

//+-----------------------------------------------------------------------------
//
//  Abstract Class:
//      A2DIMAGEPROPERTIES
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
#include "A2DFileInfo.h"
#include "A2DCommon.h"

////////////////////////////////////////////////////////////////////////////////
// FORWARD DECLARATIONS
////////////////////////////////////////////////////////////////////////////////

class A2D;
class A2DAbstract;
class A2DRenderable;
class A2DCamera;
struct A2DCameraProperties;
struct A2DRenderData;
class A2DGraphics;
class A2DBackBuffer;
class A2DMatrixFactory;
class A2DModelFactory;
class A2DRootPane;

class A2DWindow;

////////////////////////////////////////////////////////////////////////////////
// DEFINE
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// DECLARATION
////////////////////////////////////////////////////////////////////////////////


struct A2DImageProperties : public A2DAbstract
{
	A2DImageProperties(){};
	~A2DImageProperties(){};
	A2DImageProperties(A2DImageProperties * xImageProps);

	int								aOptRepeat    = A2D_OPT_BACKGROUND_REPEAT_REPEAT_X | A2D_OPT_BACKGROUND_REPEAT_REPEAT_Y;      // background-repeat (CSS)
	int								aOptSizeX     = A2D_OPT_BACKGROUND_SIZE_COVER;       // background-size-x  (CSS)
	int								aOptSizeY     = A2D_OPT_BACKGROUND_SIZE_COVER;       // background-size-x  (CSS)

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