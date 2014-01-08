
#include "../../../Include/Windows/ExtLibs.h"
#include "../../../Include/Windows/AbstractShader.h"

using namespace A2D;

ID3D10BlendState * AbstractShader::aBlendState = NULL;
ID3D10BlendState * AbstractShader::aBlendDisabledState = NULL;

AbstractShader::AbstractShader(ID3D10Device ** xDevice) : aDevice(xDevice) {}

AbstractShader::~AbstractShader()
{
	DESTROY(aTechnique);
}

HRESULT AbstractShader::initialize()
{
	unsigned int polygonLayoutElements = getPolygonLayoutElementCount();
	D3D10_INPUT_ELEMENT_DESC * polygonLayout = new D3D10_INPUT_ELEMENT_DESC[polygonLayoutElements];
	ID3D10Effect **	effect = getEffect();

	// Use the DXShaderUtils to create a shader
	// and cache it.
	if (!*effect)
	{
		SAFELY(DXShaderUtils::LoadEffectFromFile(getEffectName(), *aDevice, effect));
	}

	// Create alpha channel supported blend states
	// and cache it for reuse.
	if (!aBlendState || !aBlendDisabledState)
	{
		SAFELY(DXShaderUtils::CreatePNGCompatibleBlendStates(*aDevice, &aBlendState, &aBlendDisabledState));
	}

	SAFELY(createPolygonLayout(polygonLayout));

	SAFELY(DXShaderUtils::loadTechniqueFromEffect(*aDevice, *effect, &aLayout, &aTechnique, polygonLayout, getTechniqueName(), polygonLayoutElements));
	
	SAFELY(getUsableVariablePointers(*effect));

	DESTROY(polygonLayout);

	return S_OK;
}

void AbstractShader::renderShader()
{
	D3D10_TECHNIQUE_DESC techniqueDesc;
	unsigned int i;

	// Cache the device onto L1 CPU cache for speed
	ID3D10Device * device = *aDevice;

	// Cache the texture onto L1 CPU cache for speed
	ID3D10EffectTechnique * technique = aTechnique;

	if (aHasAlpha)
	{
		device->OMSetBlendState(aBlendState, 0, 0xffffffff);
	}
	else
	{
		device->OMSetBlendState(aBlendDisabledState, 0, 0xffffffff);
	}

	// Set the input layout.
	device->IASetInputLayout(aLayout);

	// Get the description structure of the technique 
	// from inside the shader so it can be used for rendering.
	technique->GetDesc(&techniqueDesc);

	// Go through each pass in the technique (should be just 
	// one currently) and render the triangles.
	for (i = 0; i < techniqueDesc.Passes; ++i)
	{
		// hard coded 6. change this to a variable later.
		technique->GetPassByIndex(i)->Apply(0);
		device->DrawIndexed(6, 0, 0);
	}
}