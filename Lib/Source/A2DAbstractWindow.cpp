
#include "../../include/A2DExtLibs.h"
#include "../../include/A2DAbstractWindow.h"

A2DAbstractWindow::A2DAbstractWindow(A2DCPInstanceHandle * xHInstance){}

A2DAbstractWindow::~A2DAbstractWindow(){}

A2DRect * A2DAbstractWindow::getBounds()
{
	return &aRect;
} 

HWND * A2DAbstractWindow::getChildHandle()
{
	return &aChildHandle;
}

HWND * A2DAbstractWindow::getParentHandle()
{
    return &aParentHandle;
}

bool A2DAbstractWindow::isShadowed()
{
    return aShadowed;
}

bool A2DAbstractWindow::isUndecorated()
{
	return aUndecorated;
}

void A2DAbstractWindow::setUndecorated(bool XUndecoratedFlag)
{
    aUndecorated = XUndecoratedFlag;
}

void A2DAbstractWindow::setShadowed(bool xShadowed)
{
    if (!isUndecorated())
    {
        setUndecorated(true);
    }
        
    aShadowed = xShadowed;

    // Update
    Update();
}

Color A2DAbstractWindow::getBorderColor()
{
    return aBorderColor;
}

void A2DAbstractWindow::setBorderColor(Color xBorderColor)
{
    aBorderColor = xBorderColor;
}

bool A2DAbstractWindow::isVisible()
{
	return aVisible;
}

bool A2DAbstractWindow::setVisible()
{
	aVisible = true;
}
void A2DAbstractWindow::setName(LPCWSTR * xName)
{
    aName = *xName;
    SetWindowText(aChildHandle, *xName);
    SetWindowText(aParentHandle, *xName);
}

LPCWSTR * A2DAbstractWindow::getName()
{
    return &aName;
}

void  A2DAbstractWindow::setFrame(A2DFrame * xFrame)
{
    aFrame = xFrame;
}

A2DFrame *  A2DAbstractWindow::getFrame()
{
    return aFrame;
}

A2DRect * A2DAbstractWindow::getBounds()
{
    return &aRect;
}

int A2DAbstractWindow::getDefaultCloseOperation()
{
    return aDefaultCloseOperation;
}

void A2DAbstractWindow::setDefaultCloseOperation(int xOperation)
{
    aDefaultCloseOperation = xOperation;
}

void A2DAbstractWindow::setLocationRelativeTo(A2DWindow * xWindow)
{
	if (xWindow == NULL)
	{
		aRect.aX = (GetSystemMetrics(SM_CXSCREEN) - aRect.aWidth) / 2;
		aRect.aY = (GetSystemMetrics(SM_CYSCREEN) - aRect.aHeight) / 2;
	}
}