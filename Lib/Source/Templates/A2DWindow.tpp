
#include "../../../include/A2DExtLibs.h"
#include "../../../include/A2DWindow.h"
#include "../../../include/A2DFrame.h"

template <typename HNWND, typename HSTRING>
HNWND A2DWindow<HNWND, HSTRING>::getHNWnd()
{
    return aHNWnd;
}

template <typename HNWND, typename HSTRING>
bool A2DWindow<HNWND, HSTRING>::isShadowed()
{
    return aShadowed;
}

template <typename HNWND, typename HSTRING>
bool A2DWindow<HNWND, HSTRING>::isUndecorated()
{
    return aUndecorated;
}

template <typename HNWND, typename HSTRING>
void A2DWindow<HNWND, HSTRING>::setUndecorated(bool XUndecoratedFlag)
{
    aUndecorated = XUndecoratedFlag;
}

template <typename HNWND, typename HSTRING>
void A2DWindow<HNWND, HSTRING>::setShadowed(bool xShadowed)
{
    if (!isUndecorated())
    {
        setUndecorated(true);
    }
        
    aShadowed = xShadowed;

    Update();
}

template <typename HNWND, typename HSTRING>
Color A2DWindow<HNWND, HSTRING>::getBorderColor()
{
    return aOptBorderColor;
}

template <typename HNWND, typename HSTRING>
void A2DWindow<HNWND, HSTRING>::setBorderColor(Color xOptBorderColor)
{
    aOptBorderColor = xOptBorderColor;
}

template <typename HNWND, typename HSTRING>
bool A2DWindow<HNWND, HSTRING>::isVisible()
{
    return aVisible;
}

template <typename HNWND, typename HSTRING>
void A2DWindow<HNWND, HSTRING>::setVisible(bool xVisible)
{
    aVisible = xVisible;
}
template <typename HNWND, typename HSTRING>
void A2DWindow<HNWND, HSTRING>::setName(HSTRING xName)
{
    aName = xName;
}

template <typename HNWND, typename HSTRING>
HSTRING A2DWindow<HNWND, HSTRING>::getName()
{
    return aName;
}

template <typename HNWND, typename HSTRING>
void  A2DWindow<HNWND, HSTRING>::setFrame(A2DFrame * xFrame)
{
    aFrame = xFrame;
}

template <typename HNWND, typename HSTRING>
A2DFrame *  A2DWindow<HNWND, HSTRING>::getFrame()
{
    return aFrame;
}

template <typename HNWND, typename HSTRING>
A2DRect * A2DWindow<HNWND, HSTRING>::getBounds()
{
    return &aRect;
}

template <typename HNWND, typename HSTRING>
int A2DWindow<HNWND, HSTRING>::getDefaultCloseOperation()
{
    return aDefaultCloseOperation;
}

template <typename HNWND, typename HSTRING>
void A2DWindow<HNWND, HSTRING>::setDefaultCloseOperation(int xOperation)
{
    aDefaultCloseOperation = xOperation;
}

template <typename HNWND, typename HSTRING>
void A2DWindow<HNWND, HSTRING>::setLocationRelativeTo(A2DWindow<HNWND, HSTRING> * xWindow)
{
    if (xWindow == NULL)
    {
        aRect.aX = (GetSystemMetrics(SM_CXSCREEN) - aRect.aWidth) / 2;
        aRect.aY = (GetSystemMetrics(SM_CYSCREEN) - aRect.aHeight) / 2;
    }
}

/**
*
* Sets the visibility of the decorations around a window. Enabling
* decorations shows you the maximize, minimize, and close buttons.
*
* @param bool
*            the boolean indicating whether window should be
*            decorated or not.
* @return void
*/
template <typename HNWND, typename HSTRING>
void A2DWindow<HNWND, HSTRING>::setBorderWidth(float xBorderWidth)
{
    aOptBorderWidth = xBorderWidth;
}

/**
*
* Sets the visibility of the decorations around a window. Enabling
* decorations shows you the maximize, minimize, and close buttons.
*
* @param bool
*            the boolean indicating whether window should be
*            decorated or not.
* @return void
*/
template <typename HNWND, typename HSTRING>
float A2DWindow<HNWND, HSTRING>::getBorderWidth()
{
    return aOptBorderWidth;
}

/**
*
* Sets the visibility of the decorations around a window. Enabling
* decorations shows you the maximize, minimize, and close buttons.
*
* @param bool
*            the boolean indicating whether window should be
*            decorated or not.
* @return void
*/
template <typename HNWND, typename HSTRING>
void A2DWindow<HNWND, HSTRING>::setBoxShadowRadius(float xBoxShadowRadius)
{
    if (abs(xBoxShadowRadius) < 1) return;

    aOptBoxShadowRadius = abs(xBoxShadowRadius);

    setMinimumSize(&aMinDims); //windows specific
}

/**
*
* Sets the visibility of the decorations around a window. Enabling
* decorations shows you the maximize, minimize, and close buttons.
*
* @param bool
*            the boolean indicating whether window should be
*            decorated or not.
* @return void
*/
template <typename HNWND, typename HSTRING>
void A2DWindow<HNWND, HSTRING>::setMinimumSize(A2DDims * xSize)
{
    aMinDims.aWidth = max(aOptBoxShadowRadius * A2D_WINDOW_BOX_SHADOW_SAFETY_RATIO, xSize->aWidth);
    aMinDims.aHeight = max(aOptBoxShadowRadius * A2D_WINDOW_BOX_SHADOW_SAFETY_RATIO, xSize->aHeight);
}

/**
*
* Sets the visibility of the decorations around a window. Enabling
* decorations shows you the maximize, minimize, and close buttons.
*
* @param bool
*            the boolean indicating whether window should be
*            decorated or not.
* @return void
*/
template <typename HNWND, typename HSTRING>
A2DDims * A2DWindow<HNWND, HSTRING>::getMinimumSize()
{
    return &aMinDims;
}


/**
*
* Sets the visibility of the decorations around a window. Enabling
* decorations shows you the maximize, minimize, and close buttons.
*
* @param bool
*            the boolean indicating whether window should be
*            decorated or not.
* @return void
*/
template <typename HNWND, typename HSTRING>
void A2DWindow<HNWND, HSTRING>::setMaximumSize(float xWidth, float xHeight)
{
    aMaxDims.aWidth = min(GetSystemMetrics(SM_CXSCREEN), xWidth);
    aMaxDims.aHeight = min(GetSystemMetrics(SM_CYSCREEN), xHeight);
}

/**
*
* Sets the visibility of the decorations around a window. Enabling
* decorations shows you the maximize, minimize, and close buttons.
*
* @param bool
*            the boolean indicating whether window should be
*            decorated or not.
* @return void
*/
template <typename HNWND, typename HSTRING>
A2DDims * A2DWindow<HNWND, HSTRING>::getMaximumSize()
{
    return &aMaxDims;
}

/**
*
* Sets the visibility of the decorations around a window. Enabling
* decorations shows you the maximize, minimize, and close buttons.
*
* @param bool
*            the boolean indicating whether window should be
*            decorated or not.
* @return void
*/
template <typename HNWND, typename HSTRING>
float A2DWindow<HNWND, HSTRING>::getBoxShadowRadius()
{
    return aOptBoxShadowRadius;
}


/**
*
* Sets the visibility of the decorations around a window. Enabling
* decorations shows you the maximize, minimize, and close buttons.
*
* @param bool
*            the boolean indicating whether window should be
*            decorated or not.
* @return void
*/
template <typename HNWND, typename HSTRING>
void A2DWindow<HNWND, HSTRING>::setBoxShadowColor(Color xBoxShadowColor)
{
    aOptBoxShadowColor = xBoxShadowColor;
}

/**
*
* Sets the visibility of the decorations around a window. Enabling
* decorations shows you the maximize, minimize, and close buttons.
*
* @param bool
*            the boolean indicating whether window should be
*            decorated or not.
* @return void
*/
template <typename HNWND, typename HSTRING>
Color A2DWindow<HNWND, HSTRING>::getBoxShadowColor()
{
    return aOptBoxShadowColor;
}

/**
*
* Sets the visibility of the decorations around a window. Enabling
* decorations shows you the maximize, minimize, and close buttons.
*
* @param bool
*            the boolean indicating whether window should be
*            decorated or not.
* @return void
*/
template <typename HNWND, typename HSTRING>
Color A2DWindow<HNWND, HSTRING>::getBackgroundColor()
{
    return aOptBackgroundColor;
}

/**
*
* Sets the visibility of the decorations around a window. Enabling
* decorations shows you the maximize, minimize, and close buttons.
*
* @param bool
*            the boolean indicating whether window should be
*            decorated or not.
* @return void
*/
template <typename HNWND, typename HSTRING>
void A2DWindow<HNWND, HSTRING>::setBackgroundColor(Color xBackgroundColor)
{
    aOptBackgroundColor = xBackgroundColor;
}
/**
*
* This method creates a 1x1 image of the color indicated by the
* aOptBackgroundColor and updates all the windows derived of the aParentHWnd to
* that color. The aOptBackgroundColor
*
* @see #destroyBackgroundResources()
* @see #createBackgroundResources()
* @see #createResources()
* @see #destroyResources()
* @param  void
* @return void
*/
template <typename HNWND, typename HSTRING>
void A2DWindow<HNWND, HSTRING>::Update()
{
    Render();
}

/**
*
* This method creates a 1x1 image of the color indicated by the
* aOptBackgroundColor and updates all the windows derived of the aParentHWnd to
* that color. The aOptBackgroundColor
*
* @see #destroyBackgroundResources()
* @see #createBackgroundResources()
* @see #createResources()
* @see #destroyResources()
* @param  void
* @return void
*/
template <typename HNWND, typename HSTRING>
void A2DWindow<HNWND, HSTRING>::Render()
{
    RenderComponent();
    RenderComponentBorder();
}