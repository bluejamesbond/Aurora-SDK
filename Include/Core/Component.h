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
#include "CascadingLayout.h"
#include "Styles.h"
#include GRAPHICS__

namespace A2D {

    ////////////////////////////////////////////////////////////////////////////////
    // FORWARD DECLARATIONS
    ////////////////////////////////////////////////////////////////////////////////

	class AbstractFrame;
    class Abstract;
	class Graphics;
	class Component;
	struct ImageProperties;

    ////////////////////////////////////////////////////////////////////////////////
    // DECLARATION
    ////////////////////////////////////////////////////////////////////////////////

    class Component
	{
		friend class RepaintManager;
		friend class CascadingLayout;

	public:

		Component();
		~Component();

	private:

		float							aDepth = FLT_ZERO;

		bool							aForced = false;
		bool							aVisible = true;

		AbstractFrame		    *		aFrame;
		Component			    *		aParent = NULL;
		OrderedList<Component*>			aChildren;
		Pipeline				*		aPipeline = NULL;

	protected:

		Styles::Display					aDisplay = Styles::Display::BLOCK;
		Styles::Position				aPosition = Styles::Position::RELATIVE_;

		Styles::Units					aSizeWidthUnits = Styles::Units::PIXEL;
		Styles::Units					aSizeHeightUnits = Styles::Units::PIXEL;	
		
		Styles::Units					aMarginLeftUnits = Styles::Units::PIXEL;
		Styles::Units					aMarginTopUnits = Styles::Units::PIXEL;
		Styles::Units					aMarginBottomUnits = Styles::Units::PIXEL;
		Styles::Units					aMarginRightUnits = Styles::Units::PIXEL;

		Styles::Units					aPositionLeftUnits = Styles::Units::PIXEL;
		Styles::Units					aPositionTopUnits = Styles::Units::PIXEL;
		Styles::Units					aPositionBottomUnits = Styles::Units::PIXEL;
		Styles::Units					aPositionRightUnits = Styles::Units::PIXEL;

		unsigned int					aSizeWidth = 0;
		unsigned int							aSizeHeight = 0;

		int							aMarginLeft = 0;
		int							aMarginTop = 0;
		int							aMarginBottom = 0;
		int							aMarginRight = 0;

		int							aPositionLeft = 0;
		int							aPositionTop = 0;
		int							aPositionBottom = 0;
		int							aPositionRight = 0;

	public:
		
		void							setPosition(Styles::Position xPosition);
		void							setDisplay(Styles::Display xDisplay);
		void							setFloat(Styles::Float xFloat);
		void							setSize(Styles::Units xWidthUnits, unsigned int xWidth, Styles::Units xHeightUnits, unsigned int xHeight);
		void							setMargins(Styles::Units xLeftUnits, int xLeft, Styles::Units xTopUnits, int xTop, Styles::Units xRightUnits, int xRight, Styles::Units xBottomUnits, int xBottom);
		void							setPositioning(Styles::Units xLeftUnits, int xLeft, Styles::Units xTopUnits, int xTop, Styles::Units xRightUnits, int xRight, Styles::Units xBottomUnits, int xBottom);
		void							forceBounds(bool xForce);
	
	public:

		Rect *							getBoundsAtPtr();
		void							setDepth(float xDepth);
		void							setGraphics(Graphics& xGraphics);
		void                            setParent(Component& xComponent);
		void							setFrame(AbstractFrame& xFrame);
		void							add(Component& xComponent);
		void							remove(Component& xComponent);
		
    protected:

		bool                            aValidatedContents;
		float							aCalculatedNegativeDeltaX = FLT_ZERO;
		float							aCalculatedNegativeDeltaY = FLT_ZERO;
		Graphics                *       aGraphics;
		Rect                            aOptRegion;
		Rect                            aOptBackgroundRegion;
		Rect                            aCalculatedRegion;
		Rect                            aVisibleRegion;

        ImageProperties                 aOptBackgroundProps;                    // background-size/background-repeat
        LPCWSTR                         aOptBackgroundSrc = NULL;               // background-image  (CSS)
        Paint                           aOptBackgroundPaint;			        // background-color  (CSS)
        int                             aOptBackgroundPosX = 0;                 // background-position-x  (CSS)
        int                             aOptBackgroundPosY = 0;                 // background-position-x  (CSS)

        virtual void                    paintComponent();
        virtual void                    paintComponentBorder();

	protected:
		
		void							validate();

    public:

		void							revalidate();
		void							validated();
		void							invalidate();

		float							getDepth();
		Graphics&						getGraphics();
		Component&						getParent();
		Component&						getRoot();
		AbstractFrame&					getFrame();

		void							update();
		Rect                            getBounds();
		void                            setBounds(Rect& xRect);
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

    public:

        virtual HRESULT                 initialize();

	////////////////////////////////////////////////////////////////////////////////
	// INLINE
	////////////////////////////////////////////////////////////////////////////////

	protected:

		inline void Component::setBounds(float xX, float xY, float xWidth, float xHeight)
		{
			aOptRegion.aWidth = xWidth;
			aOptRegion.aHeight = xHeight;
			aOptRegion.aX = xX;
			aOptRegion.aY = xY;

			aOptBackgroundRegion.aWidth = xWidth;
			aOptBackgroundRegion.aHeight = xHeight;

			aValidatedContents = false;
		}

    };
}
#endif
