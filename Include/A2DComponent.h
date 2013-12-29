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

////////////////////////////////////////////////////////////////////////////////
// FORWARD DECLARATIONS
////////////////////////////////////////////////////////////////////////////////

class ;
class Abstract;
class Renderable;
class AbstractComponent;
class Camera;
struct CameraProperties;
struct RenderData;
class BackBuffer;
class MatrixFactory;
class ModelFactory;
class RootPane;

class Window;
class TextureBuffer;

////////////////////////////////////////////////////////////////////////////////
// DEFINE
////////////////////////////////////////////////////////////////////////////////

#define COMPONENT_LL(str1, str2)                           str1 str2

////////////////////////////////////////////////////////////////////////////////
// DECLARATION
////////////////////////////////////////////////////////////////////////////////

class Component : public AbstractComponent
{
public:

	// Variables
	bool blurred = false;
	TextureBuffer		  *     aTextureBuffer;
	bool aDoubleBuffer = false;
	//Public Methods
	void SetDoubleBuffered(bool xDoubleBuffer);
	bool IsDoubleBuffered();
	Pipeline * pipeline = NULL;

protected:

	// Variables
	ImageProperties	*			aOptBackgroundProps;					// background-size/background-repeat
	LPCWSTR			*				aOptBackgroundSrc = NULL;				// background-image  (CSS)
	int								aOptBackgroundColor = 0xFF000000;       // background-color  (CSS)
	int								aOptBackgroundPosX = 0;					// background-position-x  (CSS)
	int								aOptBackgroundPosY = 0;					// background-position-x  (CSS)

public:

    // Accessors
	LPCWSTR				*			GetOptBackgroundImage()													{ return	aOptBackgroundSrc; };
	int								GetOptBackgroundPositionX()												{ return	aOptBackgroundPosX; };
	int								GetOptBackgroundPositionY()												{ return	aOptBackgroundPosY; };
	int								GetOptBackgroundSizeX()													{ return	aOptBackgroundProps->aOptSizeX; };
	int								GetOptBackgroundSizeY()													{ return	aOptBackgroundProps->aOptSizeY; };
	int								GetOptBackgroundColor()													{ return	aOptBackgroundColor; };
	int								GetOptBackgroundRepeat()												{ return	aOptBackgroundProps->aOptRepeat; };
	ImageProperties	*			GetOptBackgroundProperties()											{ return	aOptBackgroundProps; };

    // Mutators
	void							SetOptBackground(LPCWSTR * xOptBackgroundImage, int xOptBackroundPositionX,	int xOptBackroundPositionY,	
													 int xOptBackroundSizeX, int xOptBackroundSizeY, int xOptBackgroundColor, int xOptBackgroundRepeat);

	void							SetOptBackgroundImage(LPCWSTR * xOptBackgroundImage)					{ aOptBackgroundSrc = xOptBackgroundImage; };
	void							SetOptBackgroundPositionX(int xOptPositionX)							{ aOptBackgroundPosX = xOptPositionX; };
	void							SetOptBackgroundPositionY(int xOptPositionY)							{ aOptBackgroundPosY = xOptPositionY; };
	void							SetOptBackgroundSizeX(int xOptSizeX)									{ aOptBackgroundProps->aOptSizeX = xOptSizeX; };
	void							SetOptBackgroundSizeY(int xOptSizeY)									{ aOptBackgroundProps->aOptSizeY = xOptSizeY; };
	void							SetOptBackgroundColor(int xOptColor)									{ aOptBackgroundColor = xOptColor; };
	void							SetOptBackgroundRepeat(int xOptRepeat)									{ aOptBackgroundProps->aOptRepeat = xOptRepeat; };
	void							SetOptBackgroundProperties(ImageProperties * xOptBackgroundProps)	{ aOptBackgroundProps = xOptBackgroundProps; };

    // Builders
    // { NONE }

    // Factory
    // { NONE }

public:

    // Additional
	virtual void                    RenderComponent(RenderData * xRenderData);
	virtual void                    RenderComponentBorder(RenderData * xRenderData);
	// virtual void					Render(RenderData * xRenderData);

    // Pure Virtual
    // { NONE }

    // Virtual
    // { NONE }

public:

    // Implementation
    // { ABSTRACT }
    virtual HRESULT                 Initialize();
    virtual void                    Deinitialize();
    virtual LPCWSTR                 GetClass();
    virtual LPCWSTR                 ToString();
    virtual bool                    operator==(Abstract * xAbstract);
};

#endif
