
#include "../../../Include/Windows/ExtLibs.h"
#include "../../../Include/Windows/VerticalBlurShader.h"

using namespace A2D;

VerticalBlurShader::VerticalBlurShader(ID3D10Device ** xDevice) :
AbstractTextureShader(xDevice){}

STATUS VerticalBlurShader::createPolygonLayout(D3D10_INPUT_ELEMENT_DESC ** xPolygonLayout)
{
	*xPolygonLayout = TextureVertex::aPolygonLayout;

	return STATUS_OK;
}

unsigned int VerticalBlurShader::getPolygonLayoutElementCount()
{
	return 2;
}

LPCSTR VerticalBlurShader::getTechniqueName()
{
	return "MainTechnique";
}

LPCWSTR VerticalBlurShader::getEffectName()
{
	return L"../../../Aurora-SDK/Lib/Assets/Shaders/verticalblur.fx";
}

STATUS VerticalBlurShader::getUsableVariablePointers(ID3D10Effect * xEffect)
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

void VerticalBlurShader::setTexelSize(float x_size)
{
	m_texelSize->SetFloat(x_size);
}