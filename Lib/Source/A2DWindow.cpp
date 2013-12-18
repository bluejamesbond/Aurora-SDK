
#include "../../include/A2DExtLibs.h"
#include "../../include/A2DWindow.h"

A2DWindow::A2DWindow(HINSTANCE * xHInstance) : aHInstance(xHInstance) {}

A2DWindow::~A2DWindow(){}

void A2DWindow::setUndecorated(bool xUndecoratedFlag)
{
    // we cannot just use WS_POPUP style
    // WS_THICKFRAME: without this the window cannot be resized and so aero snap, de-maximizing and minimizing won't work
    // WS_SYSMENU: enables the context menu with the move, close, maximize, minize... commands (shift + right-click on the task bar item)
    // HOWEVER, this also enables the menu with the maximize buttons in the title bar, which will exist inside your client area and are clickable. 
    // WS_CAPTION: enables aero minimize animation/transition
    // WS_MAXIMIZEBOX, WS_MINIMIZEBOX: enable minimize/maximize

    LONG lStyle, lExStyle;

    lStyle = GetWindowLongPtr(aParentHandle, GWL_STYLE);
    lExStyle = GetWindowLongPtr(aParentHandle, GWL_EXSTYLE);

    lStyle &= xUndecoratedFlag ? ~(WS_CAPTION | WS_THICKFRAME | WS_MINIMIZE | WS_MAXIMIZE | WS_SYSMENU) : (WS_CAPTION | WS_THICKFRAME | WS_MINIMIZE | WS_MAXIMIZE | WS_SYSMENU);
    lStyle |= xUndecoratedFlag ? (WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP) : 0;
    lExStyle |= xUndecoratedFlag ? (WS_EX_LAYERED | WS_EX_APPWINDOW) : WS_EX_LAYERED;

    SetWindowLongPtr(aParentHandle, GWL_STYLE, lStyle);
    SetWindowLongPtr(aParentHandle, GWL_EXSTYLE, lExStyle);

    //SetWindowPos(aParentWin->aHwnd, HWND_TOP, aWindowProps->aRealLeft, aWindowProps->aRealTop, aGdiRealRealWidth, aGdiRealRealHeight, SWP_FRAMECHANGED);
    SetWindowPos(aParentHandle, NULL, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOOWNERZORDER);
}

void A2DWindow::setPadding(float xPadding)
{
    aPadding = xPadding;
}

float A2DWindow::getPadding()
{
    return aPadding;
}

void A2DWindow::setShadowPadding(float xShadowPadding)
{
    aShadowPadding = xShadowPadding;
}

float A2DWindow::getShadowPadding()
{
    return aShadowPadding;
}

HWND* A2DWindow::getChildHandle()
{
    return &aChildHandle;
}

HWND* A2DWindow::getParentHandle()
{
    return &aParentHandle;
}

bool A2DWindow::isShadowed()
{
    return aShadowed;
}

bool A2DWindow::isUndecorated()
{
	return aUndecorated;
}

void A2DWindow::setShadowed(bool xShadowed)
{
    if (!isUndecorated())
    {
        setUndecorated(true);
    }
        
    aShadowed = xShadowed;

    // Update
    Update();
}

Color A2DWindow::getBorderColor()
{
    return aBorderColor;
}

void A2DWindow::setBorderColor(Color xBorderColor)
{
    aBorderColor = xBorderColor;
}

bool A2DWindow::isVisible()
{
	return aVisible;
}

void A2DWindow::setName(LPCWSTR * xName)
{
    aName = *xName;
    SetWindowText(aChildHandle, *xName);
    SetWindowText(aParentHandle, *xName);
}

LPCWSTR * A2DWindow::getName()
{
    return &aName;
}

void  A2DWindow::setFrame(A2DFrame * xFrame)
{
    aFrame = xFrame;
}

A2DFrame *  A2DWindow::getFrame()
{
    return aFrame;
}

A2DRect * A2DWindow::getBounds()
{
    return &aRect;
}

int A2DWindow::getDefaultCloseOperation()
{
    return aDefaultCloseOperation;
}

void A2DWindow::setDefaultCloseOperation(int xOperation)
{
    aDefaultCloseOperation = xOperation;
}

void A2DWindow::setLocationRelativeTo(A2DWindow * xWindow)
{
	if (xWindow == NULL)
	{
		aRect.aX = (GetSystemMetrics(SM_CXSCREEN) - aRect.aWidth) / 2;
		aRect.aY = (GetSystemMetrics(SM_CYSCREEN) - aRect.aHeight) / 2;
	}
}

void A2DWindow::setBorderWidth(float xBorderWidth)
{
	aBorderWidth = xBorderWidth;
}

float A2DWindow::getBorderWidth()
{
	return aBorderWidth;
}

/*
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
*/

HRESULT A2DWindow::RegisterClass()
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
    wcex.lpszClassName = aName;
    wcex.hIconSm = LoadIcon(*aHInstance, IDI_APPLICATION);

    return RegisterClassEx(&wcex);
}

void A2DWindow::RunMessageLoop()
{
    MSG msg;

    while (aVisible)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        if (aFrame) aFrame->Update();
    }
}

HRESULT A2DWindow::CreateHandle(HWND& xHandle)
{
    HRESULT         hr = S_OK;
    HWND            hWnd, hwndParent;
    int             left, top, width, height;
    DWORD           lStyle, lExStyle;
    LPCWSTR         className, titleName;
    
	left =			(int)(xHandle == aParentHandle ? aRect.aX - aPadding : aRect.aX + aBorderWidth);
	top =			(int)(xHandle == aParentHandle ? aRect.aY - aPadding : aRect.aY + aBorderWidth);
	width =			(int)(xHandle == aParentHandle ? aRect.aWidth - aPadding * 2 : aRect.aWidth - aBorderWidth * 2);
	height =		(int)(xHandle == aParentHandle ? aRect.aHeight - aPadding * 2 : aRect.aHeight - aBorderWidth * 2);
	lStyle =		(int)(xHandle == aParentHandle ? WS_POPUP | WS_OVERLAPPED : WS_POPUP);
	lExStyle =		(int)(xHandle == aParentHandle ? WS_EX_LAYERED | WS_EX_APPWINDOW : 0);
	hwndParent =	xHandle == aParentHandle ? HWND_DESKTOP : aParentHandle;
    className =     aName;
    titleName =     aName;

    hWnd = CreateWindowEx(lExStyle, className, titleName, lStyle, left, top, width, height, hwndParent, NULL, *aHInstance, this);
    hr = hWnd ? S_OK : E_FAIL;
    if (FAILED(hr)) return hr;

    xHandle = hWnd;
    aStyle = WS_EX_APPWINDOW;
    
	if (aChildHandle && aParentHandle)
    {
        // Force the child on top of parent!
        SetWindowPos(aChildHandle, aParentHandle, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
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

	aHDCSize = { (long)aGdiRealRelativeWidth, (long) aGdiRealRelativeHeight };

    HDC screenDC = GetDC(NULL);
	POINT ptDst = { (long)aGdiRealRelativeX, (long) aGdiRealRelativeY };
    POINT ptSrc = { 0, 0 };

    BLENDFUNCTION blendFunction;
    blendFunction.AlphaFormat = AC_SRC_ALPHA;
    blendFunction.BlendFlags = 0;
    blendFunction.BlendOp = AC_SRC_OVER;
    blendFunction.SourceConstantAlpha = 255;

    UpdateLayeredWindow(aParentHandle, screenDC, &ptDst, &aHDCSize, aGraphics->GetHDC(), &ptSrc, 0, &blendFunction, 2);
}

HRESULT A2DWindow::CreateResources()
{
    return CreateComponentResources();
}

HRESULT A2DWindow::CreateComponentResources()
{
    HRESULT hr = S_OK;
    HDC hdc, memDC;

    // Cache variables as Gdi Real
    aGdiRealRealX = aRect.aX;
    aGdiRealRealY = aRect.aY;
    aGdiRealRealWidth = aRect.aWidth;
    aGdiRealRealHeight = aRect.aHeight;
    aGdiRealRelativeX = aGdiRealRealX - aPadding;
    aGdiRealRelativeY = aGdiRealRealY - aPadding;
    aGdiRealRelativeWidth = aGdiRealRealWidth + aPadding * 2;
    aGdiRealRelativeHeight = aGdiRealRealHeight + aPadding * 2;

    hdc = GetDC(aParentHandle);
    memDC = CreateCompatibleDC(hdc);

	HBITMAP memBitmap = CreateCompatibleBitmap(hdc, (long)aGdiRealRelativeWidth, (long) aGdiRealRelativeHeight);

    SelectObject(memDC, memBitmap);

    aGraphics =  new Graphics(memDC);

    return hr;

}

void A2DWindow::setVisible(bool xVisible)
{
    aVisible = xVisible;

    if (aVisible)
    {
        // Create resources!
        aFrame->CreateResources();

        ShowWindow(aChildHandle, SW_SHOWNORMAL);
        ShowWindow(aParentHandle, SW_SHOWNORMAL);
        RunMessageLoop();
    }
    else
    {
        ShowWindow(aChildHandle, SW_HIDE);
        ShowWindow(aParentHandle, SW_HIDE);
    }
}

void A2DWindow::RenderComponentBorder()
{
	Pen borderPen(aBorderColor, aBorderWidth);
    
	aGraphics->DrawRectangle(&borderPen, aPadding, aPadding, aGdiRealRealWidth, aGdiRealRealHeight);
    
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

    topShadowBrush.TranslateTransform(aShadowPadding, aGdiRealZero);
    aGraphics->FillRectangle(&topShadowBrush, aShadowPadding, aGdiRealZero, aGdiRealRelativeWidth - aShadowPadding * 2, aPadding);

    leftShadowBrush.TranslateTransform(aShadowPadding, aPadding);
    aGraphics->FillRectangle(&leftShadowBrush, aGdiRealZero, aShadowPadding, aPadding, aGdiRealRelativeHeight - aShadowPadding * 2);

    rightShadowBrush.TranslateTransform(aGdiRealRelativeWidth - aPadding, aShadowPadding);
    aGraphics->FillRectangle(&rightShadowBrush, aGdiRealRelativeWidth - aPadding, aShadowPadding, aPadding, aGdiRealRelativeHeight - aShadowPadding * 2);

    bottomShadowBrush.TranslateTransform(aShadowPadding, aGdiRealRelativeHeight - aPadding);
    aGraphics->FillRectangle(&bottomShadowBrush, aShadowPadding, aGdiRealRealHeight + aPadding, aGdiRealRelativeWidth - aShadowPadding * 2, aPadding);

    aGraphics->DrawImage(&topLeftShadow, aGdiRealZero, aGdiRealZero, aShadowPadding, aShadowPadding);
    aGraphics->DrawImage(&bottomLeftShadow, aGdiRealZero, aGdiRealRelativeHeight - aShadowPadding, aShadowPadding, aShadowPadding);
    aGraphics->DrawImage(&topRightShadow, aGdiRealRelativeWidth - aShadowPadding, aGdiRealZero, aShadowPadding, aShadowPadding);
    aGraphics->DrawImage(&bottomRightShadow, aGdiRealRelativeWidth - aShadowPadding, aGdiRealRelativeHeight - aShadowPadding, aShadowPadding, aShadowPadding);

    aGraphics->FillRectangle(&backgroundBrush, aPadding, aPadding, aGdiRealRealWidth, aGdiRealRealHeight);

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
        SetWindowLongPtr(xHwnd, GWLP_USERDATA, (LONG_PTR)aWindow);
        
        return S_OK;
    }
    else
    {
        aWindow = reinterpret_cast<A2DWindow *>(static_cast<LONG_PTR>(GetWindowLongPtrW(xHwnd, GWLP_USERDATA)));
        
        switch (xMessage)
        {
            case WM_CLOSE:
            {       
                DestroyWindow(xHwnd);
                return S_OK;
            }
            case WM_DESTROY:
            {       
                PostQuitMessage(0);
                return S_OK;
            }
        }
    }

    return  DefWindowProc(xHwnd, xMessage, xWParam, xLParam);
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

HRESULT A2DWindow::Initialize()
{
    HRESULT hr = S_OK;

    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR           gdiplusToken;

    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
    
	/*****************************************************/
	// TEMP SETUP
	aRect.aX = 30;
	aRect.aY = 30;
	aRect.aHeight = 480;
	aRect.aWidth = 640;
	aPadding = 25;
	aShadowPadding = 75;
	aName = L"TESTING";
	/*****************************************************/

	setLocationRelativeTo(NULL);
	setBorderColor(Color(202, 225, 255));
	setBorderWidth(5);

    hr = RegisterClass();

    if (FAILED(hr)) return hr;
    
    hr = CreateHandle(aParentHandle);

    if (FAILED(hr)) return hr;

    hr = CreateHandle(aChildHandle);

    if (FAILED(hr)) return hr;

    hr = CreateResources();

    if (FAILED(hr)) return hr;

    Update();

    return hr;
}

void A2DWindow::Deinitialize()
{
    aParentHandle = NULL;
    aChildHandle = NULL;
}
