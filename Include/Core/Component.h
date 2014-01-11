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

#include "../_A2D.h"
#include "OrderedList.h"
#include "ImageProperties.h"
#include "Pipeline.h"
#include "Rect.h"
#include "Paint.h"
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

    public:

        Component();
        ~Component();

    private:

        float							aDepth = FLT_MIN;

        bool							aForced = false;

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

        float							aSizeWidth = 0.0f;
        float							aSizeHeight = 0.0f;

        float							aMarginLeft = 0.0f;
        float							aMarginTop = 0.0f;
        float							aMarginBottom = 0.0f;
        float							aMarginRight = 0.0f;

        float							aPositionLeft = 0.0f;
        float							aPositionTop = 0.0f;
        float							aPositionBottom = 0.0f;
        float							aPositionRight = 0.0f;

    public:

        void							setPosition(Styles::Position xPosition);
        void							setDisplay(Styles::Display xDisplay);
        void							setFloat(Styles::Float xFloat);
        void							setSize(Styles::Units xWidthUnits, float xWidth, Styles::Units xHeightUnits, float xHeight);
        void							setMargins(Styles::Units xLeftUnits, float xLeft, Styles::Units xTopUnits, float xTop, Styles::Units xRightUnits, float xRight, Styles::Units xBottomUnits, float xBottom);
        void							setPositioning(Styles::Units xLeftUnits, float xLeft, Styles::Units xTopUnits, float xTop, Styles::Units xRightUnits, float xRight, Styles::Units xBottomUnits, float xBottom);

        void							applyCascadingStyleLayout();
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
        float							aCalculatedNegativeDeltaX = 0.0f;
        float							aCalculatedNegativeDeltaY = 0.0f;
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

        void                            validate();

    public:

        void							revalidate();
        void							validated();
        void							invalidate();

        float							getDepth();
        Graphics&						getGraphics();
        Component&						getParent();
        Component&						getRoot(){};
        AbstractFrame&					getFrame();

        void							update();
        Rect                            getBounds();
        void                            setBounds(Rect& xRect);

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

    public:

        virtual HRESULT                 initialize();
    };
}
#endif
