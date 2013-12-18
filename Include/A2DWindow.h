////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////


#ifndef __A2DWINDOW_H__
#define __A2DWINDOW_H__

//+-----------------------------------------------------------------------------
//
//  Class:
//      A2DWINDOW
//
//  Synopsis:
//      Differentiates which of the two possible arcs could match the given arc
//      parameters.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "A2DFrame.h"
#include "A2DAbstract.h"
#include "A2DWindowProperties.h"

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

////////////////////////////////////////////////////////////////////////////////
// DEFINE
////////////////////////////////////////////////////////////////////////////////
        
#define RES_BSW_DIR                                         L"libs\\Aurora SDK\\Lib\\Assets\\Images\\"
#define IDB_BSW_BOTTOM_LEFT_SHADOW_PNG                      RES_BSW_DIR L"muzzler windows-sync bottomLeftShadow [a] 1.png"
#define IDB_BSW_BOTTOM_RIGHT_SHADOW_PNG                     RES_BSW_DIR L"muzzler windows-sync bottomRightShadow [a] 1.png"
#define IDB_BSW_BOTTOM_SHADOW_PNG                           RES_BSW_DIR L"muzzler windows-sync bottomShadow [a] 1.png"
#define IDB_BSW_TOP_LEFT_SHADOW_PNG                         RES_BSW_DIR L"muzzler windows-sync topLeftShadow [a] 1.png"
#define IDB_BSW_TOP_RIGHT_SHADOW_PNG                        RES_BSW_DIR L"muzzler windows-sync topRightShadow [a] 1.png"
#define IDB_BSW_TOP_SHADOW_PNG                              RES_BSW_DIR L"muzzler windows-sync topShadow [a] 1.png"
#define IDB_BSW_LEFT_SHADOW_PNG                             RES_BSW_DIR L"muzzler windows-sync leftShadow [a] 1.png"
#define IDB_BSW_RIGHT_SHADOW_PNG                            RES_BSW_DIR L"muzzler windows-sync rightShadow [a] 1.png"
#define IDB_BSW_BACKGROUND_PNG                              RES_BSW_DIR L"muzzler windows-sync background [c] 1.png"
#define IDP_BSW_ACTIVE_BORDER_COLOR                         0x00929292
#define DEF_PAD_VALUE                                       25
#define DEF_SPAD_VALUE                                      75

////////////////////////////////////////////////////////////////////////////////
// DECLARATION
////////////////////////////////////////////////////////////////////////////////

using namespace Gdiplus;

class A2DWindow : public A2DAbstract
{

public:

    // Constructor
	A2DWindow(HINSTANCE * xHInstance); // <-- WILL ALWAYS CENTER THE WINDOW FOR NOW

    // Deconstructor
    ~A2DWindow();
  
private:

    // Variables
	HINSTANCE				  *		aHInstance;
	A2DFrame                  *     aFrame;

    HWND                            aParentHwnd;
    HWND                            aChildHwnd;
	
	// Variables
	int								aPadding;
	int								aShadowPadding;

	A2DRect					        aRealRect;
	A2DRect					        aRelativeRect;
	A2DDims					        aRealDims;
	A2DDims					        aRelativeDims;
	LPCWSTR                         aName;

public:

	// Accessors and mutators

	// These don't need mutators because we are giving direct access to the structs
	A2DRect                   *     getRealBounds();
	A2DRect                   *     getRelativeBounds();
	A2DDims					  *     getRealSize();
	A2DDims					  *     getRelativeSize();
		
	// Accessing internal variables. Do not provide mutators for these.
	HWND					  *		getChildHandle();
	HWND					  *		getParentHandle();

	LPCWSTR					  *		getName(); // Fix this, should we use pointer or not?
	void					  		setName(LPCWSTR * xName); // Fix this, should we use pointer or not?
	
	A2DFrame				  *     getFrame(); // GET
	void						    setFrame(A2DFrame * xFrame); // SET

	bool						    isUndecorated(); // Get
	void                            setUndecorated(bool xUndecoratedFlag); // SET

	int								getDefaultCloseOperation();
	void							setDefaultCloseOperation(int xCloseOperation);

	A2DWindow				  *		getLocationRelativeTo();
	void							setLocationRelativeTo(A2DWindow * xWindow);
	
	boolean							isVisible();
	void                            setVisible(bool xVisibile);

	boolean							isShadowed();
	void                            setShadowed(bool xShadowFlag);

	Color		                    getBorderColor();
	void                            setBorderColor(Color xColor);

	float							getPadding();
	void							setPadding(float xPadding);
	
	float							getShadowPadding();
	void							setShadowPadding(float xShadowPadding);

	// Builders
	// { NONE }

	// Factory
	// { NONE }

	// Additional

public:

    // Accessors
	HWND					  *		GetChildHwnd();

    // Mutators
    // Builders
    // { NONE }

    // Factory
    // { NONE }

    // Additional
	void							CacheVariables();

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

private:
    
    // Variables
    int                             aOptionShadow = 1;
	int                             aOptionBorder = 1;
	bool							aOptionVisible;
    int                             aOptionDecorated = 0;
    int                             CurrentStyleProc;
    Graphics                  *     aGraphics;
    SIZE                            aWindowSize;

    // Functions
    void                            RunMessageLoop();
    ATOM                            RegisterClass(HWND xHwnd);
    static LRESULT CALLBACK         WndProc(HWND xHwnd, UINT xMessage, WPARAM xWParam, LPARAM xLParam);
    static inline A2DWindow*        GetAppState(HWND xHwnd);

    HRESULT                         CreateHandle(HWND& xHandler);
	HRESULT                         CreateComponentResources();
	void							Update();
	void                            Render();
    void                            RenderComponent();
    void                            RenderComponentClear();
    void                            RenderComponentShadow();
    void                            RenderComponentBorder();
};

#endif
