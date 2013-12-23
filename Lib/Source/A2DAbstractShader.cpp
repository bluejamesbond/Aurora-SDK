
#include "../../include/A2DExtLibs.h"
#include "../../include/A2DAbstractShader.h"

A2DAbstractShader::A2DAbstractShader(A2DBackBuffer * xBackBuffer) : 
A2DPipelineComponent(xBackBuffer){}
A2DAbstractShader::~A2DAbstractShader(){}

HRESULT A2DAbstractShader::LoadFromFile(LPCWSTR * xFilename)
{
	HRESULT hr;
	ID3D10Blob* errorMessage;

	// Initialize the error message.
	errorMessage = 0;

	// Load the shader in from the file.
	hr = D3DX10CreateEffectFromFile(*xFilename, NULL, NULL, "fx_4_0", D3D10_SHADER_ENABLE_STRICTNESS, 0,
		aDXDevice, NULL, NULL, &aEffect, &errorMessage, NULL);

	if (FAILED(hr))
	{
		// If the shader failed to compile it should have writen something to the error message.
		if (errorMessage)
		{
			SysOut(errorMessage, xFilename);
		}
		// If there was  nothing in the error message then it simply could not find the shader file itself.
		else
		{
			MessageBox(*aHWnd, *xFilename, L"Missing Shader File", MB_OK);
		}

		return hr;
	}

	return hr;
}

void A2DAbstractShader::SysOut(ID3D10Blob * xErrorMessage, LPCWSTR * xFilename){}

ID3D10BlendState *	A2DAbstractShader::aBlendState = NULL;
ID3D10BlendState *	A2DAbstractShader::aBlendDisabledState = NULL;

HRESULT A2DAbstractShader::CreateResources(void * xArgs[])
{
	HRESULT hr = S_OK;
	D3D10_INPUT_ELEMENT_DESC polygonLayout[2];
	unsigned int numElements;
	D3D10_PASS_DESC passDesc;

	// Get a pointer to the technique inside the shader.
	aTechnique = aEffect->GetTechniqueByName("A2DShaderTechnique");
	if (!aTechnique)		return hr;

	// Now setup the layout of the data that goes into the shader.
	// This setup needs to match the VertexType stucture in the ModelClass and in the shader.
	polygonLayout[0].SemanticName = "POSITION";
	polygonLayout[0].SemanticIndex = 0;
	polygonLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[0].InputSlot = 0;
	polygonLayout[0].AlignedByteOffset = 0;
	polygonLayout[0].InputSlotClass = D3D10_INPUT_PER_VERTEX_DATA;
	polygonLayout[0].InstanceDataStepRate = 0;

	polygonLayout[1].SemanticName = "TEXCOORD";
	polygonLayout[1].SemanticIndex = 0;
	polygonLayout[1].Format = DXGI_FORMAT_R32G32_FLOAT;
	polygonLayout[1].InputSlot = 0;
	polygonLayout[1].AlignedByteOffset = D3D10_APPEND_ALIGNED_ELEMENT;
	polygonLayout[1].InputSlotClass = D3D10_INPUT_PER_VERTEX_DATA;
	polygonLayout[1].InstanceDataStepRate = 0;

	// Get a count of the elements in the layout.
	numElements = sizeof(polygonLayout) / sizeof(polygonLayout[0]);

	// Get the description of the first pass described in the shader technique.
	aTechnique->GetPassByIndex(0)->GetDesc(&passDesc);

	// Create the input layout.
	hr = aDXDevice->CreateInputLayout(polygonLayout, numElements, passDesc.pIAInputSignature, passDesc.IAInputSignatureSize, &aLayout);
	if (FAILED(hr))		return hr;

	return hr;
}

void A2DAbstractShader::Render()
{
	D3D10_TECHNIQUE_DESC techniqueDesc;
	unsigned int i;

	// if (aTexture->loaded)aDXDevice->OMSetBlendState(g_pBlendState, 0, 0xffffffff);
	// else aDXDevice->OMSetBlendState(g_pBlendDisableState, 0, 0xffffffff);

	// Set the input layout.
	aDXDevice->IASetInputLayout(aLayout);

	// Get the description structure of the technique from inside the shader so it can be used for rendering.
	aTechnique->GetDesc(&techniqueDesc);

	// Go through each pass in the technique (should be just one currently) and render the triangles.
	for (i = 0; i < techniqueDesc.Passes; ++i)
	{
		aTechnique->GetPassByIndex(i)->Apply(0);
		aDXDevice->DrawIndexed(6, 0, 0);
	}
}

HRESULT A2DAbstractShader::CreateBlendStates()
{

	if (aBlendState && aBlendDisabledState)
	{
		return S_OK;
	}

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

	hr = aDXDevice->CreateBlendState(&blendDesc, &aBlendState);
	if (FAILED(hr))		return hr;

	blendDesc.BlendEnable[0] = FALSE;

	hr = aDXDevice->CreateBlendState(&blendDesc, &aBlendDisabledState);
	if (FAILED(hr))		return hr;

	return hr;
}

HRESULT A2DAbstractShader::Initialize()
{
	HRESULT hr = S_OK;

	hr = CreateBlendStates();
	if (FAILED(hr))		return hr;
		
	return hr;
}

void A2DAbstractShader::Deinitialize(){}

LPCWSTR A2DAbstractShader::GetClass()
{
	return L"A2DAbstractShader";
}

LPCWSTR A2DAbstractShader::ToString()
{
	return L"A2DAbstractShader";
}

bool A2DAbstractShader::operator==(A2DAbstract * xAbstract)
{
	return false;
}