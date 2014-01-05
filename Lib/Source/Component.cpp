
#include "../../include/ExtLibs.h"
#include "../../include/Component.h"
#include "../../include/Graphics.h"
#include "time.h"

using namespace A2D;

Component::Component(){}

Component::~Component(){}

void Component::setBackground(LPCWSTR xOptBackgroundImage, int xOptBackroundPositionX,	int xOptBackroundPositionY,	
	int xOptBackroundSizeX,	int xOptBackroundSizeY,	Paint& xOptBackgroundPaint, int xOptBackgroundRepeat)
{
	aOptBackgroundSrc = xOptBackgroundImage;
	aOptBackgroundPosX = xOptBackroundPositionX;
	aOptBackgroundPosY = xOptBackroundPositionY;
	aOptBackgroundProps.aOptSizeX = xOptBackroundSizeX;
	aOptBackgroundProps.aOptSizeY = xOptBackroundSizeY;
	aOptBackgroundProps.aOptRepeat = xOptBackgroundRepeat;

	Paint::from(aOptBackgroundPaint, xOptBackgroundPaint);
};

void Component::paintComponent()
{
	Graphics& graphics = *aGraphics;

	if (aOptBackgroundSrc != NULL)
	{
		bool repeat = aOptBackgroundProps.aOptRepeat == (_OPT_BACKGROUND_REPEAT_REPEAT_X | _OPT_BACKGROUND_REPEAT_REPEAT_Y);
		graphics.drawImage(&aPipeline, aOptBackgroundRegion, aOptBackgroundSrc, aOptBackgroundPaint, repeat);
	}
}

void Component::update()
{
	Graphics& graphics = *aGraphics;

	if (!aValidatedContents)
	{
		validate();
	}

	graphics.setClip(&aVisibleRegion, aDepth);

	// Render the current component
	paintComponent();

	// Force region
	graphics.setClip(&aVisibleRegion, aDepth);

	// Render the currect component border
	paintComponentBorder();
}

void Component::paintComponentBorder(){}

Component& Component::getParent()
{
	return *aParent;
}

float Component::getDepth()
{
	return aDepth;
}

AbstractFrame& Component::getFrame()
{
	return *aFrame;
}

void Component::_setGraphics(Graphics& xGraphics)
{
	aGraphics = &xGraphics;
}

Graphics& Component::getGraphics()
{
	return *aGraphics;
}

void Component::_setDepth( float xDepth)
{
	aDepth = xDepth;
}

void Component::_setFrame(AbstractFrame& xFrame)
{
	aFrame = &xFrame;
}

void Component::_setParent(Component& xParent)
{
	aParent = &xParent;
}

Rect Component::getBounds()
{
	return aOptRegion;
}

Rect * Component::_getBounds()
{
	return &aOptRegion;
}

void Component::_add(Component& xContainer)
{
	aChildren.push_back(&xContainer, NULL);
}

void Component::_remove(Component& xContainer)
{
	aChildren.remove(&xContainer);
}

void Component::setBounds(Rect& xRect)
{
	aOptRegion.aWidth = xRect.aWidth;
	aOptRegion.aHeight = xRect.aHeight;
	aOptRegion.aX = xRect.aX;
	aOptRegion.aY = xRect.aY;

	aOptBackgroundRegion.aWidth = xRect.aWidth;
	aOptBackgroundRegion.aHeight = xRect.aHeight;

	invalidate();
}

void Component::invalidate()
{
	aValidatedContents = false;
}

void Component::revalidate()
{
	validate();
}

void Component::validated()
{
	aValidatedContents = true;
}

void Component::validate()
{
	Component * parentComp = aParent;
	Rect& compRect = aOptRegion;
	bool hasParent = parentComp != NULL;

	if (!hasParent)
	{
		aCalculatedRegion.aX = max(0, compRect.aX);
		aCalculatedRegion.aY = max(0, compRect.aY);
		aCalculatedRegion.aWidth = max(0, compRect.aWidth);
		aCalculatedRegion.aHeight = max(0, compRect.aHeight);
	}
	else
	{
		float sX, sY;
		Rect& parentRect = parentComp->aOptRegion;
		Rect& parentCalculatedRegion = parentComp->aCalculatedRegion;
		Rect& parentVisibleRegion = parentComp->aVisibleRegion;
				
		// Running x and y
		aCalculatedRegion.aX = parentCalculatedRegion.aX + compRect.aX;
		aCalculatedRegion.aY = parentCalculatedRegion.aY + compRect.aY;
		
		// Reduce the size based on parent x, y
		aCalculatedRegion.aWidth = compRect.aWidth + (parentRect.aX < 0 ? (max(0, compRect.aX) + parentRect.aX) : 0.0);
		aCalculatedRegion.aHeight = compRect.aHeight + (parentRect.aY < 0 ? (max(0, compRect.aY) + parentRect.aY) : 0.0);

		// Account for negative x, y of this
		aCalculatedRegion.aWidth += compRect.aX < 0 ? compRect.aX : 0.0;
		aCalculatedRegion.aHeight += compRect.aY < 0 ? compRect.aY : 0.0;
		
		// Account for larger than parent
		aCalculatedRegion.aWidth = min(aCalculatedRegion.aWidth, parentCalculatedRegion.aWidth);
		aCalculatedRegion.aHeight = min(aCalculatedRegion.aHeight, parentCalculatedRegion.aHeight);

		// Account for positive shift
		aCalculatedRegion.aWidth -= (sX = (compRect.aX + aCalculatedRegion.aWidth)) > parentCalculatedRegion.aWidth ? (sX - parentCalculatedRegion.aWidth) : 0.0;
		aCalculatedRegion.aHeight -= (sY = (compRect.aY + aCalculatedRegion.aHeight)) > parentCalculatedRegion.aHeight ? (sY - parentCalculatedRegion.aHeight) : 0.0;
		
		// Set the visible x and y based on previous
		aVisibleRegion.aX = parentVisibleRegion.aX + max(0, min(aCalculatedRegion.aX, compRect.aX));
		aVisibleRegion.aY = parentVisibleRegion.aY + max(0, min(aCalculatedRegion.aY, compRect.aY));

		// Set the region based on if it is even visible
		aVisibleRegion.aWidth = (aCalculatedRegion.aX + compRect.aWidth) >= 0 ? aCalculatedRegion.aWidth : 0.0;
		aVisibleRegion.aHeight = (aCalculatedRegion.aY + compRect.aHeight) >= 0 ? aCalculatedRegion.aHeight : 0.0;
	}

	aValidatedContents = true;
}

void Component::setBounds(float xX, float xY, float xWidth, float xHeight)
{
	aOptRegion.aWidth = xWidth;
	aOptRegion.aHeight = xHeight;
	aOptRegion.aX = xX;
	aOptRegion.aY = xY;

	aOptBackgroundRegion.aWidth = xWidth;
	aOptBackgroundRegion.aHeight = xHeight;

	invalidate();
}

LPCWSTR Component::getClass()
{
	return L"Camera";
}

LPCWSTR Component::toString()
{
	return L"Camera";
}

HRESULT Component::initialize()
{
	return S_OK;
}