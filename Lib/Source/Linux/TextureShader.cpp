
#include "../../../Include/Windows/ExtLibs.h"
#include "../../../Include/Windows/TextureShader.h"

using namespace A2D;

TextureShader::TextureShader(ID3D10Device ** xDevice) :
AbstractTextureShader(xDevice){}

HRESULT	TextureShader::createPolygonLayout(D3D10_INPUT_ELEMENT_DESC * xPolygonLayout)
{

}

unsigned int TextureShader::getPolygonLayoutElementCount()
{

}

LPCSTR TextureShader::getTechniqueName()
{
	return "TextureTechnique";
}
