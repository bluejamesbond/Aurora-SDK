
#include "../../../include/Core/ExtLibs.h"
#include "../../../include/Core/CascadingLayout.h"
#include "../../../include/Core/Component.h"

#include <time.h>

using namespace A2D;

void _fastcall CascadingLayout::doLayout(Component& x_component)
{
	int size = x_component.aChildren.size();
	OrderedList<Component*>::Node<Component*> * start = x_component.aChildren._head();

	float height, width, mX = 0, mY = 0, aX = 0, aY = 0,
		marginLeft, marginTop, marginRight, marginBottom, maxElementHeight = 0.0f, tempVerticalOffset,
		positionLeft, positionTop, positionRight, positionBottom;

	Styles::Display display;
	Styles::Position position;
	Rect& compRect = x_component.aOptRegion;
	Component* component;

	bool firstElement = true;

	while (start && size--)
	{
		component = start->value;

		if (component->aForced)
		{
			#ifdef A2D_DE__			
			SYSOUT_STR("[CascadingLayout] Skipping calculations. Using forced bounds.");
			#endif // A2D_DE__

			start = start->right;
			continue;
		}
		else if (mY >= compRect.aHeight)
		{
			#ifdef A2D_DE__			
			SYSOUT_STR("[CascadingLayout] Skipping calculations. Component out of window.");
			#endif // A2D_DE__

			component->aVisible = false;
			continue;
		}

		///*************************************** CACHE **********************************//
		display = component->aDisplay;
		position = component->aPosition;

		width = cvtsu2px__(component->aSizeWidthUnits, component->aSizeWidth, compRect.aWidth);
		height = cvtsu2px__(component->aSizeHeightUnits, component->aSizeHeight, compRect.aHeight);

		marginLeft = cvtsu2px__(component->aMarginLeftUnits, component->aMarginLeft, compRect.aWidth);
		marginTop = cvtsu2px__(component->aMarginTopUnits, component->aMarginTop, compRect.aHeight);
		marginBottom = cvtsu2px__(component->aMarginBottomUnits, component->aMarginBottom, compRect.aHeight);
		marginRight = cvtsu2px__(component->aMarginRightUnits, component->aMarginRight, compRect.aWidth);

		positionLeft = cvtsu2px__(component->aPositionLeftUnits, component->aPositionLeft, compRect.aWidth);
		positionTop = cvtsu2px__(component->aPositionTopUnits, component->aPositionTop, compRect.aHeight);
		positionBottom = cvtsu2px__(component->aPositionBottomUnits, component->aPositionBottom, compRect.aHeight);
		positionRight = cvtsu2px__(component->aPositionRightUnits, component->aPositionRight, compRect.aWidth);
		///********************************************************************************//

		if (position == Styles::RELATIVE_)
		{
			if (display == Styles::INLINE_BLOCK)
			{
				if ((marginLeft + mX + width + marginRight) > (compRect.aWidth + 1.0f))
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

				// try to move this elswhere
				firstElement = false;
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
			component->aVisible = true;
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
				mX = 0.0f;
				mY = mY + height + marginBottom;
			}
		}
		else/*if (position == Styles::ABSOLUTE_)*/
		{
			/***********************************************/
			component->aVisible = true;
			component->setBounds(aX, aY, width, height);
			/***********************************************/
		}

		start = start->right;
	}
}
