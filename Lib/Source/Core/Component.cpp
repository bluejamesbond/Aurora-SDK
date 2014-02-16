
#include "../../../include/Core/ExtLibs.h"
#include "../../../include/Core/Component.h"
#include "../../../include/Core/AbstractFrame.h"

using namespace A2D;

A2DANIMATABLEFLOAT1 Component::ANIMATE_OPACITY(&Component::getOpacity, &Component::setOpacity, 0.0f, 1.0f);
A2DANIMATABLEFLOAT1 Component::ANIMATE_WIDTH(&Component::getWidth, &Component::setWidth, 0.0f, FLT_MAX);
A2DANIMATABLEFLOAT1 Component::ANIMATE_HEIGHT(&Component::getHeight, &Component::setHeight, 0.0f, FLT_MAX);
A2DANIMATABLEFLOAT1 Component::ANIMATE_BORDER_RADII_TOP_LEFT(&Component::getBorderRadiiTopLeft, &Component::setBorderRadiiTopLeft, 0.0f, FLT_MAX);
A2DANIMATABLEFLOAT1 Component::ANIMATE_BORDER_RADII_UNIFIED(&Component::getBorderRadiiUnified, &Component::setBorderRadiiUnified, 0.0f, FLT_MAX);
A2DANIMATABLEFLOAT1 Component::ANIMATE_BOUNDS_X(&Component::getBoundsX, &Component::setBoundsX, FLT_MIN, FLT_MAX);
A2DANIMATABLEFLOAT1 Component::ANIMATE_BOUNDS_Y(&Component::getBoundsY, &Component::setBoundsY, FLT_MIN, FLT_MAX);

Component::Component() :
    m_forcedBounds(false),
    m_parent(NULL),
    m_pipeline(NULL),
	m_id(rand()),
    m_componentManager(NULL),
    m_calculatedNegativeDeltaX(0.0f),
    m_calculatedNegativeDeltaY(0.0f),
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
	m_scrollTop(0.0f),
	m_scrollLeft(0.0f),
	m_cachedAnimationPositionXY(Animator::COMPONENT_BOUNDS_XY, Easing::OUT_QUAD, 0, 0, 200, NULL, NULL) 
{
	m_styleSet.m_visibleRegion = &m_visibleRegion;
	m_styleSet.m_region = &m_region;
	m_styleSet.m_cropDistance = &m_cropDistance;
	m_styleSet.m_id = &m_id;

	m_styleSet.markBorderColorsAsDirty();
	m_styleSet.markBackgroundAsDirty();
}

Component::~Component(){}

void Component::paintComponentBorder(){}

void Component::interpolate()
{
	OrderedList<A2DINTERPOLATORFLOAT*>::Node<A2DINTERPOLATORFLOAT*> * node = m_interpolators._head();
	int currentTime = kerneltimelp__;

	while (node->value)
	{
		A2DINTERPOLATORFLOAT * interpolator = node->value;
		float duration = SFLOAT(currentTime - interpolator->m_startTime);

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
			if (interpolator->m_callback)
			{
				(*(*interpolator->m_callback))(interpolator->m_arg);
			}
			
			// Remove request
			stop(&interpolator->m_removeTicket);
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

Animation Component::animate(A2DANIMATABLEFLOAT1& x_A2DANIMATABLEFLOAT1, TWEEN& x_tween, float x_to, int x_period, A2DCALLBACKVOID1 * x_callback, void * x_arg)
{
	float start_a = (this->*x_A2DANIMATABLEFLOAT1.m_accessor_a)();

	A2DINTERPOLATORFLOAT * interpolator = 
		new A2DINTERPOLATORFLOAT(&x_A2DANIMATABLEFLOAT1.m_mutator,
								  &x_tween,
								  kerneltimelp__,
								  start_a,
								  x_to - start_a,
								  SFLOAT(x_period),
								  x_callback,
								  x_arg);


	m_interpolators.push_back(interpolator, &interpolator->m_removeTicket);

	m_activeInterpolations = true;

	m_eventQueue->startedAnimation();

	#ifdef A2D_DE__			
	SYSOUT_F("[Component] [ComponentId: 0x%X] Adding interpolator.", m_id);
	#endif // A2D_DE__

	return &interpolator->m_removeTicket;
}

void Component::stop(Animation x_animation, bool x_arg)
{
	// BROKEN - FIXME!!!
	// NOTE: This is not really used in dev.

	if (x_arg)
	{
		// Get the data
		A2DINTERPOLATORFLOAT ** interpolator = m_interpolators.from_ticket(x_animation);
	
		if (!interpolator)
		{
			return;
		}

		// Execute callback
		if ((*interpolator)->m_callback)
		{
			(*(*interpolator)->m_callback)((*interpolator)->m_arg);
		}
	}

	m_interpolators.remove_request(x_animation);
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
		m_visibleRegion.aX = m_calculatedRegion.aX = max__(0.0f, region.aX);
		m_visibleRegion.aY = m_calculatedRegion.aY = max__(0.0f, region.aY);
		m_visibleRegion.aWidth = m_calculatedRegion.aWidth = max__(0.0f, region.aWidth);
		m_visibleRegion.aHeight = m_calculatedRegion.aHeight = max__(0.0f, region.aHeight);

        m_calculatedNegativeDeltaX = 0.0f;
        m_calculatedNegativeDeltaY = 0.0f;
    }
    else
    {
		m_calculatedRegion = { m_parent->m_calculatedRegion.aX + region.aX,
							   m_parent->m_calculatedRegion.aY + region.aY,
							   region.aWidth,
							   region.aHeight };

		m_visibleRegion = Math::intersect(m_parent->m_visibleRegion, m_calculatedRegion);

		if (m_visibleRegion.aHeight != m_previousVisibleDimensions.aHeight ||
			m_visibleRegion.aWidth != m_previousVisibleDimensions.aWidth)
		{
			// FIXME Use SSE2 Acceleration
			m_previousVisibleDimensions.aWidth = m_visibleRegion.aWidth;
			m_previousVisibleDimensions.aHeight = m_visibleRegion.aHeight;

			// Request the validation of the components
			m_componentTreeValidationRequest = true;

			// Mark background as dirty
			m_styleSet.markBackgroundAsDirty();

			#ifdef A2D_DE__			
			SYSOUT_F("[Component] [ComponentId: 0x%X] Requesting background update.", m_id);
			#endif // A2D_DE__
		}

		m_styleSet.m_scrollLeft = m_scrollLeft + m_parent->m_styleSet.m_scrollLeft;
		m_styleSet.m_scrollTop = m_scrollTop + m_parent->m_styleSet.m_scrollTop;
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
    return STATUS_OK;
}

void Component::paintComponent()
{	
    Graphics& graphics = *m_graphics;

	if (m_styleSet.m_backgroundSrc != NULL)
    {
		graphics.drawComponent(&m_pipeline, m_styleSet);
    }
    else
    {
		graphics.fillRect(&m_pipeline, m_backgroundRegion, m_styleSet.m_backgroundPaint);
    }
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

void Component::setBackgroundImage(wchar_t* xOptBackgroundImage)
{ 
	m_styleSet.m_backgroundSrc = xOptBackgroundImage;

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

LPCWSTR Component::getBackgroundImage() 
{ 
	return m_styleSet.m_backgroundSrc;
}

Paint& Component::getBackgroundPaint()
{ 
	return m_styleSet.m_backgroundPaint;
};

void Component::setBoundsX(float x_x)
{
	m_region.aX = x_x;

	m_validatedContents = false;
	m_styleSet.markRequestRegionAsDirty();
}

float Component::getBoundsX()
{
	return m_region.aX;
}

void Component::setBoundsY(float x_y)
{
	m_region.aY = x_y;

	m_validatedContents = false;
	m_styleSet.markRequestRegionAsDirty();
}

void Component::setBoundsXY(float x_x, float x_y)
{
	m_region.aX = x_x;
	m_region.aY = x_y;
	
	m_validatedContents = false;
	m_styleSet.markRequestRegionAsDirty();
}

float Component::getBoundsY()
{
	return m_region.aY;
}

void Component::setScroll(float x_left, float x_top)
{
	m_scrollLeft = x_left;
	m_scrollTop = x_top;

	m_validatedContents = false;

	m_styleSet.markRequestRegionAsDirty();
}