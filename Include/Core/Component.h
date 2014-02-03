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
#include "A2DANIMATABLEFLOAT1.h"
#include "A2DINTERPOLATORFLOAT1.h"

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

	private:

		bool                        m_forcedBounds;
        bool                        m_focused;
        bool                        m_focusable;

        AbstractFrame*              m_frame;
        Component*                  m_parent;
		OrderedList<Component*>     m_children;
		OrderedList<A2DINTERPOLATORFLOAT1*>  m_interpolators;
        ComponentManager*           m_componentManager;
		AbstractEventQueue*			m_eventQueue;
        
		Component*                  m_nextCompListener;
        Component*                  m_prevCompListener;
		
		Animation					m_positionAnimationX = NULL;
		Animation					m_positionAnimationY = NULL;

    protected:

		int							m_id;

		int							m_calculatedRowIndex;
		int							m_calculatedColumnIndex;

		int							m_previousCalculatedRowIndex;
		int							m_previousCalculatedColumnIndex;

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

		static A2DANIMATABLEFLOAT1				ANIMATE_OPACITY;
		static A2DANIMATABLEFLOAT1				ANIMATE_WIDTH;
		static A2DANIMATABLEFLOAT1				ANIMATE_HEIGHT;
		static A2DANIMATABLEFLOAT1				ANIMATE_BORDER_RADII_TOP_LEFT;
		static A2DANIMATABLEFLOAT1				ANIMATE_BORDER_RADII_UNIFIED;
		static A2DANIMATABLEFLOAT1				ANIMATE_BOUNDS_X;
		static A2DANIMATABLEFLOAT1				ANIMATE_BOUNDS_Y;
		
		Animation					animate(A2DANIMATABLEFLOAT1 x_A2DANIMATABLEFLOAT1, TWEEN x_tween, float x_to, int x_period, A2DCALLBACKVOID1 x_callback, void * x_arg);
		void						stop(Animation x_animation, bool x_callback);

		inline void stop(Animation x_animation)
		{
			if (m_interpolators.remove_request(x_animation))
			{
				m_eventQueue->finishedAnimation();
			}
		}

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

		float						getBoundsY();
		void 						setBoundsY(float x_y);

		float						getBoundsX();
		void						setBoundsX(float x_x);

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

		void						setEventQueue(AbstractEventQueue& x_eventQueue);
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
			if (m_previousCalculatedRowIndex != m_calculatedRowIndex ||
				m_previousCalculatedColumnIndex != m_calculatedColumnIndex /*FIXME && NOT RESIZING*/ )
			{
				m_region.aWidth = xWidth;
				m_region.aHeight = xHeight;

				if (m_positionAnimationX)
				{
					stop(m_positionAnimationX);
				}
				if (m_positionAnimationY)
				{
					stop(m_positionAnimationY);
				}

				m_positionAnimationX = animate(Component::ANIMATE_BOUNDS_X, Easing::OUT_QUAD, xX, 200, NULL, NULL);
				m_positionAnimationY = animate(Component::ANIMATE_BOUNDS_Y, Easing::OUT_QUAD, xY, 200, NULL, NULL);

				m_previousCalculatedRowIndex = m_calculatedRowIndex;
				m_previousCalculatedColumnIndex = m_calculatedColumnIndex;
			}
			else
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
			}

			m_validatedContents = false;
			m_styleSet.markRequestRegionAsDirty();
        }
    };
}
#endif
