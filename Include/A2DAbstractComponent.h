////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __A2DABSTRACTCOMPONENT_H__
#define __A2DABSTRACTCOMPONENT_H__

//+-----------------------------------------------------------------------------
//
//  Abstract Class:
//      A2DABSTRACTCOMPONENT
//
//  Synopsis:
//      Differentiates which of the two possible arcs could match the given arc
//      parameters.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "A2DRenderable.h"
#include "A2DRect.h"

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

#define A2DABSTRACTCOMPONENT_LL(str1, str2)                   str1 str2

////////////////////////////////////////////////////////////////////////////////
// DECLARATION
////////////////////////////////////////////////////////////////////////////////


class A2DAbstractComponent : public A2DRenderable
{
public:

	// Constructor
	A2DAbstractComponent();

	// Deconstructor
	~A2DAbstractComponent();

protected:

	// Variables
	A2DGraphics				  *     aGraphics;
	A2DAbstractComponent      **    aChildrenComps;
	A2DAbstractComponent	  *	    aParentComp;
	int                             aChildrenCompsLength = 0;
	int                             aChildrenCompsIndex = 0;

	A2DRect							aOptRegion;

public:
	// Accessors
	A2DAbstractComponent      *		GetParent();
	A2DGraphics				  *		GetGraphics();

public:

	// Accessors
	virtual A2DRect			  *		GetBounds();

	// Mutators
	// { NONE }

private:

	// Builders
	A2DAbstractComponent      **    CreateAmmoritizedComponentArray();
	A2DGraphics               *		CreateGraphics();

	// Factory
	// { NONE }

public:

	// Additional
	void                            Add(A2DAbstractComponent * xAbstractComponent);

protected:

	// Additional
	void							SetParent(A2DAbstractComponent * xComponent);

private:

	// Additional
	void                            RemoveComponent(A2DAbstractComponent * xAbstractComponent);
	void                            AddComponent(A2DAbstractComponent * xAbstractComponent);

public:

	// Pure Virtual
	virtual void                    RenderComponent(A2DRenderData * xRenderData) = 0;
	virtual void                    RenderComponentBorder(A2DRenderData * xRenderData) = 0;

public:

	// Virtual
	virtual void					SetBounds(A2DRect * xRect);
	virtual void					SetBounds(int xX, int xY, int xWidth, int xHeight);

protected:

	// Virtual
	virtual LRESULT                 WindowMsg(HWND * xHwnd, UINT * xMessage, WPARAM * xWParam, LPARAM * xLParam);
	virtual void                    RenderChildren(A2DRenderData * xRenderData);
	virtual HRESULT                 CreateChildrenResources(A2DRenderData * xRenderData) final;
//  virtual HRESULT                 InitializeChildren() final;
	virtual void                    DeinitializeChildren() final;
	virtual void					DestroyChildrenResources() final;

public:

	// Virtual
	virtual HRESULT                 CreateComponentResources(A2DRenderData * xRenderData) final;
	virtual void                    DestroyComponentResources() final;
	virtual void                    Render(A2DRenderData * xRenderData);


public:

	// Virtual
	// { A2DRENDERABLE }
	virtual void                    Update() final;
	virtual HRESULT                 CreateResources(A2DRenderData * xRenderData) final;
	virtual void                    DestroyResources() final;

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
