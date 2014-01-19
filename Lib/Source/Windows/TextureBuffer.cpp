
#include "../../../Include/Windows/ExtLibs.h"
#include "../../../Include/Windows/TextureBuffer.h"

using namespace A2D;

TextureBuffer::TextureBuffer(ID3D10Device ** xDevice, ID3D10DepthStencilView ** xBackBufferaDXDepthStencilView, Dims * xSize) :
aDevice(xDevice), aBackBufferaDXDepthStencilView(xBackBufferaDXDepthStencilView)
{
	aDims.aWidth = xSize->aWidth;
	aDims.aHeight = xSize->aHeight;
}

bool TextureBuffer::hasAlpha()
{
	// Force to be false
	return false;
}

STATUS TextureBuffer::initialize()
{
	D3D10_TEXTURE2D_DESC textureDesc;
	D3D10_RENDER_TARGET_VIEW_DESC renderTargetViewDesc;
	D3D10_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc;
	ID3D10Device * device = *aDevice;

	// initialize the render target texture description.
	ZeroMemory(&textureDesc, sizeof(textureDesc));

	// Setup the render target texture description.
	textureDesc.Width = SINT(aDims.aWidth);
	textureDesc.Height = SINT(aDims.aHeight);
	textureDesc.MipLevels = 1;
	textureDesc.ArraySize = 1;
	textureDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.Usage = D3D10_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D10_BIND_RENDER_TARGET | D3D10_BIND_SHADER_RESOURCE;
	textureDesc.CPUAccessFlags = 0;
	textureDesc.MiscFlags = 0;

	// Create the render target texture.
	SAFELY(device->CreateTexture2D(&textureDesc, NULL, &aDXRenderTargetTexture));

	// Setup the description of the render target view.
	renderTargetViewDesc.Format = textureDesc.Format;
	renderTargetViewDesc.ViewDimension = D3D10_RTV_DIMENSION_TEXTURE2D;
	renderTargetViewDesc.Texture2D.MipSlice = 0;

	// Create the render target view.
	SAFELY(device->CreateRenderTargetView(aDXRenderTargetTexture, &renderTargetViewDesc, &aDXRenderTargetView));

	// Setup the description of the shader resource view.
	shaderResourceViewDesc.Format = textureDesc.Format;
	shaderResourceViewDesc.ViewDimension = D3D10_SRV_DIMENSION_TEXTURE2D;
	shaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
	shaderResourceViewDesc.Texture2D.MipLevels = 1;
	
	// Create the shader resource view.
	SAFELY(device->CreateShaderResourceView(aDXRenderTargetTexture, &shaderResourceViewDesc, &aResource));

	return STATUS_OK;
}

void TextureBuffer::SetActive()
{
	ID3D10Device * device = *aDevice;

	// Bind the render target view and depth stencil buffer to the output render pipeline.
	device->OMSetRenderTargets(1, &aDXRenderTargetView, *aBackBufferaDXDepthStencilView);
}

void * TextureBuffer::getPlatformCompatibleResource()
{
	return aResource;
}

void TextureBuffer::Clear()
{
	float color[4];
	ID3D10Device * device = *aDevice;
	
	// Setup the color to clear the buffer to.
	color[0] = 1.0f;
	color[1] = 0.0f;
	color[2] = 0.0f;
	color[3] = 1.0f;

	// Clear the back buffer.
	device->ClearRenderTargetView(aDXRenderTargetView, color);

	// Clear the depth buffer.
	device->ClearDepthStencilView(*aBackBufferaDXDepthStencilView, D3D10_CLEAR_DEPTH, 1.0f, 0);
}

/////////////////////////////////////////////////////////////////////////////
// REQUIRED BY _ABSTRACT
////////////////////////////////////////////////////////////////////////////

TextureBuffer::~TextureBuffer()
{
	D3DDESTROY(aDXRenderTargetTexture);
	D3DDESTROY(aDXRenderTargetView);
	D3DDESTROY(aDXDepthStencilState);
	D3DDESTROY(aResource);
}
