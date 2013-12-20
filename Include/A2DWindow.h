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
#include "A2DRect.h"
#include "A2DAbstractWindow.h"
#include "A2DCPString.h"
#include "A2DCPWindowHandle.h"
#include "A2DCPInstanceHandle.h"
#include "A2DCPResultHandle.h"

////////////////////////////////////////////////////////////////////////////////
// FORWARD DECLARATIONS
////////////////////////////////////////////////////////////////////////////////

class A2DFrame;
class A2DAbstract;
class A2DAbstractWindow;
class A2DCPString;
class A2DCPWindowHandle;
class A2DCPResultHandle;
class A2DCPInstanceHandle;

////////////////////////////////////////////////////////////////////////////////
// DEFINE
////////////////////////////////////////////////////////////////////////////////
        
#define RES_BSW_DIR                                         L"..\\..\\..\\Aurora-SDK\\Lib\\Assets\\Images\\"
#define IDB_BSW_BOTTOM_LEFT_SHADOW_PNG                      RES_BSW_DIR L"muzzler windows-sync bottomLeftShadow [a] 1.png"
#define IDB_BSW_BOTTOM_RIGHT_SHADOW_PNG                     RES_BSW_DIR L"muzzler windows-sync bottomRightShadow [a] 1.png"
#define IDB_BSW_BOTTOM_SHADOW_PNG                           RES_BSW_DIR L"muzzler windows-sync bottomShadow [a] 1.png"
#define IDB_BSW_TOP_LEFT_SHADOW_PNG                         RES_BSW_DIR L"muzzler windows-sync topLeftShadow [a] 1.png"
#define IDB_BSW_TOP_RIGHT_SHADOW_PNG                        RES_BSW_DIR L"muzzler windows-sync topRightShadow [a] 1.png"
#define IDB_BSW_TOP_SHADOW_PNG                              RES_BSW_DIR L"muzzler windows-sync topShadow [a] 1.png"
#define IDB_BSW_LEFT_SHADOW_PNG                             RES_BSW_DIR L"muzzler windows-sync leftShadow [a] 1.png"
#define IDB_BSW_RIGHT_SHADOW_PNG                            RES_BSW_DIR L"muzzler windows-sync rightShadow [a] 1.png"
#define IDB_BSW_BACKGROUND_PNG                              RES_BSW_DIR L"muzzler windows-sync background [a] 2.jpg"
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
    A2DWindow(HINSTANCE * xHInstance); // <-- WILL ALWAYS CENTER THE WINDOW FOR NOW

    // Deconstructor
    ~A2DWindow();
  
private:

    // Variables - NOTE: No need to use the acronym aOpt since variables are PRIVATE!
    int                             aDefaultCloseOperation;

    bool                            aVisible;
    bool                            aShadowed;
    bool                            aUndecorated;

    float                           aPadding;
    float                           aShadowPadding;
    float                           aBorderWidth;

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
    A2DCPWindowHandle         *     getChildHandle();
    A2DCPWindowHandle         *     getParentHandle();

    A2DCPString               *     getName(); // Fix this, should we use pointer or not?
    void                            setName(LPCWSTR * xName); // Fix this, should we use pointer or not?
    
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
	
	float		                    getBorderWidth();
	void                            setBorderWidth(float xWidth);

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
    virtual HRESULT                 Initialize();
    virtual void                    Deinitialize();
    virtual A2DCPString             GetClass();
    virtual A2DCPString             ToString();
    virtual bool                    operator==(A2DAbstract * xAbstract);

    /*********************************************************************/
    /*                      CROSS-PLATFORM END                           */
    /*********************************************************************/

    /*********************************************************************/
    /*                      WINDOWS-SPECIFIC START                       */
    /*********************************************************************/

    // Variables - WINDOW ONLY - INTERNAL USE ONLY

	REAL                            aGdiRealZero = 0;

    REAL                            aGdiRealRealX = 0;
    REAL                            aGdiRealRealY = 0;
    REAL                            aGdiRealRealWidth = 0;
    REAL                            aGdiRealRealHeight = 0;

    REAL                            aGdiRealRelativeX = 0;
    REAL                            aGdiRealRelativeY = 0;
    REAL                            aGdiRealRelativeWidth = 0;
    REAL                            aGdiRealRelativeHeight = 0;

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
	HRESULT                         CreateHandle(HWND& xHandle);

    /*********************************************************************/
    /*                      WINDOWS-SPECIFIC END                         */
    /*********************************************************************/
};

#endif
