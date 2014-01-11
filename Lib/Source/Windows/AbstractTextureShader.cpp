
#include "../../../Include/Windows/ExtLibs.h"
#include "../../../Include/Windows/AbstractTextureShader.h"

using namespace A2D;

//******************* STATIC _ VARIABLES *****************//
// These are the variables held as static for every effect file.
// Filename: texture.fx
//
// Why?
// ----
// All chidlren will automatically get these. Updating these,
// will update the children as well.
Texture * AbstractTextureShader::aTexture = NULL;
float ** AbstractTextureShader::aProjectionMatrix = NULL;
ID3D10Effect * AbstractTextureShader::aTextureEffect = NULL;
ID3D10EffectShaderResourceVariable * AbstractTextureShader::aTexturePtr = NULL;
ID3D10EffectMatrixVariable * AbstractTextureShader::aWorldMatrixPtr = NULL;
ID3D10EffectMatrixVariable * AbstractTextureShader::aViewMatrixPtr = NULL;
ID3D10EffectMatrixVariable * AbstractTextureShader::aProjectionMatrixPtr = NULL;
/***********************************************************/

AbstractTextureShader::AbstractTextureShader(ID3D10Device ** xDevice) : AbstractShader(xDevice) {}

AbstractTextureShader::~AbstractTextureShader()
{
	AbstractShader::~AbstractShader();

	// This is really unsafe, but for now its okay.
	// Its unsafe because these are static variables
	DESTROY(aTexturePtr);
	DESTROY(aWorldMatrixPtr);
	DESTROY(aViewMatrixPtr);
	DESTROY(aProjectionMatrixPtr);
}

ID3D10Effect ** AbstractTextureShader::getEffect()
{
	return &aTextureEffect;
}

LPCWSTR AbstractTextureShader::getEffectName()
{
	return L"../../../Aurora-SDK/Lib/Assets/Shaders/texture.fx";
}

HRESULT AbstractTextureShader::getUsableVariablePointers(ID3D10Effect * xEffect)
{
	// Get pointers to the three matrices inside the 
	// shader so we can update them from this class.

	if (!aWorldMatrixPtr)
	{
		aWorldMatrixPtr = xEffect->GetVariableByName("worldMatrix")->AsMatrix();
	}

	if (!aViewMatrixPtr)
	{
		aViewMatrixPtr = xEffect->GetVariableByName("viewMatrix")->AsMatrix();
	}

	if (!aProjectionMatrixPtr)
	{
		aProjectionMatrixPtr = xEffect->GetVariableByName("projectionMatrix")->AsMatrix();
	}

	if (!aTexturePtr)
	{
		aTexturePtr = aTextureEffect->GetVariableByName("shaderTexture")->AsShaderResource();
	}

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
	aHasAlpha = xTexture->hasAlpha();

	// Bind and update the texture.
	// Also cache the texture while doing so.!!!!
	aTexturePtr->SetResource(static_cast<ID3D10ShaderResourceView*>(xTexture->getPlatformCompatibleResource()));
}