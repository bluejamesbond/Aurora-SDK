
#include "../../../include/Core/ExtLibs.h"
#include "../../../include/Core/Component.h"
#include "../../../include/Core/AbstractFrame.h"

using namespace A2D;

Component::Component() :
    m_depth(0.0f),
    m_forcedBounds(false),
    m_visible(true),
    m_parent(NULL),
    m_pipeline(NULL),
    m_componentManager(NULL),
    m_displayStyle(Style::Display::BLOCK),
    m_positionStyle(Style::Position::RELATIVE_),
    m_sizeWidthUnitsStyle(Style::Units::PIXEL),
    m_sizeHeightUnitsStyle(Style::Units::PIXEL),
    m_marginLeftUnitsStyle(Style::Units::PIXEL),
    m_marginTopUnitsStyle(Style::Units::PIXEL),
    m_marginBottomUnitsStyle(Style::Units::PIXEL),
    m_marginRightUnitsStyle(Style::Units::PIXEL),
    m_positionLeftUnitsStyle(Style::Units::PIXEL),
    m_positionTopUnitsStyle(Style::Units::PIXEL),
    m_positionBottomUnitsStyle(Style::Units::PIXEL),
    m_positionRightUnitsStyle(Style::Units::PIXEL),
    m_sizeWidth(0.0f),
    m_sizeHeight(0.0f),
    m_marginLeft(0.0f),
    m_marginTop(0.0f),
    m_marginBottom(0.0f),
    m_marginRight(0.0f),
    m_positionLeft(0.0f),
    m_positionTop(0.0f),
    m_positionBottom(0.0f),
    m_positionRight(0.0f),
    m_backgroundSrc(NULL),
    m_calculatedNegativeDeltaX(0.0f),
    m_calculatedNegativeDeltaY(0.0f),
    m_focused(false),
    m_focusable(true),
    m_nextCompListener(NULL),
    m_prevCompListener(NULL)

{
}

Component::~Component(){}

void Component::paintComponentBorder(){}

Component& Component::getParent()
{
    return *m_parent;
}

float Component::getDepth()
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

void Component::setDepth( float xDepth)
{
    m_depth = xDepth;
}

void Component::setFrame(AbstractFrame& xFrame)
{
    m_frame = &xFrame;
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
    m_children.remove(&xContainer);
}

void Component::setBounds(Rect& xRect)
{
    m_region.aWidth = xRect.aWidth;
    m_region.aHeight = xRect.aHeight;
    m_region.aX = xRect.aX;
    m_region.aY = xRect.aY;

    m_backgroundRegion.aWidth = xRect.aWidth;
    m_backgroundRegion.aHeight = xRect.aHeight;

    invalidate();
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

    if (!m_visible)
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
        m_calculatedRegion.aX = parentCalculatedRegion.aX + compRect.aX;
        m_calculatedRegion.aY = parentCalculatedRegion.aY + compRect.aY;
        
        // Reduce the size based on parent x, y
        // Account for negative x, y of this
        // Accumulate negatives
        m_calculatedRegion.aWidth = compRect.aWidth + (m_calculatedNegativeDeltaX = parentComp->m_calculatedNegativeDeltaX + min__(0.0f, compRect.aX));
        m_calculatedRegion.aHeight = compRect.aHeight + (m_calculatedNegativeDeltaY = parentComp->m_calculatedNegativeDeltaY + min__(0.0f, compRect.aY));
        
        // Account for larger than parent
        m_calculatedRegion.aWidth = min__(m_calculatedRegion.aWidth, parentCalculatedRegion.aWidth);
        m_calculatedRegion.aHeight = min__(m_calculatedRegion.aHeight, parentCalculatedRegion.aHeight);

        // Account for positive shift
        m_calculatedRegion.aWidth -= SFLOAT((sX = (compRect.aX + m_calculatedRegion.aWidth)) > parentCalculatedRegion.aWidth ? (sX - parentCalculatedRegion.aWidth) : 0.0f);
        m_calculatedRegion.aHeight -= SFLOAT((sY = (compRect.aY + m_calculatedRegion.aHeight)) > parentCalculatedRegion.aHeight ? (sY - parentCalculatedRegion.aHeight) : 0.0f);
        
        // Account for negative height
        m_calculatedRegion.aWidth = max__(0.0f, m_calculatedRegion.aWidth);
        m_calculatedRegion.aHeight = max__(0.0f, m_calculatedRegion.aHeight);

        // Set the visible x and y based on previous
        m_visibleRegion.aX = parentVisibleRegion.aX + max__(0.0f, min__(m_calculatedRegion.aX, compRect.aX));
        m_visibleRegion.aY = parentVisibleRegion.aY + max__(0.0f, min__(m_calculatedRegion.aY, compRect.aY));

        // Set the region based on if it is even visible
        m_visibleRegion.aWidth = SFLOAT((m_calculatedRegion.aX + compRect.aWidth) >= 0.0f ? m_calculatedRegion.aWidth : 0.0f);
        m_visibleRegion.aHeight = SFLOAT((m_calculatedRegion.aY + compRect.aHeight) >= 0.0f ? m_calculatedRegion.aHeight : 0.0f);       
    }

    CascadingLayout::doLayout(*this);

    m_validatedContents = true;
}

void Component::forceBounds(bool xForce)
{
    m_forcedBounds = xForce;
}

void Component::setSize(Style::Units xWidthUnits, float xWidth, Style::Units xHeightUnits, float xHeight)
{
    m_sizeWidthUnitsStyle = xWidthUnits;
    m_sizeHeightUnitsStyle = xHeightUnits;

    m_sizeWidth = xWidth;
    m_sizeHeight = xHeight;
}

void Component::setDisplay(Style::Display xDisplay)
{
    m_displayStyle = xDisplay;
}

void Component::setMargins(Style::Units xLeftUnits, float xLeft, Style::Units xTopUnits, float xTop, Style::Units xRightUnits, float xRight, Style::Units xBottomUnits, float xBottom)
{
    m_marginLeftUnitsStyle = xLeftUnits;
    m_marginTopUnitsStyle = xTopUnits;
    m_marginBottomUnitsStyle = xRightUnits;
    m_marginRightUnitsStyle = xBottomUnits;

    m_marginLeft = xLeft;
    m_marginTop = xTop;
    m_marginBottom = xBottom;
    m_marginRight = xRight;
}

void Component::setPositioning(Style::Units xLeftUnits, float xLeft, Style::Units xTopUnits, float xTop, Style::Units xRightUnits, float xRight, Style::Units xBottomUnits, float xBottom)
{
    m_positionLeftUnitsStyle = xLeftUnits;
    m_positionTopUnitsStyle = xTopUnits;
    m_positionBottomUnitsStyle = xRightUnits;
    m_positionRightUnitsStyle = xBottomUnits;

    m_positionLeft = xLeft;
    m_positionTop = xTop;
    m_positionBottom = xBottom;
    m_positionRight = xRight;
}

void Component::setPosition(Style::Position xPosition)
{
    m_positionStyle = xPosition;
}

STATUS Component::initialize()
{
    return STATUS_OK;
}


void Component::paintComponent()
{
    if (!m_visible)
    {
        return;
    }

    Graphics& graphics = *m_graphics;

    if (m_backgroundSrc != NULL)
    {
        graphics.drawComponent(&m_pipeline, m_backgroundRegion, m_backgroundSrc, m_borderSet, m_backgroundPaint, m_backgroundStyle);
    }
    else
    {
        graphics.fillRect(&m_pipeline, m_backgroundRegion, m_backgroundPaint);
    }
}

void Component::update()
{
    Graphics& graphics = *m_graphics;

    if (!m_validatedContents)
    {
        validate();
    }

    graphics.setClip(&m_visibleRegion, m_depth);

    // Render the current component
    paintComponent();

    // Force region
    graphics.setClip(&m_visibleRegion, m_depth);

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
            eQ->addEventDepthTracker(this, abs__(m_depth));
        }
        else
        {
            eQ->removeEventDepthTracker(this, abs__(m_depth + 1.0f));
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
            Toolkit::getSystemEventQueue(m_componentManager->getWindow()->getFrame()->id())->addEventDepthTracker(this, abs__(m_depth));
        }
        else
        {
            eQ->removeEventDepthTracker(this, abs__(m_depth + 1.0f));
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
            Toolkit::getSystemEventQueue(m_componentManager->getWindow()->getFrame()->id())->addEventDepthTracker(this, abs__(m_depth));
        }
        else
        {
            eQ->removeEventDepthTracker(this, abs__(m_depth + 1));
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
            Toolkit::getSystemEventQueue(m_componentManager->getWindow()->getFrame()->id())->addEventDepthTracker(this, abs__(m_depth));
        }
        else
        {
            eQ->removeEventDepthTracker(this, abs__(m_depth + 1.0f));
        }
        return hr;
    }
    return ComponentEventSource::addActionListener(xListener);
}