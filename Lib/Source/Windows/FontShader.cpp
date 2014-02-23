
#include "../../../Include/Windows/ExtLibs.h"
#include "../../../Include/Windows/FontShader.h"

using namespace A2D;

FontShader::FontShader(ID3D10Device ** xDevice) : TextureShader(xDevice) {}

ID3D10Effect ** FontShader::getEffect()
{
	return &aFontEffect;
}

LPCWSTR FontShader::getEffectName()
{
	return L"../../../Aurora-SDK/Lib/Assets/Shaders/texture.fx";
}

STATUS FontShader::getUsableVariablePointers(ID3D10Effect * xEffect)
{
	// Get pointers to the three matrices inside the 
	// shader so we can update them from this class.

	if (!aTexturePtr)
	{
		aTexturePtr = aFontEffect->GetVariableByName("shaderTexture")->AsShaderResource();
	}
	
	if (!aPixelColorPtr)
	{
		aPixelColorPtr = aFontEffect->GetVariableByName("pixelColor")->AsVector();
	}

	return STATUS_OK;
}

LPCSTR FontShader::getTechniqueName()
{
	return "TextureTechnique"; // HAVE TO CHANGE THIS LATER
}

void FontShader::setTexture(Texture * xTexture)
{
	aTexture = xTexture;
	aHasAlpha = xTexture->hasAlpha();

	// Bind and update the texture.
	// Also cache the texture while doing so.!!!!

	aTexturePtr->SetResource(static_cast<ID3D10ShaderResourceView*>(xTexture->getPlatformCompatibleResource()));
}

void FontShader::setColor(Color * xColor)
{
	//xColor->aRed;
	//D3DXVECTOR4 pixelColor = xColor;
}

// temporary solution
void FontShader::setColor(float r, float b, float y, float a)
{
	D3DXVECTOR4 pixelColor = D3DXVECTOR4(r, b, y, a);
	aPixelColorPtr->SetFloatVector(static_cast<float*>(pixelColor));
}

void FontShader::renderShader(int xIndexCount)
{
		int temp = aIndexCount;
		aIndexCount = xIndexCount;

		AbstractShader::renderShader();

		aIndexCount = temp;
}