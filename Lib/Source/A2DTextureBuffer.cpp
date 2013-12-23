
#include "../../include/A2DExtLibs.h"
#include "../../include/A2DTextureBuffer.h"

A2DTextureBuffer::A2DTextureBuffer(A2DBackBuffer * xBackBuffer, A2DDims * xSize) :
A2DAbstractTexture(xBackBuffer)
{
	aDims.aWidth = xSize->aWidth;
	aDims.aHeight = xSize->aHeight;
}

bool A2DTextureBuffer::hasAlpha()
{
	// Force to be false
	return false;
}

HRESULT A2DTextureBuffer::CreateResources(void * xArgs[])
{
	D3D10_TEXTURE2D_DESC textureDesc;
	HRESULT hr;
	D3D10_RENDER_TARGET_VIEW_DESC renderTargetViewDesc;
	D3D10_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc;

	// Initialize the render target texture description.
	ZeroMemory(&textureDesc, sizeof(textureDesc));

	// Setup the render target texture description.
	textureDesc.Width = (int)aDims.aWidth;
	textureDesc.Height = (int)aDims.aHeight;
	textureDesc.MipLevels = 1;
	textureDesc.ArraySize = 1;
	textureDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.Usage = D3D10_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D10_BIND_RENDER_TARGET | D3D10_BIND_SHADER_RESOURCE;
	textureDesc.CPUAccessFlags = 0;
	textureDesc.MiscFlags = 0;

	// Create the render target texture.
	hr = aBackBuffer->aDXDevice->CreateTexture2D(&textureDesc, NULL, &aDXRenderTargetTexture);
	if (FAILED(hr))		return hr;

	// Setup the description of the render target view.
	renderTargetViewDesc.Format = textureDesc.Format;
	renderTargetViewDesc.ViewDimension = D3D10_RTV_DIMENSION_TEXTURE2D;
	renderTargetViewDesc.Texture2D.MipSlice = 0;

	// Create the render target view.
	hr = aBackBuffer->aDXDevice->CreateRenderTargetView(aDXRenderTargetTexture, &renderTargetViewDesc, &aDXRenderTargetView);
	if (FAILED(hr))		return hr;

	// Setup the description of the shader resource view.
	shaderResourceViewDesc.Format = textureDesc.Format;
	shaderResourceViewDesc.ViewDimension = D3D10_SRV_DIMENSION_TEXTURE2D;
	shaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
	shaderResourceViewDesc.Texture2D.MipLevels = 1;
	
	// Create the shader resource view.
	hr = aBackBuffer->aDXDevice->CreateShaderResourceView(aDXRenderTargetTexture, &shaderResourceViewDesc, &aResource);
	if (FAILED(hr))		return hr;

	return hr;
}

void A2DTextureBuffer::Update(void * xArgs[])
{
	// Change size and stuff here	
}

void A2DTextureBuffer::Render()
{
	// No real rendering for textures to do. They just act as containers in the pipeline.
}

void A2DTextureBuffer::SetActive()
{
	// Bind the render target view and depth stencil buffer to the output render pipeline.
	aBackBuffer->aDXDevice->OMSetRenderTargets(1, &aDXRenderTargetView, aBackBuffer->aDXDepthStencilView);
}

void A2DTextureBuffer::DestroyResources()
{
	A2DAbstractTexture::DestroyResources();
	
	// Delete all the other global variables created for a texture except for ones like A2DDim and A2DRect
}

void A2DTextureBuffer::Clear()
{
	float color[4];
	
	// Setup the color to clear the buffer to.
	color[0] = 1.0f;
	color[1] = 0.0f;
	color[2] = 0.0f;
	color[3] = 1.0f;

	// Clear the back buffer.
	aBackBuffer->aDXDevice->ClearRenderTargetView(aDXRenderTargetView, color);

	// Clear the depth buffer.
	aBackBuffer->aDXDevice->ClearDepthStencilView(aBackBuffer->aDXDepthStencilView, D3D10_CLEAR_DEPTH, 1.0f, 0);
}

/////////////////////////////////////////////////////////////////////////////
// REQUIRED BY A2D_ABSTRACT
////////////////////////////////////////////////////////////////////////////

LPCWSTR A2DTextureBuffer::GetClass()
{
	return L"A2DTextureBuffer";
}

LPCWSTR A2DTextureBuffer::ToString()
{
	return L"A2DTextureBuffer";
}

bool A2DTextureBuffer::operator==(A2DAbstract * xAbstract)
{
	return false;
}