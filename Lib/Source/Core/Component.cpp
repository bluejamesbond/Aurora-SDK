
#include "../../../include/Core/ExtLibs.h"
#include "../../../include/Core/Component.h"
#include "../../../include/Core/AbstractFrame.h"

using namespace A2D;

Component::Component() :
    m_forcedBounds(false),
    m_parent(NULL),
    m_pipeline(NULL),
	m_id(rand()),
    m_componentManager(NULL),
    m_focused(false),
    m_focusable(true),
    m_nextCompListener(NULL),
	m_prevCompListener(NULL),
	m_activeInterpolations(false),
	m_componentTreeValidationRequest(false),
	m_calculatedRowIndex(0),
	m_calculatedColumnIndex(0),
	m_previousCalculatedRowIndex(0),
	m_previousCalculatedColumnIndex(0),
	m_positionAnimationXY(NULL),
	m_eventQueue(NULL),
	m_depth(0),
	m_scrollTop(0),
	m_scrolling(false),
	m_scrollLeft(0),
	m_cachedAnimationPositionXY(Animator::COMPONENT_BOUNDS_XY, Easing::OUT_CIRC, 0, 0, 800, NULL, NULL, NULL)
{
	m_styleSet.m_visibleRegion = &m_visibleRegion;
	m_styleSet.m_region = &m_region;
	m_styleSet.m_subRegion = &m_subRegion;
	m_styleSet.m_subBordersRegion = &m_subBordersRegion;
	m_styleSet.m_id = &m_id;

	m_styleSet.markBorderColorsAsDirty();
	m_styleSet.markBackgroundAsDirty();
}

Component::~Component(){}

void Component::paintComponentBorder(){}

void Component::interpolate()
{
	OrderedList<A2DINTERPOLATORFLOAT*>::Node<A2DINTERPOLATORFLOAT*> * node = m_interpolators._head();
	double currentTime = nanotime__;

	while (node->value)
	{
		A2DINTERPOLATORFLOAT * interpolator = node->value;
		Callable * callable = interpolator->m_callable;
		float duration = SFLOAT((currentTime - interpolator->m_startTime) * 1000.0f);

		// Save the next node
		node = node->right;
				
		// Remove the node
		if (duration > interpolator->m_period)
		{
			// Force end 
			switch (interpolator->m_mode)
			{
				case A2DINTERPOLATORFLOAT::Mode::FOUR_PARAMETERS:{	
					(this->*(*interpolator->m_interpolatable_d))(interpolator->m_start_a + interpolator->m_range_a, 
																 interpolator->m_start_b + interpolator->m_range_b, 
																 interpolator->m_start_c + interpolator->m_range_c, 
																 interpolator->m_start_d + interpolator->m_range_d);
					break;
				}
				case A2DINTERPOLATORFLOAT::Mode::THREE_PARAMETERS: {
					(this->*(*interpolator->m_interpolatable_c))(interpolator->m_start_a + interpolator->m_range_a, 
																 interpolator->m_start_b + interpolator->m_range_b, 
																 interpolator->m_start_c + interpolator->m_range_c);
					break;
				}
				case A2DINTERPOLATORFLOAT::Mode::TWO_PARAMETERS:{	
					(this->*(*interpolator->m_interpolatable_b))(interpolator->m_start_a + interpolator->m_range_a,
															     interpolator->m_start_b + interpolator->m_range_b);
					break;
				}
				case A2DINTERPOLATORFLOAT::Mode::ONE_PARAMETER:{	
					(this->*(*interpolator->m_interpolatable))(interpolator->m_start_a + interpolator->m_range_a);
					break;
				}
			}

			// Execute callback
			if (callable)
			{
				callable->callback(interpolator->m_arg);
			}
			
			// Remove request
			Animator::stop(*this, &interpolator->m_removeTicket);
		}

		// OR Update the value
		else
		{
			float interpolated_a,
				  interpolated_b,
				  interpolated_c,
				  interpolated_d,
				  period = interpolator->m_period;

			TWEEN * tween = interpolator->m_tween;

			switch (interpolator->m_mode)
			{
				case A2DINTERPOLATORFLOAT::Mode::FOUR_PARAMETERS : interpolated_d = (*tween)(duration, interpolator->m_start_d, interpolator->m_range_d, period);
				case A2DINTERPOLATORFLOAT::Mode::THREE_PARAMETERS: interpolated_c = (*tween)(duration, interpolator->m_start_c, interpolator->m_range_c, period);
				case A2DINTERPOLATORFLOAT::Mode::TWO_PARAMETERS:   interpolated_b = (*tween)(duration, interpolator->m_start_b, interpolator->m_range_b, period);
				case A2DINTERPOLATORFLOAT::Mode::ONE_PARAMETER:    interpolated_a = (*tween)(duration, interpolator->m_start_a, interpolator->m_range_a, period);
			}

			switch (interpolator->m_mode)
			{
				case A2DINTERPOLATORFLOAT::Mode::FOUR_PARAMETERS:{
					(this->*(*interpolator->m_interpolatable_d))(interpolated_a, 
																 interpolated_b, 
																 interpolated_c, 
																 interpolated_d);
					break;
				}
				case A2DINTERPOLATORFLOAT::Mode::THREE_PARAMETERS:{
					(this->*(*interpolator->m_interpolatable_c))(interpolated_a, 
																 interpolated_b, 
																 interpolated_c);
					break;
				}
				case A2DINTERPOLATORFLOAT::Mode::TWO_PARAMETERS:{
					(this->*(*interpolator->m_interpolatable_b))(interpolated_a, 
																 interpolated_b);
					break;
				}
				case A2DINTERPOLATORFLOAT::Mode::ONE_PARAMETER:{
					(this->*(*interpolator->m_interpolatable))(interpolated_a);
					break;
				}
			}

		}
	}

	// Remaining interpolators?
	if (m_interpolators.size() == 0)
	{
		m_activeInterpolations = false;

		#ifdef A2D_DE__			
		SYSOUT_F("[Component] [ComponentId: 0x%X] Turning off interpolators.", m_id);
		#endif // A2D_DE__
	}
}

Component& Component::getParent()
{
    return *m_parent;
}

void Component::setId(int x_id)
{
	m_id = x_id;
}

int Component::getDepth()
{
	return m_depth;
}

AbstractFrame& Component::getFrame()
{
    return *m_frame;
}

void Component::setGraphics(Graphics& xGraphics)
{
    m_graphics = &xGraphics;
}

Graphics& Component::getGraphics()
{
    return *m_graphics;
}

void Component::setDepth(int xDepth)
{
	m_styleSet.m_depth = (A2D_MAX_Z_DEPTH - SFLOAT(m_depth = xDepth)) / A2D_MAX_Z_DEPTH;
	
	m_styleSet.markDepthAsDirty();
}

void Component::setFrame(AbstractFrame& xFrame)
{
    m_frame = &xFrame;
}

void Component::setComponentManager(ComponentManager& x_componentManager)
{
	m_componentManager = &x_componentManager;
}

void Component::setParent(Component& xParent)
{
    m_parent = &xParent;
}

void Component::setEventQueue(AbstractEventQueue& x_eventQueue)
{
	m_eventQueue = &x_eventQueue;
}

Rect Component::getBounds()
{
    return m_region;
}

Rect * Component::getBoundsAsPtr()
{
    return &m_region;
}

Rect * Component::getVisibleRegion()
{
    return &m_visibleRegion;
}

void Component::add(Component& xContainer)
{
    m_children.push_back(&xContainer, NULL);
}

void Component::remove(Component& xContainer)
{
	// FIXME Use remove_request
    m_children.remove(&xContainer);
}

void Component::invalidate()
{
    m_validatedContents = false;
}

void Component::revalidate()
{
    validate();
}

void Component::validated()
{
    m_validatedContents = true;
}

void Component::validate()
{
    Rect& region = m_region;
	bool hasParent = m_parent != NULL;

	if (!m_styleSet.m_visible)
    {
        m_validatedContents = true;
        return;
    }
	
	if (!hasParent)
	{
		m_visibleRegion = m_calculatedRegion = 
					{ max__(0.0f, region.m_x), 
					  max__(0.0f, region.m_y), 
					  max__(0.0f, region.m_width), 
					  max__(0.0f, region.m_height) };
	}
    else
    {
		// Create shifts
		m_calculatedRegion = { m_parent->m_calculatedRegion.m_x + region.m_x,
							   m_parent->m_calculatedRegion.m_y + region.m_y,
							   region.m_width,
							   region.m_height };
		
		A2DPIXELDISTANCESETUINT4& borderWidths = m_styleSet.m_borders.m_precalculatedBorderWidths;

		// Applying constraints
		m_visibleRegion = Math::intersect(m_parent->m_visibleRegion, m_calculatedRegion);
		m_subRegion = Math::subtract(m_visibleRegion, m_calculatedRegion);
		m_subBordersRegion = Math::subtract(m_parent->m_visibleRegion,  { m_calculatedRegion.m_x - borderWidths.m_left,
																		  m_calculatedRegion.m_y - borderWidths.m_top,
																		  m_calculatedRegion.m_width,
																		  m_calculatedRegion.m_height });

		if (m_visibleRegion.m_height != m_previousVisibleDimensions.m_height ||
			m_visibleRegion.m_width != m_previousVisibleDimensions.m_width)
		{
			// FIXME Use SSE2 Acceleration
			m_previousVisibleDimensions.m_width = m_visibleRegion.m_width;
			m_previousVisibleDimensions.m_height = m_visibleRegion.m_height;

			// Request the validation of the components
			m_componentTreeValidationRequest = true;

			// Mark background as dirty
			m_styleSet.markBackgroundAsDirty();

			#ifdef A2D_DE__			
			SYSOUT_F("[Component] [ComponentId: 0x%X] Requesting background update.", m_id);
			#endif // A2D_DE__
		}
    }

    CascadingLayout::doLayout(*this);
	
	m_validatedContents = true;
	m_componentTreeValidationRequest = false;

	m_styleSet.markVisibleRegionAsDirty();
}

void Component::forceBounds(bool xForce)
{
    m_forcedBounds = xForce;
}

void Component::setSize(Style::Units xWidthUnits, float xWidth, Style::Units xHeightUnits, float xHeight)
{
	A2DDISTANCESET2& size = m_styleSet.m_size;

	size.m_widthUnits = xWidthUnits;
	size.m_heightUnits = xHeightUnits;
	size.m_width = xWidth;
	size.m_height = xHeight;

	m_validatedContents = false;
}

void Component::setWidth(float x_width)
{
	m_styleSet.m_size.m_width = x_width;

	m_parent->m_componentTreeValidationRequest = true;
}

void Component::setWidthUnits(Style::Units x_units)
{
	m_styleSet.m_size.m_widthUnits = x_units;

	m_parent->m_componentTreeValidationRequest = true;
}

void Component::setHeight(float x_height)
{
	m_styleSet.m_size.m_height = x_height;

	m_parent->m_componentTreeValidationRequest = true;
}

void Component::setHeightUnits(Style::Units x_units)
{
	m_styleSet.m_size.m_widthUnits = x_units;

	m_parent->m_componentTreeValidationRequest = true;
}

void Component::setDisplay(Style::Display xDisplay)
{
	m_styleSet.m_display = xDisplay;

	m_validatedContents = false;
}

void Component::setMargins(Style::Units xLeftUnits, float xLeft, Style::Units xTopUnits, float xTop, Style::Units xRightUnits, float xRight, Style::Units xBottomUnits, float xBottom)
{
	A2DDISTANCESET4& margins = m_styleSet.m_margins;

	margins.m_leftUnits = xLeftUnits;
	margins.m_topUnits = xTopUnits;
	margins.m_rightUnits = xRightUnits;
	margins.m_bottomUnits = xBottomUnits;

	margins.m_left = xLeft;
	margins.m_top = xTop;
	margins.m_bottom = xBottom;
	margins.m_right = xRight;

	m_validatedContents = false;
}

void Component::setPositioning(Style::Units xLeftUnits, float xLeft, Style::Units xTopUnits, float xTop, Style::Units xRightUnits, float xRight, Style::Units xBottomUnits, float xBottom)
{
	A2DDISTANCESET4& positioning = m_styleSet.m_positioning;

	positioning.m_leftUnits = xLeftUnits;
	positioning.m_topUnits = xTopUnits;
	positioning.m_rightUnits = xRightUnits;
	positioning.m_bottomUnits = xBottomUnits;

	positioning.m_left = xLeft;
	positioning.m_top = xTop;
	positioning.m_bottom = xBottom;
	positioning.m_right = xRight;

	m_validatedContents = false;
}

void Component::setPadding(Style::Units xLeftUnits, float xLeft, Style::Units xTopUnits, float xTop, Style::Units xRightUnits, float xRight, Style::Units xBottomUnits, float xBottom)
{
	A2DDISTANCESET4& padding = m_styleSet.m_padding;

	padding.m_leftUnits = xLeftUnits;
	padding.m_topUnits = xTopUnits;
	padding.m_rightUnits = xRightUnits;
	padding.m_bottomUnits = xBottomUnits;

	padding.m_left = xLeft;
	padding.m_top = xTop;
	padding.m_bottom = xBottom;
	padding.m_right = xRight;

	m_validatedContents = false;
}

void Component::setPosition(Style::Position xPosition)
{
	m_styleSet.m_position = xPosition;

	m_validatedContents = false;
}

STATUS Component::initialize()
{
	m_graphics->resetDrawable(m_styleSet.m_drawable);

    return STATUS_OK;
}

void Component::paintComponent()
{	
    Graphics& graphics = *m_graphics;

	graphics.drawComponent(&m_pipeline, m_styleSet);
}

void Component::update()
{
    Graphics& graphics = *m_graphics;
	
	// If Component is not visible return
	if (!m_styleSet.m_visible)
	{
		return;
	}

	// Interpolate the options
	if (m_activeInterpolations)
	{
		interpolate();
	}

	// Update the visible region of the component
    if (!m_validatedContents)
    {
        validate();
    }
	// Update the location and revalidate
	else if (m_componentTreeValidationRequest)
	{
		CascadingLayout::doLayout(*this);

		m_componentTreeValidationRequest = false;
	}

	// Set the graphics clip
	graphics.setClip(&m_visibleRegion, m_styleSet.m_depth);

    // Render the current component
    paintComponent();

    // Force region
	graphics.setClip(&m_visibleRegion, m_styleSet.m_depth);

    // Render the currect component border
    paintComponentBorder();
}

STATUS Component::requestFocus()
{
    // Also it's broken, as aFrame is not initialized.
    if (m_focusable && !m_focused)
    {
        FocusEvent& focusRequest = *new FocusEvent(this, FocusEvent::FOCUS_GAINED);
        Toolkit::getSystemEventQueue(m_frame->id())->processFocusEvent(&focusRequest);
    }
    return STATUS_OK;
}

void Component::setFocusable(bool xFocusable)
{
    m_focusable = xFocusable;
}

Rect * Component::getEventRegion()
{
    return &m_visibleRegion;
}

STATUS Component::addMouseListener(MouseListener * xListener)
{
	if (m_eventQueue)
    {
        // Add depth manually
		STATUS status = ComponentEventSource::addMouseListener(xListener);

        if (xListener)
        {
			m_eventQueue->addEventDepthTracker(this, abs__(m_depth));
        }
        else
        {
			m_eventQueue->removeEventDepthTracker(this, abs__(m_depth + 1));
        }

		return status;
    }

    return ComponentEventSource::addMouseListener(xListener);
}

STATUS Component::addMouseMotionListener(MouseMotionListener * xListener)
{
    if (m_eventQueue)
    {
        // Add depth manually
		STATUS status = ComponentEventSource::addMouseMotionListener(xListener);

        if (xListener)
        {
			m_eventQueue->addEventDepthTracker(this, abs__(m_depth));
        }
        else
        {
			m_eventQueue->removeEventDepthTracker(this, abs__(m_depth + 1));
        }

		return status;
    }

    return ComponentEventSource::addMouseMotionListener(xListener);
}

STATUS Component::addFocusListener(FocusListener * xListener)
{
	if (m_eventQueue)
    {
        // Add depth manually
		STATUS status = ComponentEventSource::addFocusListener(xListener);

        if (xListener)
        {
			m_eventQueue->addEventDepthTracker(this, abs__(m_depth));
        }
        else
        {
			m_eventQueue->removeEventDepthTracker(this, abs__(m_depth + 1));
        }

		return status;
    }

    return ComponentEventSource::addFocusListener(xListener);
}

STATUS Component::addActionListener(ActionListener * xListener)
{
	if (m_eventQueue)
    {
        // Add depth manually
		STATUS hr = ComponentEventSource::addActionListener(xListener);

        if (xListener != NULL)
        {
			m_eventQueue->addEventDepthTracker(this, abs__(m_depth));
        }
        else
        {
			m_eventQueue->removeEventDepthTracker(this, abs__(m_depth + 1));
        }

        return hr;
    }

    return ComponentEventSource::addActionListener(xListener);
}

void Component::setBackgroundImage(wchar_t* x_src)
{ 
	m_styleSet.m_drawable.setSource(x_src);

	m_graphics->bindDrawable(m_styleSet.m_drawable);

	m_styleSet.markBackgroundAsDirty();
}

void Component::setBackgroundPaint(Paint& xOptPaint)
{ 
	Paint::from(m_styleSet.m_backgroundPaint, xOptPaint);

	m_styleSet.markBackgroundAsDirty();
};

void Component::setBorderWidths(Style::Units xLeftUnits, float xLeft, Style::Units xTopUnits, float xTop, Style::Units xRightUnits, float xRight, Style::Units xBottomUnits, float xBottom)
{
	A2DDISTANCESET4& bordersWidths = m_styleSet.m_borders.m_borderWidths;

	bordersWidths.m_leftUnits = xLeftUnits;
	bordersWidths.m_topUnits = xTopUnits;
	bordersWidths.m_rightUnits = xRightUnits;
	bordersWidths.m_bottomUnits = xBottomUnits;

	bordersWidths.m_left = xLeft;
	bordersWidths.m_top = xTop;
	bordersWidths.m_bottom = xBottom;
	bordersWidths.m_right = xRight;

	m_styleSet.markBorderWidthsAsDirty();
}

void Component::setOpacity(float x_opacity)
{
	m_styleSet.m_opacity = x_opacity;

	m_styleSet.markOpacityAsDirty();
}

void Component::setBorderRadii(Style::Units xLeftUnits, float xLeft, Style::Units xTopUnits, float xTop, Style::Units xRightUnits, float xRight, Style::Units xBottomUnits, float xBottom)
{
	A2DDISTANCESET4& borderRadii = m_styleSet.m_borderRadii;

	borderRadii.m_leftUnits = xLeftUnits;
	borderRadii.m_topUnits = xTopUnits;
	borderRadii.m_rightUnits = xRightUnits;
	borderRadii.m_bottomUnits = xBottomUnits;

	borderRadii.m_left = xLeft;
	borderRadii.m_top = xTop;
	borderRadii.m_bottom = xBottom;
	borderRadii.m_right = xRight;

	m_styleSet.markBorderRadiiAsDirty();
}

void Component::setBorderRadiiTopLeft(float x_value)
{
	A2DDISTANCESET4& borderRadii = m_styleSet.m_borderRadii;
	A2DPIXELDISTANCESETUINT4& precalculatedBorderRadii = m_styleSet.m_precalculatedBorderRadii;

	unsigned int width = m_styleSet.m_precalculatedSize.m_width;
	unsigned int height = m_styleSet.m_precalculatedSize.m_height;

	unsigned int usableDim = min__(width, height);
	
	precalculatedBorderRadii.m_left = min__(SUINT(cvtsu2px__(borderRadii.m_leftUnits, (borderRadii.m_left = x_value), width)), usableDim / 2);

	m_styleSet.markBorderRadiiAsDirty();
}

void Component::setBorderRadiiTopLeftUnits(Style::Units x_units)
{
	m_styleSet.m_borderRadii.m_leftUnits = x_units;

	m_styleSet.markBorderRadiiAsDirty();
}

void Component::setBorderRadiiUnified(float x_value)
{
	A2DDISTANCESET4& borderRadii = m_styleSet.m_borderRadii;
	A2DPIXELDISTANCESETUINT4& precalculatedBorderRadii = m_styleSet.m_precalculatedBorderRadii;

	unsigned int width = m_styleSet.m_precalculatedSize.m_width;
	unsigned int height = m_styleSet.m_precalculatedSize.m_height;

	unsigned int usableDim = min__(width, height);

	precalculatedBorderRadii.m_left = min__(SUINT(cvtsu2px__(borderRadii.m_leftUnits, (borderRadii.m_left = x_value), width)), usableDim / 2);
	precalculatedBorderRadii.m_top = min__(SUINT(cvtsu2px__(borderRadii.m_topUnits, (borderRadii.m_top = x_value), height)), usableDim / 2);
	precalculatedBorderRadii.m_right = min__(SUINT(cvtsu2px__(borderRadii.m_bottomUnits, (borderRadii.m_bottom = x_value), height)), usableDim / 2);
	precalculatedBorderRadii.m_bottom = min__(SUINT(cvtsu2px__(borderRadii.m_bottomUnits, (borderRadii.m_right = x_value), width)), usableDim / 2);

	m_styleSet.markBorderRadiiAsDirty();
}

void Component::setBorderColor(unsigned int xLeft, unsigned int xTop, unsigned int xRight, unsigned int xBottom)
{
	A2DBORDERSET4& borders = m_styleSet.m_borders;

	Color3D::from(borders.m_leftColor, xLeft);
	Color3D::from(borders.m_topColor, xTop);
	Color3D::from(borders.m_rightColor, xRight);
	Color3D::from(borders.m_bottomColor, xBottom);

	m_validatedContents = false;
	m_styleSet.markBorderColorsAsDirty();
}

wchar_t* Component::getBackgroundImage() 
{ 
	return m_styleSet.m_drawable.getSource();
}

Paint& Component::getBackgroundPaint()
{ 
	return m_styleSet.m_backgroundPaint;
};

void Component::setBoundsX(float x_x)
{
	m_region.m_x = x_x;

	m_validatedContents = false;
	m_styleSet.markRequestRegionAsDirty();
}

float Component::getBoundsX()
{
	return m_region.m_x;
}

void Component::setBoundsY(float x_y)
{
	m_region.m_y = x_y;

	m_validatedContents = false;
	m_styleSet.markRequestRegionAsDirty();
}

void Component::setBoundsXY(float x_x, float x_y)
{
	m_region.m_x = x_x;
	m_region.m_y = x_y;
	
	m_validatedContents = false;
	m_styleSet.markRequestRegionAsDirty();
}

float Component::getBoundsY()
{
	return m_region.m_y;
}

void Component::setScroll(float x_left, float x_top)
{
	m_scrollLeft = x_left;
	m_scrollTop = x_top;

	m_componentTreeValidationRequest = m_validatedContents = false;

	m_styleSet.markRequestRegionAsDirty();
}

void Component::setScrollTop(float x_top)
{
	m_scrollTop = x_top;

	m_componentTreeValidationRequest = m_validatedContents = false;

	m_styleSet.markRequestRegionAsDirty();
}

void Component::captureScroll()
{
	m_scrolling = true;
}

void Component::releaseScroll()
{
	m_scrolling = false;
}

void Component::setBounds(float xX, float xY, float xWidth, float xHeight)
{
	// FIX-ME
	if ((m_previousCalculatedRowIndex != m_calculatedRowIndex ||
		m_previousCalculatedColumnIndex != m_calculatedColumnIndex) && 
		!m_parent->m_scrolling)
	{
		m_region.m_width = xWidth;
		m_region.m_height = xHeight;

		if (m_positionAnimationXY)
		{
			Animator::stop(*this, m_positionAnimationXY);
		}

		m_cachedAnimationPositionXY.toValues(xX, xY);

		m_positionAnimationXY = Animator::animate(*this, m_cachedAnimationPositionXY);

		m_previousCalculatedRowIndex = m_calculatedRowIndex;
		m_previousCalculatedColumnIndex = m_calculatedColumnIndex;
	}
	else /*if (!Animator::isAnimating(*this, m_positionAnimationXY))*/
	{
		m_region.m_width = xWidth;
		m_region.m_height = xHeight;
		m_region.m_x = xX;
		m_region.m_y = xY;

		m_backgroundRegion.m_width = xWidth;
		m_backgroundRegion.m_height = xHeight;

		if (m_region.m_height != m_previousDimensions.m_height ||
			m_region.m_width != m_previousDimensions.m_width)
		{
			// FIXME Use SSE2 Acceleration
			m_previousDimensions = { m_region.m_width, m_region.m_height };
			m_styleSet.markBackgroundAsDirty();
		}
	}

	m_validatedContents = false;
	m_styleSet.markRequestRegionAsDirty();
}