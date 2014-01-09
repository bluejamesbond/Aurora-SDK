
#include "../../../Include/Windows/ExtLibs.h"
#include "../../../Include/Windows/QuadExpansionShader.h"

using namespace A2D;

//******************* STATIC _ VARIABLES *****************//
// These are the variables held as static for every effect file.
// Filename: color.fx
//
// Why?
// ----
// All chidlren will automatically get these. Updating these,
// will update the children as well.
ID3D10Effect * QuadExpansionShader::aColorEffect = NULL;
ID3D10EffectShaderResourceVariable * QuadExpansionShader::aTexturePtr = NULL;
/***********************************************************/

QuadExpansionShader::QuadExpansionShader(ID3D10Device ** xDevice) : AbstractShader(xDevice) {}

QuadExpansionShader::~QuadExpansionShader()
{
	AbstractShader::~AbstractShader();

	DESTROY(aTexturePtr);
}

ID3D10Effect ** QuadExpansionShader::getEffect()
{
	return &aColorEffect;
}

LPCWSTR QuadExpansionShader::getEffectName()
{
	return L"../../../Aurora-SDK/Lib/Assets/Shaders/quad.fx";
}

HRESULT QuadExpansionShader::getUsableVariablePointers(ID3D10Effect * xEffect)
{
	// Get pointers to the three matrices inside the 
	// shader so we can update them from this class.

	if (!aTexturePtr)
	{
		aTexturePtr = xEffect->GetVariableByName("shaderTexture")->AsShaderResource();
	}

	return S_OK;
}

HRESULT	QuadExpansionShader::createPolygonLayout(D3D10_INPUT_ELEMENT_DESC ** xPolygonLayout)
{	
	*xPolygonLayout = QuadExpansionVertex::aPolygonLayout;

	return S_OK;
}

unsigned int QuadExpansionShader::getPolygonLayoutElementCount()
{
	return 2;
}

LPCSTR QuadExpansionShader::getTechniqueName()
{
	return "ColorTechnique";
}