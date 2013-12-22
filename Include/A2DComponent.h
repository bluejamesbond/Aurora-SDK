///////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __A2DCOMPONENT_H__
#define __A2DCOMPONENT_H__

//+-----------------------------------------------------------------------------
//
//  Struct:
//      A2DCOMPONENT
//
//  Synopsis:
//      Differentiates which of the two possible arcs could match the given arc
//      parameters.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "A2DAbstractComponent.h"
#include "A2DImageProperties.h"

////////////////////////////////////////////////////////////////////////////////
// FORWARD DECLARATIONS
////////////////////////////////////////////////////////////////////////////////

class A2D;
class A2DAbstract;
class A2DRenderable;
class A2DAbstractComponent;
class A2DCamera;
struct A2DCameraProperties;
struct A2DRenderData;
class A2DBackBuffer;
class A2DMatrixFactory;
class A2DModelFactory;
class A2DRootPane;

class A2DWindow;
class A2DTextureBuffer;

////////////////////////////////////////////////////////////////////////////////
// DEFINE
////////////////////////////////////////////////////////////////////////////////

#define A2DCOMPONENT_LL(str1, str2)                           str1 str2

////////////////////////////////////////////////////////////////////////////////
// DECLARATION
////////////////////////////////////////////////////////////////////////////////

class A2DComponent : public A2DAbstractComponent
{
public:

	// Variables
	double translationX = 0;
	double translationXG1 = 10;
	double translationYG1 = 10;
	double translationY = 0;
	bool blurred = false;
	double translationYDirection = 1;
	double translationXDirection = 1;
	double translationXDirectionG1 = 1;
	double translationYDirectionG1 = 1;
	A2DTextureBuffer		  *     aTextureBuffer;
	bool aDoubleBuffer = false;
	//Public Methods
	void SetDoubleBuffered(bool xDoubleBuffer);
	bool IsDoubleBuffered();

protected:

	// Variables
	A2DImageProperties	*			aOptBackgroundProps;					// background-size/background-repeat
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
	A2DImageProperties	*			GetOptBackgroundProperties()											{ return	aOptBackgroundProps; };

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
	void							SetOptBackgroundProperties(A2DImageProperties * xOptBackgroundProps)	{ aOptBackgroundProps = xOptBackgroundProps; };

    // Builders
    // { NONE }

    // Factory
    // { NONE }

public:

    // Additional
	virtual void                    RenderComponent(A2DRenderData * xRenderData);
	virtual void                    RenderComponentBorder(A2DRenderData * xRenderData);
	// virtual void					Render(A2DRenderData * xRenderData);

    // Pure Virtual
    // { NONE }

    // Virtual
    // { NONE }

public:

    // Implementation
    // { A2DABSTRACT }
    virtual HRESULT                 Initialize();
    virtual void                    Deinitialize();
    virtual LPCWSTR                 GetClass();
    virtual LPCWSTR                 ToString();
    virtual bool                    operator==(A2DAbstract * xAbstract);
};

#endif
