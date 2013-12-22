
#include "../../include/A2DExtLibs.h"
#include "../../include/A2DNativeWindow.h"
#include "../../include/A2DFrame.h"

HNWND A2DNativeWindow::getHNWnd()
{
	return aHNWnd;
}

bool A2DNativeWindow::isShadowed()
{
	return aShadowed;
}

bool A2DNativeWindow::isUndecorated()
{
	return aUndecorated;
}

void A2DNativeWindow::setUndecorated(bool XUndecoratedFlag)
{
	aUndecorated = XUndecoratedFlag;
}

void A2DNativeWindow::setShadowed(bool xShadowed)
{
	if (!isUndecorated())
	{
		setUndecorated(true);
	}

	aShadowed = xShadowed;

	Update();
}

Color A2DNativeWindow::getBorderColor()
{
	return aOptBorderColor;
}

void A2DNativeWindow::setBorderColor(Color xOptBorderColor)
{
	aOptBorderColor = xOptBorderColor;
}

bool A2DNativeWindow::isVisible()
{
	return aVisible;
}

void A2DNativeWindow::setVisible(bool xVisible)
{
	aVisible = xVisible;
}
void A2DNativeWindow::setName(HSTRING xName)
{
	aName = xName;
}

HSTRING A2DNativeWindow::getName()
{
	return aName;
}

void  A2DNativeWindow::setFrame(A2DFrame * xFrame)
{
	aFrame = xFrame;
}

A2DFrame *  A2DNativeWindow::getFrame()
{
	return aFrame;
}

A2DRect * A2DNativeWindow::getBounds()
{
	return &aRect;
}

int A2DNativeWindow::getDefaultCloseOperation()
{
	return aDefaultCloseOperation;
}

void A2DNativeWindow::setDefaultCloseOperation(int xOperation)
{
	aDefaultCloseOperation = xOperation;
}

void A2DNativeWindow::setLocationRelativeTo(A2DNativeWindow * xWindow)
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
void A2DNativeWindow::setBorderWidth(float xBorderWidth)
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
float A2DNativeWindow::getBorderWidth()
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
void A2DNativeWindow::setBoxShadowRadius(float xBoxShadowRadius)
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
void A2DNativeWindow::setMinimumSize(A2DDims * xSize)
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
A2DDims * A2DNativeWindow::getMinimumSize()
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
void A2DNativeWindow::setMaximumSize(float xWidth, float xHeight)
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
A2DDims * A2DNativeWindow::getMaximumSize()
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
float A2DNativeWindow::getBoxShadowRadius()
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
void A2DNativeWindow::setBoxShadowColor(Color xBoxShadowColor)
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
Color A2DNativeWindow::getBoxShadowColor()
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
Color A2DNativeWindow::getBackgroundColor()
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
void A2DNativeWindow::setBackgroundColor(Color xBackgroundColor)
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
void A2DNativeWindow::Update()
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
void A2DNativeWindow::Render()
{
	RenderComponent();
	RenderComponentBorder();
}

