
#include "stdafx.h"
#include "globals.h"

using namespace std;
using namespace Gdiplus;

// BorderlessShadowWindow constructor
BorderlessShadowWindow::BorderlessShadowWindow() :
mWinProps(NULL) 
{
	mWinProps = new WindowProperties(IDP_BSW_DEFAULT_WIDTH,
								IDP_BSW_DEFAULT_HEIGHT, 
								IDP_BSW_BORDER_PADDING,
								IDP_BSW_SHADOW_PADDING );
}

// BorderlessShadowWindow destructor
// Releases the application's resources.
BorderlessShadowWindow::~BorderlessShadowWindow(){}

void BorderlessShadowWindow::RunMessageLoop()
{
	MSG msg;

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

ATOM BorderlessShadowWindow::RegisterClass()
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = BorderlessShadowWindow::WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = mWinProps->hInstance;
	wcex.hIcon = LoadIcon(mWinProps->hInstance, IDI_APPLICATION);
	wcex.hCursor =LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = mWinProps->WindowClass;
	wcex.hIconSm = LoadIcon(mWinProps->hInstance, IDI_APPLICATION);

	return RegisterClassEx(&wcex);
}

HRESULT BorderlessShadowWindow::initialize()
{
	HRESULT hr;
	HWND hWnd;
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;

	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	mWinProps->CenterWindow();

	mWinProps->hWnd = hWnd = CreateWindowEx(WS_EX_LAYERED | WS_EX_APPWINDOW, mWinProps->WindowClass, mWinProps->WindowTitle, WS_POPUP | WS_OVERLAPPED,
		mWinProps->Left, mWinProps->Top, mWinProps->Width, mWinProps->Height, HWND_DESKTOP, NULL, mWinProps->hInstance, this);

	hr = hWnd ? S_OK : E_FAIL;

	ShowWindow(hWnd, SW_SHOWNORMAL);

	BorderlessShadowWindow::OnPaint();

	return hr;
}

HRESULT BorderlessShadowWindow::OnPaint()
{

	/********************************************
	*   step 1.
	*   Using Gdiplus to load the image
	********************************************/
	HDC hdc = GetDC(aMWindowProps->hWnd);
	HDC memDC = CreateCompatibleDC(hdc);
	SIZE wndSize = { aMWindowProps->GetRealPosWidth(), aMWindowProps->GetRealPosHeight() };
	HBITMAP memBitmap = CreateCompatibleBitmap(hdc, aMWindowProps->GetRealPosWidth(), aMWindowProps->GetRealPosHeight());
	SelectObject(memDC, memBitmap);

	Graphics graphics(memDC);

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

	topShadowBrush.TranslateTransform(aMWindowProps->aShadowPadding, 0);
	graphics.FillRectangle(&topShadowBrush, aMWindowProps->aShadowPadding, 0, aMWindowProps->aRealWidth - (aMWindowProps->aShadowPadding) * 2, aMWindowProps->aPadding);

	leftShadowBrush.TranslateTransform(aMWindowProps->aShadowPadding, aMWindowProps->aPadding);
	graphics.FillRectangle(&leftShadowBrush, 0, aMWindowProps->aShadowPadding, aMWindowProps->aPadding, aMWindowProps->aRealHeight);

	rightShadowBrush.TranslateTransform(aMWindowProps->aRealWidth - aMWindowProps->aPadding, aMWindowProps->aShadowPadding);
	graphics.FillRectangle(&rightShadowBrush, aMWindowProps->aRealWidth - aMWindowProps->aPadding, aMWindowProps->aShadowPadding, aMWindowProps->aPadding, aMWindowProps->aRealHeight);

	bottomShadowBrush.TranslateTransform(aMWindowProps->aShadowPadding, aMWindowProps->aRealHeight - aMWindowProps->aPadding);
	graphics.FillRectangle(&bottomShadowBrush, aMWindowProps->aShadowPadding, aMWindowProps->aRealHeight - aMWindowProps->aPadding, aMWindowProps->aRealWidth - aMWindowProps->aShadowPadding * 2, aMWindowProps->aPadding);

	graphics.DrawImage(&topLeftShadow, 0, 0, aMWindowProps->aShadowPadding, aMWindowProps->aShadowPadding);
	graphics.DrawImage(&bottomLeftShadow, 0, aMWindowProps->aRealHeight - aMWindowProps->aShadowPadding, aMWindowProps->aShadowPadding, aMWindowProps->aShadowPadding);
	graphics.DrawImage(&topRightShadow, aMWindowProps->aRealWidth - aMWindowProps->aShadowPadding, 0, aMWindowProps->aShadowPadding, aMWindowProps->aShadowPadding);
	graphics.DrawImage(&bottomRightShadow, aMWindowProps->aRealWidth - aMWindowProps->aShadowPadding, aMWindowProps->aRealHeight - aMWindowProps->aShadowPadding, aMWindowProps->aShadowPadding, aMWindowProps->aShadowPadding);

	TextureBrush backgroundBrush(&background);
	graphics.FillRectangle(&backgroundBrush, aMWindowProps->aPadding, aMWindowProps->aPadding, aMWindowProps->aRealWidth - aMWindowProps->aPadding * 2, aMWindowProps->aRealHeight - aMWindowProps->aPadding * 2);

	if (aMWindowProps->_WinActive && IDP_BSW_ACTIVE_BORDER)
	{
		Pen borderPen(Color(IDP_BSW_ACTIVE_BORDER_COLOR), 1);
		graphics.DrawRectangle(&borderPen, aMWindowProps->aPadding, aMWindowProps->aPadding, aMWindowProps->aRealWidth - aMWindowProps->aPadding * 2, aMWindowProps->aRealHeight - aMWindowProps->aPadding * 2);
		DeleteObject(&borderPen);
	}

	HDC screenDC = GetDC(NULL);
	POINT ptDst = { aMWindowProps->GetRelativePosLeft(), aMWindowProps->GetRelativePosTop() };
	POINT ptSrc = { 0, 0 };

	/*********************************************
	*   step 3.
	*   Use UpdateLayeredWindow to Draw the Window
	*
	*********************************************/
	BLENDFUNCTION blendFunction;
	blendFunction.AlphaFormat = AC_SRC_ALPHA;
	blendFunction.BlendFlags = 0;
	blendFunction.BlendOp = AC_SRC_OVER;
	blendFunction.SourceConstantAlpha = 255;

	UpdateLayeredWindow(mWinProps->hWnd, screenDC, &ptDst, &wndSize, memDC, &ptSrc, 0, &blendFunction, 2);

	DeleteDC(memDC);

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

	return 0;
}

LRESULT CALLBACK BorderlessShadowWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	BorderlessShadowWindow *shWinPtr;

	if (message == WM_CREATE)
	{
		LPCREATESTRUCT pcs = (LPCREATESTRUCT)lParam;
		shWinPtr = (BorderlessShadowWindow *)pcs->lpCreateParams;
		SetWindowLongPtrW(hWnd, GWLP_USERDATA, PtrToUlong(shWinPtr));

		return 1;
	}
	else
	{
		if (message == WM_DESTROY)
		{
			PostQuitMessage(0);
		}
		else if (message == WM_MOVE)
		{
			return 1;
		}
		else if (message == WM_SIZE)
		{
			return 1;
		}
		else if (message == WM_ACTIVATE)
		{
			return 1;
		}
		else
		{
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}

	return 0;
}