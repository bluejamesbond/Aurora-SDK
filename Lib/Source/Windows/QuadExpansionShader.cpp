
#include "../../../Include/Windows/ExtLibs.h"
#include "../../../Include/Windows/QuadExpansionShader.h"

using namespace A2D;

QuadExpansionShader* QuadExpansionShader::m_singelton = NULL;

QuadExpansionShader::QuadExpansionShader(ID3D10Device ** xDevice) : 
	AbstractShader(xDevice),
	aQuadEffect(NULL),
	aTexturePtr(NULL),
	m_borderCalculationMatrixPtr(NULL),
	aConstantBufferPtr(NULL)
{
	if (!m_singelton)
	{
		m_singelton = this;
	}
}
QuadExpansionShader::~QuadExpansionShader()
{
	AbstractShader::~AbstractShader();

	DESTROY(aTexturePtr);
}

void QuadExpansionShader::updateBorderCalculationMatrix(D3DXMATRIX * x_borderCalculationMatrix)
{
	m_borderCalculationMatrixPtr->SetMatrix((float*)(x_borderCalculationMatrix));
}

ID3D10Effect ** QuadExpansionShader::getEffect()
{
	return &aQuadEffect;
}

LPCWSTR QuadExpansionShader::getEffectName()
{
	return L"../../../Aurora-SDK/Lib/Assets/Shaders/quad.fx";
}

void QuadExpansionShader::setConstantBuffer(ID3D10Buffer * x_buffer)
{
	aConstantBufferPtr->SetConstantBuffer(x_buffer);
}


STATUS QuadExpansionShader::getUsableVariablePointers(ID3D10Effect * xEffect)
{
	// Get pointers to the three matrices inside the 
	// shader so we can update them from this class.

	if (!aTexturePtr)
	{
		aTexturePtr = xEffect->GetVariableByName("shaderTexture")->AsShaderResource();
	}

	if (!aConstantBufferPtr)
	{
		aConstantBufferPtr = xEffect->GetConstantBufferByName("GS_CONSTANT_BUFFER")->AsConstantBuffer();
	}

	return STATUS_OK;
}

STATUS	QuadExpansionShader::createPolygonLayout(D3D10_INPUT_ELEMENT_DESC ** xPolygonLayout)
{	
	*xPolygonLayout = QuadExpansionVertex::aPolygonLayout;

	return STATUS_OK;
}

unsigned int QuadExpansionShader::getPolygonLayoutElementCount()
{
	return 6;
}

LPCSTR QuadExpansionShader::getTechniqueName()
{
	return "ColorTechnique";
}