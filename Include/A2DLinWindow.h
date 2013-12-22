////////////////////////////////////////////////////////////////////////////////

#ifndef __A2DLINWINDOW_H__
#define __A2DLINWINDOW_H__

//+-----------------------------------------------------------------------------
//
//  Class:
//      A2DLINWINDOW
//
//  Synopsis:
//      Custom LINUX/UNIX implmentatino of A2DAbstractWindow
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////
#include "A2DFrame.h"
#include "A2DAbstract.h"
#include "A2DRect.h"
#include "A2DWindow.h"

////////////////////////////////////////////////////////////////////////////////
// FORWARD DECLARATIONS
////////////////////////////////////////////////////////////////////////////////

class A2DFrame;
class A2DAbstract;
class A2DAbstractWindow;

////////////////////////////////////////////////////////////////////////////////
// DEFINE
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// DEFINE
////////////////////////////////////////////////////////////////////////////////

#define FLOAT_ZERO                                          0.0f
#define FLOAT_ONE                                           1.0f
#define WIN32_LEAN_AND_MEAN

////////////////////////////////////////////////////////////////////////////////
// DECLARATION
////////////////////////////////////////////////////////////////////////////////

using namespace Gdiplus;  // WINDOWS specific

class A2DLinWindow : public A2DWindow<HWND, LPCWSTR>
{
    /*********************************************************************/
    /*                      CROSS-PLATFORM START                         */
    /*********************************************************************/

public:

    // Constructor
    A2DLinWindow(HINSTANCE  xHInstance); // <-- WILL ALWAYS CENTER THE WINDOW FOR NOW

    // Deconstructor
    ~A2DLinWindow();
  

    /*********************************************************************/
    /*                              REQUIRED                             */
    /*********************************************************************/

    

public:

    HINSTANCE                       aHInstance;

    // Accessors and mutators
    // These don't need mutators because we are giving direct access to the structs
    // Accessing internal variables. Do not provide mutators for these.\

    //Windows specific, for now. maybe change later
    virtual void                    setMinimumSize(float xWidth, float xHeight);

    //A2DMSWindow               *     getLocationRelativeTo(); never defined
    
    virtual void                    setVisible(bool xVisibile);

    virtual void                    setUndecorated(bool xUndecoratedFlag); // SET

    virtual void                    setBoxShadowRadius(float xBoxShadowRadius);

    virtual void                    setName(LPCWSTR xName);

    // Additional
    virtual void                    Update();
    virtual void                    updateAndCacheBoxShadow();
    virtual void                    UpdateAndCacheBackground();

    virtual  void                   RenderComponent();
    virtual void                    RenderComponentBorder();
    virtual HRESULT                 CreateResources();
    virtual void                    DestroyResources();
    
    // Implementation
    // { A2DABSTRACT }
    virtual HRESULT                 Initialize();
    virtual void                    Deinitialize();
    virtual LPCWSTR                 GetClass();
    virtual LPCWSTR                 ToString();
    virtual bool                    operator==(A2DAbstract * xAbstract);

    /*********************************************************************/
    /*                      CROSS-PLATFORM END                           */
    /*********************************************************************/

    /*********************************************************************/
    /*                      WINDOWS-SPECIFIC START                       */
    /*********************************************************************/

private:
    //GL ONLY. NOT GL + LINUX THOUGH, SO WINDOWS STUFF BELOW AS WELL
    LPCWSTR m_applicationName;
    HINSTANCE m_hinstance;
    HWND m_hwnd;

    // Variables - WINDOW ONLY - INTERNAL USE ONLY

    Image                     *     aTopShadow;
    Image                     *     aLeftShadow;
    Image                     *     aRightShadow;
    Image                     *     aBottomShadow;
    Image                     *     aTopLeftShadow;
    Image                     *     aBottomLeftShadow;
    Image                     *     aTopRightShadow;
    Image                     *     aBottomRightShadow;
    Image                     *     aBackground;

    TextureBrush              *     aTopShadowBrush;
    TextureBrush              *     aLeftShadowBrush;
    TextureBrush              *     aRightShadowBrush;
    TextureBrush              *     aBottomShadowBrush;
    TextureBrush              *     aBackgroundBrush;

    float                           aPadding;
    float                           aShadowPadding;

    float                           aRealX = 0;
    float                           aRealY = 0;
    float                           aRealWidth = 0;
    float                           aRealHeight = 0;

    float                           aRelativeX = 0;
    float                           aRelativeY = 0;
    float                           aRelativeWidth = 0;
    float                           aRelativeHeight = 0;

    int                             aStyle;
    Graphics                  *     aGraphics;

    bool                            isDragged = false;
    bool                            isResizing = false;
    bool                            aWinMoveRes = false;

    HWND                            aParentHWnd;
    HCURSOR                         aCurrentCursor;
    POINT                           aLastDraggedPoint;

    A2DDims                         aMinSafeDims;

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
    // { NONE }

    // Pure Virtual
    // { NONE }

    // Virtual
    // { NONE }     

private:
    
    // Functions

    // Win API
    void                            RunMessageLoop();
    static LRESULT CALLBACK         WndProc(HWND xHwnd, UINT xMessage, WPARAM xWParam, LPARAM xLParam);
    HRESULT                         RegisterClass();
    HWND                            CreateCompatibleWindow(bool isParent);

    // Background
    HRESULT                         CreateBackgroundResources();
    void                            DestroyBackgroundResources();

    // Box Shadow - Set 1
    HRESULT                         createBoxShadowResources();
    void                            destroyBoxShadowResources();

    //  Box Shadow - Set 2
    void                            spliceToNinePatch(Image * src, Image * dest, float srcX, float srcY, float srcWidth, float srcHeight);
    float                     *     getGaussianKernel(int xRadius);
    void                            applyHorizontalblur(BitmapData * srcPixels, BitmapData * dstPixels, float * kernel, int radius);
    Bitmap                    *     applyGaussianBlur(Bitmap * src, int radius);
    BitmapData                *     getLockedBitmapData(Bitmap * src);    

    /*********************************************************************/
    /*                      WINDOWS-SPECIFIC END                         */
    /*********************************************************************/
};

#endif
