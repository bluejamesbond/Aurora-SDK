
#include "../../include/ExtLibs.h"
#include "../../include/Component.h"
#include "../../include/Graphics.h"

using namespace A2D;

void Component::setBackground(LPCWSTR xOptBackgroundImage, int xOptBackroundPositionX,	int xOptBackroundPositionY,	
	int xOptBackroundSizeX,	int xOptBackroundSizeY,	int xOptBackgroundColor, int xOptBackgroundRepeat)
{
	aOptBackgroundSrc = xOptBackgroundImage;
	aOptBackgroundPosX = xOptBackroundPositionX;
	aOptBackgroundPosY = xOptBackroundPositionY;
	aOptBackgroundProps.aOptSizeX = xOptBackroundSizeX;
	aOptBackgroundProps.aOptSizeY = xOptBackroundSizeY;
	aOptBackgroundColor = xOptBackgroundColor;
	aOptBackgroundProps.aOptRepeat = xOptBackgroundRepeat;
};

void Component::paintComponent()
{
	Graphics& graphics = *aGraphics;

	if (aOptBackgroundSrc != NULL)
	{
		graphics.drawImage(&aPipeline, aOptBackgroundSrc, aOptBackgroundRegion, aOptBackgroundProps);
	}
}

void Component::update()
{
	Graphics& graphics = *aGraphics;

	graphics.setClip(&aCalculatedRegion);

	// Render the current component
	paintComponent();

	// Force region
	graphics.setClip(&aCalculatedRegion);

	// Render the currect component border
	paintComponentBorder();
}

void Component::paintComponentBorder(){}

Component& Component::getParent()
{
	return *aParentComp;
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
	aChildren.push_back(&xContainer);
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
	Component * parentComp = aParentComp;
	bool hasParent = parentComp != NULL;

	Rect& compRect = aOptRegion;
	Rect * parentRect = hasParent ? &parentComp->aOptRegion : NULL;
	Rect * parentGraphicsClip = hasParent ? &parentComp->aCalculatedRegion : NULL;

	aCalculatedRegion.aX = (hasParent ? parentGraphicsClip->aX : 0) + compRect.aX;
	aCalculatedRegion.aY = (hasParent ? parentGraphicsClip->aY : 0) + compRect.aY;
	aCalculatedRegion.aWidth = min(compRect.aWidth, (hasParent ? parentRect->aWidth : INT_MAX));
	aCalculatedRegion.aHeight = min(compRect.aHeight, (hasParent ? parentRect->aHeight : INT_MAX));

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