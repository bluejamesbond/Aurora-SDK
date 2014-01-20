
#include "../../../include/Core/ExtLibs.h"
#include "../../../include/Core/CascadingLayout.h"
#include "../../../include/Core/Component.h"

using namespace A2D;

void _fastcall CascadingLayout::doLayout(Component& x_component)
{
	int size = x_component.m_children.size();
	OrderedList<Component*>::Node<Component*> * start = x_component.m_children._head();

	int
		compWidth = SINT(x_component.m_region.aWidth),
		compHeight = SINT(x_component.m_region.aHeight),
		mX = 0, 
		mY = 0, 
		aX = 0, 
		aY = 0,
		maxElementHeight = 0, 
		tempVerticalOffset,
		marginLeft,
		marginTop,
		marginBottom,
		marginRight,
		positionLeft,
		positionTop,
		positionBottom,
		positionRight;

	unsigned int
		width,
		height,
		borderLeft,
		borderTop,
		borderRight,
		borderBottom;

	Style::Display display;
	Style::Position position;
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
		else if (mY >= compHeight)
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
			
		if (x_component.m_componentTreeValidationRequest)
		{
			Style::DISTANCESET2& size = component->m_styleSet.m_size;
			Style::PIXELDISTANCESETUINT2& precalculatedSize = component->m_styleSet.m_precalculatedSize;

			width = precalculatedSize.m_width = SUINT(cvtsu2px__(size.m_widthUnits, size.m_width, compWidth));
			height = precalculatedSize.m_height = SUINT(cvtsu2px__(size.m_heightUnits, size.m_height, compHeight));

			Style::DISTANCESET4& margins = component->m_styleSet.m_margins;
			Style::PIXELDISTANCESETINT4& precalculatedMargins = component->m_styleSet.m_precalculatedMargins;

			marginLeft = precalculatedMargins.m_left = cvtsu2px__(margins.m_leftUnits, margins.m_left, compWidth);
			marginTop = precalculatedMargins.m_top = cvtsu2px__(margins.m_topUnits, margins.m_top, compHeight);
			marginRight = precalculatedMargins.m_right = cvtsu2px__(margins.m_rightUnits, margins.m_right, compWidth);
			marginBottom = precalculatedMargins.m_bottom = cvtsu2px__(margins.m_bottomUnits, margins.m_bottom, compHeight);

			Style::DISTANCESET4& positioning = component->m_styleSet.m_positioning;
			Style::PIXELDISTANCESETINT4& precalculatedPositioning = component->m_styleSet.m_precalculatedPositioning;

			positionLeft = precalculatedPositioning.m_left = cvtsu2px__(positioning.m_leftUnits, positioning.m_left, compWidth);
			positionTop = precalculatedPositioning.m_top = cvtsu2px__(positioning.m_topUnits, positioning.m_top, compHeight);
			positionRight = precalculatedPositioning.m_right = cvtsu2px__(positioning.m_rightUnits, positioning.m_right, compWidth);
			positionBottom = precalculatedPositioning.m_bottom = cvtsu2px__(positioning.m_bottomUnits, positioning.m_bottom, compHeight);

			Style::DISTANCESET4& borderWidths = component->m_styleSet.m_borders.m_borderWidths;
			Style::PIXELDISTANCESETUINT4& precalculatedBorderWidths = component->m_styleSet.m_borders.m_borderWidthsInPixels;

			borderLeft = precalculatedBorderWidths.m_left = SUINT(cvtsu2px__(borderWidths.m_leftUnits, borderWidths.m_left, compWidth));
			borderTop = precalculatedBorderWidths.m_top = SUINT(cvtsu2px__(borderWidths.m_topUnits, borderWidths.m_top, compHeight));
			borderRight = precalculatedBorderWidths.m_right = SUINT(cvtsu2px__(borderWidths.m_bottomUnits, borderWidths.m_bottom, compHeight));
			borderBottom = precalculatedBorderWidths.m_bottom = SUINT(cvtsu2px__(borderWidths.m_bottomUnits, borderWidths.m_right, compWidth));

			// Mark the border widths as dirty since
			// borderWidths are affected by validation
			// windowResize
			//------------------------------------------------------------------------------
			component->m_styleSet.markBorderWidthsAsDirty();

			// Request children to have full validation
			//------------------------------------------------------------------------------
			component->m_componentTreeValidationRequest = true;
		}
		else
		{
			Style::PIXELDISTANCESETUINT2& precalculatedSize = component->m_styleSet.m_precalculatedSize;

			width = precalculatedSize.m_width;
			height = precalculatedSize.m_height;

			Style::PIXELDISTANCESETINT4& precalculatedMargins = component->m_styleSet.m_precalculatedMargins;

			marginLeft = precalculatedMargins.m_left;
			marginTop = precalculatedMargins.m_top;
			marginRight = precalculatedMargins.m_right;
			marginBottom = precalculatedMargins.m_bottom;

			Style::PIXELDISTANCESETINT4& precalculatedPositioning = component->m_styleSet.m_precalculatedPositioning;

			positionLeft = precalculatedPositioning.m_left;
			positionTop = precalculatedPositioning.m_top;
			positionRight = precalculatedPositioning.m_right;
			positionBottom = precalculatedPositioning.m_bottom;

			Style::PIXELDISTANCESETUINT4& precalculatedBorderWidths = component->m_styleSet.m_borders.m_borderWidthsInPixels;

			borderLeft = precalculatedBorderWidths.m_left;
			borderTop = precalculatedBorderWidths.m_top;
			borderRight = precalculatedBorderWidths.m_right;
			borderBottom = precalculatedBorderWidths.m_bottom;
		}

		if (position == Style::RELATIVE_)
		{
			if (display == Style::INLINE_BLOCK)
			{
				if ((marginLeft + mX + width + marginRight) > (compWidth + 1.0f))
				{
					mX = marginLeft;
					mY = mY + maxElementHeight + marginTop;

					// new row
					maxElementHeight = 0;
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
				aX += (compWidth - width) - positionRight;
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
				width = compWidth - (positionLeft + positionRight);
			}

			// top: auto | bottom: auto
			if (positionTop == Style::AUTO && positionBottom == Style::AUTO) {}
			// top: auto | bottom: X
			else if (positionTop == Style::AUTO)
			{
				aY += (compWidth - width) - positionBottom;
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
				height = compHeight - (positionTop + positionBottom);
			}
		}

		if (position == Style::RELATIVE_)
		{
			// Update bounds
			//------------------------------------------------------------------------------
			component->m_styleSet.m_visible = true;
			component->setBounds(SFLOAT(mX + positionLeft + positionRight), 
								 SFLOAT(mY + positionTop + positionBottom), 
								 SFLOAT(width),
								 SFLOAT(height));

			if (display == Style::INLINE_BLOCK)
			{
				mX = mX + width + marginRight;
				// mY = mY;

				// Inline block uses last_height
				maxElementHeight = (tempVerticalOffset = marginBottom + height) > maxElementHeight ? tempVerticalOffset : maxElementHeight;
			}
			else/*if (display == Style::BLOCK)*/
			{
				mX = 0;
				mY = mY + height + marginBottom;
			}
		}
		else/*if (position == Style::ABSOLUTE_)*/
		{
			// Update bounds
			//------------------------------------------------------------------------------
			component->m_styleSet.m_visible = true;
			component->setBounds(SFLOAT(aX), SFLOAT(aY), SFLOAT(width), SFLOAT(height));
		}

		start = start->right;
	}
}
