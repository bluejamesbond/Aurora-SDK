
#include "../../include/A2DExtLibs.h"
#include "../../include/A2DWindow.h"

A2DWindow::A2DWindow(HINSTANCE * xHInstance) : aHInstance(xHInstance) {}

A2DWindow::~A2DWindow(){}

/**
*
* Sets the visibility of the decorations around a window. Enabling
* decorations shows you the maximize, minimize, and close buttons.
*
* @param bool
*            the boolean indicating whether window should be 
*            decorated or not.
* @return void
*/
void A2DWindow::setUndecorated(bool xUndecoratedFlag)
{
    // we cannot just use WS_POPUP style
    // WS_THICKFRAME: without this the window cannot be resized and so aero snap, de-maximizing and minimizing won't work
    // WS_SYSMENU: enables the context menu with the move, close, maximize, minize... commands (shift + right-click on the task bar item)
    // HOWEVER, this also enables the menu with the maximize buttons in the title bar, which will exist inside your client area and are clickable. 
    // WS_CAPTION: enables aero minimize animation/transition
    // WS_MAXIMIZEBOX, WS_MINIMIZEBOX: enable minimize/maximize

    LONG lStyle, lExStyle;

    lStyle = GetWindowLongPtr(aParentHWnd, GWL_STYLE);
    lExStyle = GetWindowLongPtr(aParentHWnd, GWL_EXSTYLE);

    lStyle &= xUndecoratedFlag ? ~(WS_CAPTION | WS_THICKFRAME | WS_MINIMIZE | WS_MAXIMIZE | WS_SYSMENU) : (WS_CAPTION | WS_THICKFRAME | WS_MINIMIZE | WS_MAXIMIZE | WS_SYSMENU);
    lStyle |= xUndecoratedFlag ? (WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP) : 0;
    lExStyle |= xUndecoratedFlag ? (WS_EX_LAYERED | WS_EX_APPWINDOW) : WS_EX_LAYERED;

    SetWindowLongPtr(aParentHWnd, GWL_STYLE, lStyle);
    SetWindowLongPtr(aParentHWnd, GWL_EXSTYLE, lExStyle);

    SetWindowPos(aParentHWnd, NULL, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOOWNERZORDER);
}


/**
*
* Sets the visibility of the decorations around a window. Enabling
* decorations shows you the maximize, minimize, and close buttons.
*
* @param bool
*            the boolean indicating whether window should be
*            decorated or not.
* @return void
*/
void A2DWindow::setBoxShadowRadius(float xBoxShadowRadius)
{
	if (abs(xBoxShadowRadius) < 1) return;

	aOptBoxShadowRadius = abs(xBoxShadowRadius);
}

/**
*
* Sets the visibility of the decorations around a window. Enabling
* decorations shows you the maximize, minimize, and close buttons.
*
* @param bool
*            the boolean indicating whether window should be
*            decorated or not.
* @return void
*/
float A2DWindow::getBoxShadowRadius()
{
	return aOptBoxShadowRadius;
}

/**
*
* Sets the visibility of the decorations around a window. Enabling
* decorations shows you the maximize, minimize, and close buttons.
*
* @param bool
*            the boolean indicating whether window should be
*            decorated or not.
* @return void
*/
void A2DWindow::setBoxShadowColor(Color xBoxShadowColor)
{
	aOptBoxShadowColor = xBoxShadowColor;
}

/**
*
* Sets the visibility of the decorations around a window. Enabling
* decorations shows you the maximize, minimize, and close buttons.
*
* @param bool
*            the boolean indicating whether window should be
*            decorated or not.
* @return void
*/
Color A2DWindow::getBoxShadowColor()
{
	return aOptBoxShadowColor;
}

/**
* 
* This method creates a 1x1 image of the color indicated by the 
* aOptBackgroundColor and updates all the windows derived of the aParentHWnd to
* that color. The aOptBackgroundColor
*
* @see #destroyBackgroundResources()
* @see #createBackgroundResources()
* @see #createResources()
* @see #destroyResources()
* @param  void
* @return void
*/
void A2DWindow::UpdateAndCacheBackground()
{
	DestroyBackgroundResources();
	CreateBackgroundResources();
	
	HBRUSH brush = CreateSolidBrush(RGB(aOptBackgroundColor.GetRed(), aOptBackgroundColor.GetGreen(), aOptBackgroundColor.GetBlue()));
	SetClassLongPtr(aParentHWnd, GCLP_HBRBACKGROUND, (LONG)brush);

	CloseHandle(brush);
}

/**
*
* This method creates a 1x1 image of the color indicated by the
* aOptBackgroundColor and updates all the windows derived of the aParentHWnd to
* that color. The aOptBackgroundColor
*
* @see #destroyBackgroundResources()
* @see #createBackgroundResources()
* @see #createResources()
* @see #destroyResources()
* @param  void
* @return void
*/
void A2DWindow::updateAndCacheBoxShadow()
{
	destroyBoxShadowResources();
	createBoxShadowResources();
}

/**
*
* Sets the visibility of the decorations around a window. Enabling
* decorations shows you the maximize, minimize, and close buttons.
*
* @param bool
*            the boolean indicating whether window should be
*            decorated or not.
* @return void
*/
HWND A2DWindow::getChildHWnd()
{
    return aChildHWnd;
}

/**
*
* Sets the visibility of the decorations around a window. Enabling
* decorations shows you the maximize, minimize, and close buttons.
*
* @param bool
*            the boolean indicating whether window should be
*            decorated or not.
* @return void
*/
HWND A2DWindow::getParentHWnd()
{
    return aParentHWnd;
}
/**
*
* Sets the visibility of the decorations around a window. Enabling
* decorations shows you the maximize, minimize, and close buttons.
*
* @param bool
*            the boolean indicating whether window should be
*            decorated or not.
* @return void
*/
bool A2DWindow::isShadowed()
{
    return aShadowed;
}

/**
*
* Sets the visibility of the decorations around a window. Enabling
* decorations shows you the maximize, minimize, and close buttons.
*
* @param bool
*            the boolean indicating whether window should be
*            decorated or not.
* @return void
*/
bool A2DWindow::isUndecorated()
{
	return aUndecorated;
}

/**
*
* Sets the visibility of the decorations around a window. Enabling
* decorations shows you the maximize, minimize, and close buttons.
*
* @param bool
*            the boolean indicating whether window should be
*            decorated or not.
* @return void
*/
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

/**
*
* Sets the visibility of the decorations around a window. Enabling
* decorations shows you the maximize, minimize, and close buttons.
*
* @param bool
*            the boolean indicating whether window should be
*            decorated or not.
* @return void
*/
Color A2DWindow::getBorderColor()
{
    return aOptBorderColor;
}

/**
*
* Sets the visibility of the decorations around a window. Enabling
* decorations shows you the maximize, minimize, and close buttons.
*
* @param bool
*            the boolean indicating whether window should be
*            decorated or not.
* @return void
*/
void A2DWindow::setBorderColor(Color xBorderColor)
{
    aOptBorderColor = xBorderColor;
}

/**
*
* Sets the visibility of the decorations around a window. Enabling
* decorations shows you the maximize, minimize, and close buttons.
*
* @param bool
*            the boolean indicating whether window should be
*            decorated or not.
* @return void
*/
Color A2DWindow::getBackgroundColor()
{
	return aOptBackgroundColor;
}

/**
*
* Sets the visibility of the decorations around a window. Enabling
* decorations shows you the maximize, minimize, and close buttons.
*
* @param bool
*            the boolean indicating whether window should be
*            decorated or not.
* @return void
*/
void A2DWindow::setBackgroundColor(Color xBackgroundColor)
{
	aOptBackgroundColor = xBackgroundColor;
}

/**
*
* Sets the visibility of the decorations around a window. Enabling
* decorations shows you the maximize, minimize, and close buttons.
*
* @param bool
*            the boolean indicating whether window should be
*            decorated or not.
* @return void
*/
bool A2DWindow::isVisible()
{
	return aVisible;
}

/**
*
* Sets the visibility of the decorations around a window. Enabling
* decorations shows you the maximize, minimize, and close buttons.
*
* @param bool
*            the boolean indicating whether window should be
*            decorated or not.
* @return void
*/
void A2DWindow::setName(LPCWSTR xName)
{
    aName = xName;
    // SetWindowText(aChildHWnd, *xName);
    SetWindowText(aParentHWnd, xName);
}

/**
*
* Sets the visibility of the decorations around a window. Enabling
* decorations shows you the maximize, minimize, and close buttons.
*
* @param bool
*            the boolean indicating whether window should be
*            decorated or not.
* @return void
*/
LPCWSTR * A2DWindow::getName()
{
    return &aName;
}

/**
*
* Sets the visibility of the decorations around a window. Enabling
* decorations shows you the maximize, minimize, and close buttons.
*
* @param bool
*            the boolean indicating whether window should be
*            decorated or not.
* @return void
*/
void  A2DWindow::setFrame(A2DFrame * xFrame)
{
    aFrame = xFrame;
}

/**
*
* Sets the visibility of the decorations around a window. Enabling
* decorations shows you the maximize, minimize, and close buttons.
*
* @param bool
*            the boolean indicating whether window should be
*            decorated or not.
* @return void
*/
A2DFrame *  A2DWindow::getFrame()
{
    return aFrame;
}

/**
*
* Sets the visibility of the decorations around a window. Enabling
* decorations shows you the maximize, minimize, and close buttons.
*
* @param bool
*            the boolean indicating whether window should be
*            decorated or not.
* @return void
*/
A2DRect * A2DWindow::getBounds()
{
    return &aRect;
}

/**
*
* Sets the visibility of the decorations around a window. Enabling
* decorations shows you the maximize, minimize, and close buttons.
*
* @param bool
*            the boolean indicating whether window should be
*            decorated or not.
* @return void
*/
int A2DWindow::getDefaultCloseOperation()
{
    return aDefaultCloseOperation;
}

/**
*
* Sets the visibility of the decorations around a window. Enabling
* decorations shows you the maximize, minimize, and close buttons.
*
* @param bool
*            the boolean indicating whether window should be
*            decorated or not.
* @return void
*/
void A2DWindow::setDefaultCloseOperation(int xOperation)
{
    aDefaultCloseOperation = xOperation;
}

/**
*
* Sets the visibility of the decorations around a window. Enabling
* decorations shows you the maximize, minimize, and close buttons.
*
* @param bool
*            the boolean indicating whether window should be
*            decorated or not.
* @return void
*/
void A2DWindow::setLocationRelativeTo(A2DWindow * xWindow)
{
	if (xWindow == NULL)
	{
		aRect.aX = (GetSystemMetrics(SM_CXSCREEN) - aRect.aWidth) / 2;
		aRect.aY = (GetSystemMetrics(SM_CYSCREEN) - aRect.aHeight) / 2;
	}
}

/**
*
* Sets the visibility of the decorations around a window. Enabling
* decorations shows you the maximize, minimize, and close buttons.
*
* @param bool
*            the boolean indicating whether window should be
*            decorated or not.
* @return void
*/
void A2DWindow::setBorderWidth(float xBorderWidth)
{
	aOptBorderWidth = xBorderWidth;
}

/**
*
* Sets the visibility of the decorations around a window. Enabling
* decorations shows you the maximize, minimize, and close buttons.
*
* @param bool
*            the boolean indicating whether window should be
*            decorated or not.
* @return void
*/
float A2DWindow::getBorderWidth()
{
	return aOptBorderWidth;
}

/**
*
* This method creates a 1x1 image of the color indicated by the
* aOptBackgroundColor and updates all the windows derived of the aParentHWnd to
* that color. The aOptBackgroundColor
*
* @see #destroyBackgroundResources()
* @see #createBackgroundResources()
* @see #createResources()
* @see #destroyResources()
* @param  void
* @return void
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
	wcex.hbrBackground = CreateSolidBrush(RGB(aOptBackgroundColor.GetRed(), aOptBackgroundColor.GetGreen(), aOptBackgroundColor.GetBlue()));;
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = aName;
    wcex.hIconSm = LoadIcon(*aHInstance, IDI_APPLICATION);
	
    return RegisterClassEx(&wcex);
}

/**
*
* This method creates a 1x1 image of the color indicated by the
* aOptBackgroundColor and updates all the windows derived of the aParentHWnd to
* that color. The aOptBackgroundColor
*
* @see #destroyBackgroundResources()
* @see #createBackgroundResources()
* @see #createResources()
* @see #destroyResources()
* @param  void
* @return void
*/
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

/**
*
* This method creates a 1x1 image of the color indicated by the
* aOptBackgroundColor and updates all the windows derived of the aParentHWnd to
* that color. The aOptBackgroundColor
*
* @see #destroyBackgroundResources()
* @see #createBackgroundResources()
* @see #createResources()
* @see #destroyResources()
* @param  void
* @return void
*/
HWND A2DWindow::CreateCompatibleWindow(bool isParent)
{
    HRESULT         hr = S_OK;
    HWND            hWnd, hwndParent;
    int             left, top, width, height;
    DWORD           lStyle, lExStyle;
    LPCWSTR         className, titleName;
    
	left = static_cast<int>(isParent ? aRect.aX - aPadding : aRect.aX + aOptBorderWidth);
	top = static_cast<int>(isParent ? aRect.aY - aPadding : aRect.aY + aOptBorderWidth);
	width = static_cast<int>(isParent ? aRect.aWidth - aPadding * 2 : aRect.aWidth - aOptBorderWidth * 2);
	height = static_cast<int>(isParent ? aRect.aHeight - aPadding * 2 : aRect.aHeight - aOptBorderWidth * 2);
	lStyle = static_cast<int>(isParent ? WS_POPUP | WS_OVERLAPPED : WS_POPUP);
	lExStyle = static_cast<int>(isParent ? WS_EX_LAYERED | WS_EX_APPWINDOW : 0);
	hwndParent = isParent ? HWND_DESKTOP : aParentHWnd;
    className =  aName;
    titleName =  aName;

    hWnd = CreateWindowEx(lExStyle, className, titleName, lStyle, left, top, width, height, hwndParent, NULL, *aHInstance, this);
	
	aStyle = WS_EX_APPWINDOW;
    
	if (aChildHWnd && aParentHWnd)
    {
        // Force the child on top of parent!
        SetWindowPos(aChildHWnd, aParentHWnd, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
    }

	return hWnd;
}

/**
*
* This method creates a 1x1 image of the color indicated by the
* aOptBackgroundColor and updates all the windows derived of the aParentHWnd to
* that color. The aOptBackgroundColor
*
* @see #destroyBackgroundResources()
* @see #createBackgroundResources()
* @see #createResources()
* @see #destroyResources()
* @param  void
* @return void
*/
void A2DWindow::Render()
{   
    RenderComponent();
    RenderComponentBorder();
}

/**
*
* This method creates a 1x1 image of the color indicated by the
* aOptBackgroundColor and updates all the windows derived of the aParentHWnd to
* that color. The aOptBackgroundColor
*
* @see #destroyBackgroundResources()
* @see #createBackgroundResources()
* @see #createResources()
* @see #destroyResources()
* @param  void
* @return void
*/
void A2DWindow::Update()
{
	HDC hdc, memDC;

	// Cache variables to ensure that these variables
	// won't be changed in the middle of Update() via concurrent
	// threads.
	aRealX = aRect.aX;
	aRealY = aRect.aY;
	aRealWidth = aRect.aWidth + aOptBorderWidth * 2;
	aRealHeight = aRect.aHeight + aOptBorderWidth * 2;
	aRelativeX = aRealX - aPadding - aOptBorderWidth;
	aRelativeY = aRealY - aPadding - aOptBorderWidth;
	aRelativeWidth = aRealWidth + aPadding * 2;
	aRelativeHeight = aRealHeight + aPadding * 2;

	hdc = GetDC(aParentHWnd);
	memDC = CreateCompatibleDC(hdc);

	HBITMAP memBitmap = CreateCompatibleBitmap(hdc, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));

	SelectObject(memDC, memBitmap);

	aGraphics = new Graphics(memDC);
		
	/***********************************************/

    Render();

	/***********************************************/

	SIZE size = { (long)aRelativeWidth, (long)aRelativeHeight };

	HDC screenDC = GetDC(NULL);
	POINT ptDst = { (long)aRelativeX, (long)aRelativeY };
	POINT ptSrc = { 0, 0 };

	BLENDFUNCTION blendFunction;
	blendFunction.AlphaFormat = AC_SRC_ALPHA;
	blendFunction.BlendFlags = 0;
	blendFunction.BlendOp = AC_SRC_OVER;
	blendFunction.SourceConstantAlpha = 255;

	UpdateLayeredWindow(aParentHWnd, screenDC, &ptDst, &size, aGraphics->GetHDC(), &ptSrc, 0, &blendFunction, 2);
	
	/***********************************************/
	
	aGraphics->ReleaseHDC(memDC);
	delete aGraphics;
	aGraphics = 0;

	DeleteObject(memBitmap);
	DeleteObject(hdc);
	DeleteObject(memDC);
}

/**
*
* This method creates a 1x1 image of the color indicated by the
* aOptBackgroundColor and updates all the windows derived of the aParentHWnd to
* that color. The aOptBackgroundColor
*
* @see #destroyBackgroundResources()
* @see #createBackgroundResources()
* @see #createResources()
* @see #destroyResources()
* @param  void
* @return void
*/
void A2DWindow::destroyBoxShadowResources()
{	
	if (aTopLeftShadow)
	{
		delete aTopLeftShadow;
		aTopLeftShadow = 0;
	}

	if (aBottomLeftShadow)
	{
		delete aBottomLeftShadow;
		aBottomLeftShadow = 0;
	}

	if (aTopRightShadow)
	{
		delete aTopRightShadow;
		aTopRightShadow = 0;
	}

	if (aBottomRightShadow)
	{
		delete aBottomRightShadow;
		aBottomRightShadow = 0;
	}

	/*****************************************/
	if (aTopShadow)
	{
		delete aTopShadow;
		aTopShadow = 0;
	}

	if (aLeftShadow)
	{
		delete aLeftShadow;
		aLeftShadow = 0;
	}
	if (aRightShadow)
	{
		delete aRightShadow;
		aRightShadow = 0;
	}

	if (aBottomShadow)
	{
		delete aBottomShadow;
		aBottomShadow = 0;
	}
	
	/*****************************************/

	if (aTopShadowBrush)
	{
		delete aTopShadowBrush;
		aTopShadowBrush = 0;
	}
	if (aLeftShadowBrush)
	{
		delete aLeftShadowBrush;
		aLeftShadowBrush = 0;
	}

	if (aRightShadowBrush)
	{
		delete aRightShadowBrush;
		aRightShadowBrush = 0;
	}

	if (aBottomShadowBrush)
	{
		delete aBottomShadowBrush;
		aBottomShadowBrush = 0;
	}

}

/**
*
* This method creates a 1x1 image of the color indicated by the
* aOptBackgroundColor and updates all the windows derived of the aParentHWnd to
* that color. The aOptBackgroundColor
*
* @see #destroyBackgroundResources()
* @see #createBackgroundResources()
* @see #createResources()
* @see #destroyResources()
* @param  void
* @return void
*/
float* A2DWindow::getGaussianKernel(int xRadius)
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
		float distance = (float)(i * i);
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

	if (ret) return NULL;

	return bitmapData;
}


/**
* Blurs the source pixels into the destination pixels. The force of
* the blur is specified by the radius which must be greater than 0.</p>
* The source and destination pixels arrays are expected to be in the
* INT_ARGB format.
*
* After this method is executed, dstPixels contains a transposed and
* filtered copy of srcPixels.
*
* @param srcPixels the source pixels
* @param dstPixels the destination pixels
* @param width the width of the source picture
* @param height the height of the source picture
* @param kernel the kernel of the blur effect
* @param radius the radius of the blur effect
*/
Bitmap * A2DWindow::applyGaussianBlur(Bitmap * src, int radius)
{
	// NOTE: There could be memory leaks if the BitmapData is NULL
	// PLEASE FIX!

	float * kernel;
	Bitmap * blurred, *rotated;
	BitmapData * rotatedData, *srcData, *blurredData;

	kernel = getGaussianKernel(radius);

	blurred  = new Bitmap(src->GetWidth(), src->GetHeight());
	rotated = new Bitmap(src->GetHeight(), src->GetWidth());	

	// horizontal pass 0
	srcData = getLockedBitmapData(src);
	if (!srcData) return NULL;

	blurredData = getLockedBitmapData(blurred);
	if (!blurredData) return NULL;

	applyHorizontalblur(srcData, blurredData, kernel, radius);

	src->UnlockBits(srcData);

	blurred->UnlockBits(blurredData);		
	blurred->RotateFlip(Rotate90FlipNone);
	
	delete srcData;
	delete blurredData;

	blurredData = getLockedBitmapData(blurred);
	if (!blurredData) return NULL;

	rotatedData = getLockedBitmapData(rotated);
	if (!rotatedData) return NULL;

	// horizontal pass 1
	applyHorizontalblur(blurredData, rotatedData, kernel, radius);

	blurred->UnlockBits(blurredData);
	rotated->UnlockBits(rotatedData);

	rotated->RotateFlip(Rotate270FlipNone);

	delete rotatedData;
	delete blurredData;

	delete blurred;
	delete kernel;

	return rotated;
}

/**
* Blurs the source pixels into the destination pixels. The force of
* the blur is specified by the radius which must be greater than 0.</p>
* The source and destination pixels arrays are expected to be in the
* INT_ARGB format.
*
* After this method is executed, dstPixels contains a transposed and
* filtered copy of srcPixels.
*
* @param srcPixels the source pixels
* @param dstPixels the destination pixels
* @param width the width of the source picture
* @param height the height of the source picture
* @param kernel the kernel of the blur effect
* @param radius the radius of the blur effect
*/
void  A2DWindow::applyHorizontalblur(BitmapData * srcPixels, BitmapData * dstPixels, float * kernel, int radius)
{
	int ca = 0, cr = 0, cg = 0, cb = 0;
	float a = 0, r = 0, g = 0, b = 0;

	int width = srcPixels->Width;
	int height = srcPixels->Height;

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

			ca = static_cast<int>(a + 0.5f);
			cr = static_cast<int>(r + 0.5f);
			cg = static_cast<int>(g + 0.5f);
			cb = static_cast<int>(b + 0.5f);
			
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

/**
* Blurs the source pixels into the destination pixels. The force of
* the blur is specified by the radius which must be greater than 0.</p>
* The source and destination pixels arrays are expected to be in the
* INT_ARGB format.
*
* After this method is executed, dstPixels contains a transposed and
* filtered copy of srcPixels.
*
* @param srcPixels the source pixels
* @param dstPixels the destination pixels
* @param width the width of the source picture
* @param height the height of the source picture
* @param kernel the kernel of the blur effect
* @param radius the radius of the blur effect
*/
void A2DWindow::spliceToNinePatch(Image * src, Image * dest, float srcX, float srcY, float srcWidth, float srcHeight)
{
    Graphics graphics(dest);

	graphics.DrawImage(src, FLOAT_ZERO, FLOAT_ZERO, srcX, srcY, srcWidth, srcHeight, UnitPixel);
	graphics.DrawImage(src, FLOAT_ZERO, FLOAT_ZERO, srcX, srcY, srcWidth, srcHeight, UnitPixel); // Render twice to increase opacity
	graphics.DrawImage(src, FLOAT_ZERO, FLOAT_ZERO, srcX, srcY, srcWidth, srcHeight, UnitPixel); // Render twice to increase opacity
}

/**
* Blurs the source pixels into the destination pixels. The force of
* the blur is specified by the radius which must be greater than 0.</p>
* The source and destination pixels arrays are expected to be in the
* INT_ARGB format.
*
* After this method is executed, dstPixels contains a transposed and
* filtered copy of srcPixels.
*
* @param srcPixels the source pixels
* @param dstPixels the destination pixels
* @param width the width of the source picture
* @param height the height of the source picture
* @param kernel the kernel of the blur effect
* @param radius the radius of the blur effect
*/
HRESULT A2DWindow::createBoxShadowResources()
{
	HRESULT hr = S_OK;

	Bitmap * solid, *blurred;
	Graphics * graphics;
    SolidBrush blackBrush(aOptBoxShadowColor);

	float radius = aOptBoxShadowRadius;
	float radiusSafety = radius * 2;
	float realDim = radius * 3;
	float relativeDim = realDim + radius * 2;
	
	int radiusAsInt = static_cast<int>(radius);
	int radiusSafetyAsInt = static_cast<int>(radiusSafety);
	int relativeDimAsInt = static_cast<int>(relativeDim);

	aTopLeftShadow = new Bitmap(radiusSafetyAsInt, radiusSafetyAsInt);
	aBottomLeftShadow = new Bitmap(radiusSafetyAsInt, radiusSafetyAsInt);
	aTopRightShadow = new Bitmap(radiusSafetyAsInt, radiusSafetyAsInt);
	aBottomRightShadow = new Bitmap(radiusSafetyAsInt, radiusSafetyAsInt);

	aTopShadow = new Bitmap(1, radiusAsInt);
	aLeftShadow = new Bitmap(radiusAsInt, 1);
	aRightShadow = new Bitmap(radiusAsInt, 1);
	aBottomShadow = new Bitmap(1, radiusAsInt);

	solid = new Bitmap(relativeDimAsInt, relativeDimAsInt);
	graphics = new Graphics(solid);

	// Draw base shape

	graphics->FillRectangle(&blackBrush, radius, radius, realDim, realDim);

    // Create box shadow
	
	blurred = applyGaussianBlur(solid, radiusAsInt);
	
    // Cache as 9-patch
	
    spliceToNinePatch(blurred, aTopLeftShadow, FLOAT_ZERO, FLOAT_ZERO, radiusSafety, radiusSafety);
    spliceToNinePatch(blurred, aBottomLeftShadow, FLOAT_ZERO, relativeDim - radiusSafety, radiusSafety, radiusSafety);
    spliceToNinePatch(blurred, aBottomRightShadow, relativeDim - radiusSafety, relativeDim - radiusSafety, radiusSafety, radiusSafety);
    spliceToNinePatch(blurred, aTopRightShadow, relativeDim - radiusSafety, FLOAT_ZERO, radiusSafety, radiusSafety);

    spliceToNinePatch(blurred, aTopShadow, radiusSafety, FLOAT_ZERO, FLOAT_ONE, radius);
    spliceToNinePatch(blurred, aLeftShadow, FLOAT_ZERO, radiusSafety, radius, FLOAT_ONE);
	spliceToNinePatch(blurred, aRightShadow, relativeDim - radius, radiusSafety, radius, FLOAT_ONE);
    spliceToNinePatch(blurred, aBottomShadow, radiusSafety, relativeDim - radius, FLOAT_ONE, radius);

	aTopShadowBrush = new TextureBrush(aTopShadow);
	aLeftShadowBrush = new TextureBrush(aLeftShadow);
	aRightShadowBrush = new TextureBrush(aRightShadow);
	aBottomShadowBrush = new TextureBrush(aBottomShadow);

	// Update values
	aPadding = radius;
	aShadowPadding = radiusSafety;

    delete graphics;
    delete blurred;
    delete solid;

	return hr;
}

/**
* Blurs the source pixels into the destination pixels. The force of
* the blur is specified by the radius which must be greater than 0.</p>
* The source and destination pixels arrays are expected to be in the
* INT_ARGB format.
*
* After this method is executed, dstPixels contains a transposed and
* filtered copy of srcPixels.
*
* @param srcPixels the source pixels
* @param dstPixels the destination pixels
* @param width the width of the source picture
* @param height the height of the source picture
* @param kernel the kernel of the blur effect
* @param radius the radius of the blur effect
*/
HRESULT A2DWindow::CreateBackgroundResources()
{
	HRESULT hr = S_OK;

	aBackground = new Bitmap(1, 1);

	Graphics  graphics(aBackground);
	SolidBrush blackBrush(aOptBackgroundColor);

	graphics.FillRectangle(&blackBrush, 0, 0, 1, 1);

	aBackgroundBrush = new TextureBrush(aBackground);

	return hr;
}

/**
* Blurs the source pixels into the destination pixels. The force of
* the blur is specified by the radius which must be greater than 0.</p>
* The source and destination pixels arrays are expected to be in the
* INT_ARGB format.
*
* After this method is executed, dstPixels contains a transposed and
* filtered copy of srcPixels.
*
* @param srcPixels the source pixels
* @param dstPixels the destination pixels
* @param width the width of the source picture
* @param height the height of the source picture
* @param kernel the kernel of the blur effect
* @param radius the radius of the blur effect
*/
void A2DWindow::DestroyBackgroundResources()
{
	if (aBackground)
	{
		delete aBackground;
		aBackground = 0;
	}

	if (aBackgroundBrush)
	{
		delete aBackgroundBrush;
		aBackgroundBrush = 0;
	}
}

/**
* Blurs the source pixels into the destination pixels. The force of
* the blur is specified by the radius which must be greater than 0.</p>
* The source and destination pixels arrays are expected to be in the
* INT_ARGB format.
*
* After this method is executed, dstPixels contains a transposed and
* filtered copy of srcPixels.
*
* @param srcPixels the source pixels
* @param dstPixels the destination pixels
* @param width the width of the source picture
* @param height the height of the source picture
* @param kernel the kernel of the blur effect
* @param radius the radius of the blur effect
*/
HRESULT A2DWindow::CreateResources()
{
	HRESULT hr = S_OK;
	
	hr = CreateBackgroundResources();
	if (FAILED(hr))	return hr;

	hr = createBoxShadowResources();

	return hr;
}

/**
* Blurs the source pixels into the destination pixels. The force of
* the blur is specified by the radius which must be greater than 0.</p>
* The source and destination pixels arrays are expected to be in the
* INT_ARGB format.
*
* After this method is executed, dstPixels contains a transposed and
* filtered copy of srcPixels.
*
* @param srcPixels the source pixels
* @param dstPixels the destination pixels
* @param width the width of the source picture
* @param height the height of the source picture
* @param kernel the kernel of the blur effect
* @param radius the radius of the blur effect
*/
void A2DWindow::DestroyResources()
{
	if (aBackground)
	{
		delete aBackground;
		aBackground = 0;
	}

	if (aBackgroundBrush)
	{
		delete aBackgroundBrush;
		aBackgroundBrush = 0;
	}

	destroyBoxShadowResources();
	DestroyBackgroundResources();
}

/**
* Blurs the source pixels into the destination pixels. The force of
* the blur is specified by the radius which must be greater than 0.</p>
* The source and destination pixels arrays are expected to be in the
* INT_ARGB format.
*
* After this method is executed, dstPixels contains a transposed and
* filtered copy of srcPixels.
*
* @param srcPixels the source pixels
* @param dstPixels the destination pixels
* @param width the width of the source picture
* @param height the height of the source picture
* @param kernel the kernel of the blur effect
* @param radius the radius of the blur effect
*/
void A2DWindow::setVisible(bool xVisible)
{
    aVisible = xVisible;

    if (aVisible)
    {
        // Create resources!
        aFrame->CreateResources();

        ShowWindow(aChildHWnd, SW_SHOWNORMAL);
        ShowWindow(aParentHWnd, SW_SHOWNORMAL);

        RunMessageLoop();
    }
    else
    {
        ShowWindow(aChildHWnd, SW_HIDE);
        ShowWindow(aParentHWnd, SW_HIDE);
    }
}

/**
* Blurs the source pixels into the destination pixels. The force of
* the blur is specified by the radius which must be greater than 0.</p>
* The source and destination pixels arrays are expected to be in the
* INT_ARGB format.
*
* After this method is executed, dstPixels contains a transposed and
* filtered copy of srcPixels.
*
* @param srcPixels the source pixels
* @param dstPixels the destination pixels
* @param width the width of the source picture
* @param height the height of the source picture
* @param kernel the kernel of the blur effect
* @param radius the radius of the blur effect
*/
void A2DWindow::RenderComponentBorder()
{
	if (aOptBorderWidth > 0)
	{
		Pen borderPen(aOptBorderColor, aOptBorderWidth);
    
		aGraphics->DrawRectangle(&borderPen, aPadding, aPadding, aRealWidth, aRealHeight);
    
		DeleteObject(&borderPen);
	}
}

/**
* Blurs the source pixels into the destination pixels. The force of
* the blur is specified by the radius which must be greater than 0.</p>
* The source and destination pixels arrays are expected to be in the
* INT_ARGB format.
*
* After this method is executed, dstPixels contains a transposed and
* filtered copy of srcPixels.
*
* @param srcPixels the source pixels
* @param dstPixels the destination pixels
* @param width the width of the source picture
* @param height the height of the source picture
* @param kernel the kernel of the blur effect
* @param radius the radius of the blur effect
*/
void A2DWindow::RenderComponent()
{	
	aTopShadowBrush->ResetTransform();
	aLeftShadowBrush->ResetTransform();
	aRightShadowBrush->ResetTransform();
	aBottomShadowBrush->ResetTransform();
	
	aTopShadowBrush->TranslateTransform(aShadowPadding, FLOAT_ZERO);
	aGraphics->FillRectangle(aTopShadowBrush, aShadowPadding, FLOAT_ZERO, aRelativeWidth - aShadowPadding * 2, aPadding);

	aLeftShadowBrush->TranslateTransform(FLOAT_ZERO, aShadowPadding);
    aGraphics->FillRectangle(aLeftShadowBrush, FLOAT_ZERO, aShadowPadding, aPadding, aRelativeHeight - aShadowPadding * 2);

	aRightShadowBrush->TranslateTransform(aRelativeWidth - aPadding, aShadowPadding);
    aGraphics->FillRectangle(aRightShadowBrush, aRelativeWidth - aPadding, aShadowPadding, aPadding, aRelativeHeight - aShadowPadding * 2);

	aBottomShadowBrush->TranslateTransform(aShadowPadding, aRelativeHeight - aPadding);
    aGraphics->FillRectangle(aBottomShadowBrush, aShadowPadding, aRealHeight + aPadding, aRelativeWidth - aShadowPadding * 2, aPadding);
	
	aGraphics->DrawImage(aTopLeftShadow, FLOAT_ZERO, FLOAT_ZERO, aShadowPadding, aShadowPadding);
    aGraphics->DrawImage(aBottomLeftShadow, FLOAT_ZERO, aRelativeHeight - aShadowPadding, aShadowPadding, aShadowPadding);
    aGraphics->DrawImage(aTopRightShadow, aRelativeWidth - aShadowPadding, FLOAT_ZERO, aShadowPadding, aShadowPadding);
    aGraphics->DrawImage(aBottomRightShadow, aRelativeWidth - aShadowPadding, aRelativeHeight - aShadowPadding, aShadowPadding, aShadowPadding);

    aGraphics->FillRectangle(aBackgroundBrush, aPadding, aPadding, aRealWidth, aRealHeight);	
}

/**
* Blurs the source pixels into the destination pixels. The force of
* the blur is specified by the radius which must be greater than 0.</p>
* The source and destination pixels arrays are expected to be in the
* INT_ARGB format.
*
* After this method is executed, dstPixels contains a transposed and
* filtered copy of srcPixels.
*
* @param srcPixels the source pixels
* @param dstPixels the destination pixels
* @param width the width of the source picture
* @param height the height of the source picture
* @param kernel the kernel of the blur effect
* @param radius the radius of the blur effect
*/
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
		}
		case WM_LBUTTONDOWN:
		{
			aWindow = reinterpret_cast<A2DWindow *>(static_cast<LONG_PTR>(GetWindowLongPtrW(xHwnd, GWLP_USERDATA)));
			if (aWindow->aChildHWnd != xHwnd) return 0;

			SetCapture(xHwnd);
			aWindow->isDragged = true;

			return S_OK;
		}
		case WM_MOUSEMOVE:
		{
			aWindow = reinterpret_cast<A2DWindow *>(static_cast<LONG_PTR>(GetWindowLongPtrW(xHwnd, GWLP_USERDATA)));
			if (aWindow->aChildHWnd != xHwnd) return 0;

			if (!aWindow->isDragged)
			{
				GetCursorPos(&aWindow->lastDraggedPoint);
				ScreenToClient(xHwnd, &aWindow->lastDraggedPoint);
			}

			aWindow = reinterpret_cast<A2DWindow *>(static_cast<LONG_PTR>(GetWindowLongPtrW(xHwnd, GWLP_USERDATA)));
			if (aWindow->aChildHWnd != xHwnd) return 0;

			if (aWindow->isDragged)
			{

				POINT p;
				GetCursorPos(&p);
				ScreenToClient(xHwnd, &p);
					
				HDWP hdwp = BeginDeferWindowPos(2);

				int deltaY = aWindow->lastDraggedPoint.y - p.y;
				int deltaX = aWindow->lastDraggedPoint.x - p.x;

				int offset = aWindow->getBoxShadowRadius() + aWindow->getBorderWidth();

				// DEFER REGION //

				A2DRect& aRect = aWindow->aRect;

				aRect.aX = 500;
				aRect.aY = 500;
				aRect.aWidth += deltaX;
				aRect.aHeight += deltaY;
					
				aWindow->Update();

				SetWindowPos(aWindow->aChildHWnd, aWindow->aParentHWnd, aRect.aX, aRect.aY, aRect.aWidth, aRect.aHeight, SWP_NOZORDER | SWP_NOACTIVATE);						

				// DEFER REGION //

				aWindow->lastDraggedPoint = p;
			}

			return S_OK;
		}
		case WM_LBUTTONUP:
		{
			aWindow = reinterpret_cast<A2DWindow *>(static_cast<LONG_PTR>(GetWindowLongPtrW(xHwnd, GWLP_USERDATA)));
			if (aWindow->aChildHWnd != xHwnd) return 0;

			ReleaseCapture();
			aWindow->isDragged = false;

			return S_OK;
		}
        case WM_CLOSE:
        {       
            DestroyWindow(xHwnd);

            return S_OK;
        }
        case WM_DESTROY:
        {       
			PostQuitMessage(0);
			CloseHandle(xHwnd);

            return S_OK;
        }
        }
    }

    return  DefWindowProc(xHwnd, xMessage, xWParam, xLParam);
}


/**
* 
* Returns a thumbnail of a source image. <code>newSize</code> defines the
* length of the longest dimension of the thumbnail. The other dimension is
* then computed according to the dimensions ratio of the original picture.
* 
* This method favors speed over quality. When the new size is less than
* half the longest dimension of the source image,
* {@link #createThumbnail(BufferedImage, int)} or
* {@link #createThumbnail(BufferedImage, int, int)} should be used instead
* to ensure the quality of the result without sacrificing too much
* performance.
*
* @see #createThumbnailFast(java.awt.image.BufferedImage, int, int)
* @see #createThumbnail(java.awt.image.BufferedImage, int)
* @see #createThumbnail(java.awt.image.BufferedImage, int, int)
* @param image
*            the source image
* @param newSize
*            the length of the largest dimension of the thumbnail
* @return a new compatible <code>BufferedImage</code> containing a
*         thumbnail of <code>image</code>
* @throws IllegalArgumentException
*             if <code>newSize</code> is larger than the largest
*             dimension of <code>image</code> or &lt;= 0
*/
LPCWSTR A2DWindow::GetClass()
{
    return L"A2DWindow";
}

/**
* Blurs the source pixels into the destination pixels. The force of
* the blur is specified by the radius which must be greater than 0.</p>
* The source and destination pixels arrays are expected to be in the
* INT_ARGB format.
*
* After this method is executed, dstPixels contains a transposed and
* filtered copy of srcPixels.
*
* @param srcPixels the source pixels
* @param dstPixels the destination pixels
* @param width the width of the source picture
* @param height the height of the source picture
* @param kernel the kernel of the blur effect
* @param radius the radius of the blur effect
*/
LPCWSTR A2DWindow::ToString()
{
    return L"A2DWindow";
}

/**
* Blurs the source pixels into the destination pixels. The force of
* the blur is specified by the radius which must be greater than 0.</p>
* The source and destination pixels arrays are expected to be in the
* INT_ARGB format.
*
* After this method is executed, dstPixels contains a transposed and
* filtered copy of srcPixels.
*
* @param srcPixels the source pixels
* @param dstPixels the destination pixels
* @param width the width of the source picture
* @param height the height of the source picture
* @param kernel the kernel of the blur effect
* @param radius the radius of the blur effect
*/
bool A2DWindow::operator==(A2DAbstract * xAbstract)
{
    return false;
}

/**
* Blurs the source pixels into the destination pixels. The force of
* the blur is specified by the radius which must be greater than 0.</p>
* The source and destination pixels arrays are expected to be in the
* INT_ARGB format.
*
* After this method is executed, dstPixels contains a transposed and
* filtered copy of srcPixels.
*
* @param srcPixels the source pixels
* @param dstPixels the destination pixels
* @param width the width of the source picture
* @param height the height of the source picture
* @param kernel the kernel of the blur effect
* @param radius the radius of the blur effect
*/
HRESULT A2DWindow::Initialize()
{
    HRESULT hr = S_OK;

    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR           gdiplusToken;

    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
    
	/*****************************************************/

	aRect.aX = 30;
	aRect.aY = 30;
	aRect.aHeight = 480;
	aRect.aWidth = 640;
	aPadding = 25;
	aShadowPadding = 75;
	aName = L"TESTING";

	setLocationRelativeTo(NULL);
	setBorderColor(Color(202, 225, 255));
	setBoxShadowColor(Color(255, 0, 0));
	setBackgroundColor(Color(0, 0, 255));
	setBorderWidth(1); //Force the border in DX window
	setBoxShadowRadius(80);

	/*****************************************************/

    hr = RegisterClass();

    if (FAILED(hr)) return hr;
    
	aParentHWnd = A2DWindow::CreateCompatibleWindow(true);

	if (!aParentHWnd) return E_FAIL;

	aChildHWnd = A2DWindow::CreateCompatibleWindow(false);

	if (!aChildHWnd) return E_FAIL;

    hr = CreateResources();

    if (FAILED(hr)) return hr;

    Update();
	
    return hr;
}

/**
* Blurs the source pixels into the destination pixels. The force of
* the blur is specified by the radius which must be greater than 0.</p>
* The source and destination pixels arrays are expected to be in the
* INT_ARGB format.
*
* After this method is executed, dstPixels contains a transposed and
* filtered copy of srcPixels.
*
* @param srcPixels the source pixels
* @param dstPixels the destination pixels
* @param width the width of the source picture
* @param height the height of the source picture
* @param kernel the kernel of the blur effect
* @param radius the radius of the blur effect
*/
void A2DWindow::Deinitialize()
{
    aParentHWnd = NULL;
    aChildHWnd = NULL;
}
