////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __A2DPIPELINECOMPONENT_H__
#define __A2DPIPELINECOMPONENT_H__

//+-----------------------------------------------------------------------------
//
//  Class:
//      A2DPIPELINECOMPONENT
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

class A2DWindow;

////////////////////////////////////////////////////////////////////////////////
// DEFINE
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// DECLARATION
////////////////////////////////////////////////////////////////////////////////

class A2DPipelineable : public A2DAbstract
{

public:

	virtual HRESULT					CreateResources(void * xArgs[]) = 0;
	virtual void					Update(void * xArgs[]) = 0; // Dont worry about destroying anything...but all that into Destroy Resources
	virtual void					Render() = 0; // Render should be defined seperately but called inside Update
	virtual void					DestroyResources() = 0;

	virtual HRESULT                 Initialize() = 0;
	virtual void                    Deinitialize() = 0; // Set Backbuffer pointer to 0 during this step! 
	virtual LPCWSTR                 GetClass() = 0;
	virtual LPCWSTR                 ToString() = 0;
	virtual bool                    operator==(A2DAbstract * xAbstract) = 0;

};

#endif
