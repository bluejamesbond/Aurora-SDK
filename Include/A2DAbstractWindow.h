////////////////////////////////////////////////////////////////////////////////
// GUARDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __A2DABSTRACTWINDOW_H__
#define __A2DABSTRACTWINDOW_H__

//+-----------------------------------------------------------------------------
//
//  Abstract Class:
//      A2DABSTRACTWINDOW
//
//  Synopsis:
//      Abstract Class to allow cross-patform implementation of A2DWindow. 
//		Currently compatible with Windows and Linux.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "A2DFrame.h"
#include "A2DAbstract.h"
#include "A2DWindowProperties.h"
//WE WILL UTILIZE HE CP TYPES LATER, FOR NOW IT'S ALL MS WINDOWS
/*#include "A2DCPWindowHandle.h"
#include "A2DCPResultHandle.h"
#include "A2DCPInstanceHandle.h"
#include "A2DCPString.h"
*/

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
class A2DAbstractWindow;

////////////////////////////////////////////////////////////////////////////////
// DEFINE
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// DECLARATION
////////////////////////////////////////////////////////////////////////////////

class A2DAbstractWindow : public A2DAbstract
{

public:

	// Constructor
	A2DAbstractWindow(A2DCPInstanceHandle * xHInstance); // <-- WILL ALWAYS CENTER THE WINDOW FOR NOW
		//A2DCPInstanceHandle will be defined later as custom type for HINSTANCE + linux type
	// Deconstructor
	~A2DAbstractWindow();

private:

	// Variables - NOTE: No need to use the acronym aOpt since variables are PRIVATE!
	int                             aDefaultCloseOperation;

	bool                            aVisible;
	bool                            aShadowed;
	bool                            aUndecorated;

	float                           aPadding;
	float                           aShadowPadding;

	HWND			                aParentHandle;
	HWND			                aChildHandle;

	LPCWSTR				            aName;
	// LPCWSTR or string

	xHInstance                *     aHInstance;

	Color                           aBorderColor;

	A2DFrame                  *     aFrame;

	A2DWindow                 *     aRelativeWindow;

	A2DRect                         aRect;

public:

	// Accessors and mutators
	// These don't need mutators because we are giving direct access to the structs
	virtual A2DRect                   *     getBounds();

	// Accessing internal variables. Do not provide mutators for these.
	virtual HWND			          *     getChildHandle();
	virtual HWND			          *     getParentHandle();

	virtual LPCWSTR	                  *     getName(); // Fix this, should we use pointer or not?
	virtual void                            setName(A2DCPString * xName); // Fix this, should we use pointer or not?

	virtual A2DFrame                  *     getFrame(); // GET
	virtual void                            setFrame(A2DFrame * xFrame); // SET

	virtual bool                            isUndecorated(); // Get
	virtual void                            setUndecorated(bool xUndecoratedFlag); // SET

	virtual int                             getDefaultCloseOperation();
	virtual void                            setDefaultCloseOperation(int xCloseOperation);

	virtual A2DWindow                 *     getLocationRelativeTo() = 0;
	virtual void                            setLocationRelativeTo(A2DWindow * xWindow);

	virtual bool                            isVisible();
	virtual void                            setVisible(bool xVisibile);

	virtual bool                            isShadowed();
	virtual void                            setShadowed(bool xShadowFlag);

	virtual Color                           getBorderColor();
	virtual void                            setBorderColor(Color xBorderColor);

	// Additional
	virtual void                            Update() = 0;
	virtual void                            Render() = 0;
	virtual void                            RenderComponent() = 0;
	virtual void                            RenderComponentClear() = 0;
	virtual void                            RenderComponentBorder() = 0;
	virtual HRESULT                         CreateResources() = 0;
	virtual HRESULT			                CreateComponentResources() = 0;

	// Implementation
	// { A2DABSTRACT }
	virtual HRESULT			                Initialize() = 0;
	virtual void							Deinitialize() = 0;
	virtual LPCWSTR  						GetClass() = 0;
	virtual LPCWSTR						    ToString() = 0;
	virtual bool							operator==(A2DAbstract * xAbstract) = 0;

};

#endif
