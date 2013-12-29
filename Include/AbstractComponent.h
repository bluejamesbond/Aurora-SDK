////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __ABSTRACTCOMPONENT_H__
#define __ABSTRACTCOMPONENT_H__

//+-----------------------------------------------------------------------------
//
//  Abstract Class:
//      ABSTRACTCOMPONENT
//
//  Synopsis:
//      Differentiates which of the two possible arcs could match the given arc
//      parameters.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "Renderable.h"
#include "Rect.h"

////////////////////////////////////////////////////////////////////////////////
// FORWARD DECLARATIONS
////////////////////////////////////////////////////////////////////////////////

class ;
class Abstract;
class Renderable;
class Camera;
struct CameraProperties;
struct RenderData;
class Graphics;
class BackBuffer;
class MatrixFactory;
class ModelFactory;
class RootPane;

class Window;

////////////////////////////////////////////////////////////////////////////////
// DEFINE
////////////////////////////////////////////////////////////////////////////////

#define ABSTRACTCOMPONENT_LL(str1, str2)                   str1 str2

////////////////////////////////////////////////////////////////////////////////
// DECLARATION
////////////////////////////////////////////////////////////////////////////////


class AbstractComponent : public Renderable
{
public:

	// Constructor
	AbstractComponent();

	// Deconstructor
	~AbstractComponent();

protected:

	// Variables
	Graphics				  *     aGraphics;
	AbstractComponent      **    aChildrenComps;
	AbstractComponent	  *	    aParentComp;
	int                             aChildrenCompsLength = 0;
	int                             aChildrenCompsIndex = 0;

	Rect							aOptRegion;
	Rect							aOptBackgroundRegion;

	Rect							aCalculatedRegion;

public:
	// Accessors
	AbstractComponent      *		GetParent();
	Graphics				  *		GetGraphics();

public:

	// Accessors
	Rect					  *		GetBounds();

	// Mutators
	// { NONE }


private:

	bool							aValidatedContents;

protected:

	void							validated();

public:

	void							invalidate();
	void							revalidate();

private:

	// Builders
	AbstractComponent      **    CreateAmmoritizedComponentArray();
	Graphics               *		CreateGraphics();

	// Factory
	// { NONE }

public:

	// Additional
	void                            Add(AbstractComponent * xAbstractComponent);

protected:

	// Additional
	void							SetParent(AbstractComponent * xComponent);

private:

	// Additional
	void                            RemoveComponent(AbstractComponent * xAbstractComponent);
	void                            AddComponent(AbstractComponent * xAbstractComponent);

public:

	// Pure Virtual
	virtual void                    RenderComponent(RenderData * xRenderData) = 0;
	virtual void                    RenderComponentBorder(RenderData * xRenderData) = 0;

public:

	// Virtual
	virtual void					SetBounds(Rect * xRect);
	virtual void					SetBounds(float xX, float xY, float xWidth, float xHeight);

protected:

	// Virtual
	virtual LRESULT                 WindowMsg(HWND * xHwnd, UINT * xMessage, WPARAM * xWParam, LPARAM * xLParam);
	virtual void                    RenderChildren(RenderData * xRenderData);
	virtual void                    DeinitializeChildren() final;
	virtual void					validate();

public:

	virtual void                    Render(RenderData * xRenderData);
	
public:

	// Virtual
	// { RENDERABLE }
	virtual void                    Update(RenderData * xRenderData) final;

public:

	// Implementation
	// { ABSTRACT }
	virtual HRESULT                 Initialize();
	virtual void                    Deinitialize();
	virtual LPCWSTR                 GetClass();
	virtual LPCWSTR                 ToString();
	virtual bool                    operator==(Abstract * xAbstract);

};

#endif
