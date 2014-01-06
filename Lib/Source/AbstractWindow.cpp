
#include "../../include/ExtLibs.h"
#include "../../include/AbstractWindow.h"
#include "../../include/AbstractFrame.h"
#include "../../include/AbstractEventQueue.h"

using namespace A2D;

AbstractWindow::AbstractWindow(AbstractFrame * xFrame) : aFrame(xFrame) {}

/**
* Notifies the user whether the window object being referenced
* is shadowed
*
* @param void
* @return bool
*			the boolean indicating whether window is shadowed
*/
bool AbstractWindow::isShadowed()
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
bool AbstractWindow::isUndecorated()
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
bool AbstractWindow::isVisible()
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
Color AbstractWindow::getBorderColor()
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
LPCWSTR AbstractWindow::getName()
{
	return aName;
}

/**
* returns the reference Frame of the specified Window object
*
* @param void
* @return AbstractFrame
the Frame that is associated with the window
*/
AbstractFrame *  AbstractWindow::getFrame()
{
	return aFrame;
}

/**
* returns a pointer to the Rect object associated with
* the AbstractWindow object referenced
*
* @param void
* @return Rect*
the Frame that is associated with the window
*/
Rect AbstractWindow::getBounds()
{
	return aRect;
}

Dims * AbstractWindow::_getSize()
{
	return static_cast<Dims*>(&aRect);
}


Dims AbstractWindow::getSize()
{
	return static_cast<Dims>(aRect);
}

/**
* Returns the specified color of the Shadow set for
* the referenced Window object
*
* @param void
* @return Color
*			The Color object of the Shadow
*/
Color AbstractWindow::getShadowColor()
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
Color AbstractWindow::getBackgroundColor()
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
int AbstractWindow::getDefaultCloseOperation()
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
float AbstractWindow::getBorderWidth()
{
	return aOptBorderWidth;
}

/**
* Returns the minimum size dimensions of the referenced
* AbstractWindow object
*
* @param void
* @return Dims*
*			im of min. size
*/
Dims AbstractWindow::getMinimumSize()
{
	return aMinDims;
}

/**
* Returns the minimum size dimensions of the referenced
* AbstractWindow object
*
* @param void
* @return Dims*
*			Pointer to im of max. size
*/
Dims AbstractWindow::getMaximumSize()
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
float AbstractWindow::getShadowRadius()
{
	return aOptShadowRadius;
}

/**
* Update and re-renders the AbstractWindow object
*
* @param void
* @return void
*/
void AbstractWindow::update()
{
	if (!aValidatedContents)
	{
		validate();
	}

	render();
}

void AbstractWindow::invalidate()
{
	aValidatedContents = false;
}

void AbstractWindow::validated()
{
	aValidatedContents = true;
}

void AbstractWindow::revalidate()
{
	validate();
}

HRESULT AbstractWindow::initialize()
{	
	//------------------------------------------------------------
	// ABSTRACTWINDOW DEFAULTS
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

	return S_OK;
}