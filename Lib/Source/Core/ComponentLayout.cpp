
#include "../../../Include/Core/ExtLibs.h"
#include "../../../Include/Core/Component.h"

using namespace A2D;

#define UNITS(unit, value, range) ((unit == Styles::PERCENTAGE) ? FLOAT(range * (value / 100)) : (value)) 

void Component::applyCascadingStyleLayout()
{
	int size = aChildren.size();
	OrderedList<Component*>::Node<Component*> * start = aChildren._head();

	float height, width, mX = 0, mY = 0, aX = 0, aY = 0,
		marginLeft, marginTop, marginRight, marginBottom, maxElementHeight = 0.0f, tempVerticalOffset,
		positionLeft, positionTop, positionRight, positionBottom;

	Styles::Display display;
	Styles::Position position;
	Rect& compRect = aOptRegion;
	Component* component;
	
	bool firstElement = true;

	while (start && size--)
	{
		component = start->value;

		if (component->aForced)
		{
			start = start->right;
			continue;
		}
		
		///*************************************** CACHE **********************************//
		display = component->aDisplay;
		position = component->aPosition;

		width = UNITS(component->aSizeWidthUnits, component->aSizeWidth, compRect.aWidth);
		height = UNITS(component->aSizeHeightUnits, component->aSizeHeight, compRect.aHeight);

		marginLeft = UNITS(component->aMarginLeftUnits, component->aMarginLeft, compRect.aWidth);
		marginTop = UNITS(component->aMarginTopUnits, component->aMarginTop, compRect.aHeight);
		marginBottom = UNITS(component->aMarginBottomUnits, component->aMarginBottom, compRect.aHeight);
		marginRight = UNITS(component->aMarginRightUnits, component->aMarginRight, compRect.aWidth);

		positionLeft = UNITS(component->aPositionLeftUnits, component->aPositionLeft, compRect.aWidth);
		positionTop = UNITS(component->aPositionTopUnits, component->aPositionTop, compRect.aHeight);
		positionBottom = UNITS(component->aPositionBottomUnits, component->aPositionBottom, compRect.aHeight);
		positionRight = UNITS(component->aPositionRightUnits, component->aPositionRight, compRect.aWidth);
		///********************************************************************************//
		
		if (position == Styles::RELATIVE_)
		{
			if (display == Styles::INLINE_BLOCK)
			{
				if ((marginLeft + mX + width + marginRight) > (compRect.aWidth + FLT_ONE))
				{
					mX = marginLeft;
					mY = mY + maxElementHeight + marginTop;

					// new row
					maxElementHeight = 0.0;
				}
				else
				{
					mX = mX + marginLeft;
					mY = firstElement ? marginTop : mY;

					// try to move this elswhere
					firstElement = false;
				}
			}
			else/*if (display == Styles::BLOCK)*/
			{
				mX += marginLeft;
				mY += marginTop;
			}
		}
		else/*if (position == Styles::ABSOLUTE_)*/
		{
			aX = marginLeft; 
			aY = marginTop;

			// left: auto | right: auto
			if (positionLeft == Styles::AUTO && positionRight == Styles::AUTO) {}
			// left: auto | right: X
			else if (positionLeft == Styles::AUTO)
			{
				aX += (compRect.aWidth - width) - positionRight;
			}
			// left: X | right: auto
			else if (positionRight == Styles::AUTO)
			{
				aX += positionLeft;
			}
			// left: x | right: X
			else
			{
				aX += positionLeft;
				width = compRect.aWidth - (positionLeft + positionRight);
			}

			// top: auto | bottom: auto
			if (positionTop == Styles::AUTO && positionBottom == Styles::AUTO) {}
			// top: auto | bottom: X
			else if (positionTop == Styles::AUTO)
			{
				aY += (compRect.aWidth - width) - positionBottom;
			}
			// top: X | bottom: auto
			else if (positionBottom == Styles::AUTO)
			{
				aY += positionTop;
			}
			// top: x | bottom: X
			else
			{
				aY += positionTop;
				height = compRect.aHeight - (positionTop + positionBottom);
			}

		}

		if (position == Styles::RELATIVE_)
		{
			/***********************************************/
			component->setBounds(mX + positionLeft + positionRight, mY + positionTop + positionBottom, width, height);
			/***********************************************/

			if (display == Styles::INLINE_BLOCK)
			{				
				mX = mX + width + marginRight;
				// mY = mY;
				
				// Inline block uses last_height
				maxElementHeight = (tempVerticalOffset = marginBottom + height) > maxElementHeight ? tempVerticalOffset : maxElementHeight;
			}
			else/*if (display == Styles::BLOCK)*/
			{
				mX = FLT_ZERO;
				mY = mY + height + marginBottom;
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
