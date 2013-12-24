
#include "../../../Include/Windows/A2DExtLibs.h"
#include "../../../Include/Windows/A2DWindow.h"

////////////////////////////////////////////////////////////////////////////////
// PLATFORM COMPATIBLE IMPLEMENTATION
////////////////////////////////////////////////////////////////////////////////

A2DWindow::A2DWindow(HINSTANCE xHInstance) : aHInstance(xHInstance){}

A2DWindow::~A2DWindow(){}

LRESULT CALLBACK A2DWindow::wndProc(HWND xHwnd, UINT xMessage, WPARAM xWParam, LPARAM xLParam)
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
            case WM_LBUTTONDOWN:
            {
                aWindow = reinterpret_cast<A2DWindow *>(static_cast<LONG_PTR>(GetWindowLongPtrW(xHwnd, GWLP_USERDATA)));
                return aWindow->updateOnMouseDown(xHwnd);      
            }
            case WM_MOUSEMOVE:
            {
                aWindow = reinterpret_cast<A2DWindow *>(static_cast<LONG_PTR>(GetWindowLongPtrW(xHwnd, GWLP_USERDATA)));
                return aWindow->updateOnMouseMove(xHwnd);     
            }
            case WM_LBUTTONUP:
            {
                aWindow = reinterpret_cast<A2DWindow *>(static_cast<LONG_PTR>(GetWindowLongPtrW(xHwnd, GWLP_USERDATA)));
                return aWindow->updateOnMouseUp(xHwnd);
            }
            case WM_CLOSE:
            {
                DestroyWindow(xHwnd);
                return S_OK;
            }
            default: return DefWindowProc(xHwnd, xMessage, xWParam, xLParam);
        }
 
    }
}

void A2DWindow::setMinimumSize(float xWidth, float xHeight)
{
    aMinDims.aWidth = max(aOptShadowRadius * A2D_WINDOW_BOX_SHADOW_SAFETY_RATIO, xWidth);
    aMinDims.aHeight = max(aOptShadowRadius * A2D_WINDOW_BOX_SHADOW_SAFETY_RATIO, xHeight);

    aMinDims.aWidth = max(aMinDims.aWidth, (aOptBorderWidth * 2) + 1);
    aMinDims.aHeight = max(aMinDims.aHeight, (aOptBorderWidth * 2) + 1);
}

void A2DWindow::setMaximumSize(float xWidth, float xHeight)
{
    aMaxDims.aWidth = max(aOptShadowRadius * A2D_WINDOW_BOX_SHADOW_SAFETY_RATIO, xWidth);
    aMaxDims.aHeight = max(aOptShadowRadius * A2D_WINDOW_BOX_SHADOW_SAFETY_RATIO, xHeight);
}

void A2DWindow::runMessageLoop()
{
    MSG msg;

    while (aVisible)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

		A2DAbstractWindow::renderGX();
    }
}

HWND A2DWindow::createCompatibleWindow(bool isParent)
{
    HRESULT         hr = S_OK;
    HWND            hWnd, hwndParent;
    int             left, top, width, height;
    DWORD           lStyle, lExStyle;
    LPCWSTR         className, titleName;
    
    left = static_cast<int>(isParent ? aRect.aX - aOptShadowRadius : aRect.aX + aOptBorderWidth);
    top = static_cast<int>(isParent ? aRect.aY - aOptShadowRadius : aRect.aY + aOptBorderWidth);
    width = static_cast<int>(isParent ? aRect.aWidth + aOptShadowRadius * 2 : aRect.aWidth - aOptBorderWidth * 2);
    height = static_cast<int>(isParent ? aRect.aHeight + aOptShadowRadius * 2 : aRect.aHeight - aOptBorderWidth * 2);
    lStyle = static_cast<int>(isParent ? WS_POPUP | WS_OVERLAPPED : WS_POPUP);
    lExStyle = static_cast<int>(isParent ? WS_EX_LAYERED | WS_EX_APPWINDOW : 0);
    hwndParent = isParent ? HWND_DESKTOP : aParentHWnd;
    className =  aName;
    titleName =  aName;

    hWnd = CreateWindowEx(lExStyle, className, titleName, lStyle, left, top, width, height, hwndParent, NULL, aHInstance, this);
    
    aStyle = WS_EX_APPWINDOW;
    
    if (aChildHWnd && aParentHWnd)
    {
        // Force the child on top of parent!
        SetWindowPos(aChildHWnd, aParentHWnd, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
    }

    return hWnd;
}

HRESULT A2DWindow::updateOnMouseDown(HWND xHwnd)
{
    if (aHResizeWnd != xHwnd) return 0;

    SetCapture(xHwnd);
    isDragged = true;

    RECT rect;
    GetWindowRect(xHwnd, &rect);

    long padding = static_cast<long>(aPadding);
    bool isParent = aParentHWnd == xHwnd;

    rect.bottom -= (isParent ? padding : 0);
    rect.right -= (isParent ? padding : 0);
    rect.left += (isParent ? padding : 0);
    rect.top += (isParent ? padding : 0);

    POINT p;
    GetCursorPos(&p);

    int x = p.x;
    int y = p.y;

    if ((x >= rect.left && x < rect.left + A2D_WINDOW_RESIZE_EDGE_DISTANCE ||
        x < rect.right && x >= rect.right - A2D_WINDOW_RESIZE_EDGE_DISTANCE ||
        y < rect.bottom && y >= rect.bottom - A2D_WINDOW_RESIZE_EDGE_DISTANCE ||
        y >= rect.top && y < rect.top + A2D_WINDOW_RESIZE_EDGE_DISTANCE) &&
        !isResizing)
    {
        isResizing = true;
    }

    SetCursor(aCurrentCursor);

    return S_OK;
}

HRESULT A2DWindow::updateOnMouseMove(HWND xHwnd)
{
    if (aHResizeWnd != xHwnd)
    {
        return 0;
    }

    RECT rect;
    GetWindowRect(xHwnd, &rect);

    long padding = static_cast<long>(aPadding);
    bool isParent = aParentHWnd == xHwnd;

    rect.bottom -= (isParent ? padding : 0);
    rect.right -= (isParent ? padding : 0);
    rect.left += (isParent ? padding : 0);
    rect.top += (isParent ? padding : 0);

    POINT p;
    GetCursorPos(&p);

    int x = p.x;
    int y = p.y;

    if (!isResizing)
    {
        //bottom left corner
        if (x >= rect.left && x < rect.left + A2D_WINDOW_RESIZE_EDGE_DISTANCE &&
            y < rect.bottom && y >= rect.bottom - A2D_WINDOW_RESIZE_EDGE_DISTANCE)
        {
            aCurrentCursor = LoadCursor(NULL, IDC_SIZENESW);
            aWinMoveRes = true;
        }
        //bottom right corner
        else if (x < rect.right && x >= rect.right - A2D_WINDOW_RESIZE_EDGE_DISTANCE &&
            y < rect.bottom && y >= rect.bottom - A2D_WINDOW_RESIZE_EDGE_DISTANCE)
        {
            aCurrentCursor = LoadCursor(NULL, IDC_SIZENWSE);
            aWinMoveRes = false;
        }
        //top left corner
        else if (x >= rect.left && x < rect.left + A2D_WINDOW_RESIZE_EDGE_DISTANCE &&
            y >= rect.top && y < rect.top + A2D_WINDOW_RESIZE_EDGE_DISTANCE)
        {
            aCurrentCursor = LoadCursor(NULL, IDC_SIZENWSE);
            aWinMoveRes = true;
        }
        //top right corner
        else if (x < rect.right && x >= rect.right - A2D_WINDOW_RESIZE_EDGE_DISTANCE &&
            y >= rect.top && y < rect.top + A2D_WINDOW_RESIZE_EDGE_DISTANCE)
        {
            aCurrentCursor = LoadCursor(NULL, IDC_SIZENESW);
            aWinMoveRes = false;
        }
        //left border
        else if (x >= rect.left && x < rect.left + A2D_WINDOW_RESIZE_EDGE_DISTANCE)
        {
            aCurrentCursor = LoadCursor(NULL, IDC_SIZEWE);
            aWinMoveRes = true;
        }
        //right border
        else if (x < rect.right && x >= rect.right - A2D_WINDOW_RESIZE_EDGE_DISTANCE)
        {
            aCurrentCursor = LoadCursor(NULL, IDC_SIZEWE);
            aWinMoveRes = false;
        }
        //bottom border
        else if (y < rect.bottom && y >= rect.bottom - A2D_WINDOW_RESIZE_EDGE_DISTANCE)
        {
            aCurrentCursor = LoadCursor(NULL, IDC_SIZENS);
            aWinMoveRes = false;
        }
        //top border
        else if (y >= rect.top && y < rect.top + A2D_WINDOW_RESIZE_EDGE_DISTANCE)
        {
            aCurrentCursor = LoadCursor(NULL, IDC_SIZENS);
            aWinMoveRes = true;
        }
        //default
        else
        {
            aCurrentCursor = LoadCursor(NULL, IDC_ARROW);
            aWinMoveRes = false;
        }

        SetCursor(aCurrentCursor);
    }

    if (!isDragged)
    {
        GetCursorPos(&aLastDraggedPoint);
        ScreenToClient(xHwnd, &aLastDraggedPoint);
    }

    if (isDragged && isResizing)
    {
        POINT p;
        GetCursorPos(&p);
        ScreenToClient(xHwnd, &p);

        float deltaY = static_cast<float>(aLastDraggedPoint.y - p.y);
        float deltaX = static_cast<float>(aLastDraggedPoint.x - p.x);

        HCURSOR currentCursor = GetCursor();

        // Process resizing.

        // Resize up and down.
        if (currentCursor == LoadCursor(NULL, IDC_SIZENS))
        {
            if (aWinMoveRes)
            {
                if (aRect.aHeight + deltaY >= aMinDims.aHeight &&
                    aRect.aHeight + deltaY < aMaxDims.aHeight)
                {
                    aRect.aY -= (deltaY);
                    aRect.aHeight += (deltaY);
                    p.y += static_cast<long>(deltaY);
                }
            }
            else
            {
                aRect.aHeight -= (aRect.aHeight - deltaY >= aMinDims.aHeight) && (aRect.aHeight - deltaY < aMaxDims.aHeight) ? static_cast<float>(deltaY) : 0;
            }
        }
        // Resize left and right.
        else if (currentCursor == LoadCursor(NULL, IDC_SIZEWE))
        {
            if (aWinMoveRes)
            {
                if (aRect.aWidth + deltaX >= aMinDims.aWidth &&
                    aRect.aWidth + deltaX < aMaxDims.aWidth)
                {
                    aRect.aX -= (deltaX);
                    aRect.aWidth += (deltaX);
                    p.x += static_cast<long>(deltaX);
                }
            }
            else
            {
                aRect.aWidth -= (aRect.aWidth - deltaX >= aMinDims.aWidth) && (aRect.aWidth - deltaX < aMaxDims.aWidth) ? static_cast<float>(deltaX) : 0;
            }

        }
        // Resize upper right and lower left corners.
        else if (currentCursor == LoadCursor(NULL, IDC_SIZENESW))
        {
            if (aWinMoveRes)
            {
                aRect.aHeight -= (aRect.aHeight - deltaY >= aMinDims.aHeight) && (aRect.aHeight - deltaY < aMaxDims.aHeight) ? static_cast<float>(deltaY) : 0;
                if (aRect.aWidth + deltaX >= aMinDims.aWidth &&
                    aRect.aWidth + deltaX < aMaxDims.aWidth)
                {
                    aRect.aX -= (deltaX);
                    aRect.aWidth += (deltaX);
                    p.x += static_cast<long>(deltaX);
                }
            }
            else
            {
                aRect.aWidth -= (aRect.aWidth - deltaX >= aMinDims.aWidth) && (aRect.aWidth - deltaX < aMaxDims.aWidth) ? static_cast<float>(deltaX) : 0;
                if (aRect.aHeight + deltaY >= aMinDims.aHeight &&
                    aRect.aHeight + deltaY < aMaxDims.aHeight)
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
            if (aWinMoveRes)
            {
                if (aRect.aWidth + deltaX >= aMinDims.aWidth &&
                    aRect.aWidth + deltaX < aMaxDims.aWidth)
                {
                    aRect.aX -= (deltaX);
                    aRect.aWidth += (deltaX);
                    p.x += static_cast<long>(deltaX);
                }
                if (aRect.aHeight + deltaY >= aMinDims.aHeight &&
                    aRect.aHeight + deltaY < aMaxDims.aHeight)
                {
                    aRect.aY -= (deltaY);
                    aRect.aHeight += (deltaY);
                    p.y += static_cast<long>(deltaY);
                }
            }
            else
            {
                aRect.aWidth -= (aRect.aWidth - deltaX >= aMinDims.aWidth) && (aRect.aWidth - deltaX < aMaxDims.aWidth) ? static_cast<float>(deltaX) : 0;
                aRect.aHeight -= (aRect.aHeight - deltaY >= aMinDims.aHeight) && (aRect.aHeight - deltaY < aMaxDims.aHeight) ? static_cast<float>(deltaY) : 0;
            }

        }
        // DEFER REGION //

        update();

        // DEFER REGION //

        aLastDraggedPoint = p;
    }
    return S_OK;
}

HRESULT A2DWindow::updateOnMouseUp(HWND xHwnd)
{
    if (aHResizeWnd != xHwnd) return 0;

    ReleaseCapture();
    isDragged = false;
    isResizing = false;
    return S_OK;
}

HRESULT A2DWindow::registerClass()
{
    WNDCLASSEX wcex = { sizeof(WNDCLASSEX) };
    wcex.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wcex.lpfnWndProc = A2DWindow::wndProc;
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

void A2DWindow::updateAndCacheBackground()
{
    destroyBackgroundResources();
    createBackgroundResources();
    
    HBRUSH brush = CreateSolidBrush(RGB(aOptBackgroundColor.GetRed(), aOptBackgroundColor.GetGreen(), aOptBackgroundColor.GetBlue()));
    SetClassLongPtr(aParentHWnd, GCLP_HBRBACKGROUND, (LONG)brush);

    CloseHandle(brush);
}

void A2DWindow::updateAndCacheShadow()
{
    destroyShadowResources();
    createShadowResources();
}

void A2DWindow::destroyShadowResources()
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

void A2DWindow::spliceToNinePatch(Image * src, Image * dest, float srcX, float srcY, float srcWidth, float srcHeight)
{
    Graphics graphics(dest);

    graphics.DrawImage(src, FLOAT_ZERO, FLOAT_ZERO, srcX, srcY, srcWidth, srcHeight, UnitPixel);
    graphics.DrawImage(src, FLOAT_ZERO, FLOAT_ZERO, srcX, srcY, srcWidth, srcHeight, UnitPixel); // Render twice to increase opacity
    graphics.DrawImage(src, FLOAT_ZERO, FLOAT_ZERO, srcX, srcY, srcWidth, srcHeight, UnitPixel); // Render twice to increase opacity
}

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
    
    delete rotatedData;
    delete blurredData;

    delete blurred;
    delete kernel;

    return rotated;
}

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

HRESULT A2DWindow::createShadowResources()
{
    HRESULT hr = S_OK;

    Bitmap * solid, *blurred;
    Graphics * graphics;
    SolidBrush blackBrush(aOptShadowColor);

    float radius = aOptShadowRadius;
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

    // update values
    aPadding = radius;
    aShadowPadding = radiusSafety;

    delete graphics;
    delete blurred;
    delete solid;

    return hr;
}

HRESULT A2DWindow::createBackgroundResources()
{
    HRESULT hr = S_OK;

    aBackground = new Bitmap(1, 1);

    Graphics  graphics(aBackground);
    SolidBrush blackBrush(aOptBackgroundColor);

    graphics.FillRectangle(&blackBrush, 0, 0, 1, 1);

    aBackgroundBrush = new TextureBrush(aBackground);

    return hr;
}

void A2DWindow::destroyBackgroundResources()
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

HRESULT A2DWindow::createResources()
{
    HRESULT hr = S_OK; 

    // Create resize window pointer.
    aHResizeWnd = aOptBorderWidth < A2D_WINDOW_RESIZE_DEFAULT_DISTANCE ? aChildHWnd : aParentHWnd;

    hr = createBackgroundResources();
    if (FAILED(hr)) return hr;

    hr = createShadowResources();

    return hr;
}

void A2DWindow::destroyResources()
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

    destroyShadowResources();
    destroyBackgroundResources();
}

void A2DWindow::renderComponentBorder()
{
    if (aOptBorderWidth > 0)
    {
        Pen borderPen(aOptBorderColor, aOptBorderWidth);
    
        aGraphics->DrawRectangle(&borderPen, aPadding + aOptBorderWidth / 2, aPadding + aOptBorderWidth / 2, aRealWidth + aOptBorderWidth, aRealHeight + aOptBorderWidth);
    
        DeleteObject(&borderPen);
    }
}

void A2DWindow::renderComponent()
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

////////////////////////////////////////////////////////////////////////////////
// A2DABSTRACTWINDOW
////////////////////////////////////////////////////////////////////////////////

void A2DWindow::setMinimumSize(A2DDims * xSize)
{
    setMinimumSize(xSize->aWidth, xSize->aHeight);
}

void A2DWindow::setMaximumSize(A2DDims * xSize)
{
    setMaximumSize(xSize->aWidth, xSize->aHeight);
}

void A2DWindow::setName(LPCWSTR xName)
{
	aName = xName;

    SetWindowText(aChildHWnd, aName);
    SetWindowText(aParentHWnd, aName);
}

void A2DWindow::setUndecorated(bool xUndecorated)
{
    // we cannot just use WS_POPUP style
    // WS_THICKFRAME: without this the window cannot be resized and so aero snap, de-maximizing and minimizing won't work
    // WS_SYSMENU: enables the context menu with the move, close, maximize, minize... commands (shift + right-click on the task bar item)
    // HOWEVER, this also enables the menu with the maximize buttons in the title bar, which will exist inside your client area and are clickable. 
    // WS_CAPTION: enables aero minimize animation/transition
    // WS_MAXIMIZEBOX, WS_MINIMIZEBOX: enable minimize/maximize

	aUndecorated = xUndecorated;

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

void A2DWindow::setDefaultCloseOperation(int xDefaultCloseOperation)
{
	aDefaultCloseOperation = xDefaultCloseOperation;
}

void A2DWindow::setLocationRelativeTo(A2DAbstractWindow * xRelativeWindow)
{
    aRelativeWindow = xRelativeWindow;

    if (aRelativeWindow == NULL)
    {
        aRect.aX = (GetSystemMetrics(SM_CXSCREEN) - aRect.aWidth) / 2;
        aRect.aY = (GetSystemMetrics(SM_CYSCREEN) - aRect.aHeight) / 2;
    }
}

void A2DWindow::setVisible(bool xVisible)
{
    aVisible = xVisible;

    if (aVisible)
    {
        ShowWindow(aChildHWnd, SW_SHOWNORMAL);
        ShowWindow(aParentHWnd, SW_SHOWNORMAL);
		
		A2DAbstractWindow::createGXResources();

        runMessageLoop();
    }
    else
    {
        ShowWindow(aChildHWnd, SW_HIDE);
        ShowWindow(aParentHWnd, SW_HIDE);
    }
}

void A2DWindow::setBorderWidth(float xBorderWidth)
{
    aOptBorderWidth = xBorderWidth;
}

void A2DWindow::setBorderColor(Color xBorderColor)
{
	aOptBorderColor = xBorderColor;
}

void A2DWindow::setShadowed(bool xShadowed)
{
    aShadowed = xShadowed;
}

void A2DWindow::setShadowRadius(float xShadowRadius)
{
    aOptShadowRadius = xShadowRadius;
}

void A2DWindow::setShadowColor(Color xShadowColor)
{
    aOptShadowColor = xShadowColor;
}

void A2DWindow::setBackgroundColor(Color xBackgroundColor)
{
	aOptBackgroundColor = xBackgroundColor;
}

void* A2DWindow::getPlatformCompatibleWindowHandle()
{
	return static_cast<void*>(&aChildHWnd);
}       

void A2DWindow::render()
{
     HDC hdc, memDC;
    //A2DWindow::update();
    // Cache variables to ensure that these variables
    // won't be changed in the middle of update() via concurrent
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

    renderComponent();
    renderComponentBorder();

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

    if (hdwp) hdwp = DeferWindowPos(hdwp, aChildHWnd, aParentHWnd, aRealX, aRealY, aRealWidth, aRealHeight, SWP_NOZORDER | SWP_NOACTIVATE);

    EndDeferWindowPos(hdwp);

    /***********************************************/

    aGraphics->ReleaseHDC(memDC);
    delete aGraphics;
    aGraphics = 0;

    DeleteObject(memBitmap);
    DeleteObject(hdc);
    DeleteObject(memDC);
}       

////////////////////////////////////////////////////////////////////////////////
// A2DABSTRACT
////////////////////////////////////////////////////////////////////////////////

HRESULT A2DWindow::Initialize()
{
    HRESULT hr = S_OK;

    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR           gdiplusToken;

    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
    
    /*****************************************************/
    aRect.aHeight = 600;
    aRect.aWidth = 800;
    aName = L"TESTING";
    
    setLocationRelativeTo(NULL);
    setBorderColor(Color(202, 225, 255));
    setBorderWidth(10); //Force the border in DX window
    setShadowColor(Color(0, 0, 0));
    setBackgroundColor(Color(0, 0, 0));
    setShadowRadius(100);
    setMinimumSize(75, 75);
    setMaximumSize(1000, 1000);
    
    /*****************************************************/

    hr = registerClass();

    if (FAILED(hr)) return hr;
    
    aParentHWnd = createCompatibleWindow(true);

    if (!aParentHWnd) return E_FAIL;

    aChildHWnd = createCompatibleWindow(false);

    if (!aChildHWnd) return E_FAIL;
    
    hr = createResources();

    if (FAILED(hr)) return hr;

    update();
    
    return hr;
}

void A2DWindow::Deinitialize()
{
    destroyResources();

    aParentHWnd = NULL;
    aChildHWnd = NULL;
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