
#include "../../Include/A2DExtLibs.h"
#include "../../Include/A2DFrame.h"

A2DFrame::A2DFrame(HINSTANCE * xHInstance) : aHInstance(xHInstance) {}

A2DFrame::~A2DFrame(){}

HRESULT A2DFrame::CreateResources()
{
	return S_OK;
}

LRESULT A2DFrame::PumpWindowMsg(HWND * xHwnd, UINT * xMessage, WPARAM * xWParam, LPARAM * xLParam)
{
	return S_OK;
}

void A2DFrame::Update()
{
	
}

void A2DFrame::SetVisible(bool xVisible)
{
	aWindow->setVisible(xVisible);
}


/////////////////////////////////////////////////////////////////////////////
// REQUIRED BY A2D_ABSTRACT
/////////////////////////////////////////////////////////////////////////////

LPCWSTR A2DFrame::GetClass()
{
	return L"A2DFrame";
}

LPCWSTR A2DFrame::ToString()
{
	return L"A2DFrame";
}

bool A2DFrame::operator==(A2DAbstract * xAbstract)
{
	return false;
}

HRESULT A2DFrame::Initialize()
{
	HRESULT hr;	

	// -----------------------------------------------------

	aWindow = new A2DWindow(aHInstance);

	hr = aWindow->Initialize();
	if (FAILED(hr))	return hr;

	// -----------------------------------------------------

	aWindow->setFrame(this);

	// -----------------------------------------------------
	
	return hr;
}

void A2DFrame::Deinitialize()
{
	// Release the D3D object.
	if (aWindow)
	{
		aWindow->Deinitialize();
		delete aWindow;
		aWindow = 0;
	}
}