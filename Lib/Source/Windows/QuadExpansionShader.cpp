
#include "../../../Include/Windows/ExtLibs.h"
#include "../../../Include/Windows/QuadExpansionShader.h"

using namespace A2D;

QuadExpansionShader::QuadExpansionShader(ID3D10Device ** xDevice) : 
	AbstractShader(xDevice),
	aQuadEffect(NULL),
	aTexturePtr(NULL)
{
}

QuadExpansionShader::~QuadExpansionShader()
{
	AbstractShader::~AbstractShader();

	DESTROY(aTexturePtr);
}

ID3D10Effect ** QuadExpansionShader::getEffect()
{
	return &aQuadEffect;
}

LPCWSTR QuadExpansionShader::getEffectName()
{
	return L"../../../Aurora-SDK/Lib/Assets/Shaders/quad.fx";
}

STATUS QuadExpansionShader::getUsableVariablePointers(ID3D10Effect * xEffect)
{
	// Get pointers to the three matrices inside the 
	// shader so we can update them from this class.

	if (!aTexturePtr)
	{
		aTexturePtr = xEffect->GetVariableByName("shaderTexture")->AsShaderResource();
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