
#include "../../../include/Core/ExtLibs.h"
#include "../../../include/Core/Component.h"
#include "../../../include/Core/AbstractFrame.h"

using namespace A2D;

Component::Component() :
    m_forcedBounds(false),
    m_parent(NULL),
    m_pipeline(NULL),
    m_componentManager(NULL),
    m_calculatedNegativeDeltaX(0.0f),
    m_calculatedNegativeDeltaY(0.0f),
    m_focused(false),
    m_focusable(true),
    m_nextCompListener(NULL),
	m_prevCompListener(NULL),
	m_componentTreeValidationRequest(false)
{
	m_styleSet.m_visibleRegion = &m_visibleRegion;
	m_styleSet.m_region = &m_region;

	m_styleSet.markBorderColorsAsDirty();
	m_styleSet.markBackgroundAsDirty();
}

Component::~Component(){}

void Component::paintComponentBorder(){}

Component& Component::getParent()
{
    return *m_parent;
}

int Component::getDepth()
{
	return m_styleSet.m_depth;
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
	m_styleSet.m_depth = xDepth;

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
    Component * parentComp = m_parent;
    Rect& compRect = m_region;
    bool hasParent = parentComp != NULL;

	if (!m_styleSet.m_visible)
    {
        m_validatedContents = true;
        return;
    }

    if (!hasParent)
    {
        m_visibleRegion.aX = m_calculatedRegion.aX = max__(0.0f, compRect.aX);
        m_visibleRegion.aY = m_calculatedRegion.aY = max__(0.0f, compRect.aY);
        m_visibleRegion.aWidth = m_calculatedRegion.aWidth = max__(0.0f, compRect.aWidth);
        m_visibleRegion.aHeight = m_calculatedRegion.aHeight = max__(0.0f, compRect.aHeight);

        m_calculatedNegativeDeltaX = 0.0f;
        m_calculatedNegativeDeltaY = 0.0f;
    }
    else
    {
        float sX, sY;
        Rect& parentRect = parentComp->m_region;
        Rect& parentCalculatedRegion = parentComp->m_calculatedRegion;
        Rect& parentVisibleRegion = parentComp->m_visibleRegion;
                
        // Running x and y
		//------------------------------------------------------------------------------
        m_calculatedRegion.aX = parentCalculatedRegion.aX + compRect.aX;
        m_calculatedRegion.aY = parentCalculatedRegion.aY + compRect.aY;
        
        // Reduce the size based on parent x, y
        // Account for negative x, y of this
        // Accumulate negatives
		//------------------------------------------------------------------------------
        m_calculatedRegion.aWidth = compRect.aWidth + (m_calculatedNegativeDeltaX = parentComp->m_calculatedNegativeDeltaX + min__(0.0f, compRect.aX));
        m_calculatedRegion.aHeight = compRect.aHeight + (m_calculatedNegativeDeltaY = parentComp->m_calculatedNegativeDeltaY + min__(0.0f, compRect.aY));
        
        // Account for larger than parent
		//------------------------------------------------------------------------------
        m_calculatedRegion.aWidth = min__(m_calculatedRegion.aWidth, parentCalculatedRegion.aWidth);
        m_calculatedRegion.aHeight = min__(m_calculatedRegion.aHeight, parentCalculatedRegion.aHeight);

        // Account for positive shift
		//------------------------------------------------------------------------------
        m_calculatedRegion.aWidth -= SFLOAT((sX = (compRect.aX + m_calculatedRegion.aWidth)) > parentCalculatedRegion.aWidth ? (sX - parentCalculatedRegion.aWidth) : 0.0f);
        m_calculatedRegion.aHeight -= SFLOAT((sY = (compRect.aY + m_calculatedRegion.aHeight)) > parentCalculatedRegion.aHeight ? (sY - parentCalculatedRegion.aHeight) : 0.0f);
        
        // Account for negative height
		//------------------------------------------------------------------------------
        m_calculatedRegion.aWidth = max__(0.0f, m_calculatedRegion.aWidth);
        m_calculatedRegion.aHeight = max__(0.0f, m_calculatedRegion.aHeight);

        // Set the visible x and y based on previous
		//------------------------------------------------------------------------------
        m_visibleRegion.aX = parentVisibleRegion.aX + max__(0.0f, min__(m_calculatedRegion.aX, compRect.aX));
        m_visibleRegion.aY = parentVisibleRegion.aY + max__(0.0f, min__(m_calculatedRegion.aY, compRect.aY));

        // Set the region based on if it is even visible
		//------------------------------------------------------------------------------
        m_visibleRegion.aWidth = SFLOAT((m_calculatedRegion.aX + compRect.aWidth) >= 0.0f ? m_calculatedRegion.aWidth : 0.0f);
        m_visibleRegion.aHeight = SFLOAT((m_calculatedRegion.aY + compRect.aHeight) >= 0.0f ? m_calculatedRegion.aHeight : 0.0f); 	
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
	if (!m_styleSet.m_visible)
    {
        return;
    }

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

    if (!m_validatedContents)
    {
        validate();
    }

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
    if (m_componentManager != NULL)
    {
        // Add depth manually
        AbstractEventQueue * eQ = Toolkit::getSystemEventQueue(m_componentManager->getWindow()->getFrame()->id());
        STATUS hr = ComponentEventSource::addMouseListener(xListener);

        if (xListener != NULL)
        {
			eQ->addEventDepthTracker(this, abs__(m_styleSet.m_depth));
        }
        else
        {
			eQ->removeEventDepthTracker(this, abs__(m_styleSet.m_depth + 1.0f));
        }

        return hr;
    }

    return ComponentEventSource::addMouseListener(xListener);
}

STATUS Component::addMouseMotionListener(MouseMotionListener * xListener)
{
    if (m_componentManager != NULL)
    {
        // Add depth manually
        AbstractEventQueue * eQ = Toolkit::getSystemEventQueue(m_componentManager->getWindow()->getFrame()->id());
        STATUS hr = ComponentEventSource::addMouseMotionListener(xListener);

        if (xListener != NULL)
        {
			Toolkit::getSystemEventQueue(m_componentManager->getWindow()->getFrame()->id())->addEventDepthTracker(this, abs__(m_styleSet.m_depth));
        }
        else
        {
			eQ->removeEventDepthTracker(this, abs__(m_styleSet.m_depth + 1.0f));
        }

        return hr;
    }

    return ComponentEventSource::addMouseMotionListener(xListener);
}

STATUS Component::addFocusListener(FocusListener * xListener)
{
    if (m_componentManager != NULL)
    {
        // Add depth manually
        STATUS hr = ComponentEventSource::addFocusListener(xListener);
        AbstractEventQueue * eQ = Toolkit::getSystemEventQueue(m_componentManager->getWindow()->getFrame()->id());

        if (xListener != NULL)
        {
			Toolkit::getSystemEventQueue(m_componentManager->getWindow()->getFrame()->id())->addEventDepthTracker(this, abs__(m_styleSet.m_depth));
        }
        else
        {
			eQ->removeEventDepthTracker(this, abs__(m_styleSet.m_depth + 1.0f));
        }

        return hr;
    }

    return ComponentEventSource::addFocusListener(xListener);
}

STATUS Component::addActionListener(ActionListener * xListener)
{
    if (m_componentManager != NULL)
    {
        // Add depth manually
        AbstractEventQueue * eQ = Toolkit::getSystemEventQueue(m_componentManager->getWindow()->getFrame()->id());
        STATUS hr = ComponentEventSource::addActionListener(xListener);

        if (xListener != NULL)
        {
			Toolkit::getSystemEventQueue(m_componentManager->getWindow()->getFrame()->id())->addEventDepthTracker(this, abs__(m_styleSet.m_depth));
        }
        else
        {
			eQ->removeEventDepthTracker(this, abs__(m_styleSet.m_depth + 1.0f));
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

	m_validatedContents = false;
	m_styleSet.markBorderWidthsAsDirty();
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

