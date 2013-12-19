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
#include "A2DCPWindowHandle.h"
#include "A2DCPResultHandle.h"
#include "A2DCPInstanceHandle.h"
#include "A2DCPString.h"

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

	/*********************************************************************/
	/*                      CROSS-PLATFORM START                         */
	/*********************************************************************/
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

	A2DCPWindowHandle               aParentHandle;
	A2DCPWindowHandle               aChildHandle;

	A2DCPString			            aName;
	// LPCWSTR or string

	A2DCPInstanceHandle       *     aHInstance;

	Color                           aBorderColor;

	A2DFrame                  *     aFrame;

	A2DWindow                 *     aRelativeWindow;

	A2DRect                         aRect;

public:

	// Accessors and mutators
	// These don't need mutators because we are giving direct access to the structs
	virtual A2DRect                   *     getBounds() = 0;

	// Accessing internal variables. Do not provide mutators for these.
	virtual A2DCPWindowHandle         *     getChildHandle() = 0;
	virtual A2DCPWindowHandle         *     getParentHandle() = 0;

	virtual A2DCPString               *     getName() = 0; // Fix this, should we use pointer or not?
	virtual void                            setName(A2DCPString * xName) = 0; // Fix this, should we use pointer or not?

	virtual A2DFrame                  *     getFrame() = 0; // GET
	virtual void                            setFrame(A2DFrame * xFrame) = 0; // SET

	virtual bool                            isUndecorated() = 0; // Get
	virtual void                            setUndecorated(bool xUndecoratedFlag) = 0; // SET

	virtual int                             getDefaultCloseOperation() = 0;
	virtual void                            setDefaultCloseOperation(int xCloseOperation) = 0;

	virtual A2DWindow                 *     getLocationRelativeTo() = 0;
	virtual void                            setLocationRelativeTo(A2DWindow * xWindow) = 0;

	virtual bool                            isVisible() = 0;
	virtual void                            setVisible(bool xVisibile) = 0;

	virtual bool                            isShadowed() = 0;
	virtual void                            setShadowed(bool xShadowFlag) = 0;

	virtual Color                           getBorderColor() = 0;
	virtual void                            setBorderColor(Color xBorderColor) = 0;

	virtual float                           getPadding() = 0;
	virtual void                            setPadding(float xPadding) = 0;

	virtual float                           getShadowPadding() = 0;
	virtual void                            setShadowPadding(float xShadowPadding) = 0;

	// Additional
	virtual void                            Update() = 0;
	virtual void                            Render() = 0;
	virtual void                            RenderComponent() = 0;
	virtual void                            RenderComponentClear() = 0;
	virtual void                            RenderComponentBorder() = 0;
	virtual A2DCPResultHandle               CreateResources() = 0;
	virtual A2DCPResultHandle               CreateComponentResources() = 0;

	// Implementation
	// { A2DABSTRACT }
	virtual A2DCPResultHandle               Initialize() = 0;
	virtual void							Deinitialize() = 0;
	virtual A2DCPString						GetClass() = 0;
	virtual A2DCPString					    ToString() = 0;
	virtual bool							operator==(A2DAbstract * xAbstract) = 0;

	/*********************************************************************/
	/*                      CROSS-PLATFORM END                           */
	/*********************************************************************/

	/*********************************************************************/
	/*                      WINDOWS-SPECIFIC START                       */
	/*********************************************************************/

	// Variables - WINDOW ONLY - INTERNAL USE ONLY

	REAL                            aCachedZero = 0;
	REAL                            aCachedPadding = 0;
	REAL                            aCachedShadowPadding = 0;

	REAL                            aCachedRealX = 0;
	REAL                            aCachedRealY = 0;
	REAL                            aCachedRealWidth = 0;
	REAL                            aCachedRealHeight = 0;

	REAL                            aCachedRelativeX = 0;
	REAL                            aCachedRelativeY = 0;
	REAL                            aCachedRelativeWidth = 0;
	REAL                            aCachedRelativeHeight = 0;

	int                             aStyle;
	SIZE                            aHDCSize;
	Graphics                  *     aGraphics;

	// Builders
	// { NONE }

	// Factory
	// { NONE }

	// Accessors
	// { NONE }

	// Mutators
	// { NONE }

	// Factory
	// { NONE }

	// Additional
	void                                                        preCache();

	// Pure Virtual
	// { NONE }

	// Virtual
	// { NONE }     

private:

	// Functions
	void                            RunMessageLoop();
	static LRESULT CALLBACK         WndProc(HWND xHwnd, UINT xMessage, WPARAM xWParam, LPARAM xLParam);
	static inline A2DWindow*        GetAppState(HWND xHwnd);

	HRESULT                         RegisterClass();
	HRESULT                         CreateHandle(HWND * xHandle);

	/*********************************************************************/
	/*                      WINDOWS-SPECIFIC END                         */
	/*********************************************************************/
};

#endif
