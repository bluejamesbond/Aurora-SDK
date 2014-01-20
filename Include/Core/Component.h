///////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __COMPONENT_H__
#define __COMPONENT_H__

//+-----------------------------------------------------------------------------
//
//  Struct:
//      COMPONENT
//
//  Synopsis:
//      Differentiates which of the two possible arcs could match the given arc
//      parameters.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "../_A2DLinkers.h"

#include "OrderedList.h"
#include "ImageProperties.h"
#include "Pipeline.h"
#include "Rect.h"
#include "Paint.h"
#include "Style.h"
#include "CascadingLayout.h"
#include "BorderSet.h"
#include GRAPHICS__
#include "ComponentEventSource.h"

namespace A2D {

    ////////////////////////////////////////////////////////////////////////////////
    // FORWARD DECLARATIONS
    ////////////////////////////////////////////////////////////////////////////////

    class AbstractFrame;
    class Abstract;
    class Graphics;
    class Component;
    struct ImageProperties;
    class ComponentManager;

    ////////////////////////////////////////////////////////////////////////////////
    // DECLARATION
    ////////////////////////////////////////////////////////////////////////////////

    class Component : public ComponentEventSource
    {
        friend class ComponentManager;
        friend class CascadingLayout;
        friend class AbstractEventQueue;

    public:

        Component();
        ~Component();

    private:

        float                       m_depth;

        bool                        m_forcedBounds;
        bool                        m_focused;
        bool                        m_focusable;

        AbstractFrame*              m_frame;
        Component*                  m_parent;
        OrderedList<Component*>     m_children;
        ComponentManager*           m_componentManager;
        BorderSet                   m_borderSet;

        Component*                  m_nextCompListener;
        Component*                  m_prevCompListener;

    protected:

        bool                        m_visible;

        Pipeline*                   m_pipeline;
        Style::Background           m_backgroundStyle;

        Style::Display              m_displayStyle;
        Style::Position             m_positionStyle;

        Style::Units                m_sizeWidthUnitsStyle;
        Style::Units                m_sizeHeightUnitsStyle;     

        Style::Units                m_marginLeftUnitsStyle;
        Style::Units                m_marginTopUnitsStyle;
        Style::Units                m_marginBottomUnitsStyle;
        Style::Units                m_marginRightUnitsStyle;

        Style::Units                m_positionLeftUnitsStyle;
        Style::Units                m_positionTopUnitsStyle;
        Style::Units                m_positionBottomUnitsStyle;
        Style::Units                m_positionRightUnitsStyle;
        
        float                       m_sizeWidth;
        float                       m_sizeHeight;

        float                       m_marginLeft;
        float                       m_marginTop;
        float                       m_marginBottom;
        float                       m_marginRight;

        float                       m_positionLeft;
        float                       m_positionTop;
        float                       m_positionBottom;
        float                       m_positionRight;

        bool                        m_validatedContents;
        float                       m_calculatedNegativeDeltaX;
        float                       m_calculatedNegativeDeltaY;
        Graphics*                   m_graphics;
        Rect                        m_region;
        Rect                        m_backgroundRegion;
        Rect                        m_calculatedRegion;
        Rect                        m_visibleRegion;

        LPCWSTR                     m_backgroundSrc;          
        Paint                       m_backgroundPaint;        

    public:
        
        void                        setDoubleBuffered(bool xDoubleBuffer);
        void                        setBackgroundImage(LPCWSTR xOptBackgroundImage)     { m_backgroundSrc = xOptBackgroundImage;    };
        void                        setBackgroundPaint(Paint& xOptPaint)                { Paint::from(m_backgroundPaint, xOptPaint); };
        void                        setPosition(Style::Position xPosition);
        void                        setDisplay(Style::Display xDisplay);
        void                        setFloat(Style::Float xFloat);
        void                        setSize(Style::Units xWidthUnits, float xWidth, Style::Units xHeightUnits, float xHeight);
        void                        setMargins(Style::Units xLeftUnits, float xLeft, Style::Units xTopUnits, float xTop, Style::Units xRightUnits, float xRight, Style::Units xBottomUnits, float xBottom);
        void                        setPositioning(Style::Units xLeftUnits, float xLeft, Style::Units xTopUnits, float xTop, Style::Units xRightUnits, float xRight, Style::Units xBottomUnits, float xBottom);
        void                        setDepth(float xDepth);
        void                        setGraphics(Graphics& xGraphics);
        void                        setParent(Component& xComponent);
        void                        setFrame(AbstractFrame& xFrame);
        void                        setFocusable(bool xFocusable);
  
        STATUS                      requestFocus();
        STATUS                      addMouseListener(MouseListener * xListener);
        STATUS                      addMouseMotionListener(MouseMotionListener * xListener);
        STATUS                      addFocusListener(FocusListener * xListener);
        STATUS                      addActionListener(ActionListener * xListener);

        void                        update();
        void                        validate();
        void                        revalidate();
        void                        validated();
        void                        invalidate();
        void                        add(Component& xComponent);
        void                        remove(Component& xComponent);
        void                        forceBounds(bool xForce);
        virtual STATUS              initialize();  

        float                       getDepth();
        Graphics&                   getGraphics();
        Component&                  getParent();
        Component&                  getRoot();
        AbstractFrame&              getFrame();
        Rect*                       getVisibleRegion();
        Rect*                       getBoundsAsPtr();
        Rect                        getBounds();
        LPCWSTR                     getBackgroundImage()                                { return m_backgroundSrc; };
        Paint&                      getBackgroundPaint()                                { return m_backgroundPaint; };
 
        bool                        isDoubleBuffered();     

    protected:

        virtual void                paintComponent();
        virtual void                paintComponentBorder();
        virtual Rect*               getEventRegion();
        void                        setBounds(Rect& xRect);

    ////////////////////////////////////////////////////////////////////////////////
    // INLINE
    ////////////////////////////////////////////////////////////////////////////////

        inline void Component::setBounds(float xX, float xY, float xWidth, float xHeight)
        {
            m_region.aWidth = xWidth;
            m_region.aHeight = xHeight;
            m_region.aX = xX;
            m_region.aY = xY;

            m_backgroundRegion.aWidth = xWidth;
            m_backgroundRegion.aHeight = xHeight;

            m_validatedContents = false;
        }

    };
}
#endif
