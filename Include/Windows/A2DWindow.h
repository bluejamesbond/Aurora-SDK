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

#include "../Windows/A2DExtLibs.h"
#include "../A2DCommon.h"
#include "../A2DAbstract.h"
#include "../A2DRect.h"
#include "../A2DDims.h"
#include "../A2DAbstractWindow.h"

////////////////////////////////////////////////////////////////////////////////
// FORWARD DECLARATIONS
////////////////////////////////////////////////////////////////////////////////

class A2DFrame;
class A2DAbstract;

////////////////////////////////////////////////////////////////////////////////
// DEFINE
////////////////////////////////////////////////////////////////////////////////

#define FLOAT_ZERO                                            0.0f
#define FLOAT_ONE                                             1.0f

////////////////////////////////////////////////////////////////////////////////
// DECLARATION
////////////////////////////////////////////////////////////////////////////////

using namespace Gdiplus;

class A2DWindow : public A2DAbstractWindow
{

////////////////////////////////////////////////////////////////////////////////
// PLATFORM COMPATIBLE IMPLEMENTATION
////////////////////////////////////////////////////////////////////////////////

public:

    A2DWindow(HINSTANCE  xHInstance);

    ~A2DWindow();
     
private:

    int                             aStyle;

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

    bool                            isDragged = false;
    bool                            isResizing = false;
    bool                            aWinMoveRes = false;

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

    Graphics                  *     aGraphics;

    HINSTANCE                       aHInstance; 
    HWND                            aHResizeWnd;
    HWND                            aParentHWnd;
    HWND                            aChildHWnd;
    HCURSOR                         aCurrentCursor;
    POINT                           aLastDraggedPoint;

    A2DDims                         aMinSafeDims;

public:

    static LRESULT CALLBACK         wndProc(HWND xHwnd, UINT xMessage, WPARAM xWParam, LPARAM xLParam);

private:
    
    void                            setMinimumSize(float xWidth, float xHeight);
    void                            setMaximumSize(float xWidth, float xHeight);

    void                            runMessageLoop();

    HWND                            createCompatibleWindow(bool isParent);
    HRESULT                         createBackgroundResources();
    HRESULT                         createShadowResources();
    HRESULT                         registerClass();

    HRESULT                         updateOnMouseDown(HWND xHwnd);
    HRESULT                         updateOnMouseMove(HWND xHwnd);
    HRESULT                         updateOnMouseUp(HWND xHwnd);

    void                            destroyBackgroundResources();
    void                            destroyShadowResources();

    void                            spliceToNinePatch(Image * src, Image * dest, float srcX, float srcY, float srcWidth, float srcHeight);
    float                     *     getGaussianKernel(int xRadius);
    void                            applyHorizontalblur(BitmapData * srcPixels, BitmapData * dstPixels, float * kernel, int radius);
    Bitmap                    *     applyGaussianBlur(Bitmap * src, int radius);
    BitmapData                *     getLockedBitmapData(Bitmap * src); 


    virtual void                    updateAndCacheShadow();
    virtual void                    updateAndCacheBackground();

    virtual void                    renderComponent();
    virtual void                    renderComponentBorder();
    virtual HRESULT                 createResources();
    virtual void                    destroyResources();

////////////////////////////////////////////////////////////////////////////////
// A2DABSTRACTWINDOW
////////////////////////////////////////////////////////////////////////////////

protected:

	virtual void                    render();

public:

	virtual void              *     getPlatformCompatibleWindowHandle();
	
    virtual void                    setMinimumSize(A2DDims * xSize);
    virtual void                    setMaximumSize(A2DDims * xSize);
    virtual void                    setName(LPCWSTR xName);
    virtual void                    setUndecorated(bool xUndecoratedFlag);
    virtual void                    setDefaultCloseOperation(int xCloseOperation);
    virtual void                    setLocationRelativeTo(A2DAbstractWindow * xWindow);
    virtual void                    setVisible(bool xVisible);
    virtual void                    setBorderColor(Color xBorderColor);
    virtual void                    setBorderWidth(float xBorderWidth);
    virtual void                    setShadowed(bool xShadowFlag);
    virtual void                    setShadowRadius(float xShadowRadius);
    virtual void                    setShadowColor(Color xShadowColor);
    virtual void                    setBackgroundColor(Color xBackgroundColor);
   
////////////////////////////////////////////////////////////////////////////////
// A2DABSTRACT
////////////////////////////////////////////////////////////////////////////////

public:

    virtual HRESULT                 Initialize();
    virtual void                    Deinitialize();
    virtual LPCWSTR                 GetClass();
    virtual LPCWSTR                 ToString();
    virtual bool                    operator==(A2DAbstract * xAbstract);

};

#endif
