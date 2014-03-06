
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


STATUS HorizontalBlurShader::getUsableVariablePointers(ID3D10Effect * xEffect)
{
	// Get pointers to the three matrices inside the 
	// shader so we can update them from this class.
	AbstractTextureShader::getUsableVariablePointers(xEffect);

	if (!m_texelSize)
	{
		m_texelSize = xEffect->GetVariableByName("texelSize")->AsScalar();
	}

	return STATUS_OK;
}

LPCSTR HorizontalBlurShader::getTechniqueName()
{
	return "MainTechnique";
}

LPCWSTR HorizontalBlurShader::getEffectName()
{
	return L"../../../Aurora-SDK/Lib/Assets/Shaders/horizontalblur.fx";
}

void HorizontalBlurShader::setTexelSize(float x_size)
{
	m_texelSize->SetFloat(x_size);
}