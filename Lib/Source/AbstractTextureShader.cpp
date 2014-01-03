
#include "../../include/ExtLibs.h"
#include "../../include/AbstractTextureShader.h"

using namespace A2D;

ID3D10Effect * AbstractTextureShader::aTextureEffect = NULL;
ID3D10BlendState * AbstractTextureShader::aBlendState = NULL;
ID3D10BlendState * AbstractTextureShader::aBlendDisabledState = NULL;
ID3D10EffectMatrixVariable	*	AbstractTextureShader::aWorldMatrixPtr = NULL;
ID3D10EffectMatrixVariable	*	AbstractTextureShader::aViewMatrixPtr = NULL;
ID3D10EffectMatrixVariable	*	AbstractTextureShader::aProjectionMatrixPtr = NULL;
float **	AbstractTextureShader::aProjectionMatrix = NULL;

AbstractTextureShader::AbstractTextureShader(ID3D10Device ** xDXDevice) : aDXDevice(xDXDevice) {}

AbstractTextureShader::~AbstractTextureShader()
{
	DESTROY(aTechnique);
	DESTROY(aWorldMatrixPtr);
	DESTROY(aViewMatrixPtr);
	DESTROY(aProjectionMatrixPtr);
}

HRESULT AbstractTextureShader::initialize()
{
	unsigned int polygonLayoutElements = getPolygonLayoutElementCount();
	D3D10_INPUT_ELEMENT_DESC * polygonLayout = new D3D10_INPUT_ELEMENT_DESC[polygonLayoutElements];

	// Use the DXShaderUtils to create a shader
	// and cache it.
	if (!aTextureEffect)
	{
		SAFELY(DXShaderUtils::LoadEffectFromFile(L"../../../Aurora-SDK/Lib/Assets/Shaders/texture.fx", *aDXDevice, &aTextureEffect));
	}

	// Create alpha channel supported blend states
	// and cache it for reuse.
	if (!aBlendState || !aBlendDisabledState)
	{
		SAFELY(DXShaderUtils::CreatePNGCompatibleBlendStates(*aDXDevice, &aBlendState, &aBlendDisabledState));
	}
	
	SAFELY(createPolygonLayout(polygonLayout));

	SAFELY(DXShaderUtils::loadTechniqueFromEffect(*aDXDevice, aTextureEffect, &aLayout, &aTechnique, polygonLayout, getTechniqueName(), polygonLayoutElements));

	// Get pointers to the three matrices inside the 
	// shader so we can update them from this class.
	aWorldMatrixPtr = aTextureEffect->GetVariableByName("worldMatrix")->AsMatrix();
	aViewMatrixPtr = aTextureEffect->GetVariableByName("viewMatrix")->AsMatrix();
	aProjectionMatrixPtr = aTextureEffect->GetVariableByName("projectionMatrix")->AsMatrix();
	aTexturePtr = aTextureEffect->GetVariableByName("shaderTexture")->AsShaderResource();
	
	DESTROY(polygonLayout);

	return S_OK;
}

void AbstractTextureShader::setWorldMatrix(float ** xMatrix)
{
	// Set the world matrix variable 
	// inside the shader.
	aWorldMatrixPtr->SetMatrix(*xMatrix);

}

void AbstractTextureShader::setViewMatrix(float ** xMatrix)
{

	// Set the view matrix variable 
	// minside the shader.
	aViewMatrixPtr->SetMatrix(*xMatrix);
}

void AbstractTextureShader::setProjectionMatrix(float ** xMatrix)
{

	// Set the projection matrix variable 
	// inside the shader.
	aProjectionMatrixPtr->SetMatrix(*(aProjectionMatrix = xMatrix));
}

void AbstractTextureShader::reloadProjectionMatrix()
{

	// Set the projection matrix variable 
	// inside the shader.
	aProjectionMatrixPtr->SetMatrix(*aProjectionMatrix);
}

void AbstractTextureShader::setTexture(Texture * xTexture)
{
	aTexture = xTexture;

	// Bind and update the texture.
	// Also cache the texture while doing so.!!!!
	aTexturePtr->SetResource(static_cast<ID3D10ShaderResourceView*>(xTexture->getPlatformCompatibleResource()));
}

void AbstractTextureShader::renderTexture()
{
	D3D10_TECHNIQUE_DESC techniqueDesc;
	unsigned int i;

	// Cache the device onto L1 CPU cache for speed
	ID3D10Device * device = *aDXDevice;

	// Cache the texture onto L1 CPU cache for speed
	ID3D10EffectTechnique * technique = aTechnique;

	if (aTexture->hasAlpha())
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

LPCWSTR AbstractTextureShader::toString()
{
	return L"AbstractTextureShader";
}

LPCWSTR AbstractTextureShader::getClass()
{
	return L"AbstractTextureShader";
}