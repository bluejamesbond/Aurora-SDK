
#include "../../include/ExtLibs.h"
#include "../../include/TextureShader.h"

using namespace A2D;

TextureShader::TextureShader(ID3D10Device ** xDXDevice, float ** xWorldMatrix, float ** xViewMatrix, float ** xProjectionMatrix) : 
aDXDevice(xDXDevice), aWorldMatrix(xWorldMatrix), aViewMatrix(xViewMatrix), aProjectionMatrix(xProjectionMatrix) {}

TextureShader::~TextureShader(){}

HRESULT TextureShader::Initialize()
{
	HRESULT hr = S_OK;

	D3D10_INPUT_ELEMENT_DESC polygonLayout[2];
	unsigned int numElements;
	D3D10_PASS_DESC passDesc;

	// Cache the device onto L1 CPU cache for speed
	ID3D10Device * device = *aDXDevice;

	// Use the DXShaderUtils to create a shader
	// and cache it.
	hr = DXShaderUtils::LoadShaderFromFile(L"../../../Aurora-SDK/Lib/Assets/Shaders/texture.fx", device, &aEffect);
	if (FAILED(hr))			return hr;

	// Create alpha channel supported blend states
	// and cache it for reuse.
	hr = DXShaderUtils::CreatePNGCompatibleBlendStates(device, &aBlendState, &aBlendDisabledState);
	if (FAILED(hr))			return hr;

	// Get a pointer to the technique inside the shader.
	aTechnique = aEffect->GetTechniqueByName("MainTechnique");
	if (!aTechnique)		return E_FAIL;

	// Now setup the layout of the data that goes into the shader.
	// This setup needs to match the VertexData stucture.
	// This is based on Quad input data which in this case is
	// VertexData
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

	// Get the description of the first pass 
	// described in the shader technique.
	aTechnique->GetPassByIndex(0)->GetDesc(&passDesc);

	// Create the input layout.
	hr = device->CreateInputLayout(polygonLayout, numElements, passDesc.pIAInputSignature, passDesc.IAInputSignatureSize, &aLayout);
	if (FAILED(hr))		return hr;

	// Get pointers to the three matrices inside the 
	// shader so we can update them from this class.
	aWorldMatrixPtr = aEffect->GetVariableByName("worldMatrix")->AsMatrix();
	aViewMatrixPtr = aEffect->GetVariableByName("viewMatrix")->AsMatrix();
	aProjectionMatrixPtr = aEffect->GetVariableByName("projectionMatrix")->AsMatrix();
	aTexturePtr = aEffect->GetVariableByName("shaderTexture")->AsShaderResource();
	
	// Load the matrices
	loadMatrices();

	return hr;
}

void TextureShader::loadMatrices()
{
	// Set the world matrix variable 
	// inside the shader.
	aWorldMatrixPtr->SetMatrix(*aWorldMatrix);

	// Set the view matrix variable 
	// minside the shader.
	aViewMatrixPtr->SetMatrix(*aViewMatrix);

	// Set the projection matrix variable 
	// inside the shader.
	aProjectionMatrixPtr->SetMatrix(*aProjectionMatrix);
}

void TextureShader::setTexture(Texture * xTexture)
{
	aTexture = xTexture;

	// Bind and update the texture.
	// Also cache the texture while doing so.!!!!
	aTexturePtr->SetResource(static_cast<ID3D10ShaderResourceView*>(xTexture->getPlatformCompatibleResource()));
}

void TextureShader::renderTexture()
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

LPCWSTR TextureShader::ToString()
{
	return L"TextureShader";
}

LPCWSTR TextureShader::GetClass()
{
	return L"TextureShader";
}

void TextureShader::Deinitialize()
{
	// Please add all the destroy data
}

bool TextureShader::operator==(Abstract * xAbstract)
{
	return false;
}