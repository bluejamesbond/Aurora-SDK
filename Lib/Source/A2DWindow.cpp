
#include "../../include/A2DExtLibs.h"
#include "../../include/A2DWindow.h"

A2DWindow::A2DWindow(HINSTANCE * xHInstance, A2DWindowProperties* xWinProps) :
aHInstance(xHInstance),
aWindowProps(xWinProps)
{}

A2DWindow::~A2DWindow(){}

void A2DWindow::SetUndecorated(bool xUndecoratedFlag)
{
	// we cannot just use WS_POPUP style
    // WS_THICKFRAME: without this the window cannot be resized and so aero snap, de-maximizing and minimizing won't work
    // WS_SYSMENU: enables the context menu with the move, close, maximize, minize... commands (shift + right-click on the task bar item)
    // HOWEVER, this also enables the menu with the maximize buttons in the title bar, which will exist inside your client area and are clickable. 
    // WS_CAPTION: enables aero minimize animation/transition
    // WS_MAXIMIZEBOX, WS_MINIMIZEBOX: enable minimize/maximize

	LONG lStyle, lExStyle;

	lStyle = GetWindowLongPtr(aParentHwnd, GWL_STYLE);
	lExStyle = GetWindowLongPtr(aParentHwnd, GWL_EXSTYLE);

	lStyle &= xUndecoratedFlag ? ~(WS_CAPTION | WS_THICKFRAME | WS_MINIMIZE | WS_MAXIMIZE | WS_SYSMENU) : (WS_CAPTION | WS_THICKFRAME | WS_MINIMIZE | WS_MAXIMIZE | WS_SYSMENU);
	lStyle |= xUndecoratedFlag ? (WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP) : 0;
	lExStyle |= xUndecoratedFlag ? (WS_EX_LAYERED | WS_EX_APPWINDOW) : WS_EX_LAYERED;

	SetWindowLongPtr(aParentHwnd, GWL_STYLE, lStyle);
	SetWindowLongPtr(aParentHwnd, GWL_EXSTYLE, lExStyle);

	//SetWindowPos(aParentWin->aHwnd, HWND_TOP, aWindowProps->aRealLeft, aWindowProps->aRealTop, aCacheRealWidth, aCacheRealHeight, SWP_FRAMECHANGED);
	SetWindowPos(aParentHwnd, NULL, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOOWNERZORDER);
}

void A2DWindow::SetPadding(int xPad)
{
	// Default values will be used. They are defined in SampleWindow resources.
	// The final goal is to render this using pure GDI+ and cache it and reuse it during resize. 
	// So that way, you can actually set a windowPadding!
}

HWND* A2DWindow::GetChildHwnd()
{
	return &aChildHwnd;
}

void A2DWindow::SetShadow(bool xShadowFlag)
{
	if (!aOptionDecorated)
	{
		SetUndecorated(true);
	}
		
	aOptionShadow = xShadowFlag ? 1 : 0;

	RenderComponent();

}

void A2DWindow::SetPosition(int xLeft, int xTop)
{
	HDWP hdwp;
	hdwp = BeginDeferWindowPos(2);
	
	if (hdwp)
	{
		hdwp = DeferWindowPos(hdwp, aParentHwnd, NULL, xLeft, xTop, 0, 0, SWP_NOZORDER | SWP_NOSIZE | SWP_NOACTIVATE);
		hdwp = DeferWindowPos(hdwp, aChildHwnd, aParentHwnd, xLeft, xTop, 0, 0, SWP_NOZORDER | SWP_NOSIZE | SWP_NOACTIVATE);
	}

	if (hdwp)
	{
		EndDeferWindowPos(hdwp);
	}

	// No need to redraw since you are just moving.
}

void A2DWindow::SetSize(int xWidth, int xHeight)
{
	HDWP hdwp;
	hdwp = BeginDeferWindowPos(2);
	
	if (hdwp)
	{
		hdwp = DeferWindowPos(hdwp, aParentHwnd, NULL, 0, 0, xWidth, xHeight, SWP_NOZORDER | SWP_NOMOVE | SWP_NOACTIVATE);
		hdwp = DeferWindowPos(hdwp, aChildHwnd, aParentHwnd, 0, 0, xWidth, xHeight, SWP_NOZORDER | SWP_NOMOVE | SWP_NOACTIVATE);
	}

	if (hdwp)
	{
		EndDeferWindowPos(hdwp);
	}

	// Redraw
	Update();
}

void A2DWindow::SetPositionAndSize(int xLeft, int xTop, int xWidth, int xHeight)
{
	HDWP hdwp;
	hdwp = BeginDeferWindowPos(2);
	
	if (hdwp)
	{
		hdwp = DeferWindowPos(hdwp, aParentHwnd, NULL, xLeft, xTop, xWidth, xHeight, SWP_NOZORDER | SWP_NOACTIVATE);
		hdwp = DeferWindowPos(hdwp, aChildHwnd, aParentHwnd, xLeft, xTop, xWidth, xHeight, SWP_NOZORDER | SWP_NOACTIVATE);
	}

	if (hdwp)
	{
		EndDeferWindowPos(hdwp);
	}

	// Redraw
	Update();
}

void A2DWindow::SetTitle(LPCWSTR xTitleName)
{
	SetWindowText(aChildHwnd, xTitleName);
	SetWindowText(aParentHwnd, xTitleName);
}

ATOM A2DWindow::RegisterClass(HWND xHwnd)
{
	WNDCLASSEX wcex = { sizeof(WNDCLASSEX) };
	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wcex.lpfnWndProc = A2DWindow::WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = *aHInstance;
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = *aWindowProps->GetName();
	wcex.hIconSm = LoadIcon(*aHInstance, IDI_APPLICATION);

	return RegisterClassEx(&wcex);
}

void A2DWindow::RunMessageLoop()
{
	MSG msg;


	while (aOptionVisible)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (aFrame) aFrame->Update();
	}
}

HRESULT A2DWindow::CreateHandle(HWND& xHandler)
{
	HRESULT				hr;
	HWND				hWnd;
	HWND				hwndParent;
	int					left, top, width, height;
	DWORD				lStyle, lExStyle;
	LPCWSTR				className, titleName;
	
	left = xHandler == aParentHwnd ? aCacheRelativeX : aCacheRealX;
	top = xHandler == aParentHwnd ? aCacheRelativeY : aCacheRealY;
	width = xHandler == aParentHwnd ? aCacheRelativeWidth : aCacheRealWidth;
	height = xHandler == aParentHwnd ? aCacheRelativeHeight : aCacheRealHeight;
	lStyle = xHandler == aParentHwnd ? WS_POPUP | WS_OVERLAPPED : WS_POPUP;
	lExStyle = xHandler == aParentHwnd ? WS_EX_LAYERED | WS_EX_APPWINDOW : 0;
	hwndParent = xHandler == aParentHwnd ? HWND_DESKTOP : aParentHwnd;
	className = *aWindowProps->GetName();
	titleName = *aWindowProps->GetName();

	hWnd = CreateWindowEx(lExStyle, className, titleName, lStyle, left, top, 
						  width, height, hwndParent, NULL, *aHInstance, this);

	if (hWnd == 0)
	{
		DWORD hi = GetLastError();
		int i = 0;
	}
	
	hr = hWnd ? S_OK : E_FAIL;

	xHandler = hWnd;

	CurrentStyleProc = WS_EX_APPWINDOW;
	
	if (aChildHwnd && aParentHwnd)
	{
		// Force the child on top of parent!
		SetWindowPos(aChildHwnd, aParentHwnd, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
	}

	return hr;
}

void A2DWindow::Render()
{	
	RenderComponent();
	RenderComponentBorder();
}

void A2DWindow::Update()
{
	Render();

	// A2DAbstractComponent::Update(); <---- We will use this later. This is an example of inheritence and framwork coding!!

	HDC screenDC = GetDC(NULL);
	POINT ptDst = { aCacheRelativeX, aCacheRelativeY };
	POINT ptSrc = { 0, 0 };

	BLENDFUNCTION blendFunction;
	blendFunction.AlphaFormat = AC_SRC_ALPHA;
	blendFunction.BlendFlags = 0;
	blendFunction.BlendOp = AC_SRC_OVER;
	blendFunction.SourceConstantAlpha = 255;

	UpdateLayeredWindow(aParentHwnd, screenDC, &ptDst, &aWindowSize, aGraphics->GetHDC(), &ptSrc, 0, &blendFunction, 2);
}

HRESULT A2DWindow::CreateComponentResources()
{
	HRESULT hr;
	HDC hdc;
	HDC memDC;

	hr = S_OK;
	hdc = GetDC(aParentHwnd);
	memDC = CreateCompatibleDC(hdc);

	aWindowSize = { aCacheRelativeWidth, aCacheRelativeHeight };

	HBITMAP memBitmap = CreateCompatibleBitmap(hdc, aCacheRelativeWidth, aCacheRelativeHeight);

	SelectObject(memDC, memBitmap);

	aGraphics =  new Graphics(memDC);

	return hr;

}

void  A2DWindow::SetFrame(A2DFrame * xFrame)
{
	aFrame = xFrame;
}

void A2DWindow::SetVisible(bool xVisible)
{

	if(xVisible)
	{
		// Create resources!
		aFrame->CreateResources();

		ShowWindow(aChildHwnd, SW_SHOWNORMAL);
		ShowWindow(aParentHwnd, SW_SHOWNORMAL);
		aOptionVisible = xVisible;
		RunMessageLoop();
	}
	else
	{
		ShowWindow(aChildHwnd, SW_HIDE);
		ShowWindow(aParentHwnd, SW_HIDE);
		aOptionVisible = xVisible;
	}
}

void A2DWindow::RenderComponentBorder()
{
	Pen borderPen(Color(202, 225, 255), 1);
	
	aGraphics->DrawRectangle(&borderPen, aCachePadding, aCachePadding, aCacheRealWidth - aCachePadding * 2 - 1, aCacheRealHeight - aCachePadding * 2 - 1);
	
	DeleteObject(&borderPen);
}

void A2DWindow::RenderComponent()
{
	RenderComponentClear();

	Image topShadow(IDB_BSW_TOP_SHADOW_PNG);
	Image leftShadow(IDB_BSW_LEFT_SHADOW_PNG);
	Image rightShadow(IDB_BSW_RIGHT_SHADOW_PNG);
	Image bottomShadow(IDB_BSW_BOTTOM_SHADOW_PNG);
	Image topLeftShadow(IDB_BSW_TOP_LEFT_SHADOW_PNG);
	Image bottomLeftShadow(IDB_BSW_BOTTOM_LEFT_SHADOW_PNG);
	Image topRightShadow(IDB_BSW_TOP_RIGHT_SHADOW_PNG);
	Image bottomRightShadow(IDB_BSW_BOTTOM_RIGHT_SHADOW_PNG);
	Image background(IDB_BSW_BACKGROUND_PNG);

	TextureBrush topShadowBrush(&topShadow);
	TextureBrush leftShadowBrush(&leftShadow);
	TextureBrush rightShadowBrush(&rightShadow);
	TextureBrush bottomShadowBrush(&bottomShadow);
	TextureBrush backgroundBrush(&background);

	topShadowBrush.TranslateTransform(aCacheShadowPadding, 0);
	aGraphics->FillRectangle(&topShadowBrush, aCacheShadowPadding, 0, aCacheRelativeWidth - aCacheShadowPadding * 2, aCachePadding);

	leftShadowBrush.TranslateTransform(aCacheShadowPadding, aCachePadding);
	aGraphics->FillRectangle(&leftShadowBrush, 0, aCacheShadowPadding, aCachePadding, aCacheRelativeHeight - aCacheShadowPadding * 2);

	rightShadowBrush.TranslateTransform(aCacheRelativeWidth - aCachePadding, aCacheShadowPadding);
	aGraphics->FillRectangle(&rightShadowBrush, aCacheRelativeWidth - aCachePadding, aCacheShadowPadding, aCachePadding, aCacheRelativeHeight - aCacheShadowPadding * 2);

	bottomShadowBrush.TranslateTransform(aCacheShadowPadding, aCacheRelativeHeight - aCachePadding);
	aGraphics->FillRectangle(&bottomShadowBrush, aCacheShadowPadding, aCacheRealHeight + aCachePadding, aCacheRelativeWidth - aCacheShadowPadding * 2, aCachePadding);

	aGraphics->DrawImage(&topLeftShadow, 0, 0, aCacheShadowPadding, aCacheShadowPadding);
	aGraphics->DrawImage(&bottomLeftShadow, 0, aCacheRelativeHeight - aCacheShadowPadding, aCacheShadowPadding, aCacheShadowPadding);
	aGraphics->DrawImage(&topRightShadow, aCacheRelativeWidth - aCacheShadowPadding, 0, aCacheShadowPadding, aCacheShadowPadding);
	aGraphics->DrawImage(&bottomRightShadow, aCacheRelativeWidth - aCacheShadowPadding, aCacheRelativeHeight - aCacheShadowPadding, aCacheShadowPadding, aCacheShadowPadding);

	aGraphics->FillRectangle(&backgroundBrush, aCachePadding, aCachePadding, aCacheRealWidth, aCacheRealHeight);

	DeleteObject(&topShadowBrush);
	DeleteObject(&leftShadowBrush);
	DeleteObject(&backgroundBrush);
	DeleteObject(&rightShadowBrush);
	DeleteObject(&bottomShadowBrush);

	DeleteObject(&topShadow);
	DeleteObject(&leftShadow);
	DeleteObject(&rightShadow);
	DeleteObject(&bottomShadow);
	DeleteObject(&topLeftShadow);
	DeleteObject(&topRightShadow);
	DeleteObject(&bottomRightShadow);
	DeleteObject(&bottomLeftShadow);
	DeleteObject(&background);

}

void A2DWindow::RenderComponentClear()
{
	aGraphics->Clear(Color::AlphaMask);
}

LRESULT CALLBACK A2DWindow::WndProc(HWND xHwnd, UINT xMessage, WPARAM xWParam, LPARAM xLParam)
{
	A2DWindow * aWindow;

	if (xMessage == WM_CREATE)
	{
		CREATESTRUCT *pCreate = reinterpret_cast<CREATESTRUCT*>(xLParam);
		aWindow = reinterpret_cast<A2DWindow*>(pCreate->lpCreateParams);
		SetWindowLongPtr(xHwnd, GWLP_USERDATA, (LONG_PTR)aWindow); // <-------------- Brent. Try to move this out of the static method.
		return 1;
	}
	else
	{
		aWindow = reinterpret_cast<A2DWindow *>(static_cast<LONG_PTR>(GetWindowLongPtrW(xHwnd, GWLP_USERDATA)));
		
		switch (xMessage){
		case WM_CLOSE:
				DestroyWindow(xHwnd);
				return 0;
		case WM_DESTROY:
				PostQuitMessage(0);
				return 0;
				/*		default:
			return aWindow ? aWindow->aAurora ? xHwnd == aWindow->aChildHwnd ? aWindow->aAurora->PumpWindowMsg(&xHwnd, &xMessage, &xWParam, &xLParam)
				: DefWindowProc(xHwnd, xMessage, xWParam, xLParam) : DefWindowProc(xHwnd, xMessage, xWParam, xLParam) : DefWindowProc(xHwnd, xMessage, xWParam, xLParam);*/
		}
	}

	return	DefWindowProc(xHwnd, xMessage, xWParam, xLParam);

}

inline A2DWindow* A2DWindow::GetAppState(HWND xHwnd)
{
	LONG_PTR ptr = GetWindowLongPtr(xHwnd, GWLP_USERDATA);
	A2DWindow *sampleWinPtr = reinterpret_cast <A2DWindow*>(ptr);
	return sampleWinPtr;
}

LPCWSTR A2DWindow::GetClass()
{
	return L"A2DWindow";
}

LPCWSTR A2DWindow::ToString()
{
	return L"A2DWindow";
}

bool A2DWindow::operator==(A2DAbstract * xAbstract)
{
	return false;
}

void A2DWindow::CacheVariables()
{
	A2DRect * relativeRect = aWindowProps->GetRelativeBounds();
	A2DRect * realRect = aWindowProps->GetRealBounds();

	aCacheShadowPadding = aWindowProps->GetShadowPadding();
	aCachePadding = aWindowProps->GetPadding();

	aCacheRelativeX = relativeRect->aX;
	aCacheRelativeY = relativeRect->aY;
	aCacheRelativeHeight = relativeRect->aHeight;
	aCacheRelativeWidth = relativeRect->aWidth;

	aCacheRealX = realRect->aX;
	aCacheRealY = realRect->aY;
	aCacheRealHeight = realRect->aHeight;
	aCacheRealWidth = realRect->aWidth;

}

HRESULT A2DWindow::Initialize()
{

	HRESULT hr;

	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;

	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	CacheVariables();

	aWindowProps->SetWindow(this);

	RegisterClass(aParentHwnd);
	RegisterClass(aChildHwnd);
	
	hr = CreateHandle(aParentHwnd);

	if (FAILED(hr))	return hr;

	hr = CreateHandle(aChildHwnd);

	if (FAILED(hr))	return hr;

	CreateComponentResources();

	if (FAILED(hr))	return hr;

	Update();

	return hr;
}

void A2DWindow::Deinitialize()
{
	if (aWindowProps)
	{
		delete aWindowProps;  // <-- delete the pointer NOT the struct since this was passed in to you.
		aWindowProps = nullptr;
	}

	aParentHwnd = NULL;
	aChildHwnd = NULL;
}
