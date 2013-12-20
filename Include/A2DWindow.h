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

#include "A2DCommon.h"
#include "A2DFrame.h"
#include "A2DAbstract.h"
#include "A2DRect.h"

////////////////////////////////////////////////////////////////////////////////
// FORWARD DECLARATIONS
////////////////////////////////////////////////////////////////////////////////

class A2DFrame;
class A2DAbstract;

////////////////////////////////////////////////////////////////////////////////
// DEFINE
////////////////////////////////////////////////////////////////////////////////

#define FLOAT_ZERO                                          0.0f
#define FLOAT_ONE                                           1.0f

////////////////////////////////////////////////////////////////////////////////
// DECLARATION
////////////////////////////////////////////////////////////////////////////////

using namespace Gdiplus;  // WINDOWS specific

class A2DWindow : public A2DAbstract
{
    /*********************************************************************/
    /*                      CROSS-PLATFORM START                         */
    /*********************************************************************/

public:

    // Constructor
    A2DWindow(HINSTANCE * xHInstance); // <-- WILL ALWAYS CENTER THE WINDOW FOR NOW

    // Deconstructor
    ~A2DWindow();
  
protected:

    // Variables


    /*********************************************************************/
    /*                                OPTIONS                            */
    /*********************************************************************/
    
    float                           aOptBoxShadowRadius;
    float                           aOptBorderWidth;
    
    Color                           aOptBorderColor;
    Color                           aOptBackgroundColor;
    Color                           aOptBoxShadowColor;

private :

    /*********************************************************************/
    /*                              REQUIRED                             */
    /*********************************************************************/

    int                             aDefaultCloseOperation;

    bool                            aVisible;
    bool                            aShadowed;
    bool                            aUndecorated;

    LPCWSTR                         aName;
    
    HWND                            aParentHWnd;
    HWND                            aChildHWnd;
    HINSTANCE                 *     aHInstance;

    A2DRect                         aRect;
    A2DFrame                  *     aFrame;
    A2DWindow                 *     aRelativeWindow;

public:

    // Accessors and mutators
    // These don't need mutators because we are giving direct access to the structs
    A2DRect                   *     getBounds();
        
    // Accessing internal variables. Do not provide mutators for these.
    HWND                            getChildHWnd();
    HWND                            getParentHWnd();

    LPCWSTR                   *     getName(); // Fix this, should we use pointer or not?
    void                            setName(LPCWSTR  xName); // Fix this, should we use pointer or not?
    
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
    
    float                           getBorderWidth();
    void                            setBorderWidth(float xWidth);

    float                           getBoxShadowRadius();
    void                            setBoxShadowRadius(float xBoxShadowRadius);
    
    Color                           getBoxShadowColor();
    void                            setBoxShadowColor(Color xBoxShadowColor);

    Color                           getBackgroundColor();
    void                            setBackgroundColor(Color xBoxShadowColor);

    // Additional
    void                            Update();
    void                            Render();
    void                            updateAndCacheBoxShadow();
    void                            UpdateAndCacheBackground();
    void                            RenderComponent();
    void                            RenderComponentBorder();
    HRESULT                         CreateResources();
    void                            DestroyResources();
    
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

    POINT                           lastDraggedPoint;
    bool                            isDragged = false;
    int                             aMinHeight = 300;
    int                             aMinWidth = 300;

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
