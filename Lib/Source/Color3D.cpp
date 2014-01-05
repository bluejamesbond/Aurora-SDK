
#include "../../include/ExtLibs.h"
#include "../../include/Color3D.h"

using namespace A2D;

Color3D Color3D::RED(Color::RED);
Color3D Color3D::BLUE(Color::BLUE);
Color3D Color3D::YELLOW(Color::YELLOW);
Color3D Color3D::GREEN(Color::GREEN);
Color3D Color3D::MAGENTA(Color::MAGENTA);
Color3D Color3D::CYAN(Color::CYAN);
Color3D Color3D::PURPLE(Color::PURPLE);
Color3D Color3D::GRAY(Color::GRAY);
Color3D Color3D::WHITE(Color::WHITE);
Color3D Color3D::BLACK(Color::BLACK);
Color3D Color3D::TURQUOISE(Color::TURQUOISE);
Color3D Color3D::EMERALD(Color::EMERALD);
Color3D Color3D::PETER_RIVER(Color::PETER_RIVER);
Color3D Color3D::AMETHYST(Color::AMETHYST);
Color3D Color3D::WET_ASPHALT(Color::WET_ASPHALT);
Color3D Color3D::GREEN_SEA(Color::GREEN_SEA);
Color3D Color3D::NEPHRITIS(Color::NEPHRITIS);
Color3D Color3D::BELIZE_HOLE(Color::BELIZE_HOLE);
Color3D Color3D::WISTERIA(Color::WISTERIA);
Color3D Color3D::MIDNIGHT_BLUE(Color::MIDNIGHT_BLUE);
Color3D Color3D::SUN_FLOWER(Color::SUN_FLOWER);
Color3D Color3D::CARROT(Color::CARROT);
Color3D Color3D::ALIZARIN(Color::ALIZARIN);
Color3D Color3D::CLOUDS(Color::CLOUDS);
Color3D Color3D::CONCRETE(Color::CONCRETE);
Color3D Color3D::ORANGE(Color::ORANGE);
Color3D Color3D::PUMPKIN(Color::PUMPKIN);
Color3D Color3D::POMEGRANATE(Color::POMEGRANATE);
Color3D Color3D::SILVER(Color::SILVER);
Color3D Color3D::ASBESTOS(Color::ASBESTOS);
Color3D Color3D::CLEAR(Color::CLEAR);

Color3D::Color3D(){};

Color3D::Color3D(int xColor)
{
	from(*this, xColor);
}

Color3D::Color3D(Color& xSrc)
{
	from(*this, xSrc);
}

void Color3D::from(Color3D& xDst, int xColor)
{
	xDst.aAlpha = FLOAT(((xColor >> 24) & 0xFF) / FLT_255);
	xDst.aRed = FLOAT(((xColor >> 16) & 0xFF) / FLT_255);
	xDst.aGreen = FLOAT(((xColor >> 8) & 0xFF) / FLT_255);
	xDst.aBlue = FLOAT((xColor & 0xFF) / FLT_255);
}

void Color3D::from(Color3D& xDest, Color& xSrc)
{
	xDest.aAlpha = FLOAT(xSrc.aAlpha) / FLT_255;
	xDest.aRed = FLOAT(xSrc.aRed) / FLT_255;
	xDest.aBlue = FLOAT(xSrc.aBlue) / FLT_255;
	xDest.aGreen = FLOAT(xSrc.aGreen) / FLT_255;
}

void Color3D::from(Color3D& xDst, Color3D& xSrc)
{
	xDst.aAlpha = xSrc.aAlpha;
	xDst.aRed = xSrc.aRed;
	xDst.aBlue = xSrc.aBlue;
	xDst.aGreen = xSrc.aGreen;
}