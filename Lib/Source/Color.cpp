
#include "../../include/ExtLibs.h"
#include "../../include/Color.h"

using namespace A2D;

Color Color::RED(0xFFFF0000);
Color Color::BLUE(0xFF0000FF);
Color Color::YELLOW(0xFFFFFF00);
Color Color::GREEN(0xFF00FF00);
Color Color::MAGENTA(0xFFFF00FF);
Color Color::CYAN(0xFF00FFFF);
Color Color::PURPLE(0xFF663399);
Color Color::GRAY(0xFFC0C0C0);
Color Color::WHITE(0xFFFFFFFF);
Color Color::BLACK(0xFF000000);
Color Color::TURQUOISE(0xFF1abc9c);
Color Color::EMERALD(0xFF40d47e);
Color Color::PETER_RIVER(0xFF3498db);
Color Color::AMETHYST(0xFF9b59b6);
Color Color::WET_ASPHALT(0xFF34495e);
Color Color::GREEN_SEA(0xFF16a085);
Color Color::NEPHRITIS(0xFF27ae60);
Color Color::BELIZE_HOLE(0xFF2980b9);
Color Color::WISTERIA(0xFF8e44ad);
Color Color::MIDNIGHT_BLUE(0xFF2c3e50);
Color Color::SUN_FLOWER(0xFFf1c40f);
Color Color::CARROT(0xFFe67e22);
Color Color::ALIZARIN(0xFFe74c3c);
Color Color::CLOUDS(0xFFecf0f1);
Color Color::CONCRETE(0xFF95a5a6);
Color Color::ORANGE(0xFFf39c12);
Color Color::PUMPKIN(0xFFd35400);
Color Color::POMEGRANATE(0xFFc0392b);
Color Color::SILVER(0xFFbdc3c7);
Color Color::ASBESTOS(0xFF7f8c8d);
Color Color::CLEAR(0x00FFFFFF);

Color::Color(){}

Color::Color(int xColor)
{
	from(*this, xColor);
}

void Color::from(Color& xDst, int xSrc)
{
	xDst.aAlpha = (xSrc >> 24) & 0xFF;
	xDst.aRed = (xSrc >> 16) & 0xFF;
	xDst.aGreen = (xSrc >> 8) & 0xFF;
	xDst.aBlue = xSrc & 0xFF;
}