
#include "../../Include/A2DExtLibs.h"
#include "../../Include/A2DFrame.h"
//#include "../../Include/A2DWindow.h"

A2DFrame::A2DFrame(HINSTANCE  xHInstance) : aHInstance(xHInstance) {}

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

// Mutators.

void A2DFrame::SetName(LPCWSTR xName)
{
	aWindow->setName(xName);
}

void A2DFrame::SetBounds(A2DRect * xRect)
{
	aWindow->getBounds()->aHeight = xRect->aHeight;
	aWindow->getBounds()->aWidth = xRect->aWidth;
	aWindow->getBounds()->aX = xRect->aX;
	aWindow->getBounds()->aY = xRect->aY;
}

void A2DFrame::SetBounds(float xLeft, float xTop, float xWidth, float xHeight)
{
	aWindow->getBounds()->aHeight = xHeight;
	aWindow->getBounds()->aWidth = xWidth;
	aWindow->getBounds()->aX = xLeft;
	aWindow->getBounds()->aY = xTop;
}

void A2DFrame::SetSize(float xWidth, float xHeight)
{
	aWindow->getBounds()->aHeight = xHeight;
	aWindow->getBounds()->aWidth = xWidth;
}

void A2DFrame::SetSize(A2DDims * xDims)
{
	aWindow->getBounds()->aHeight = xDims->aHeight;
	aWindow->getBounds()->aWidth = xDims->aWidth;
}

void A2DFrame::SetUndecorated(bool xDecorated)
{
	aWindow->setUndecorated(xDecorated);
}

void A2DFrame::SetLocationRelativeTo(A2DFrame * xFrame)
{
	aWindow->setLocationRelativeTo(xFrame->aWindow); //	WTF IS THIS INPUT FRAME BUT NEED WINDOW WTF
}

void A2DFrame::SetVsync(bool xVsync)
{
	// A2DWindow doesn't have vsync yet.
}

void A2DFrame::SetDefaultCloseOperation(int xOperation)
{
	aWindow->setDefaultCloseOperation(xOperation);
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

#ifdef _WIN32

	aWindow = new A2DMSWindow(aHInstance);

#elif __UNIX

	aWindow = new A2DLXWindow();

#endif

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