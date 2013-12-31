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

#include "AbstractComponent.h"
#include "ImageProperties.h"
#include "Pipeline.h"

namespace A2D {

    ////////////////////////////////////////////////////////////////////////////////
    // FORWARD DECLARATIONS
    ////////////////////////////////////////////////////////////////////////////////

    class Abstract;
    class AbstractComponent;
	class ImageProperties;

    ////////////////////////////////////////////////////////////////////////////////
    // DECLARATION
    ////////////////////////////////////////////////////////////////////////////////

    class Component : public AbstractComponent
    {
    public:

        bool							blurred = false;
        bool							aDoubleBuffer = false;

		TextureBuffer         *			aTextureBuffer;
        Pipeline			  *			pipeline = NULL;

    protected:

        ImageProperties *               aOptBackgroundProps;                    // background-size/background-repeat
        LPCWSTR                         aOptBackgroundSrc = NULL;               // background-image  (CSS)
        int                             aOptBackgroundColor = 0xFF000000;       // background-color  (CSS)
        int                             aOptBackgroundPosX = 0;                 // background-position-x  (CSS)
        int                             aOptBackgroundPosY = 0;                 // background-position-x  (CSS)

        virtual void                    paintComponent(Graphics& xGraphics) = 0;
        virtual void                    paintComponentBorder(Graphics& xGraphics) = 0;

    public:

        bool                            isDoubleBuffered();
        LPCWSTR                         getBackgroundImage()                                                    { return    aOptBackgroundSrc; };
        int                             getBackgroundPositionX()                                                { return    aOptBackgroundPosX; };
        int                             getBackgroundPositionY()                                                { return    aOptBackgroundPosY; };
        int                             getBackgroundSizeX()                                                    { return    aOptBackgroundProps->aOptSizeX; };
        int                             getBackgroundSizeY()                                                    { return    aOptBackgroundProps->aOptSizeY; };
        int                             getBackgroundColor()                                                    { return    aOptBackgroundColor; };
        int                             getBackgroundRepeat()                                                   { return    aOptBackgroundProps->aOptRepeat; };
        ImageProperties                 getBackgroundProperties()                                               { return    aOptBackgroundProps; };

        
        void                            setDoubleBuffered(bool xDoubleBuffer);
        void                            setBackgroundImage(LPCWSTR xOptBackgroundImage)                     { aOptBackgroundSrc = xOptBackgroundImage; };
        void                            setBackgroundPositionX(int xOptPositionX)                           { aOptBackgroundPosX = xOptPositionX; };
        void                            setBackgroundPositionY(int xOptPositionY)                           { aOptBackgroundPosY = xOptPositionY; };
        void                            setBackgroundSizeX(int xOptSizeX)                                   { aOptBackgroundProps->aOptSizeX = xOptSizeX; };
        void                            setBackgroundSizeY(int xOptSizeY)                                   { aOptBackgroundProps->aOptSizeY = xOptSizeY; };
        void                            setBackgroundColor(int xOptColor)                                   { aOptBackgroundColor = xOptColor; };
        void                            setBackgroundRepeat(int xOptRepeat)                                 { aOptBackgroundProps->aOptRepeat = xOptRepeat; };
        void                            setBackgroundProperties(ImageProperties& xOptBackgroundProps)        { aOptBackgroundProps = xOptBackgroundProps; };
        void                            setBackground(LPCWSTR * xOptBackgroundImage, int xOptBackroundPositionX, int xOptBackroundPositionY, 
                                                      int xOptBackroundSizeX, int xOptBackroundSizeY, int xOptBackgroundColor, int xOptBackgroundRepeat);
        
    public:

        virtual HRESULT                 Initialize();
        virtual void                    Deinitialize();
        virtual LPCWSTR                 GetClass();
        virtual LPCWSTR                 ToString();
        virtual bool                    operator==(Abstract * xAbstract);
    };
}
#endif
