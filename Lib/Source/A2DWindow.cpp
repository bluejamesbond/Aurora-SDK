
#include "../../include/A2DExtLibs.h"
#include "../../include/A2DWindow.h"

A2DWindow::A2DWindow(A2DCPInstanceHandle * xHInstance){}

A2DWindow::~A2DWindow(){}

A2DRect * A2DWindow::getBounds()
{
	return &aRect;
} 

HWND * A2DWindow::getChildHandle()
{
	return &aChildHandle;
}

HWND * A2DWindow::getParentHandle()
{
    return &aParentHandle;
}

bool A2DWindow::isShadowed()
{
    return aShadowed;
}

bool A2DWindow::isUndecorated()
{
	return aUndecorated;
}

void A2DWindow::setUndecorated(bool XUndecoratedFlag)
{
    aUndecorated = XUndecoratedFlag;
}

void A2DWindow::setShadowed(bool xShadowed)
{
    if (!isUndecorated())
    {
        setUndecorated(true);
    }
        
    aShadowed = xShadowed;

    // Update
    Update();
}

Color A2DWindow::getBorderColor()
{
    return aBorderColor;
}

void A2DWindow::setBorderColor(Color xBorderColor)
{
    aBorderColor = xBorderColor;
}

bool A2DWindow::isVisible()
{
	return aVisible;
}

bool A2DWindow::setVisible()
{
	aVisible = true;
}
void A2DWindow::setName(LPCWSTR * xName)
{
    aName = *xName;
    SetWindowText(aChildHandle, *xName);
    SetWindowText(aParentHandle, *xName);
}

LPCWSTR * A2DWindow::getName()
{
    return &aName;
}

void  A2DWindow::setFrame(A2DFrame * xFrame)
{
    aFrame = xFrame;
}

A2DFrame *  A2DWindow::getFrame()
{
    return aFrame;
}

A2DRect * A2DWindow::getBounds()
{
    return &aRect;
}

int A2DWindow::getDefaultCloseOperation()
{
    return aDefaultCloseOperation;
}

void A2DWindow::setDefaultCloseOperation(int xOperation)
{
    aDefaultCloseOperation = xOperation;
}

void A2DWindow::setLocationRelativeTo(A2DWindow * xWindow)
{
	if (xWindow == NULL)
	{
		aRect.aX = (GetSystemMetrics(SM_CXSCREEN) - aRect.aWidth) / 2;
		aRect.aY = (GetSystemMetrics(SM_CYSCREEN) - aRect.aHeight) / 2;
	}
}