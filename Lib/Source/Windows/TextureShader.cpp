
#include "../../../Include/Windows/ExtLibs.h"
#include "../../../Include/Windows/TextureShader.h"

using namespace A2D;

TextureShader::TextureShader(ID3D10Device ** xDevice) :
AbstractTextureShader(xDevice){}

HRESULT	TextureShader::createPolygonLayout(D3D10_INPUT_ELEMENT_DESC ** xPolygonLayout)
{
	*xPolygonLayout = TextureVertex::aPolygonLayout;

	return S_OK;
}

unsigned int TextureShader::getPolygonLayoutElementCount()
{
	return 2;
}

LPCSTR TextureShader::getTechniqueName()
{
	return "TextureTechnique";
}