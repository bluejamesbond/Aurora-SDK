
#include "../../include/A2DExtLibs.h"
#include "../../include/A2DMSWindow.h"

A2DMSWindow::A2DMSWindow(HINSTANCE xHInstance) 
: aHInstance(xHInstance){}

A2DMSWindow::~A2DMSWindow(){}

void A2DMSWindow::setMinimumSize(float xWidth, float xHeight)
{
    aMinDims.aWidth = max(aOptBoxShadowRadius * A2D_WINDOW_BOX_SHADOW_SAFETY_RATIO, xWidth);
    aMinDims.aHeight = max(aOptBoxShadowRadius * A2D_WINDOW_BOX_SHADOW_SAFETY_RATIO, xHeight);
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
void A2DMSWindow::setUndecorated(bool xUndecoratedFlag)
{
    // we cannot just use WS_POPUP style
    // WS_THICKFRAME: without this the window cannot be resized and so aero snap, de-maximizing and minimizing won't work
    // WS_SYSMENU: enables the context menu with the move, close, maximize, minize... commands (shift + right-click on the task bar item)
    // HOWEVER, this also enables the menu with the maximize buttons in the title bar, which will exist inside your client area and are clickable. 
    // WS_CAPTION: enables aero minimize animation/transition
    // WS_MAXIMIZEBOX, WS_MINIMIZEBOX: enable minimize/maximize

    A2DWindow::setUndecorated(xUndecoratedFlag);

    // Window has not been set up, return
    if (!aParentHWnd)   return;

    LONG lStyle, lExStyle;

    lStyle = GetWindowLongPtr(aParentHWnd, GWL_STYLE);
    lExStyle = GetWindowLongPtr(aParentHWnd, GWL_EXSTYLE);

    lStyle &= aUndecorated ? ~(WS_CAPTION | WS_THICKFRAME | WS_MINIMIZE | WS_MAXIMIZE | WS_SYSMENU) : (WS_CAPTION | WS_THICKFRAME | WS_MINIMIZE | WS_MAXIMIZE | WS_SYSMENU);
    lStyle |= aUndecorated ? (WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP) : 0;
    lExStyle |= aUndecorated ? (WS_EX_LAYERED | WS_EX_APPWINDOW) : WS_EX_LAYERED;

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
void A2DMSWindow::setBoxShadowRadius(float xBoxShadowRadius)
{
    A2DWindow::setBoxShadowRadius(xBoxShadowRadius);
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
void A2DMSWindow::UpdateAndCacheBackground()
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
void A2DMSWindow::updateAndCacheBoxShadow()
{
destroyBoxShadowResources();
createBoxShadowResources();
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
HRESULT A2DMSWindow::RegisterClass()
{
    WNDCLASSEX wcex = { sizeof(WNDCLASSEX) };
    wcex.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wcex.lpfnWndProc = A2DMSWindow::WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = aHInstance;
    wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = CreateSolidBrush(RGB(aOptBackgroundColor.GetRed(), aOptBackgroundColor.GetGreen(), aOptBackgroundColor.GetBlue()));;
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = aName;
    wcex.hIconSm = LoadIcon(aHInstance, IDI_APPLICATION);
    
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
void A2DMSWindow::RunMessageLoop()
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

void A2DMSWindow::setName(LPCWSTR xName)
{
    A2DWindow::setName(xName);

    SetWindowText(aHNWnd, aName);
    SetWindowText(aParentHWnd, aName);
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
HWND A2DMSWindow::CreateCompatibleWindow(bool isParent)
{
    HRESULT         hr = S_OK;
    HWND            hWnd, hwndParent;
    int             left, top, width, height;
    DWORD           lStyle, lExStyle;
    LPCWSTR         className, titleName;
    
    left = static_cast<int>(isParent ? aRect.aX - aOptBoxShadowRadius : aRect.aX + aOptBorderWidth);
    top = static_cast<int>(isParent ? aRect.aY - aOptBoxShadowRadius : aRect.aY + aOptBorderWidth);
    width = static_cast<int>(isParent ? aRect.aWidth + aOptBoxShadowRadius * 2 : aRect.aWidth - aOptBorderWidth * 2);
    height = static_cast<int>(isParent ? aRect.aHeight + aOptBoxShadowRadius * 2 : aRect.aHeight - aOptBorderWidth * 2);
    lStyle = static_cast<int>(isParent ? WS_POPUP | WS_OVERLAPPED : WS_POPUP);
    lExStyle = static_cast<int>(isParent ? WS_EX_LAYERED | WS_EX_APPWINDOW : 0);
    hwndParent = isParent ? HWND_DESKTOP : aParentHWnd;
    className =  aName;
    titleName =  aName;

    hWnd = CreateWindowEx(lExStyle, className, titleName, lStyle, left, top, width, height, hwndParent, NULL, aHInstance, this);
    
    aStyle = WS_EX_APPWINDOW;
    
    if (aHNWnd && aParentHWnd)
    {
        // Force the child on top of parent!
        SetWindowPos(aHNWnd, aParentHWnd, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
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
void A2DMSWindow::Update()
{
    HDC hdc, memDC;
    //A2DWindow::Update();
    // Cache variables to ensure that these variables
    // won't be changed in the middle of Update() via concurrent
    // threads.
    aRealX = aRect.aX + aOptBorderWidth;
    aRealY = aRect.aY + aOptBorderWidth;
    aRealWidth = aRect.aWidth - aOptBorderWidth * 2;
    aRealHeight = aRect.aHeight - aOptBorderWidth * 2;
    aRelativeX = aRect.aX - aPadding;
    aRelativeY = aRect.aY - aPadding;
    aRelativeWidth = aRect.aWidth + aPadding * 2;
    aRelativeHeight = aRect.aHeight + aPadding * 2;

    /***********************************************/

    HDWP hdwp = BeginDeferWindowPos(2);

    if (hdwp) hdwp = DeferWindowPos(hdwp, aParentHWnd, NULL, aRelativeX, aRelativeY, aRelativeWidth, aRelativeHeight, SWP_NOZORDER | SWP_NOACTIVATE);
    
    /***********************************************/

    hdc = GetDC(aParentHWnd);
    memDC = CreateCompatibleDC(hdc);

    HBITMAP memBitmap = CreateCompatibleBitmap(hdc, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));

    SelectObject(memDC, memBitmap);

    aGraphics = new Graphics(memDC);
        
    /***********************************************/

    A2DWindow::Update();

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

	if (hdwp) hdwp = DeferWindowPos(hdwp, aHNWnd, aParentHWnd, aRealX, aRealY, aRealWidth, aRealHeight, SWP_NOZORDER | SWP_NOACTIVATE);

	EndDeferWindowPos(hdwp);

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
void A2DMSWindow::destroyBoxShadowResources()
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
float* A2DMSWindow::getGaussianKernel(int xRadius)
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

BitmapData * A2DMSWindow::getLockedBitmapData(Bitmap * src)
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
Bitmap * A2DMSWindow::applyGaussianBlur(Bitmap * src, int radius)
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
void  A2DMSWindow::applyHorizontalblur(BitmapData * srcPixels, BitmapData * dstPixels, float * kernel, int radius)
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
void A2DMSWindow::spliceToNinePatch(Image * src, Image * dest, float srcX, float srcY, float srcWidth, float srcHeight)
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
HRESULT A2DMSWindow::createBoxShadowResources()
{
    HRESULT hr = S_OK;

    Bitmap * solid, *blurred;
    Graphics * graphics;
    SolidBrush blackBrush(aOptBoxShadowColor);

    float radius = aOptBoxShadowRadius;
    float radiusSafety = radius * A2D_WINDOW_BOX_SHADOW_SAFETY_RATIO;
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
HRESULT A2DMSWindow::CreateBackgroundResources()
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
void A2DMSWindow::DestroyBackgroundResources()
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
HRESULT A2DMSWindow::CreateResources()
{
    HRESULT hr = S_OK; 

	// Create resize window pointer.
	aHResizeWnd = aOptBorderWidth < A2D_WINDOW_RESIZE_DEFAULT_DISTANCE ? aHNWnd : aParentHWnd;

    hr = CreateBackgroundResources();
    if (FAILED(hr)) return hr;

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
void A2DMSWindow::DestroyResources()
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
void A2DMSWindow::setVisible(bool xVisible)
{
    A2DWindow::setVisible(xVisible);

    if (aVisible)
    {
        // Create resources!
        aFrame->CreateResources();

        ShowWindow(aHNWnd, SW_SHOWNORMAL);
        ShowWindow(aParentHWnd, SW_SHOWNORMAL);

        RunMessageLoop();
    }
    else
    {
        ShowWindow(aHNWnd, SW_HIDE);
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
void A2DMSWindow::RenderComponentBorder()
{
    if (aOptBorderWidth > 0)
    {
        Pen borderPen(aOptBorderColor, aOptBorderWidth);
    
        aGraphics->DrawRectangle(&borderPen, aPadding + aOptBorderWidth / 2, aPadding + aOptBorderWidth / 2, aRealWidth + aOptBorderWidth, aRealHeight + aOptBorderWidth);
    
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
void A2DMSWindow::RenderComponent()
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
    aGraphics->FillRectangle(aBottomShadowBrush, aShadowPadding, aRelativeHeight - aPadding, aRelativeWidth - aShadowPadding * 2, aPadding);
    
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
LRESULT CALLBACK A2DMSWindow::WndProc(HWND xHwnd, UINT xMessage, WPARAM xWParam, LPARAM xLParam)
{
    A2DMSWindow * aWindow;

    if (xMessage == WM_CREATE)
    {
        CREATESTRUCT *pCreate = reinterpret_cast<CREATESTRUCT*>(xLParam);
        aWindow = reinterpret_cast<A2DMSWindow*>(pCreate->lpCreateParams);
        SetWindowLongPtr(xHwnd, GWLP_USERDATA, (LONG_PTR)aWindow);
        return S_OK;
    }
    else
    {
        switch (xMessage)
        {
        case WM_LBUTTONDOWN:
        {
                               aWindow = reinterpret_cast<A2DMSWindow *>(static_cast<LONG_PTR>(GetWindowLongPtrW(xHwnd, GWLP_USERDATA)));
                               if (aWindow->aHResizeWnd != xHwnd) return 0;
                               
                               SetCapture(xHwnd);
                               aWindow->isDragged = true;

                               RECT rect;
                               GetWindowRect(xHwnd, &rect);

							   rect.bottom -= aWindow->aParentHWnd == xHwnd ? aWindow->aPadding : 0;
							   rect.right -= aWindow->aParentHWnd == xHwnd ? aWindow->aPadding : 0;
							   rect.left += aWindow->aParentHWnd == xHwnd ? aWindow->aPadding : 0;
							   rect.top += aWindow->aParentHWnd == xHwnd ? aWindow->aPadding : 0;

                               POINT p;
                               GetCursorPos(&p);

                               int x = p.x;
                               int y = p.y;

                               if ((x >= rect.left && x < rect.left + A2D_WINDOW_RESIZE_EDGE_DISTANCE ||
                                   x < rect.right && x >= rect.right - A2D_WINDOW_RESIZE_EDGE_DISTANCE ||
                                   y < rect.bottom && y >= rect.bottom - A2D_WINDOW_RESIZE_EDGE_DISTANCE ||
                                   y >= rect.top && y < rect.top + A2D_WINDOW_RESIZE_EDGE_DISTANCE) &&
                                   !aWindow->isResizing)
                               {
                                   aWindow->isResizing = true;
                               }

                               SetCursor(aWindow->aCurrentCursor);

                               return S_OK;
        }
        case WM_MOUSEMOVE:
        {
                            aWindow = reinterpret_cast<A2DMSWindow *>(static_cast<LONG_PTR>(GetWindowLongPtrW(xHwnd, GWLP_USERDATA)));
							if (aWindow->aHResizeWnd != xHwnd)
							{
								return 0;
							}

                            //const LONG border_width = 1; //in pixels
                            RECT rect;
                            GetWindowRect(xHwnd, &rect);

							rect.bottom -= aWindow->aParentHWnd == xHwnd ? aWindow->aPadding : 0;
							rect.right -= aWindow->aParentHWnd == xHwnd ? aWindow->aPadding : 0;
							rect.left += aWindow->aParentHWnd == xHwnd ? aWindow->aPadding : 0;
							rect.top += aWindow->aParentHWnd == xHwnd ? aWindow->aPadding : 0;

                            POINT p;
                            GetCursorPos(&p);

                            int x = p.x;
                            int y = p.y;

                            if (!aWindow->isResizing)
                            {
                                //bottom left corner
                                if (x >= rect.left && x < rect.left + A2D_WINDOW_RESIZE_EDGE_DISTANCE &&
                                    y < rect.bottom && y >= rect.bottom - A2D_WINDOW_RESIZE_EDGE_DISTANCE)
                                {
                                    aWindow->aCurrentCursor = LoadCursor(NULL, IDC_SIZENESW);
                                    aWindow->aWinMoveRes = true;
                                }
                                //bottom right corner
                                else if (x < rect.right && x >= rect.right - A2D_WINDOW_RESIZE_EDGE_DISTANCE &&
                                    y < rect.bottom && y >= rect.bottom - A2D_WINDOW_RESIZE_EDGE_DISTANCE)
                                {
                                    aWindow->aCurrentCursor = LoadCursor(NULL, IDC_SIZENWSE);
                                    aWindow->aWinMoveRes = false;
                                }
                                //top left corner
                                else if (x >= rect.left && x < rect.left + A2D_WINDOW_RESIZE_EDGE_DISTANCE &&
                                    y >= rect.top && y < rect.top + A2D_WINDOW_RESIZE_EDGE_DISTANCE)
                                {
                                    aWindow->aCurrentCursor = LoadCursor(NULL, IDC_SIZENWSE);
                                    aWindow->aWinMoveRes = true;
                                }
                                //top right corner
                                else if (x < rect.right && x >= rect.right - A2D_WINDOW_RESIZE_EDGE_DISTANCE &&
                                    y >= rect.top && y < rect.top + A2D_WINDOW_RESIZE_EDGE_DISTANCE)
                                {
                                    aWindow->aCurrentCursor = LoadCursor(NULL, IDC_SIZENESW);
                                    aWindow->aWinMoveRes = false;
                                }
                                //left border
                                else if (x >= rect.left && x < rect.left + A2D_WINDOW_RESIZE_EDGE_DISTANCE)
                                {
                                    aWindow->aCurrentCursor = LoadCursor(NULL, IDC_SIZEWE);
                                    aWindow->aWinMoveRes = true;
                                }
                                //right border
                                else if (x < rect.right && x >= rect.right - A2D_WINDOW_RESIZE_EDGE_DISTANCE)
                                {
                                    aWindow->aCurrentCursor = LoadCursor(NULL, IDC_SIZEWE);
                                    aWindow->aWinMoveRes = false;
                                }
                                //bottom border
                                else if (y < rect.bottom && y >= rect.bottom - A2D_WINDOW_RESIZE_EDGE_DISTANCE)
                                {
                                    aWindow->aCurrentCursor = LoadCursor(NULL, IDC_SIZENS);
                                    aWindow->aWinMoveRes = false;
                                }
                                //top border
                                else if (y >= rect.top && y < rect.top + A2D_WINDOW_RESIZE_EDGE_DISTANCE)
                                {
                                    aWindow->aCurrentCursor = LoadCursor(NULL, IDC_SIZENS);
                                    aWindow->aWinMoveRes = true;
                                }
                                //default
                                else
                                {
                                    aWindow->aCurrentCursor = LoadCursor(NULL, IDC_ARROW);
                                    aWindow->aWinMoveRes = false;
                                }

                                SetCursor(aWindow->aCurrentCursor);
                            }                       
                             
                            if (!aWindow->isDragged)
                            {
                                GetCursorPos(&aWindow->aLastDraggedPoint);
                                ScreenToClient(xHwnd, &aWindow->aLastDraggedPoint);
                            }

                             if (aWindow->isDragged && aWindow->isResizing)
                             {
                                 POINT p;
                                 GetCursorPos(&p);
                                 ScreenToClient(xHwnd, &p);
                                 
                                 A2DRect& aRect = aWindow->aRect;
                                 float deltaY = static_cast<float>(aWindow->aLastDraggedPoint.y - p.y);
                                 float deltaX = static_cast<float>(aWindow->aLastDraggedPoint.x - p.x);

                                 HCURSOR currentCursor = GetCursor();
                                 
                                 // Process resizing.

                                 // Resize up and down.
                                 if (currentCursor == LoadCursor(NULL, IDC_SIZENS))
                                 {
                                     if (aWindow->aWinMoveRes)
                                     {
                                         if (aRect.aHeight + deltaY >= aWindow->aMinDims.aHeight &&
                                             aRect.aHeight + deltaY < aWindow->aMaxDims.aHeight)
                                         {
                                             aRect.aY -= (deltaY);
                                             aRect.aHeight += (deltaY);
                                             p.y += static_cast<long>(deltaY);
                                         }
                                     }
                                     else
                                     {
                                         aRect.aHeight -= (aRect.aHeight - deltaY >= aWindow->aMinDims.aHeight) && (aRect.aHeight - deltaY < aWindow->aMaxDims.aHeight) ? static_cast<float>(deltaY) : 0;
                                     }                                   
                                 }
                                 // Resize left and right.
                                 else if (currentCursor == LoadCursor(NULL, IDC_SIZEWE))
                                 {
                                     if (aWindow->aWinMoveRes)
                                     {
                                         if (aRect.aWidth + deltaX >= aWindow->aMinDims.aWidth &&
                                             aRect.aWidth + deltaX < aWindow->aMaxDims.aWidth)
                                         {
                                             aRect.aX -= (deltaX);
                                             aRect.aWidth += (deltaX);
                                             p.x += static_cast<long>(deltaX);
                                         }
                                     }
                                     else
                                     {
                                         aRect.aWidth -= (aRect.aWidth - deltaX >= aWindow->aMinDims.aWidth) && (aRect.aWidth - deltaX < aWindow->aMaxDims.aWidth) ? static_cast<float>(deltaX) : 0 ;
                                     }
                                     
                                 }
                                 // Resize upper right and lower left corners.
                                 else if (currentCursor == LoadCursor(NULL, IDC_SIZENESW))
                                 {
                                     if (aWindow->aWinMoveRes)
                                     {
                                         aRect.aHeight -= (aRect.aHeight - deltaY >= aWindow->aMinDims.aHeight) && (aRect.aHeight - deltaY < aWindow->aMaxDims.aHeight) ? static_cast<float>(deltaY) : 0;
                                         if (aRect.aWidth + deltaX >= aWindow->aMinDims.aWidth &&
                                             aRect.aWidth + deltaX < aWindow->aMaxDims.aWidth)
                                         {
                                             aRect.aX -= (deltaX);
                                             aRect.aWidth += (deltaX);
                                             p.x += static_cast<long>(deltaX);
                                         }
                                     }
                                     else
                                     {
                                         aRect.aWidth -= (aRect.aWidth - deltaX >= aWindow->aMinDims.aWidth) && (aRect.aWidth - deltaX < aWindow->aMaxDims.aWidth) ? static_cast<float>(deltaX) : 0;
                                         if (aRect.aHeight + deltaY >= aWindow->aMinDims.aHeight &&
                                             aRect.aHeight + deltaY < aWindow->aMaxDims.aHeight)
                                         {
                                             aRect.aY -= (deltaY);
                                             aRect.aHeight += (deltaY);
                                             p.y += static_cast<long>(deltaY);
                                         }
                                     }
                                 }
                                 // Resize upper left and lower right corners.
                                 else if (currentCursor == LoadCursor(NULL, IDC_SIZENWSE))
                                 {
                                     if (aWindow->aWinMoveRes)
                                     {
                                         if (aRect.aWidth + deltaX >= aWindow->aMinDims.aWidth &&
                                             aRect.aWidth + deltaX < aWindow->aMaxDims.aWidth)
                                         {
                                             aRect.aX -= (deltaX);
                                             aRect.aWidth += (deltaX);
                                             p.x += static_cast<long>(deltaX);
                                         }
                                         if (aRect.aHeight + deltaY >= aWindow->aMinDims.aHeight &&
                                             aRect.aHeight + deltaY < aWindow->aMaxDims.aHeight)
                                         {
                                             aRect.aY -= (deltaY);
                                             aRect.aHeight += (deltaY);
                                             p.y += static_cast<long>(deltaY);
                                         }
                                     }
                                     else
                                     {
                                         aRect.aWidth -= (aRect.aWidth - deltaX >= aWindow->aMinDims.aWidth) && (aRect.aWidth - deltaX < aWindow->aMaxDims.aWidth) ? static_cast<float>(deltaX) : 0;
                                         aRect.aHeight -= (aRect.aHeight - deltaY >= aWindow->aMinDims.aHeight) && (aRect.aHeight - deltaY < aWindow->aMaxDims.aHeight) ? static_cast<float>(deltaY) : 0;
                                     }
                                     
                                 }
                                 // DEFER REGION //
                                 
                                 aWindow->Update();

                                 // DEFER REGION //
                                 
                                 aWindow->aLastDraggedPoint = p;                                                             
                             }

                             return S_OK;
        }
        case WM_LBUTTONUP:
        {
                             aWindow = reinterpret_cast<A2DMSWindow *>(static_cast<LONG_PTR>(GetWindowLongPtrW(xHwnd, GWLP_USERDATA)));
							 if (aWindow->aHResizeWnd != xHwnd) return 0;

                             ReleaseCapture();
                             aWindow->isDragged = false;
                             aWindow->isResizing = false;
                             return S_OK;
        }
        case WM_CLOSE:
        {
                         DestroyWindow(xHwnd);
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
LPCWSTR A2DMSWindow::GetClass()
{
    return L"A2DMSWindow";
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
LPCWSTR A2DMSWindow::ToString()
{
    return L"A2DMSWindow";
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
bool A2DMSWindow::operator==(A2DAbstract * xAbstract)
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
HRESULT A2DMSWindow::Initialize()
{
    HRESULT hr = S_OK;

    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR           gdiplusToken;

    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
    
    /*****************************************************/
    aRect.aHeight = 500;
    aRect.aWidth = 640;
    aName = L"TESTING";
    
    setLocationRelativeTo(NULL);
    setBorderColor(Color(202, 225, 255));
    setBorderWidth(10); //Force the border in DX window
    setBoxShadowColor(Color(0, 0, 0));
    setBackgroundColor(Color(0, 0, 0));
    setBoxShadowRadius(100);
    setMaximumSize(700, 500);
    
    /*****************************************************/

    hr = RegisterClass();

    if (FAILED(hr)) return hr;
    
    aParentHWnd = A2DMSWindow::CreateCompatibleWindow(true);

    if (!aParentHWnd) return E_FAIL;

    aHNWnd = A2DMSWindow::CreateCompatibleWindow(false);

    if (!aHNWnd) return E_FAIL;
    
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
void A2DMSWindow::Deinitialize()
{
    aParentHWnd = NULL;
    aHNWnd = NULL;
}
