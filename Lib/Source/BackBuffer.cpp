
#include "../../include/ExtLibs.h"
#include "../../include/BackBuffer.h"

using namespace A2D;

BackBuffer::BackBuffer(AbstractWindow * xWindow, GXSettings * xGXSettings)
{
	memcpy(&aSettings, xGXSettings, sizeof(GXSettings));
	aWindow = xWindow;
}

BackBuffer::~BackBuffer()
{
	D3DDESTROY(aDXDepthStencilState);
	D3DDESTROY(aDXRasterState);
	D3DDESTROY(aDXDepthStencilView);
	D3DDESTROY(aDXDepthStencilState);
	D3DDESTROY(aDXDepthStencilBuffer);
	D3DDESTROY(aDXRenderTargetView);
	D3DDESTROY(aDXGISwapChain);
	D3DDESTROY(aDevice);
}

Dims * BackBuffer::getSize()
{
	return &aDims;
}

GXSettings * BackBuffer::getSettings()
{
	return &aSettings;
}

HRESULT BackBuffer::initialize()
{
	IDXGIFactory* factory;
	IDXGIAdapter* adapter;
	IDXGIOutput* adapterOutput;
	DXGI_MODE_DESC* displayModeList;
	DXGI_ADAPTER_DESC adapterDesc;
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ID3D10Texture2D* backBufferPtr;
	D3D10_TEXTURE2D_DESC& depthBufferDesc = aDepthBufferDesc;
	D3D10_DEPTH_STENCIL_DESC depthStencilDesc;
	D3D10_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
	D3D10_VIEWPORT& viewport = aViewport;
	D3D10_RASTERIZER_DESC rasterDesc;
	D3D10_DEPTH_STENCIL_DESC depthDisabledStencilDesc;
	ID3D10Device * device;
	Dims& windowDims = aWindow->getSize();

	unsigned int numModes, i, numerator = 0, denominator = 1, stringLength;
	int videoCardMemory, width = windowDims.aWidth, height = windowDims.aHeight;
	char videoCardDescription[128];

	// Create a DirectX graphics interface factory.
	SAFELY(CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory));

	// Use the factory to create an adapter for the primary 
	// graphics interface (video card).
	SAFELY(factory->EnumAdapters(0, &adapter));	

	// Enumerate the primary adapter output (monitor).
	SAFELY(adapter->EnumOutputs(0, &adapterOutput));	

	// Get the number of modes that fit the 
	// DXGI_FORMAT_R8G8B8A8_UNORM display format 
	// for the adapter output (monitor).
	SAFELY(adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, NULL));	

	// Create a list to hold all the possible display 
	// modes for this monitor/video card combination.
	NULLCHECK((displayModeList = new DXGI_MODE_DESC[numModes]));

	// Now fill the display mode list structures.
	SAFELY(adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, displayModeList));
	
	// Now go through all the display modes and find 
	// the one that matches the screen width and height.
	// When a match is found store the numerator and 
	// denominator of the refresh rate for that monitor.
	for (i = 0; i < numModes; i++)
	{
		if (displayModeList[i].Width == width)
		{
			if (displayModeList[i].Height == height)
			{
				numerator = displayModeList[i].RefreshRate.Numerator;
				denominator = displayModeList[i].RefreshRate.Denominator;
			}
		}
	}

	// Get the adapter (video card) description.
	SAFELY(adapter->GetDesc(&adapterDesc));
	
	// Store the dedicated video card memory in
	// megabytes.
	videoCardMemory = (int)(adapterDesc.DedicatedVideoMemory / 1024 / 1024);

	// Convert the name of the video card to a 
	// character array and store it.
	SAFELY(wcstombs_s(&stringLength, videoCardDescription, 128, adapterDesc.Description, 128));

	// Release the display mode list.
	delete[] displayModeList;
	displayModeList = 0;

	// Release the adapter output.
	D3DDESTROY(adapterOutput);

	// Release the adapter.
	D3DDESTROY(adapter);

	// Release the factory.
	D3DDESTROY(factory);

	// initialize the swap chain description.
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));

	// Set to a single back buffer.
	swapChainDesc.BufferCount = 1;

	// Set the width and height of the back buffer.
	swapChainDesc.BufferDesc.Width = width;
	swapChainDesc.BufferDesc.Height = height;

	// Set regular 32-bit surface for the back buffer.
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	// Set the refresh rate of the back buffer.
	if (aSettings.aVsync)
	{
		swapChainDesc.BufferDesc.RefreshRate.Numerator = numerator;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = denominator;
	}
	else
	{
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	}

	// Set the usage of the back buffer.
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	// Set the handle for the window to render to.
	swapChainDesc.OutputWindow = *static_cast<HWND*>(aWindow->getPlatformCompatibleWindowHandle());

	// Turn multisampling off.
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;

	// Set to full screen or windowed mode.
	if (aSettings.aFullScreen)
	{
		swapChainDesc.Windowed = false;
	}
	else
	{
		swapChainDesc.Windowed = true;
	}

	// Set the scan line ordering and scaling to 
	// unspecified.
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	// Discard the back buffer contents after presenting.
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	// Don't set the advanced flags.
	swapChainDesc.Flags = 0;

	// Create the swap chain and the Direct3D device.
	SAFELY(D3D10CreateDeviceAndSwapChain(NULL, D3D10_DRIVER_TYPE_HARDWARE, NULL, 0, D3D10_SDK_VERSION,
		&swapChainDesc, &aDXGISwapChain, &aDevice));
	
	// Local copy
	device = aDevice;

	// Get the pointer to the back buffer.
	SAFELY(aDXGISwapChain->GetBuffer(0, __uuidof(ID3D10Texture2D), (LPVOID*)&backBufferPtr));
	

	// Create the render target view with the 
	// back buffer pointer.
	SAFELY(device->CreateRenderTargetView(backBufferPtr, NULL, &aDXRenderTargetView));
	

	// Release pointer to the back buffer as we 
	// no longer need it.
	backBufferPtr->Release();
	backBufferPtr = 0;

	// initialize the description of the depth buffer.
	ZeroMemory(&depthBufferDesc, sizeof(depthBufferDesc));

	// Set up the description of the depth buffer.
	depthBufferDesc.Width = width;
	depthBufferDesc.Height = height;
	depthBufferDesc.MipLevels = 1;
	depthBufferDesc.ArraySize = 1;
	depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthBufferDesc.SampleDesc.Count = 1;
	depthBufferDesc.SampleDesc.Quality = 0;
	depthBufferDesc.Usage = D3D10_USAGE_DEFAULT;
	depthBufferDesc.BindFlags = D3D10_BIND_DEPTH_STENCIL;
	depthBufferDesc.CPUAccessFlags = 0;
	depthBufferDesc.MiscFlags = 0;

	// Create the texture for the depth buffer using 
	// the filled out description.
	SAFELY(device->CreateTexture2D(&depthBufferDesc, NULL, &aDXDepthStencilBuffer));
	

	// initialize the description of the stencil state.
	ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));

	// Set up the description of the stencil state.
	depthStencilDesc.DepthEnable = true;
	depthStencilDesc.DepthWriteMask = D3D10_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D10_COMPARISON_LESS;

	depthStencilDesc.StencilEnable = true;
	depthStencilDesc.StencilReadMask = 0xFF;
	depthStencilDesc.StencilWriteMask = 0xFF;

	// Stencil operations if pixel is front-facing.
	depthStencilDesc.FrontFace.StencilFailOp = D3D10_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilDepthFailOp = D3D10_STENCIL_OP_INCR;
	depthStencilDesc.FrontFace.StencilPassOp = D3D10_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilFunc = D3D10_COMPARISON_ALWAYS;

	// Stencil operations if pixel is back-facing.
	depthStencilDesc.BackFace.StencilFailOp = D3D10_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilDepthFailOp = D3D10_STENCIL_OP_DECR;
	depthStencilDesc.BackFace.StencilPassOp = D3D10_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilFunc = D3D10_COMPARISON_ALWAYS;

	// Create the depth stencil state.
	SAFELY(device->CreateDepthStencilState(&depthStencilDesc, &aDXDepthStencilState));
	
	// Set the depth stencil state on the D3D device.
	device->OMSetDepthStencilState(aDXDepthStencilState, 1);

	// Initailze the depth stencil view.
	ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));

	// Set up the depth stencil view description.
	depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilViewDesc.ViewDimension = D3D10_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0;

	// Create the depth stencil view.
	SAFELY(device->CreateDepthStencilView(aDXDepthStencilBuffer, &depthStencilViewDesc, &aDXDepthStencilView));
	

	// Bind the render target view and depth stencil 
	// buffer to the output render pipeline.
	device->OMSetRenderTargets(1, &aDXRenderTargetView, aDXDepthStencilView);

	// Setup the raster description which will determine
	// how and what polygons will be drawn.
	rasterDesc.AntialiasedLineEnable = false;
	rasterDesc.CullMode = D3D10_CULL_BACK;
	rasterDesc.DepthBias = 0;
	rasterDesc.DepthBiasClamp = 0.0f;
	rasterDesc.DepthClipEnable = true;
	rasterDesc.FillMode = D3D10_FILL_SOLID;
	rasterDesc.FrontCounterClockwise = false;
	rasterDesc.MultisampleEnable = false;
	rasterDesc.ScissorEnable = false;
	rasterDesc.SlopeScaledDepthBias = 0.0f;

	// Create the rasterizer state from the 
	// description we just filled out.
	SAFELY(device->CreateRasterizerState(&rasterDesc, &aDXRasterState));

	// Now set the rasterizer state.
	device->RSSetState(aDXRasterState);
	
	// Setup the viewport for rendering.
	viewport.Width = aDims.aWidth = width;
	viewport.Height = aDims.aHeight = height;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;

	// Create the viewport.
	aDevice->RSSetViewports(1, &viewport);

	// Clear the second depth stencil state 
	// before setting the parameters.
	ZeroMemory(&depthDisabledStencilDesc, sizeof(depthDisabledStencilDesc));

	// Now create a second depth stencil state which 
	// turns off the Z buffer for 2D rendering.  The 
	// only difference is  that DepthEnable is set to 
	// false, all other parameters  are the same as 
	//the other depth stencil state.
	depthDisabledStencilDesc.DepthEnable = false;
	depthDisabledStencilDesc.DepthWriteMask = D3D10_DEPTH_WRITE_MASK_ALL;
	depthDisabledStencilDesc.DepthFunc = D3D10_COMPARISON_LESS;
	depthDisabledStencilDesc.StencilEnable = true;
	depthDisabledStencilDesc.StencilReadMask = 0xFF;
	depthDisabledStencilDesc.StencilWriteMask = 0xFF;
	depthDisabledStencilDesc.FrontFace.StencilFailOp = D3D10_STENCIL_OP_KEEP;
	depthDisabledStencilDesc.FrontFace.StencilDepthFailOp = D3D10_STENCIL_OP_INCR;
	depthDisabledStencilDesc.FrontFace.StencilPassOp = D3D10_STENCIL_OP_KEEP;
	depthDisabledStencilDesc.FrontFace.StencilFunc = D3D10_COMPARISON_ALWAYS;
	depthDisabledStencilDesc.BackFace.StencilFailOp = D3D10_STENCIL_OP_KEEP;
	depthDisabledStencilDesc.BackFace.StencilDepthFailOp = D3D10_STENCIL_OP_DECR;
	depthDisabledStencilDesc.BackFace.StencilPassOp = D3D10_STENCIL_OP_KEEP;
	depthDisabledStencilDesc.BackFace.StencilFunc = D3D10_COMPARISON_ALWAYS;

	// Create the state using the device.
	SAFELY(device->CreateDepthStencilState(&depthDisabledStencilDesc, &aDXDepthDisabledStencilState));	

	// Set the type of primitive that should be 
	// rendered from this vertex buffer, in this case triangles.
	device->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return S_OK;
}

void BackBuffer::setActive()
{		
	// Reset the render target back to the original back
	// buffer and not the render to texture anymore.
	aDevice->OMSetRenderTargets(1, &aDXRenderTargetView, aDXDepthStencilView);
	return;
}

void BackBuffer::clear()
{
	float color[4];

	color[0] = 0.17f;
	color[1] = 0.17f;
	color[2] = 0.18f;
	color[3] = 1.0f;

	// Clear the back buffer.
	aDevice->ClearRenderTargetView(aDXRenderTargetView, color);

	// Clear the depth buffer.
	aDevice->ClearDepthStencilView(aDXDepthStencilView, D3D10_CLEAR_DEPTH, 1.0f, 0);
}

void BackBuffer::swap()
{
	// Present the back buffer to the screen since
	// rendering is complete.

	// Lock to screen refresh rate or present as fast as possible
	aDXGISwapChain->Present(0, 0);
}

ID3D10Device ** BackBuffer::getDevice()
{
	return &aDevice;
}

void BackBuffer::setZBuffer(bool val)
{
	aDevice->OMSetDepthStencilState(val ? aDXDepthStencilState : aDXDepthDisabledStencilState, 1);
}

LPCWSTR BackBuffer::getClass()
{
	return L"BackBuffer";
}

LPCWSTR BackBuffer::toString()
{
	return L"BackBuffer";
}

void BackBuffer::validate()
{
	///// CODE SHOULD BE FUNCTIONALIZED /////////////////
	///// CODE SHOULD BE FUNCTIONALIZED /////////////////
	///// CODE SHOULD BE FUNCTIONALIZED /////////////////
	///// CODE SHOULD BE FUNCTIONALIZED /////////////////
	///// CODE SHOULD BE FUNCTIONALIZED /////////////////
	///// CODE SHOULD BE FUNCTIONALIZED /////////////////
	///// CODE SHOULD BE FUNCTIONALIZED /////////////////
	///// CODE SHOULD BE FUNCTIONALIZED /////////////////
	///// CODE SHOULD BE FUNCTIONALIZED /////////////////
	///// CODE SHOULD BE FUNCTIONALIZED /////////////////

	Dims& windowDims = aWindow->getSize();
	D3D10_TEXTURE2D_DESC& depthBufferDesc = aDepthBufferDesc; // reuse for performance
	D3D10_VIEWPORT& viewport = aViewport;
	ID3D10Texture2D* backBuffer;
	ID3D10Device * device = aDevice;
	IDXGISwapChain  *  swapChain = aDXGISwapChain;

	aDXRenderTargetView->Release();
	aDXDepthStencilView->Release();
	aDXDepthStencilBuffer->Release();

	// Resize the swap chain and recreate the 
	// render target view.
	G_SAFELY(swapChain->ResizeBuffers(0, 0, 0, DXGI_FORMAT_UNKNOWN, 0));
	G_SAFELY(swapChain->GetBuffer(0, __uuidof(ID3D10Texture2D), reinterpret_cast<void**>(&backBuffer)));
	G_SAFELY(device->CreateRenderTargetView(backBuffer, 0, &aDXRenderTargetView));
	
	D3DDESTROY(backBuffer);
	
	// Update depth buffer description
	depthBufferDesc.Width = windowDims.aWidth;
	depthBufferDesc.Height = windowDims.aHeight;

	G_SAFELY(device->CreateTexture2D(&depthBufferDesc, 0, &aDXDepthStencilBuffer));
	G_SAFELY(device->CreateDepthStencilView(aDXDepthStencilBuffer, 0, &aDXDepthStencilView));

	viewport.Width = aDims.aWidth = windowDims.aWidth;
	viewport.Height = aDims.aHeight = windowDims.aHeight;

	device->RSSetViewports(1, &viewport);
}