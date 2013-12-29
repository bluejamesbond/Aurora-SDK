
#include "../../include/ExtLibs.h"
#include "../../include/DXShaderUtils.h"

HRESULT DXShaderUtils::LoadShaderFromFile(LPCWSTR xFilename, ID3D10Device * aDXDevice, ID3D10Effect ** xEffect)
{
	HRESULT hr;
	ID3D10Blob* errorMessage;

	// Initialize the error message.
	errorMessage = 0;

	// Load the shader in from the file.
	hr = D3DX10CreateEffectFromFile(xFilename, NULL, NULL, "fx_4_0", D3D10_SHADER_ENABLE_STRICTNESS, 0,
		aDXDevice, NULL, NULL, xEffect, &errorMessage, NULL);

	if (FAILED(hr))
	{
		// If the shader failed to compile it should have writen something to the error message.
		if (errorMessage)
		{
			SysOut(errorMessage, &xFilename);
		}
		// If there was  nothing in the error message then it simply could not find the shader file itself.
		else
		{
			// MessageBox(*aHWnd, xFilename, L"Missing Shader File", MB_OK);
		}

		return hr;
	}

	return hr;
}

void DXShaderUtils::SysOut(ID3D10Blob * xErrorMessage, LPCWSTR * xFilename){}

HRESULT DXShaderUtils::CreatePNGCompatibleBlendStates(ID3D10Device * aDXDevice, ID3D10BlendState ** xBlendState, ID3D10BlendState ** xBlendDisabledState)
{
	HRESULT hr = S_OK;
	D3D10_BLEND_DESC blendDesc;

	ZeroMemory(&blendDesc, sizeof(blendDesc));
	blendDesc.BlendEnable[0] = TRUE;
	blendDesc.RenderTargetWriteMask[0] = D3D10_COLOR_WRITE_ENABLE_ALL;
	blendDesc.SrcBlend = D3D10_BLEND_SRC_ALPHA;
	blendDesc.DestBlend = D3D10_BLEND_INV_SRC_ALPHA;
	blendDesc.BlendOp = D3D10_BLEND_OP_ADD;
	blendDesc.SrcBlendAlpha = D3D10_BLEND_ONE;
	blendDesc.DestBlendAlpha = D3D10_BLEND_ZERO;
	blendDesc.BlendOpAlpha = D3D10_BLEND_OP_ADD;

	hr = aDXDevice->CreateBlendState(&blendDesc, xBlendState);
	if (FAILED(hr))		return hr;

	blendDesc.BlendEnable[0] = FALSE;

	hr = aDXDevice->CreateBlendState(&blendDesc, xBlendDisabledState);
	if (FAILED(hr))		return hr;

	return hr;
}