
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
		graphics.drawImage(&aPipeline, aOptBackgroundRegion, aOptBackgroundSrc, false);
	}
	else
	{
		graphics.fillRect(&aPipeline, aOptBackgroundRegion, aOptBackgroundPaint);
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

		aCalculatedNegativeDeltaX = 0.0;
		aCalculatedNegativeDeltaY = 0.0;
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
		// Account for negative x, y of this
		// Accumulate negatives
		aCalculatedRegion.aWidth = compRect.aWidth + (aCalculatedNegativeDeltaX = parentComp->aCalculatedNegativeDeltaX + min(FLT_ZERO, compRect.aX));
		aCalculatedRegion.aHeight = compRect.aHeight + (aCalculatedNegativeDeltaY = parentComp->aCalculatedNegativeDeltaY + min(FLT_ZERO, compRect.aY));
		
		// Account for larger than parent
		aCalculatedRegion.aWidth = min(aCalculatedRegion.aWidth, parentCalculatedRegion.aWidth);
		aCalculatedRegion.aHeight = min(aCalculatedRegion.aHeight, parentCalculatedRegion.aHeight);

		// Account for positive shift
		aCalculatedRegion.aWidth -= FLOAT((sX = (compRect.aX + aCalculatedRegion.aWidth)) > parentCalculatedRegion.aWidth ? (sX - parentCalculatedRegion.aWidth) : FLT_ZERO);
		aCalculatedRegion.aHeight -= FLOAT((sY = (compRect.aY + aCalculatedRegion.aHeight)) > parentCalculatedRegion.aHeight ? (sY - parentCalculatedRegion.aHeight) : FLT_ZERO);
		
		// Account for negative height
		aCalculatedRegion.aWidth = max(FLT_ZERO, aCalculatedRegion.aWidth);
		aCalculatedRegion.aHeight = max(FLT_ZERO, aCalculatedRegion.aHeight);

		// Set the visible x and y based on previous
		aVisibleRegion.aX = parentVisibleRegion.aX + max(FLT_ZERO, min(aCalculatedRegion.aX, compRect.aX));
		aVisibleRegion.aY = parentVisibleRegion.aY + max(FLT_ZERO, min(aCalculatedRegion.aY, compRect.aY));

		// Set the region based on if it is even visible
		aVisibleRegion.aWidth = FLOAT((aCalculatedRegion.aX + compRect.aWidth) >= FLT_ZERO ? aCalculatedRegion.aWidth : FLT_ZERO);
		aVisibleRegion.aHeight = FLOAT((aCalculatedRegion.aY + compRect.aHeight) >= FLT_ZERO ? aCalculatedRegion.aHeight : FLT_ZERO);		
	}

	applyCascadingStyleLayout();

	aValidatedContents = true;
}

void Component::forceBounds(bool xForce)
{
	aForced = xForce;
}

#define UNITS(unit, value, range) ((unit == Styles::PERCENTAGE) ? FLOAT(range * (value / 100)) : (value)) 

void Component::applyCascadingStyleLayout()
{
	int size = aChildren.size();	
	OrderedList<Component*>::Node<Component*> * start = aChildren._head();
	
	float height, width, rX = 0, rY = 0, aX = 0, aY = 0, 
		last_height = 0.0f, left, top, right, bottom;
	Styles::Display display;
	Styles::Position position;
	Rect& compRect = aOptRegion;
	Component* component;

	while (start && size--)
	{
		component = start->value;

		if (component->aForced)
		{
			start = start->right;
			continue;
		}

		// Get width and height based on children requirements
		display = component->aDisplay;
		position = component->aPosition;
		width = UNITS(component->aSizeWidthUnits, component->aSizeWidth, compRect.aWidth);
		height = UNITS(component->aSizeHeightUnits, component->aSizeHeight, compRect.aHeight);
		left = UNITS(component->aPositionLeftUnits, component->aPositionLeft, compRect.aWidth);
		top = UNITS(component->aPositionTopUnits, component->aPositionTop, compRect.aHeight);

		if (position == Styles::RELATIVE_)
		{
			if (display == Styles::INLINE_BLOCK)
			{
				if ((left + rX + width) > (compRect.aWidth + FLT_ONE))
				{
					rX = left;
					rY = rY + last_height + top;
				}
				else/*if (display == Styles::BLOCK)*/
				{
					rX = rX + left;
					rY = top;
				}
			}
			else/*if (display == Styles::BLOCK)*/
			{
				rX += left;
				rY += top;
			}
		}
		else/*if (position == Styles::ABSOLUTE_)*/
		{
			aX = UNITS(component->aPositionLeftUnits, component->aPositionLeft, compRect.aWidth);
			aY = UNITS(component->aPositionTopUnits, component->aPositionTop, compRect.aHeight);
		}

		if (position == Styles::RELATIVE_)
		{
			/***********************************************/
			component->setBounds(rX, rY, width, height);
			/***********************************************/

			if (display == Styles::INLINE_BLOCK)
			{
				// If beyound edge width
				if (rX + width >= compRect.aWidth)
				{
					rX = FLT_ZERO;
					rY = rY + height;
				}
				else
				{
					rX = rX + width;
					rY = rY;
				}

				// Inline block uses last_height
				last_height = height;
			}
			else/*if (display == Styles::BLOCK)*/
			{
				rX = FLT_ZERO;
				rY = rY + height;
			}
		}
		else/*if (position == Styles::ABSOLUTE_)*/
		{
			/***********************************************/
			component->setBounds(aX, aY, width, height);
			/***********************************************/
		}
		
		start = start->right;
	}
}

void Component::setSize(Styles::Units xWidthUnits, float xWidth, Styles::Units xHeightUnits, float xHeight)
{
	aSizeWidthUnits = xWidthUnits;
	aSizeHeightUnits = xHeightUnits;

	aSizeWidth = xWidth;
	aSizeHeight = xHeight;
}

void Component::setDisplay(Styles::Display xDisplay)
{
	aDisplay = xDisplay;
}

void Component::setPositioning(Styles::Units xLeftUnits, float xLeft, Styles::Units xTopUnits, float xTop, Styles::Units xRightUnits, float xRight, Styles::Units xBottomUnits, float xBottom)
{
	aPositionLeftUnits = xLeftUnits;
	aPositionTopUnits = xTopUnits;
	aPositionBottomUnits = xRightUnits;
	aPositionRightUnits = xBottomUnits;

	aPositionLeft = xLeft;
	aPositionTop = xTop;
	aPositionBottom = xBottom;
	aPositionRight = xRight;
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
