
#include "../../include/A2DExtLibs.h"
#include "../../include/A2DTextureShader.h"

HRESULT A2DTextureShader::CreateResources(void * xArgs[])
{
	HRESULT hr = S_OK;
	
	// No need to pass any arguments for this step
	hr = A2DAbstractShader::CreateResources(NULL);
	if (FAILED(hr))		return hr;

	// Get pointers to the three matrices inside the shader so we can update them from this class.
	aWorldMatrixPtr = aEffect->GetVariableByName("worldMatrix")->AsMatrix();
	aViewMatrixPtr = aEffect->GetVariableByName("viewMatrix")->AsMatrix();
	aProjectionMatrixPtr = aEffect->GetVariableByName("projectionMatrix")->AsMatrix();
	aTexturePtr = aEffect->GetVariableByName("shaderTexture")->AsShaderResource();
	
	// Set the world matrix variable inside the shader.
	aWorldMatrixPtr->SetMatrix(static_cast<float*>(xArgs[0]));

	// Set the view matrix variable inside the shader.
	aViewMatrixPtr->SetMatrix(static_cast<float*>(xArgs[1]));

	// Set the projection matrix variable inside the shader.
	aProjectionMatrixPtr->SetMatrix(static_cast<float*>(xArgs[2]));

	// Bind the texture.
	aTexturePtr->SetResource(static_cast<ID3D10ShaderResourceView*>(xArgs[3]));

	return hr;
}

void A2DTextureShader::Update(void * xArgs[])
{
	// Bind the texture.
	aTexturePtr->SetResource(static_cast<ID3D10ShaderResourceView*>(xArgs[0]));

	A2DAbstractShader::Render();
}

LPCWSTR A2DTextureShader::GetClass()
{
	return L"A2DTextureShader";
}

LPCWSTR A2DTextureShader::ToString()
{
	return L"A2DTextureShader";
}

bool A2DTextureShader::operator==(A2DAbstract * xAbstract)
{
	return false;
}