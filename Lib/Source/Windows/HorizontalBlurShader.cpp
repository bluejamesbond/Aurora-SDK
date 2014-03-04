
#include "../../../Include/Windows/ExtLibs.h"
#include "../../../Include/Windows/HorizontalBlurShader.h"

using namespace A2D;

HorizontalBlurShader::HorizontalBlurShader(ID3D10Device ** xDevice) :
AbstractTextureShader(xDevice){}

STATUS HorizontalBlurShader::createPolygonLayout(D3D10_INPUT_ELEMENT_DESC ** xPolygonLayout)
{
	*xPolygonLayout = TextureVertex::aPolygonLayout;

	return STATUS_OK;
}

unsigned int HorizontalBlurShader::getPolygonLayoutElementCount()
{
	return 2;
}

LPCSTR HorizontalBlurShader::getTechniqueName()
{
	return "MainTechnique";
}

LPCWSTR HorizontalBlurShader::getEffectName()
{
	return L"../../../Aurora-SDK/Lib/Assets/Shaders/horizontalblur.fx";
}