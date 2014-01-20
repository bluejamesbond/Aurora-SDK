
#include "../../../include/Core/ExtLibs.h"
#include "../../../include/Core/CascadingLayout.h"
#include "../../../include/Core/Component.h"

using namespace A2D;

void _fastcall CascadingLayout::doLayout(Component& x_component)
{
	int size = x_component.m_children.size();
	OrderedList<Component*>::Node<Component*> * start = x_component.m_children._head();

	float height, width, mX = 0, mY = 0, aX = 0, aY = 0,
		maxElementHeight = 0.0f, tempVerticalOffset;

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

			component->m_styleSet.m_visible = false;
			continue;
		}

		// FIXME Update on resize only
		//------------------------------------------------------------------------------
		display = component->m_styleSet.m_display;
		position = component->m_styleSet.m_position;

		Style::DISTANCESET2& size = component->m_styleSet.m_size;

		width = cvtsu2px__(size.m_widthUnits, size.m_width, compRect.aWidth);
		height = cvtsu2px__(size.m_heightUnits, size.m_height, compRect.aHeight);

		Style::DISTANCESET4& margins = component->m_styleSet.m_margins;

		float marginLeft = cvtsu2px__(margins.m_leftUnits, margins.m_left, compRect.aWidth);
		float marginTop = cvtsu2px__(margins.m_topUnits, margins.m_top, compRect.aHeight);
		float marginBottom = cvtsu2px__(margins.m_bottomUnits, margins.m_bottom, compRect.aHeight);
		float marginRight = cvtsu2px__(margins.m_rightUnits, margins.m_right, compRect.aWidth);
		
		Style::DISTANCESET4& positioning = component->m_styleSet.m_positioning;

		float positionLeft = cvtsu2px__(positioning.m_leftUnits, positioning.m_left, compRect.aWidth);
		float positionTop = cvtsu2px__(positioning.m_topUnits, positioning.m_top, compRect.aHeight);
		float positionBottom = cvtsu2px__(positioning.m_bottomUnits, positioning.m_bottom, compRect.aHeight);
		float positionRight = cvtsu2px__(positioning.m_rightUnits, positioning.m_right, compRect.aWidth);

		Style::DISTANCESET4& borderWidths = component->m_styleSet.m_borders.m_borderWidths;
		Style::PIXELDISTANCESET4& borderWidthsPix = component->m_styleSet.m_borders.m_borderWidthsInPixels;

		borderWidthsPix.m_left = SUINT(cvtsu2px__(borderWidths.m_leftUnits, borderWidths.m_left, compRect.aWidth));
		borderWidthsPix.m_top = SUINT(cvtsu2px__(borderWidths.m_topUnits, borderWidths.m_top, compRect.aHeight));
		borderWidthsPix.m_right = SUINT(cvtsu2px__(borderWidths.m_bottomUnits, borderWidths.m_bottom, compRect.aHeight));
		borderWidthsPix.m_bottom = SUINT(cvtsu2px__(borderWidths.m_bottomUnits, borderWidths.m_right, compRect.aWidth));

		// Mark the border widths as dirty since
		// borderWidths are affected by validation
		// windowResize
		//------------------------------------------------------------------------------
		component->m_styleSet.markBorderWidthsAsDirty();

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
			// Update bounds
			//------------------------------------------------------------------------------
			component->m_styleSet.m_visible = true;
			component->setBounds(mX + positionLeft + positionRight, mY + positionTop + positionBottom, width, height);

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
			// Update bounds
			//------------------------------------------------------------------------------
			component->m_styleSet.m_visible = true;
			component->setBounds(aX, aY, width, height);
		}

		start = start->right;
	}
}
