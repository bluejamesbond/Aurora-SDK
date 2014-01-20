
#include "../../../include/Core/ExtLibs.h"
#include "../../../include/Core/CascadingLayout.h"
#include "../../../include/Core/Component.h"

using namespace A2D;

void _fastcall CascadingLayout::doLayout(Component& x_component)
{
	int size = x_component.m_children.size();
	OrderedList<Component*>::Node<Component*> * start = x_component.m_children._head();

	float height, width, mX = 0, mY = 0, aX = 0, aY = 0,
		marginLeft, marginTop, marginRight, marginBottom, maxElementHeight = 0.0f, tempVerticalOffset,
		positionLeft, positionTop, positionRight, positionBottom;

	Style::Display display;
	Style::Position position;
	Rect& compRect = x_component.m_region;
	Component* component;

	bool firstElement = true;

	while (start && size--)
	{
		component = start->value;

		if (component->m_forcedBounds)
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

			component->m_visible = false;
			continue;
		}

		///*************************************** CACHE **********************************//
		display = component->m_display;
		position = component->m_position;

		Style::DISTANCESET2& size = component->m_size;

		width = cvtsu2px__(size.m_widthUnits, size.m_width, compRect.aWidth);
		height = cvtsu2px__(size.m_heightUnits, size.m_height, compRect.aHeight);

		Style::DISTANCESET4& margins = component->m_margins;

		marginLeft = cvtsu2px__(margins.m_leftUnits, margins.m_left, compRect.aWidth);
		marginTop = cvtsu2px__(margins.m_topUnits, margins.m_top, compRect.aHeight);
		marginBottom = cvtsu2px__(margins.m_bottomUnits, margins.m_bottom, compRect.aHeight);
		marginRight = cvtsu2px__(margins.m_rightUnits, margins.m_right, compRect.aWidth);
		
		Style::DISTANCESET4& positioning = component->m_positioning;

		positionLeft = cvtsu2px__(positioning.m_leftUnits, positioning.m_left, compRect.aWidth);
		positionTop = cvtsu2px__(positioning.m_topUnits, positioning.m_top, compRect.aHeight);
		positionBottom = cvtsu2px__(positioning.m_bottomUnits, positioning.m_bottom, compRect.aHeight);
		positionRight = cvtsu2px__(positioning.m_rightUnits, positioning.m_right, compRect.aWidth);
		///********************************************************************************//

		if (position == Style::RELATIVE_)
		{
			if (display == Style::INLINE_BLOCK)
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
			else/*if (display == Style::BLOCK)*/
			{
				mX += marginLeft;
				mY += marginTop;

				// try to move this elswhere
				firstElement = false;
			}
		}
		else/*if (position == Style::ABSOLUTE_)*/
		{
			aX = marginLeft;
			aY = marginTop;

			// left: auto | right: auto
			if (positionLeft == Style::AUTO && positionRight == Style::AUTO) {}
			// left: auto | right: X
			else if (positionLeft == Style::AUTO)
			{
				aX += (compRect.aWidth - width) - positionRight;
			}
			// left: X | right: auto
			else if (positionRight == Style::AUTO)
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
			if (positionTop == Style::AUTO && positionBottom == Style::AUTO) {}
			// top: auto | bottom: X
			else if (positionTop == Style::AUTO)
			{
				aY += (compRect.aWidth - width) - positionBottom;
			}
			// top: X | bottom: auto
			else if (positionBottom == Style::AUTO)
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

		if (position == Style::RELATIVE_)
		{
			/***********************************************/
			component->m_visible = true;
			component->setBounds(mX + positionLeft + positionRight, mY + positionTop + positionBottom, width, height);
			/***********************************************/

			if (display == Style::INLINE_BLOCK)
			{
				mX = mX + width + marginRight;
				// mY = mY;

				// Inline block uses last_height
				maxElementHeight = (tempVerticalOffset = marginBottom + height) > maxElementHeight ? tempVerticalOffset : maxElementHeight;
			}
			else/*if (display == Style::BLOCK)*/
			{
				mX = 0.0f;
				mY = mY + height + marginBottom;
			}
		}
		else/*if (position == Style::ABSOLUTE_)*/
		{
			/***********************************************/
			component->m_visible = true;
			component->setBounds(aX, aY, width, height);
			/***********************************************/
		}

		start = start->right;
	}
}
