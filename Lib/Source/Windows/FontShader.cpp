
#include "../../../Include/Windows/ExtLibs.h"
#include "../../../Include/Windows/FontShader.h"

using namespace A2D;

FontShader::FontShader(ID3D10Device ** xDevice) : AbstractTextureShader(xDevice) {}


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
		aPixelColorPtr = aFontEffect->GetVariableByName("fontColor")->AsVector();
	}

	if (!aShadowColorPtr)
	{
		aShadowColorPtr = aFontEffect->GetVariableByName("shadowColor")->AsVector();
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

void FontShader::setTextColor(Color * xColor)
{
	//xColor->aRed;
	//D3DXVECTOR4 pixelColor = xColor;
}

// temporary solution
void FontShader::setTextColor(float r, float b, float y, float a)
{
	D3DXVECTOR4 pixelColor = D3DXVECTOR4(r, b, y, a);
	aPixelColorPtr->SetFloatVector(static_cast<float*>(pixelColor));
}

void FontShader::setShadowColor(Color * xColor)
{

}

// temporary solution
void FontShader::setShadowColor(float r, float b, float y, float a)
{
	D3DXVECTOR4 shadowColor = D3DXVECTOR4(r, b, y, a);
	aShadowColorPtr->SetFloatVector(static_cast<float*>(shadowColor));
}

void FontShader::renderShader(int xIndexCount)
{
		int temp = aIndexCount;
		aIndexCount = xIndexCount;

		AbstractShader::renderShader();

		aIndexCount = temp;
}

STATUS FontShader::createPolygonLayout(D3D10_INPUT_ELEMENT_DESC ** xPolygonLayout)
{
	*xPolygonLayout = TextureVertex::aPolygonLayout;

	return STATUS_OK;
}

unsigned int FontShader::getPolygonLayoutElementCount()
{
	return 2;
}
