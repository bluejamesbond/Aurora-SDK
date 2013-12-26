
#include "../../include/A2DExtLibs.h"
#include "../../include/A2DAbstractWindow.h"
#include "../../include/A2DAbstractFrame.h"
#include "../../include/A2DAbstractEventQueue.h"

/**
* Notifies the user whether the window object being referenced
* is shadowed
*
* @param void
* @return bool
*			the boolean indicating whether window is shadowed
*/
bool A2DAbstractWindow::isShadowed()
{
	return aShadowed;
}

/**
* Returns wether the window object is Undecorated
*
* @param void
* @return bool
*			the boolean indicating whether window is undecorated
*/
bool A2DAbstractWindow::isUndecorated()
{
	return aUndecorated;
}

/**
* Returns wether the window object is visible
*
* @param void
* @return bool
*			the boolean indicating whether window is set
*			as visible
*/
bool A2DAbstractWindow::isVisible()
{
	return aVisible;
}

/**
* Returns the specified color of the border
*
* @param void
* @return Color
*			The Color object of border
*/
A2DColor A2DAbstractWindow::getBorderColor()
{
	return aOptBorderColor;
}

/**
* Returns the specified Window object's name attribute
*
* @param void
* @return LPCWSTR
*			Long string representation of the name
*/
LPCWSTR A2DAbstractWindow::getName()
{
	return aName;
}

/**
* Sets the reference Frame of the specified Window object as
* specified by the user
*
* @param A2DAbstractFrame
the Frame that is associated with the window
* @return void
*/
void  A2DAbstractWindow::setFrame(A2DAbstractFrame * xFrame)
{
	aFrame = xFrame;
}

/**
* returns the reference Frame of the specified Window object
*
* @param void
* @return A2DAbstractFrame
the Frame that is associated with the window
*/
A2DAbstractFrame *  A2DAbstractWindow::getFrame()
{
	return aFrame;
}

/**
* returns a pointer to the A2DRect object associated with
* the A2DAbstractWindow object referenced
*
* @param void
* @return A2DRect*
the Frame that is associated with the window
*/
A2DRect A2DAbstractWindow::getBounds()
{
	return aRect;
}

A2DDims A2DAbstractWindow::getSize()
{
	return static_cast<A2DDims>(aRect);
}

/**
* Returns the specified color of the Shadow set for
* the referenced Window object
*
* @param void
* @return Color
*			The Color object of the Shadow
*/
A2DColor A2DAbstractWindow::getShadowColor()
{
	return aOptShadowColor;
}

/**
* Returns the specified color of the Background set for
* the referenced Window object
*
* @param void
* @return Color
*			The Color object of the Background
*/
A2DColor A2DAbstractWindow::getBackgroundColor()
{
	return aOptBackgroundColor;
}

/**
* Returns the specified value of the Specified Default Close
* Operation of the referenced window object
*
* @param void
* @return int
*			Value of the Close Operation
*/
int A2DAbstractWindow::getDefaultCloseOperation()
{
	return aDefaultCloseOperation;
}

/**
* Returns the specified value of the border's width
* of the referenced window object
*
* @param void
* @return float
*			width of the border
*/
float A2DAbstractWindow::getBorderWidth()
{
	return aOptBorderWidth;
}

/**
* Returns the minimum size dimensions of the referenced
* A2DAbstractWindow object
*
* @param void
* @return A2DDims*
*			A2Dim of min. size
*/
A2DDims A2DAbstractWindow::getMinimumSize()
{
	return aMinDims;
}

/**
* Returns the minimum size dimensions of the referenced
* A2DAbstractWindow object
*
* @param void
* @return A2DDims*
*			Pointer to A2Dim of max. size
*/
A2DDims A2DAbstractWindow::getMaximumSize()
{
	return aMaxDims;
}

/**
* Returns the specified value of the shadow's rdius
* of the referenced window object
*
* @param void
* @return float
*			radius of the shadow
*/
float A2DAbstractWindow::getShadowRadius()
{
	return aOptShadowRadius;
}

/**
* Update and re-renders the A2DAbstractWindow object
*
* @param void
* @return void
*/
void A2DAbstractWindow::update()
{
	if (!aValidatedContents)
	{
		validate();
	}

	render();
}

void A2DAbstractWindow::invalidate()
{
	aValidatedContents = false;
}

void A2DAbstractWindow::validated()
{
	aValidatedContents = true;
}

void A2DAbstractWindow::revalidate()
{
	validate();
}

HRESULT A2DAbstractWindow::Initialize()
{
	HRESULT hr = S_OK;
	
	//------------------------------------------------------------
	// A2DABSTRACTWINDOW DEFAULTS
	//------------------------------------------------------------

	// Default name
	aName = L"Aurora-SDK Unititled";

	// Default (0,0)
	aRect.aX = 0;
	aRect.aY = 0;

	// Default size
	aRect.aWidth = 800;
	aRect.aHeight = 600;

	// Default minimium is 0,0
	aMinDims.aWidth = FLT_ZERO;
	aMinDims.aHeight = FLT_ZERO;

	// Default maximum is full screen
	aMaxDims.aWidth = FLT_MAX;
	aMaxDims.aHeight = FLT_MAX;

	// Default shadow radius
	aOptShadowRadius = 30.0f;

	// Default shadow color
	aOptShadowColor.aRed = 0xFF;
	aOptShadowColor.aBlue = 0xFF;
	aOptShadowColor.aGreen = 0xFF;
	aOptShadowColor.aAlpha = 0xFF;

	// Default border width
	aOptBorderWidth = 2.0f;

	// Default border color
	aOptBorderColor.aRed = 0xFF;
	aOptBorderColor.aBlue = 0xFF;
	aOptBorderColor.aGreen = 0xFF;
	aOptBorderColor.aAlpha = 0xFF;

	// Default background color
	aOptBackgroundColor.aRed = 0xFF;
	aOptBackgroundColor.aBlue = 0xFF;
	aOptBackgroundColor.aGreen = 0xFF;
	aOptBackgroundColor.aAlpha = 0xFF;

	// Mark as dirty
	invalidate();

	//------------------------------------------------------------

	return hr;
}