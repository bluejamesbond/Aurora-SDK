
#include "../../include/A2DExtLibs.h"
#include "../../include/A2DBackBuffer.h"

A2DBackBuffer::A2DBackBuffer(A2DAbstractWindow * xWindow, A2DGXSettings * xGXSettings) :
aGXSettings(xGXSettings),
aWindow(xWindow),
aDXGISwapChain(0),
aDXDevice(0),
aDXRenderTargetView(0),
aDXDepthStencilBuffer(0),
aDXDepthStencilState(0),
aDXDepthStencilView(0),
aDXRasterState(0),
aDXDepthDisabledStencilState(0) {}

A2DBackBuffer::~A2DBackBuffer(){}

HRESULT A2DBackBuffer::Initialize()
{
	HRESULT hr;

	IDXGIFactory* factory;
	IDXGIAdapter* adapter;
	IDXGIOutput* adapterOutput;
	DXGI_MODE_DESC* displayModeList;
	DXGI_ADAPTER_DESC adapterDesc;
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ID3D10Texture2D* backBufferPtr;
	D3D10_TEXTURE2D_DESC depthBufferDesc;
	D3D10_DEPTH_STENCIL_DESC depthStencilDesc;
	D3D10_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
	D3D10_VIEWPORT viewport;
	D3D10_RASTERIZER_DESC rasterDesc;
	D3D10_DEPTH_STENCIL_DESC depthDisabledStencilDesc;

	unsigned int numModes, i, numerator = 0, denominator = 1, stringLength;
	int error, width = static_cast<int>(aWindow->getBounds().aWidth), height = static_cast<int>(aWindow->getBounds().aHeight);

	// Create a DirectX graphics interface factory.
	hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**) &factory);
	if (FAILED(hr))		return hr;

	// Use the factory to create an adapter for the primary graphics interface (video card).
	hr = factory->EnumAdapters(0, &adapter);
	if (FAILED(hr))		return hr;

	// Enumerate the primary adapter output (monitor).
	hr = adapter->EnumOutputs(0, &adapterOutput);
	if (FAILED(hr))		return hr;

	// Get the number of modes that fit the DXGI_FORMAT_R8G8B8A8_UNORM display format for the adapter output (monitor).
	hr = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, NULL);
	if (FAILED(hr))		return hr;

	// Create a list to hold all the possible display modes for this monitor/video card combination.
	displayModeList = new DXGI_MODE_DESC[numModes];
	if (!displayModeList)		return hr;

	// Now fill the display mode list structures.
	hr = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, displayModeList);
	if (FAILED(hr))		return hr;

	// Now go through all the display modes and find the one that matches the screen width and height.
	// When a match is found store the numerator and denominator of the refresh rate for that monitor.
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
	hr = adapter->GetDesc(&adapterDesc);
	if (FAILED(hr))		return hr;

	// Store the dedicated video card memory in megabytes.
	aVideoCardMemory = (int)(adapterDesc.DedicatedVideoMemory / 1024 / 1024);

	// Convert the name of the video card to a character array and store it.
	error = wcstombs_s(&stringLength, aVideoCardDescription, 128, adapterDesc.Description, 128);
	if (error != 0)		return hr = E_FAIL;

	// Release the display mode list.
	delete[] displayModeList;
	displayModeList = 0;

	// Release the adapter output.
	adapterOutput->Release();
	adapterOutput = 0;

	// Release the adapter.
	adapter->Release();
	adapter = 0;

	// Release the factory.
	factory->Release();
	factory = 0;

	// Initialize the swap chain description.
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));

	// Set to a single back buffer.
	swapChainDesc.BufferCount = 1;

	// Set the width and height of the back buffer.
	swapChainDesc.BufferDesc.Width = width;
	swapChainDesc.BufferDesc.Height = height;

	// Set regular 32-bit surface for the back buffer.
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	// Set the refresh rate of the back buffer.
	if (aGXSettings->aVsync)
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
	if (aGXSettings->aFullScreen)
	{
		swapChainDesc.Windowed = false;
	}
	else
	{
		swapChainDesc.Windowed = true;
	}

	// Set the scan line ordering and scaling to unspecified.
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	// Discard the back buffer contents after presenting.
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	// Don't set the advanced flags.
	swapChainDesc.Flags = 0;

	// Create the swap chain and the Direct3D device.
	hr = D3D10CreateDeviceAndSwapChain(NULL, D3D10_DRIVER_TYPE_HARDWARE, NULL, 0, D3D10_SDK_VERSION,
		&swapChainDesc, &aDXGISwapChain, &aDXDevice);
	if (FAILED(hr))		return hr;

	// Get the pointer to the back buffer.
	hr = aDXGISwapChain->GetBuffer(0, __uuidof(ID3D10Texture2D), (LPVOID*)&backBufferPtr);
	if (FAILED(hr))		return hr;

	// Create the render target view with the back buffer pointer.
	hr = aDXDevice->CreateRenderTargetView(backBufferPtr, NULL, &aDXRenderTargetView);
	if (FAILED(hr))		return hr;

	// Release pointer to the back buffer as we no longer need it.
	backBufferPtr->Release();
	backBufferPtr = 0;

	// Initialize the description of the depth buffer.
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

	// Create the texture for the depth buffer using the filled out description.
	hr = aDXDevice->CreateTexture2D(&depthBufferDesc, NULL, &aDXDepthStencilBuffer);
	if (FAILED(hr))		return hr;

	// Initialize the description of the stencil state.
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
	hr = aDXDevice->CreateDepthStencilState(&depthStencilDesc, &aDXDepthStencilState);
	if (FAILED(hr))		return hr;

	// Set the depth stencil state on the D3D device.
	aDXDevice->OMSetDepthStencilState(aDXDepthStencilState, 1);

	// Initailze the depth stencil view.
	ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));

	// Set up the depth stencil view description.
	depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilViewDesc.ViewDimension = D3D10_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0;

	// Create the depth stencil view.
	hr = aDXDevice->CreateDepthStencilView(aDXDepthStencilBuffer, &depthStencilViewDesc, &aDXDepthStencilView);
	if (FAILED(hr))		return hr;

	// Bind the render target view and depth stencil buffer to the output render pipeline.
	aDXDevice->OMSetRenderTargets(1, &aDXRenderTargetView, aDXDepthStencilView);

	// Setup the raster description which will determine how and what polygons will be drawn.
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

	// Create the rasterizer state from the description we just filled out.
	hr = aDXDevice->CreateRasterizerState(&rasterDesc, &aDXRasterState);
	if (FAILED(hr))
	{
		return hr;
	}

	// Now set the rasterizer state.
	aDXDevice->RSSetState(aDXRasterState);

	// Setup the viewport for rendering.
	viewport.Width = width;
	viewport.Height = height;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;

	// Create the viewport.
	aDXDevice->RSSetViewports(1, &viewport);
	
	// Clear the second depth stencil state before setting the parameters.
	ZeroMemory(&depthDisabledStencilDesc, sizeof(depthDisabledStencilDesc));

	// Now create a second depth stencil state which turns off the Z buffer for 2D rendering.  The only difference is 
	// that DepthEnable is set to false, all other parameters are the same as the other depth stencil state.
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
	hr = aDXDevice->CreateDepthStencilState(&depthDisabledStencilDesc, &aDXDepthDisabledStencilState);
	if (FAILED(hr))		return hr;

	return hr;
}


void A2DBackBuffer::Deinitialize()
{
	// Before shutting down set to windowed mode or when you release the 
	// swap chain it will throw an exception.

	if (aDXGISwapChain)
	{
		aDXGISwapChain->SetFullscreenState(false, NULL);
	}

	if (aDXDepthStencilState)
	{
		aDXDepthStencilState->Release();
		aDXDepthStencilState = 0;
	}

	if (aDXRasterState)
	{
		aDXRasterState->Release();
		aDXRasterState = 0;
	}

	if (aDXDepthStencilView)
	{
		aDXDepthStencilView->Release();
		aDXDepthStencilView = 0;
	}

	if (aDXDepthStencilState)
	{
		aDXDepthStencilState->Release();
		aDXDepthStencilState = 0;
	}

	if (aDXDepthStencilBuffer)
	{
		aDXDepthStencilBuffer->Release();
		aDXDepthStencilBuffer = 0;
	}

	if (aDXRenderTargetView)
	{
		aDXRenderTargetView->Release();
		aDXRenderTargetView = 0;
	}

	if (aDXGISwapChain)
	{
		aDXGISwapChain->Release();
		aDXGISwapChain = 0;
	}

	if (aDXDevice)
	{
		aDXDevice->Release();
		aDXDevice = 0;
	}

	return;
}

void A2DBackBuffer::SetActive()
{		
	// Reset the render target back to the original back buffer and not the render to texture anymore.
	aDXDevice->OMSetRenderTargets(1, &aDXRenderTargetView, aDXDepthStencilView);
	return;
}

void A2DBackBuffer::Clear()
{
	float color[4];

	color[0] = 0.17f;
	color[1] = 0.17f;
	color[2] = 0.18f;
	color[3] = 1.0f;

	// Clear the back buffer.
	aDXDevice->ClearRenderTargetView(aDXRenderTargetView, color);

	// Clear the depth buffer.
	aDXDevice->ClearDepthStencilView(aDXDepthStencilView, D3D10_CLEAR_DEPTH, 1.0f, 0);
}

void A2DBackBuffer::Swap()
{
	// Present the back buffer to the screen since
	// rendering is complete.

	// Lock to screen refresh rate or present as fast as possible
	aDXGISwapChain->Present(aGXSettings->aVsync ? 1 : 0, 0);
}

ID3D10Device * A2DBackBuffer::GetDevice()
{
	return aDXDevice;
}

void A2DBackBuffer::SetZBuffer(bool val)
{
	aDXDevice->OMSetDepthStencilState(val ? aDXDepthStencilState : aDXDepthDisabledStencilState, 1);
	return;
}

LPCWSTR A2DBackBuffer::GetClass()
{
	return L"A2DCamera";
}

LPCWSTR A2DBackBuffer::ToString()
{
	return L"A2DCamera";
}

bool A2DBackBuffer::operator==(A2DAbstract * xAbstract)
{
	return false;
}