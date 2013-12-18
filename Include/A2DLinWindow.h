////////////////////////////////////////////////////////////////////////////////
// GUARDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __A2DLINWINDOW_H__
#define __A2DLINWINDOW_H__

//+-----------------------------------------------------------------------------
//
//  Class:
//      A2DLINWINDOW
//
//  Synopsis:
//      Linux Implementation of A2DWindow
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "A2DFrame.h"
#include "A2DAbstract.h"
#include "A2DWindowProperties.h"
#include "A2DAbstractWindow.h"

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
class A2DLinWindow;
class A2DAbstractWindow;
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

using namespace Gdiplus;  // WINDOWS specific

class A2DWindow : public A2DAbstract, public A2DAbstractWindow
{

    /*********************************************************************/
    /*                      CROSS-PLATFORM START                         */
    /*********************************************************************/
public:

    // Constructor
    A2DLinWindow(A2DCPInstanceHandle * xHInstance); // <-- WILL ALWAYS CENTER THE WINDOW FOR NOW

    // Deconstructor
    ~A2DLinWindow();
  
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

    A2DCPString                     aName;

    A2DCPInstanceHandle       *     aHInstance;

    Color                           aBorderColor;

    A2DFrame                  *     aFrame;

    A2DWindow                 *     aRelativeWindow;

    A2DRect                         aRect;

public:

    // Accessors and mutators
    // These don't need mutators because we are giving direct access to the structs
    A2DRect                   *     getBounds();
        
    // Accessing internal variables. Do not provide mutators for these.
    A2DCPWindowHandle                      *     getChildHandle();
    A2DCPWindowHandle                    *     getParentHandle();

    A2DCPString                  *     getName(); // Fix this, should we use pointer or not?
    void                            setName(A2DCPString * xName); // Fix this, should we use pointer or not?
    
    A2DFrame                  *     getFrame(); // GET
    void                            setFrame(A2DFrame * xFrame); // SET

    bool                            isUndecorated(); // Get
    void                            setUndecorated(bool xUndecoratedFlag); // SET

    int                             getDefaultCloseOperation();
    void                            setDefaultCloseOperation(int xCloseOperation);

    A2DWindow                 *     getLocationRelativeTo();
    void                            setLocationRelativeTo(A2DWindow * xWindow);
    
    bool                            isVisible();
    void                            setVisible(bool xVisibile);

    bool                            isShadowed();
    void                            setShadowed(bool xShadowFlag);

    Color                           getBorderColor();
    void                            setBorderColor(Color xBorderColor);

    float                           getPadding();
    void                            setPadding(float xPadding);
    
    float                           getShadowPadding();
    void                            setShadowPadding(float xShadowPadding);
    
    // Additional
    void                            Update();
    void                            Render();
    void                            RenderComponent();
    void                            RenderComponentClear();
    void                            RenderComponentBorder();
    A2DCPResultHandle               CreateResources();
    A2DCPResultHandle               CreateComponentResources();
    
    // Implementation
    // { A2DABSTRACT }
    virtual A2DCPResultHandle       Initialize();
    virtual void                    Deinitialize();
    virtual A2DCPString             GetClass();
    virtual A2DCPString             ToString();
    virtual bool                    operator==(A2DAbstract * xAbstract);

    /*********************************************************************/
    /*                      CROSS-PLATFORM END                           */
    /*********************************************************************/

    /*********************************************************************/
    /*                      LINUX-SPECIFIC START                       */
    /*********************************************************************/

    // Variables - WINDOW ONLY - INTERNAL USE ONLY

    float                           aCachedZero = 0;
    float                           aCachedPadding = 0;
    float                           aCachedShadowPadding = 0;

    float                           aCachedRealX = 0;
    float                           aCachedRealY = 0;
    float                           aCachedRealWidth = 0;
    float                           aCachedRealHeight = 0;

    float                           aCachedRelativeX = 0;
    float                           aCachedRelativeY = 0;
    float                           aCachedRelativeWidth = 0;
    float                           aCachedRelativeHeight = 0;

    GLint                             aStyle;
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
    void                          RunMessageLoop();
    static bool CALLBACK          WndProc(HWND xHwnd, UINT xMessage, WPARAM xWParam, LPARAM xLParam);
	static bool CALLBACK 		  WndProc();//necssary params);
    static inline A2DWindow*      GetAppState(HWND xHwnd);
	static inline A2DWindow*	  GetAppState();//overload w/ necessary params

    bool                          RegisterClass();
    bool                          CreateHandle(HWND * xHandle);
	bool						  CreateHandle();//overload w/ necssary params

    /*********************************************************************/
    /*                      LNUX-SPECIFIC END                         */
    /*********************************************************************/
};

#endif
