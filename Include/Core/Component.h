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
#include "CascadingLayout.h"
#include "Easing.h"
#include GRAPHICS__
#include "ComponentEventSource.h"
#include "A2DCOMPONENTRENDERSTYLESET.h"

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
	class Easing;
	
	// Typedef interpolatables
	typedef void (Component::*Interpolatable)(float);

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

		struct Interpolator
		{
			Tween m_tween;
			Interpolatable m_interpolatable;

			int m_startTime;

			float m_period;
			float m_range;
			float m_start;

			void * m_removeTicket;

			Interpolator() :
				m_range(0.0f),
				m_start(0.0f),
				m_period(0),
				m_startTime(0),
				m_removeTicket(NULL)
			{
			}
		};
		
		bool                        m_forcedBounds;
        bool                        m_focused;
        bool                        m_focusable;

        AbstractFrame*              m_frame;
        Component*                  m_parent;
		OrderedList<Component*>     m_children;
		OrderedList<Interpolator*>  m_interpolators;
        ComponentManager*           m_componentManager;

        Component*                  m_nextCompListener;
        Component*                  m_prevCompListener;
		
    protected:

		int							m_id;

		bool                        m_validatedContents;
		bool						m_activeInterpolations;
		bool						m_componentTreeValidationRequest;
		
        float                       m_calculatedNegativeDeltaX;
        float                       m_calculatedNegativeDeltaY;
		
		A2DCOMPONENTRENDERSTYLESET	m_styleSet;

		Rect                        m_region;
		Rect                        m_backgroundRegion;
        Rect                        m_calculatedRegion;
        Rect                        m_visibleRegion;
		Dims						m_previousVisibleDimensions;
		Dims						m_previousDimensions;


		Pipeline*                   m_pipeline;
		Graphics*                   m_graphics;    

    public:

		static Interpolatable		INTERPOLATE_OPACITY;
		
		void						animate(Interpolatable xInterpolatable, Tween x_tween, float x_start, float x_range, int x_period);
		void						setId(int x_id);
        void                        setDoubleBuffered(bool xDoubleBuffer);
		void                        setBackgroundImage(wchar_t* xOptBackgroundImage);
		void                        setBackgroundPaint(Paint& xOptPaint);
        void                        setPosition(Style::Position xPosition);
        void                        setDisplay(Style::Display xDisplay);
        void                        setFloat(Style::Float xFloat);
        void                        setSize(Style::Units xWidthUnits, float xWidth, Style::Units xHeightUnits, float xHeight);
        void                        setMargins(Style::Units xLeftUnits, float xLeft, Style::Units xTopUnits, float xTop, Style::Units xRightUnits, float xRight, Style::Units xBottomUnits, float xBottom);
        void                        setPositioning(Style::Units xLeftUnits, float xLeft, Style::Units xTopUnits, float xTop, Style::Units xRightUnits, float xRight, Style::Units xBottomUnits, float xBottom);
		void                        setPadding(Style::Units xLeftUnits, float xLeft, Style::Units xTopUnits, float xTop, Style::Units xRightUnits, float xRight, Style::Units xBottomUnits, float xBottom);
		void                        setBorderWidths(Style::Units xLeftUnits, float xLeft, Style::Units xTopUnits, float xTop, Style::Units xRightUnits, float xRight, Style::Units xBottomUnits, float xBottom);
		void                        setBorderRadii(Style::Units xLeftUnits, float xLeft, Style::Units xTopUnits, float xTop, Style::Units xRightUnits, float xRight, Style::Units xBottomUnits, float xBottom);
		void						setBorderColor(unsigned int xLeft, unsigned int xTop, unsigned int xRight, unsigned int xBottom);
        void                        setFocusable(bool xFocusable);
		void						setOpacity(float x_opacity);

        STATUS                      requestFocus();
        STATUS                      addMouseListener(MouseListener * xListener);
        STATUS                      addMouseMotionListener(MouseMotionListener * xListener);
        STATUS                      addFocusListener(FocusListener * xListener);
        STATUS                      addActionListener(ActionListener * xListener);

        void                        update();

        void                        revalidate();
        void                        validated();
        void                        invalidate();
        void                        add(Component& xComponent);
        void                        remove(Component& xComponent);
        void                        forceBounds(bool xForce);
        STATUS						initialize();  

		int							getDepth();
        Graphics&                   getGraphics();
        Component&                  getParent();
        Component&                  getRoot();
        AbstractFrame&              getFrame();
        Rect*                       getVisibleRegion();
        Rect*                       getBoundsAsPtr();
        Rect                        getBounds();
		LPCWSTR                     getBackgroundImage();
		Paint&                      getBackgroundPaint();
 
        bool                        isDoubleBuffered();     

	private:

		void						interpolate();
		void                        validate();

		void                        setDepth(int xDepth);
		void                        setGraphics(Graphics& xGraphics);
		void                        setParent(Component& xComponent);
		void                        setFrame(AbstractFrame& xFrame);
		void						setComponentManager(ComponentManager& x_componentManager);

    protected:

        virtual void                paintComponent();
        virtual void                paintComponentBorder();
        virtual Rect*               getEventRegion();

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

			if (m_region.aHeight != m_previousDimensions.aHeight ||
				m_region.aWidth != m_previousDimensions.aWidth)
			{
				// FIXME Use SSE2 Acceleration
				m_previousDimensions.aWidth = m_region.aWidth;
				m_previousDimensions.aHeight = m_region.aHeight;

				m_styleSet.markBackgroundAsDirty();
			}

			m_validatedContents = false;
			m_styleSet.markRequestRegionAsDirty();
        }
    };
}
#endif
