
#include "../../../Include/Windows/ExtLibs.h"
#include "../../../Include/Windows/QuadExpansionShader.h"

using namespace A2D;

//******************* STATIC _ VARIABLES *****************//
// These are the variables held as static for every effect file.
// Filename: quad.fx
//
// Why?
// ----
// All chidlren will automatically get these. Updating these,
// will update the children as well.
ID3D10Effect * QuadExpansionShader::aQuadEffect = NULL;
ID3D10EffectShaderResourceVariable * QuadExpansionShader::aTexturePtr = NULL;
Texture * QuadExpansionShader::aTexture = NULL;
/***********************************************************/

QuadExpansionShader::QuadExpansionShader(ID3D10Device ** xDevice) : AbstractShader(xDevice) {}

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