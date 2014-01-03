
#include "../../include/ExtLibs.h"
#include "../../include/AbstractTextureShader.h"

using namespace A2D;

ID3D10Effect * AbstractTextureShader::aTextureEffect = NULL;

AbstractTextureShader::AbstractTextureShader(ID3D10Device ** xDevice) : AbstractShader(xDevice) {}

AbstractTextureShader::~AbstractTextureShader()
{
	AbstractShader::~AbstractShader();

	DESTROY(aTexturePtr);
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
	aTexturePtr = aTextureEffect->GetVariableByName("shaderTexture")->AsShaderResource();

	return S_OK;
}

void AbstractTextureShader::setTexture(Texture * xTexture)
{
	aTexture = xTexture;
	aHasAlpha = xTexture->hasAlpha();

	// Bind and update the texture.
	// Also cache the texture while doing so.!!!!
	aTexturePtr->SetResource(static_cast<ID3D10ShaderResourceView*>(xTexture->getPlatformCompatibleResource()));
}