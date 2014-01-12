
#include "../../../Include/Windows/ExtLibs.h"
#include "../../../Include/Windows/ColoredTextureShader.h"

using namespace A2D;

ColoredTextureShader::ColoredTextureShader(ID3D10Device ** xDevice) : AbstractTextureShader(xDevice){}

STATUS	ColoredTextureShader::createPolygonLayout(D3D10_INPUT_ELEMENT_DESC ** xPolygonLayout)
{
	*xPolygonLayout = ColoredTextureVertex::aPolygonLayout;

	return STATUS_OK;
}

unsigned int ColoredTextureShader::getPolygonLayoutElementCount()
{
	return 3;
}

LPCSTR ColoredTextureShader::getTechniqueName()
{
	return "ColoredTextureTechnique";
}