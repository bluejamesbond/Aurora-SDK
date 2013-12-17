////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __A2DPIPELINE_H__
#define __A2DPIPELINE_H__

//+-----------------------------------------------------------------------------
//
//  Class:
//      A2DPIPELINE
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
#include "A2DAbstractPipelineComponent.h"

////////////////////////////////////////////////////////////////////////////////
// FORWARD DECLARATIONS
////////////////////////////////////////////////////////////////////////////////

class A2D;
class A2DAbstract;
class A2DAbstractPipelineComponent;

////////////////////////////////////////////////////////////////////////////////
// DEFINE
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// DECLARATION
////////////////////////////////////////////////////////////////////////////////

class A2DPipeline : public A2DAbstract
{

public:

	// Constructor
	A2DPipeline();
	A2DPipeline(A2DPipeline * xRenderData);

	// Deconstructor
	// { NONE }

	// Variables
	A2DAbstractPipelineComponent  * aPipelineComps[8];

	int							    aLength = 0;
	int								aLifeCycle = 0;

	static int						aGlobalLifeCycle;

	// Accessor
	static void						nextLifeCycle();

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
