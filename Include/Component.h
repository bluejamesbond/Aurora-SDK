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

#include "OrderedList.h"
#include "ImageProperties.h"
#include "Pipeline.h"
#include "Paint.h"

#include "ComponentEventSource.h"
#include "AbstractEventQueue.h"
//#include "AbstractFrame.h"

#include "Windows\Window.h" // FORCING: @requestFocus()

namespace A2D {

    ////////////////////////////////////////////////////////////////////////////////
    // FORWARD DECLARATIONS
    ////////////////////////////////////////////////////////////////////////////////

	using namespace std;
	class AbstractFrame;
    class Abstract;
	class Graphics;
	class ComponentEventSource;
	struct ImageProperties;

    ////////////////////////////////////////////////////////////////////////////////
    // DECLARATION
    ////////////////////////////////////////////////////////////////////////////////

    class Component : public ComponentEventSource
    {
	public:

		Component();
		~Component();

	private:

		float							aDepth = FLT_MIN;
		AbstractFrame		    *		aFrame;
		Component			    *		aParent = NULL;
		OrderedList<Component*>			aChildren;
		Pipeline				*		aPipeline = NULL;

    protected:

		bool                            aValidatedContents;
		float							aCalculatedNegativeDeltaX;
		float							aCalculatedNegativeDeltaY;

		Graphics                *       aGraphics;
		
		Rect                            aOptRegion;
		Rect                            aOptBackgroundRegion;
		Rect                            aCalculatedRegion;
		Rect							aVisibleRegion;

        ImageProperties                 aOptBackgroundProps;                    // background-size/background-repeat
        LPCWSTR                         aOptBackgroundSrc = NULL;               // background-image  (CSS)
        Paint                           aOptBackgroundPaint;			        // background-color  (CSS)
        int                             aOptBackgroundPosX = 0;                 // background-position-x  (CSS)
        int                             aOptBackgroundPosY = 0;                 // background-position-x  (CSS)

        virtual void                    paintComponent();
        virtual void                    paintComponentBorder();

	protected:
		
		virtual void                    validate();

    public:

		void							revalidate();
		void							validated();
		void							invalidate();

		Rect *							_getBounds();
		void							_setDepth(float xDepth);
		void							_setGraphics(Graphics& xGraphics);
		void                            _setParent(Component& xComponent);
		void							_setFrame(AbstractFrame& xFrame);
		void							_add(Component& xComponent);
		void							_remove(Component& xComponent);

		float							getDepth();
		Graphics&						getGraphics();
		Component&						getParent();
		Component&						getRoot();
		AbstractFrame&					getFrame();
		Rect *							getVisibleRegion();

		void							update();
		Rect                            getBounds();
		void                            setBounds(Rect& xRect);
		void                            add(Component& xComponent);
		void                            remove(Component& xComponent);
		void                            setBounds(float xX, float xY, float xWidth, float xHeight);

        bool                            isDoubleBuffered();
        LPCWSTR                         getBackgroundImage()                                                    { return    aOptBackgroundSrc; };
        int                             getBackgroundPositionX()                                                { return    aOptBackgroundPosX; };
        int                             getBackgroundPositionY()                                                { return    aOptBackgroundPosY; };
        int                             getBackgroundSizeX()                                                    { return    aOptBackgroundProps.aOptSizeX; };
        int                             getBackgroundSizeY()                                                    { return    aOptBackgroundProps.aOptSizeY; };
		Paint&                          getBackgroundPaint()                                                    { return    aOptBackgroundPaint; };
        int                             getBackgroundRepeat()                                                   { return    aOptBackgroundProps.aOptRepeat; };
        ImageProperties                 getBackgroundProperties()                                               { return    aOptBackgroundProps; };
		        
        void                            setDoubleBuffered(bool xDoubleBuffer);
        void                            setBackgroundImage(LPCWSTR xOptBackgroundImage)                     { aOptBackgroundSrc = xOptBackgroundImage; };
        void                            setBackgroundPositionX(int xOptPositionX)                           { aOptBackgroundPosX = xOptPositionX; };
        void                            setBackgroundPositionY(int xOptPositionY)                           { aOptBackgroundPosY = xOptPositionY; };
        void                            setBackgroundSizeX(int xOptSizeX)                                   { aOptBackgroundProps.aOptSizeX = xOptSizeX; };
        void                            setBackgroundSizeY(int xOptSizeY)                                   { aOptBackgroundProps.aOptSizeY = xOptSizeY; };
		void                            setBackgroundPaint(Paint& xOptPaint)                                   { Paint::from(aOptBackgroundPaint, xOptPaint); };
        void                            setBackgroundRepeat(int xOptRepeat)                                 { aOptBackgroundProps.aOptRepeat = xOptRepeat; };
        void                            setBackgroundProperties(ImageProperties& xOptBackgroundProps)        { aOptBackgroundProps = xOptBackgroundProps; };
        void                            setBackground(LPCWSTR xOptBackgroundImage, int xOptBackroundPositionX, int xOptBackroundPositionY, 
														int xOptBackroundSizeX, int xOptBackroundSizeY, Paint& xOptBackgroundPaint, int xOptBackgroundRepeat);

		HRESULT							addListenerThroughChildren(AbstractListener * xListener); // doesnt work as intended
		HRESULT							removeListenerThroughChildren(AbstractListener * xListener); // doesnt work as intended
        
		// Components are the only we that can use the focus system
	public:
		friend							AbstractEventQueue;
		HRESULT							requestFocus();
		void							setFocusable(bool xFocusable);
		Rect						*	getEventRegion();

	private:

		bool							isFocused = false; //<-- can only be accessed by event handler.
		bool							isFocusable = true;

    public:

        virtual HRESULT                 initialize();
        virtual LPCWSTR                 getClass();
        virtual LPCWSTR                 toString();
    };
}
#endif
