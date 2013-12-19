
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
    // SetWindowText(aChildHandle, *xName);
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
	HDC hdc, memDC;

	// Cache variables as Gdi Real
	aGdiRealRealX = aRect.aX;
	aGdiRealRealY = aRect.aY;
	aGdiRealRealWidth = aRect.aWidth + aBorderWidth * 2;
	aGdiRealRealHeight = aRect.aHeight + aBorderWidth * 2;
	aGdiRealRelativeX = aGdiRealRealX - aPadding - aBorderWidth;
	aGdiRealRelativeY = aGdiRealRealY - aPadding - aBorderWidth;
	aGdiRealRelativeWidth = aGdiRealRealWidth + aPadding * 2;
	aGdiRealRelativeHeight = aGdiRealRealHeight + aPadding * 2;

	hdc = GetDC(aParentHandle);
	memDC = CreateCompatibleDC(hdc);

	HBITMAP memBitmap = CreateCompatibleBitmap(hdc, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));

	SelectObject(memDC, memBitmap);

	aGraphics = new Graphics(memDC);
		
	/***********************************************/

    Render();

	/***********************************************/

	SIZE size = { (long)aGdiRealRelativeWidth, (long)aGdiRealRelativeHeight };

	HDC screenDC = GetDC(NULL);
	POINT ptDst = { (long)aGdiRealRelativeX, (long)aGdiRealRelativeY };
	POINT ptSrc = { 0, 0 };

	BLENDFUNCTION blendFunction;
	blendFunction.AlphaFormat = AC_SRC_ALPHA;
	blendFunction.BlendFlags = 0;
	blendFunction.BlendOp = AC_SRC_OVER;
	blendFunction.SourceConstantAlpha = 255;

	UpdateLayeredWindow(aParentHandle, screenDC, &ptDst, &size, aGraphics->GetHDC(), &ptSrc, 0, &blendFunction, 2);
	
	/***********************************************/
	
	aGraphics->ReleaseHDC(memDC);
	delete aGraphics;
	aGraphics = 0;

	DeleteObject(memBitmap);
	DeleteObject(hdc);
	DeleteObject(memDC);
}

void A2DWindow::DestroyResources()
{
	
	// Delete the ones in CreateResources();

}

float* A2DWindow::createGaussianKernel(int xRadius) 
{
	if (xRadius < 1)
	{
		return NULL;
	}

	int dataLength = xRadius * 2 + 1;

	float * data = new float[dataLength];

	float sigma = xRadius / 3.0f;
	float twoSigmaSquare = 2.0f * sigma * sigma;
	float sigmaRoot = (float) sqrt(twoSigmaSquare * M_PI);
	float total = 0.0f;

	for (int i = -xRadius; i <= xRadius; i++) 
	{
		float distance = i * i;
		int index = i + xRadius;
		data[index] = (float) exp(-distance / twoSigmaSquare) / sigmaRoot;
		total += data[index];
	}

	for (int i = 0; i < dataLength; i++) 
	{
		data[i] /= total;
	}

	return data;
}

BitmapData * A2DWindow::getLockedBitmapData(Bitmap * src)
{
	int srcWidth = src->GetWidth();
	int srcHeight = src->GetHeight();
		
	BitmapData * bitmapData = new BitmapData();

	Status ret = src->LockBits(new Rect(0, 0, srcWidth, srcHeight),
		ImageLockMode::ImageLockModeRead | ImageLockMode::ImageLockModeWrite,
		src->GetPixelFormat(),
		bitmapData);

	if (ret != Ok) 
	{
		return NULL;
	}
	
	return bitmapData;
}

Bitmap * A2DWindow::filter(Bitmap * src, int radius)
{
	Bitmap * blurred = new Bitmap(src->GetWidth(), src->GetHeight());
	Bitmap * rotated = new Bitmap(src->GetHeight(), src->GetWidth());
	
	float * kernel = createGaussianKernel(radius);

	// horizontal pass
	BitmapData * srcData = getLockedBitmapData(src);
	BitmapData * blurredData = getLockedBitmapData(blurred);

	blur(srcData, blurredData, src->GetWidth(), src->GetHeight(), kernel, radius);

	blurred->UnlockBits(blurredData);

	SYSOUT_INT(src->GetWidth());
	SYSOUT_INT(src->GetHeight());

	//delete blurredData;

	blurred->RotateFlip(Rotate90FlipNone);
	
	blurredData = getLockedBitmapData(blurred);
	BitmapData * rotatedData = getLockedBitmapData(rotated);

	blur(blurredData, rotatedData, blurred->GetWidth(), blurred->GetHeight(), kernel, radius);

	src->UnlockBits(srcData);
	blurred->UnlockBits(blurredData);
	rotated->UnlockBits(rotatedData);

	rotated->RotateFlip(Rotate270FlipNone);

	SYSOUT_INT(blurred->GetWidth());
	SYSOUT_INT(blurred->GetHeight());


	return rotated;
}

void  A2DWindow::blur(BitmapData * srcPixels, BitmapData * dstPixels, int width, int height, float * kernel, int radius)
{
	float a = 0;
	float r = 0;
	float g = 0;
	float b = 0;

	int ca = 0;
	int cr = 0;
	int cg = 0;
	int cb = 0;
	
	for (int y = 0; y < height; y++)
	{
		byte* pixelSrcRow = (byte *)srcPixels->Scan0 + (y * srcPixels->Stride);
		byte* pixelDstRow = (byte *)dstPixels->Scan0 + (y * dstPixels->Stride);

		for (int x = 0; x < width; x++)
		{
			a = r = g = b = 0.0f;

			for (int i = -radius; i <= radius; i++)
			{
				int subOffset = x + i;

				if (subOffset < 0 || subOffset >= width)
				{
					subOffset = (x + width) % width;
				}

				float blurFactor = kernel[radius + i];

				int position = subOffset;

				a += blurFactor * (float)pixelSrcRow[position * 4 + 3];
				r += blurFactor * (float)pixelSrcRow[position * 4 + 2];
				g += blurFactor * (float)pixelSrcRow[position * 4 + 1];
				b += blurFactor * (float)pixelSrcRow[position * 4];

			}

			ca = (int)(a + 0.5f);
			cr = (int)(r + 0.5f);
			cg = (int)(g + 0.5f);
			cb = (int)(b + 0.5f);
			
			ca = ca > 255 ? 255 : ca;
			cr = cr > 255 ? 255 : cr;
			cg = cg > 255 ? 255 : cg;
			cb = ca > 255 ? 255 : cb;

			pixelDstRow[x * 4 + 3] = ca;
			pixelDstRow[x * 4 + 2] = cr;
			pixelDstRow[x * 4 + 1] = cg;
			pixelDstRow[x * 4] = cb;
		}
	}
}

void A2DWindow::createShadowResources()
{
	float radius = 50;
	float realDim = radius * 2;
	float relativeDim = realDim * 2;
	
	Bitmap * solid = new Bitmap(relativeDim, relativeDim);
	Bitmap * blurred;
	
	Graphics graphics (solid);
	SolidBrush blackBrush(Color(255, 0, 0, 0));
	
	graphics.FillRectangle(&blackBrush, radius, radius, realDim, realDim);
	
	cachedBitmap = blurred = filter(solid, radius);
}

HRESULT A2DWindow::CreateResources()
{
	HRESULT hr = S_OK;
	
	topShadow = new Image(IDB_BSW_TOP_SHADOW_PNG);
	leftShadow = new Image(IDB_BSW_LEFT_SHADOW_PNG);
	rightShadow = new Image(IDB_BSW_RIGHT_SHADOW_PNG);
	bottomShadow = new Image(IDB_BSW_BOTTOM_SHADOW_PNG);
	topLeftShadow = new Image(IDB_BSW_TOP_LEFT_SHADOW_PNG);
	bottomLeftShadow = new Image(IDB_BSW_BOTTOM_LEFT_SHADOW_PNG);
	topRightShadow = new Image(IDB_BSW_TOP_RIGHT_SHADOW_PNG);
	bottomRightShadow = new Image(IDB_BSW_BOTTOM_RIGHT_SHADOW_PNG);
	background = new Image(IDB_BSW_BACKGROUND_PNG);

	topShadowBrush = new TextureBrush(topShadow);
	leftShadowBrush = new TextureBrush(leftShadow);
	rightShadowBrush = new TextureBrush(rightShadow);
	bottomShadowBrush = new TextureBrush(bottomShadow);
	backgroundBrush = new TextureBrush(background);

	return hr;
}

void A2DWindow::setVisible(bool xVisible)
{
    aVisible = xVisible;

    if (aVisible)
    {
        // Create resources!
        aFrame->CreateResources();

        // ShowWindow(aChildHandle, SW_SHOWNORMAL);
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
	if (aBorderWidth > 0)
	{
		Pen borderPen(aBorderColor, aBorderWidth);
    
		aGraphics->DrawRectangle(&borderPen, aPadding, aPadding, aGdiRealRealWidth, aGdiRealRealHeight);
    
		DeleteObject(&borderPen);
	}
}

void A2DWindow::RenderComponent()
{	
	topShadowBrush->ResetTransform();
	leftShadowBrush->ResetTransform();
	rightShadowBrush->ResetTransform();
	bottomShadowBrush->ResetTransform();
	/*
	topShadowBrush->TranslateTransform(aShadowPadding, FLOAT_ZERO);
	aGraphics->FillRectangle(topShadowBrush, aShadowPadding, FLOAT_ZERO, aGdiRealRelativeWidth - aShadowPadding * 2, aPadding);

	leftShadowBrush->TranslateTransform(aShadowPadding, aPadding);
    aGraphics->FillRectangle(leftShadowBrush, FLOAT_ZERO, aShadowPadding, aPadding, aGdiRealRelativeHeight - aShadowPadding * 2);

	rightShadowBrush->TranslateTransform(aGdiRealRelativeWidth - aPadding, aShadowPadding);
    aGraphics->FillRectangle(rightShadowBrush, aGdiRealRelativeWidth - aPadding, aShadowPadding, aPadding, aGdiRealRelativeHeight - aShadowPadding * 2);

	bottomShadowBrush->TranslateTransform(aShadowPadding, aGdiRealRelativeHeight - aPadding);
    aGraphics->FillRectangle(bottomShadowBrush, aShadowPadding, aGdiRealRealHeight + aPadding, aGdiRealRelativeWidth - aShadowPadding * 2, aPadding);

    aGraphics->DrawImage(topLeftShadow, FLOAT_ZERO, FLOAT_ZERO, aShadowPadding, aShadowPadding);
    aGraphics->DrawImage(bottomLeftShadow, FLOAT_ZERO, aGdiRealRelativeHeight - aShadowPadding, aShadowPadding, aShadowPadding);
    aGraphics->DrawImage(topRightShadow, aGdiRealRelativeWidth - aShadowPadding, FLOAT_ZERO, aShadowPadding, aShadowPadding);
    aGraphics->DrawImage(bottomRightShadow, aGdiRealRelativeWidth - aShadowPadding, aGdiRealRelativeHeight - aShadowPadding, aShadowPadding, aShadowPadding);

    aGraphics->FillRectangle(backgroundBrush, aPadding, aPadding, aGdiRealRealWidth, aGdiRealRealHeight);	*/

	aGraphics->DrawImage(cachedBitmap, 0, 0);
}

void A2DWindow::moveTo(int xPosX, int xPosY)
{
	HDWP hdwp = BeginDeferWindowPos(2);

	if (hdwp)
	{
		int offset = aPadding + aBorderWidth;

		hdwp = DeferWindowPos(hdwp, aParentHandle, NULL, xPosX, xPosX, 0, 0, SWP_NOZORDER | SWP_NOSIZE | SWP_NOACTIVATE);
		hdwp = DeferWindowPos(hdwp, aChildHandle, aParentHandle, xPosX + offset, xPosY + offset, 0, 0, SWP_NOZORDER | SWP_NOSIZE | SWP_NOACTIVATE);
	}

	if (hdwp)
	{
		EndDeferWindowPos(hdwp);
	}
}

void A2DWindow::forceAlignment()
{
	int offset = aPadding + aBorderWidth;
	RECT rect;

	GetWindowRect(aChildHandle, &rect);

	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;

	if (width > aMinWidth && height >aMinHeight)
	{
		aRect.aX = rect.left;
		aRect.aY = rect.top;
		aRect.aWidth = width;
		aRect.aHeight = height;

		Update();
	}
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
		switch (xMessage)
		{
		case WM_SHOWWINDOW:
		{
							  aWindow = reinterpret_cast<A2DWindow *>(static_cast<LONG_PTR>(GetWindowLongPtrW(xHwnd, GWLP_USERDATA)));

							  return S_OK;
		}/*
		case WM_GETMINMAXINFO:
		{
								 ((MINMAXINFO *)xLParam)->ptMinTrackSize.x = 300;
								 ((MINMAXINFO *)xLParam)->ptMinTrackSize.y = 300;

			return 0;
		}*/
		/*	case WM_SIZE:
			{
				aWindow = reinterpret_cast<A2DWindow *>(static_cast<LONG_PTR>(GetWindowLongPtrW(xHwnd, GWLP_USERDATA)));
						
				if (aWindow->aChildHandle == xHwnd)
				{
					aWindow->forceAlignment();
				}

				return S_OK;
			}*/
			case WM_LBUTTONDOWN:
			{
				aWindow = reinterpret_cast<A2DWindow *>(static_cast<LONG_PTR>(GetWindowLongPtrW(xHwnd, GWLP_USERDATA)));
				if (aWindow->aChildHandle != xHwnd) return 0;

				SetCapture(xHwnd);
				aWindow->isDragged = true;

				return S_OK;
			}
			case WM_MOUSEMOVE:
			{
								 aWindow = reinterpret_cast<A2DWindow *>(static_cast<LONG_PTR>(GetWindowLongPtrW(xHwnd, GWLP_USERDATA)));
								 if (aWindow->aChildHandle != xHwnd) return 0;

				if (!aWindow->isDragged)
				{
					GetCursorPos(&aWindow->lastDraggedPoint);
					ScreenToClient(xHwnd, &aWindow->lastDraggedPoint);
				}

				aWindow = reinterpret_cast<A2DWindow *>(static_cast<LONG_PTR>(GetWindowLongPtrW(xHwnd, GWLP_USERDATA)));
				if (aWindow->aChildHandle != xHwnd) return 0;

				if (aWindow->isDragged)
				{

					POINT p;
					GetCursorPos(&p);
					ScreenToClient(xHwnd, &p);
					
					HDWP hdwp = BeginDeferWindowPos(2);

					int deltaY = aWindow->lastDraggedPoint.y - p.y;
					int deltaX = aWindow->lastDraggedPoint.x - p.x;

					int offset = aWindow->getPadding() + aWindow->getBorderWidth();

					// DEFER REGION //

					A2DRect& aRect = aWindow->aRect;

					aRect.aX = 500;
					aRect.aY = 500;
					aRect.aWidth += deltaX;
					aRect.aHeight += deltaY;

					aWindow->CreateResources();
					aWindow->Update();
					aWindow->DestroyResources();

					SetWindowPos(aWindow->aChildHandle, aWindow->aParentHandle, aRect.aX, aRect.aY, aRect.aWidth, aRect.aHeight, SWP_NOZORDER | SWP_NOACTIVATE);						

					// DEFER REGION //

					aWindow->lastDraggedPoint = p;
				}

				return S_OK;
			}
			case WM_LBUTTONUP:
			{
				aWindow = reinterpret_cast<A2DWindow *>(static_cast<LONG_PTR>(GetWindowLongPtrW(xHwnd, GWLP_USERDATA)));
				if (aWindow->aChildHandle != xHwnd) return 0;

				ReleaseCapture();
				aWindow->isDragged = false;

				return S_OK;
			}
			/*
			case WM_NCHITTEST:
			{
				const LONG border_width = 8; //in pixels
				RECT winrect;
				GetWindowRect(xHwnd, &winrect);
				long x = GET_X_LPARAM(xLParam);
				long y = GET_Y_LPARAM(xLParam);

				//bottom left corner
				if (x >= winrect.left && x < winrect.left + border_width &&
					y < winrect.bottom && y >= winrect.bottom - border_width)
				{
					return HTBOTTOMLEFT;
				}
				//bottom right corner
				if (x < winrect.right && x >= winrect.right - border_width &&
					y < winrect.bottom && y >= winrect.bottom - border_width)
				{
					return HTBOTTOMRIGHT;
				}
				//top left corner
				if (x >= winrect.left && x < winrect.left + border_width &&
					y >= winrect.top && y < winrect.top + border_width)
				{
					return HTTOPLEFT;
				}
				//top right corner
				if (x < winrect.right && x >= winrect.right - border_width &&
					y >= winrect.top && y < winrect.top + border_width)
				{
					return HTTOPRIGHT;
				}
				//left border
				if (x >= winrect.left && x < winrect.left + border_width)
				{
					return HTLEFT;
				}
				//right border
				if (x < winrect.right && x >= winrect.right - border_width)
				{
					return HTRIGHT;
				}
				//bottom border
				if (y < winrect.bottom && y >= winrect.bottom - border_width)
				{
					return HTBOTTOM;
				}
				//top border
				if (y >= winrect.top && y < winrect.top + border_width)
				{
					return HTTOP;
				}

				return S_OK;
			}*/
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
	setBorderWidth(2); //Force the border in DX window

    hr = RegisterClass();

    if (FAILED(hr)) return hr;
    
    hr = CreateHandle(aParentHandle);

    if (FAILED(hr)) return hr;

    hr = CreateHandle(aChildHandle);

    if (FAILED(hr)) return hr;

    hr = CreateResources();

    if (FAILED(hr)) return hr;

	createShadowResources();

    Update();
	
    return hr;
}

void A2DWindow::Deinitialize()
{
    aParentHandle = NULL;
    aChildHandle = NULL;
}
