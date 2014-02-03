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
	typedef void (Component::*INTERPOLATABLEMUTATOR)(float);
	typedef float (Component::*INTERPOLATABLEACCESSOR)(void);
	typedef void(*CALLBACK_)(void*);

	// Typedef animation
	typedef void** Animation;

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
		
		struct Interpolator
		{
			TWEEN m_tween;
			INTERPOLATABLEMUTATOR m_interpolatable;
			CALLBACK_ m_callback;

			int m_startTime;

			float m_period;
			float m_range;
			float m_start;

			void * m_arg;
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

		struct Floater
		{
			INTERPOLATABLEMUTATOR m_mutator;
			INTERPOLATABLEACCESSOR m_accessor;

			float m_max;
			float m_min;

			Floater() :
				m_max(0.0f),
				m_min(0.0f)
			{
			}

			Floater(INTERPOLATABLEACCESSOR x_accessor, INTERPOLATABLEMUTATOR x_mutator, float x_min, float x_max) :
				m_mutator(x_mutator),
				m_accessor(x_accessor),
				m_min(x_min),
				m_max(x_max)
			{
			}
		};

	private:

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

		static Floater				ANIMATE_OPACITY;
		static Floater				ANIMATE_WIDTH;
		static Floater				ANIMATE_HEIGHT;
		static Floater				ANIMATE_BORDER_RADII_TOP_LEFT;
		static Floater				ANIMATE_BORDER_RADII_UNIFIED;
		
		Animation					animate(Floater x_floater, TWEEN x_tween, float x_to, int x_period, CALLBACK_ x_callback, void * x_arg);
		void						stop(Animation x_animation, bool x_callback);
		void						stop(Animation x_animation);
		
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

		void						setWidthUnits(Style::Units x_units);
		void						setWidth(float x_width);
		inline float				getWidth() { return m_styleSet.m_size.m_width; }

		void						setHeightUnits(Style::Units x_units);
		void						setHeight(float x_height);
		inline float				getHeight() { return m_styleSet.m_size.m_height; }

		void						setBorderRadiiTopLeftUnits(Style::Units x_units);
		void						setBorderRadiiTopLeft(float x_value);
		inline float				getBorderRadiiTopLeft() { return m_styleSet.m_borderRadii.m_left; }

		void						setOpacity(float x_opacity);
		inline float				getOpacity() { return m_styleSet.m_opacity; }

		void						setBorderRadiiUnified(float x_value);
		inline float				getBorderRadiiUnified() { return m_styleSet.m_borderRadii.m_left; }

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
