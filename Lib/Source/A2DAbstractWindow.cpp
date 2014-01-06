
#include "../../include/A2DExtLibs.h"
#include "../../include/A2DAbstractWindow.h"
#include "../../include/A2DAbstractFrame.h"

bool A2DAbstractWindow::isShadowed()
{
	return aShadowed;
}

bool A2DAbstractWindow::isUndecorated()
{
	return aUndecorated;
}

bool A2DAbstractWindow::isVisible()
{
	return aVisible;
}

Color A2DAbstractWindow::getBorderColor()
{
	return aOptBorderColor;
}
LPCWSTR A2DAbstractWindow::getName()
{
	return aName;
}

void  A2DAbstractWindow::setFrame(A2DAbstractFrame * xFrame)
{
	aFrame = xFrame;
}

A2DAbstractFrame *  A2DAbstractWindow::getFrame()
{
	return aFrame;
}

A2DRect * A2DAbstractWindow::getBounds()
{
	return &aRect;
}

Color A2DAbstractWindow::getShadowColor()
{
	return aOptShadowColor;
}

Color A2DAbstractWindow::getBackgroundColor()
{
	return aOptBackgroundColor;
}

int A2DAbstractWindow::getDefaultCloseOperation()
{
	return aDefaultCloseOperation;
}

float A2DAbstractWindow::getBorderWidth()
{
	return aOptBorderWidth;
}

A2DDims * A2DAbstractWindow::getMinimumSize()
{
	return &aMinDims;
}

A2DDims * A2DAbstractWindow::getMaximumSize()
{
	return &aMaxDims;
}

float A2DAbstractWindow::getShadowRadius()
{
	return aOptShadowRadius;
}

void A2DAbstractWindow::setVisible(bool xVisible)
{
	aVisible = xVisible;
}

void A2DAbstractWindow::setUndecorated(bool xUndecoratedFlag)
{
	aUndecorated = xUndecoratedFlag;
}

void A2DAbstractWindow::update()
{
	render();
}

void A2DAbstractWindow::renderGX()
{
	aFrame->Update();
}

void A2DAbstractWindow::createGXResources()
{
	aFrame->CreateResources();
}