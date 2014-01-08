
#include "../../../Include/Core/ExtLibs.h"
#include "../../../Include/Core/Paint.h"

using namespace A2D;

// Basic colors
Paint Paint::RED(Color3D::RED);
Paint Paint::BLUE(Color3D::BLUE);
Paint Paint::YELLOW(Color3D::YELLOW);
Paint Paint::GREEN(Color3D::GREEN);
Paint Paint::MAGENTA(Color3D::MAGENTA);
Paint Paint::CYAN(Color3D::CYAN);
Paint Paint::PURPLE(Color3D::PURPLE);
Paint Paint::GRAY(Color3D::GRAY);
Paint Paint::WHITE(Color3D::WHITE);
Paint Paint::BLACK(Color3D::BLACK);
Paint Paint::TURQUOISE(Color3D::TURQUOISE);
Paint Paint::EMERALD(Color3D::EMERALD);
Paint Paint::PETER_RIVER(Color3D::PETER_RIVER);
Paint Paint::AMETHYST(Color3D::AMETHYST);
Paint Paint::WET_ASPHALT(Color3D::WET_ASPHALT);
Paint Paint::GREEN_SEA(Color3D::GREEN_SEA);
Paint Paint::NEPHRITIS(Color3D::NEPHRITIS);
Paint Paint::BELIZE_HOLE(Color3D::BELIZE_HOLE);
Paint Paint::WISTERIA(Color3D::WISTERIA);
Paint Paint::MIDNIGHT_BLUE(Color3D::MIDNIGHT_BLUE);
Paint Paint::SUN_FLOWER(Color3D::SUN_FLOWER);
Paint Paint::CARROT(Color3D::CARROT);
Paint Paint::ALIZARIN(Color3D::ALIZARIN);
Paint Paint::CLOUDS(Color3D::CLOUDS);
Paint Paint::CONCRETE(Color3D::CONCRETE);
Paint Paint::ORANGE(Color3D::ORANGE);
Paint Paint::PUMPKIN(Color3D::PUMPKIN);
Paint Paint::POMEGRANATE(Color3D::POMEGRANATE);
Paint Paint::SILVER(Color3D::SILVER);
Paint Paint::ASBESTOS(Color3D::ASBESTOS);
Paint Paint::CLEAR(Color3D::CLEAR);

// Basic gradients
Paint Paint::ALIZARIN_TO_POMEGRANATE_VERTICAL(0, 0, Color3D::ALIZARIN, 0, 0, Color3D::POMEGRANATE, Mode::VERTICAL);
Paint Paint::GREEN_SEA_TO_POMEGRANATE_VERTICAL(0, 0, Color3D::GREEN_SEA, 0, 0, Color3D::POMEGRANATE, Mode::VERTICAL);

Paint::Paint(){}

Paint::Paint(int xColor)
{
	Color3D::from(aStart, xColor);
	Color3D::from(aEnd, xColor);

	aMode = Mode::SOLID;
}

Paint::Paint(Color& xColor)
{
	Color3D::from(aStart, xColor);
	Color3D::from(aEnd, xColor);

	aMode = Mode::SOLID;
}

Paint::Paint(Color3D& xColor)
{
	Color3D::from(aStart, xColor);
	Color3D::from(aEnd, xColor);

	aMode = Mode::SOLID;
}

Paint::Paint(float xStartX, float xStartY, Color3D& xStart, float xEndX, float xEndY, Color3D& xEnd, Mode xMode)
{
	Color3D::from(aStart, xStart);
	Color3D::from(aEnd, xEnd);

	aStartX = xStartX;
	aStartY = xStartY;
	aEndX = xEndX;
	aEndY = xEndY;
	aMode = xMode;
}

void Paint::from(Paint& xDst, Paint& xSrc)
{
	memcpy(&xDst, &xSrc, sizeof(Paint));
}
