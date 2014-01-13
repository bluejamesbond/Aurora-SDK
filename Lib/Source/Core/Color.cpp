
#include "../../../include/Core/ExtLibs.h"
#include "../../../include/Core/Color.h"

using namespace A2D;

Color Color::RED(0xFF0000FF);
Color Color::BLUE(0x0000FFFF);
Color Color::YELLOW(0xFFFF00FF);
Color Color::GREEN(0x00FF00FF);
Color Color::MAGENTA(0xFF00FFFF);
Color Color::CYAN(0x00FFFFFF);
Color Color::PURPLE(0x663399FF);
Color Color::GRAY(0xC0C0C0FF);
Color Color::WHITE(0xFFFFFFFF);
Color Color::BLACK(0x000000FF);
Color Color::TURQUOISE(0x1abc9cFF);
Color Color::EMERALD(0x40d47eFF);
Color Color::PETER_RIVER(0x3498dbFF);
Color Color::AMETHYST(0x9b59b6FF);
Color Color::WET_ASPHALT(0x34495eFF);
Color Color::GREEN_SEA(0x16a085FF);
Color Color::NEPHRITIS(0x27ae60FF);
Color Color::BELIZE_HOLE(0x2980b9FF);
Color Color::WISTERIA(0x8e44adFF);
Color Color::MIDNIGHT_BLUE(0x2c3e50FF);
Color Color::SUN_FLOWER(0xf1c40fFF);
Color Color::CARROT(0xe67e22FF);
Color Color::ALIZARIN(0xe74c3cFF);
Color Color::CLOUDS(0xecf0f1FF);
Color Color::CONCRETE(0x95a5a6FF);
Color Color::ORANGE(0xf39c12FF);
Color Color::PUMPKIN(0xd35400FF);
Color Color::POMEGRANATE(0xc0392bFF);
Color Color::SILVER(0xbdc3c7FF);
Color Color::ASBESTOS(0x7f8c8dFF);
Color Color::CLEAR(0xFFFFFF00);

Color::Color(){}

Color::Color(unsigned int xColor)
{
	m_raw = xColor;
	from(*this, xColor);
}

void Color::from(Color& xDst, int xSrc)
{
	xDst.m_raw = xSrc;

	xDst.aRed = (xSrc >> 24) & 0xFF;
	xDst.aGreen = (xSrc >> 16) & 0xFF;
	xDst.aBlue = (xSrc >> 8) & 0xFF;
	xDst.aAlpha = xSrc & 0xFF; 
}