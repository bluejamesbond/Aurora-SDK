////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __A2DABSTRACTPIPELINECOMPONENT_H__
#define __A2DABSTRACTPIPELINECOMPONENT_H__

//+-----------------------------------------------------------------------------
//
//  Class:
//      A2DABSTRACTPIPELINECOMPONENT
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
struct A2DWindowProperties;
class A2DWindow;

////////////////////////////////////////////////////////////////////////////////
// DEFINE
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// DECLARATION
////////////////////////////////////////////////////////////////////////////////

class A2DAbstractPipelineComponent : public A2DAbstract
{

public:

	// Constructor
	A2DAbstractPipelineComponent(A2DBackBuffer * xBackBuffer);

	// Deconstructor
	~A2DAbstractPipelineComponent();

protected:
	// Variables
	A2DBackBuffer			*		aBackBuffer;

public:

	// Pure Virtual
	virtual HRESULT					CreateResources(void * xArgs[]) = 0;
	virtual void					Update(void * xArgs[]) = 0; // Dont worry about destroying anything...but all that into Destroy Resources
	virtual void					Render() = 0; // Render should be defined seperately but called inside Update
	virtual void					DestroyResources() = 0;

	// Virtual
	// { NONE }

public:

	// Implementation
	// { A2DABSTRACT }
	virtual HRESULT                 Initialize();
	virtual void                    Deinitialize(); // Set Backbuffer pointer to 0 during this step! 
	virtual LPCWSTR                 GetClass();
	virtual LPCWSTR                 ToString();
	virtual bool                    operator==(A2DAbstract * xAbstract);

};

#endif
