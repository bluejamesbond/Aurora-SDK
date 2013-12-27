
#include "../../../Include/Windows/A2DExtLibs.h"
#include "../../../Include/Windows/A2DWindow.h"
#include "../../../Include/Windows/A2DFrame.h"

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

HWND A2DWindow::createCompatibleWindow(bool isParent)
{
	HRESULT         hr = S_OK;
	HWND            hWnd, hwndParent;
	int             left, top, width, height;
	DWORD           lStyle, lExStyle;
	LPCWSTR titleName;

	left = static_cast<int>(isParent ? aRect.aX - aOptShadowRadius : aRect.aX + aOptBorderWidth);
	top = static_cast<int>(isParent ? aRect.aY - aOptShadowRadius : aRect.aY + aOptBorderWidth);
	width = static_cast<int>(isParent ? aRect.aWidth + aOptShadowRadius * 2 : aRect.aWidth - aOptBorderWidth * 2);
	height = static_cast<int>(isParent ? aRect.aHeight + aOptShadowRadius * 2 : aRect.aHeight - aOptBorderWidth * 2);
	lStyle = static_cast<int>(isParent ? WS_POPUP | WS_OVERLAPPED : WS_POPUP);
	lExStyle = static_cast<int>(isParent ? WS_EX_LAYERED | WS_EX_APPWINDOW : 0);
	hwndParent = isParent ? HWND_DESKTOP : aParentHWnd;
	titleName = aName;

	hWnd = CreateWindowEx(lExStyle, aClassName->c_str(), titleName, lStyle, left, top, width, height, hwndParent, NULL, aHInstance, this);

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
	if (aHResizeWnd != xHwnd)
	{
		return 0;
	}

	SetCapture(xHwnd);

	bool isParent = aParentHWnd == xHwnd;
	float left, right, bottom, top;
	int x, y;
	POINT p;

	GetCursorPos(&p);

	x = p.x;
	y = p.y;

	isDragged = true;

	left = (isParent ? aRelativeX + aPadding : aRealX);
	top = (isParent ? aRelativeY + aPadding : aRealY);
	bottom = top + aRect.aHeight;
	right = left + aRect.aWidth;

	if ((x >= left && x < left + A2D_WINDOW_RESIZE_EDGE_DISTANCE ||
		x < right && x >= right - A2D_WINDOW_RESIZE_EDGE_DISTANCE ||
		y < bottom && y >= bottom - A2D_WINDOW_RESIZE_EDGE_DISTANCE ||
		y >= top && y < top + A2D_WINDOW_RESIZE_EDGE_DISTANCE) &&
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

	bool isParent = aParentHWnd == xHwnd;
	float left, right, bottom, top;
	int x, y;
	POINT p;
	A2DRect& rect = aRect;

	GetCursorPos(&p);

	x = p.x;
	y = p.y;

	left = (isParent ? aRelativeX + aPadding : aRealX);
	top = (isParent ? aRelativeY + aPadding : aRealY);
	bottom = top + aRect.aHeight;
	right = left + aRect.aWidth;

	if (!isResizing)
	{
		//bottom left corner
		if (x >= left && x < left + A2D_WINDOW_RESIZE_EDGE_DISTANCE &&
			y < bottom && y >= bottom - A2D_WINDOW_RESIZE_EDGE_DISTANCE)
		{
			aCurrentCursor = LoadCursor(NULL, IDC_SIZENESW);
			aWinMoveRes = true;
		}
		//bottom right corner
		else if (x < right && x >= right - A2D_WINDOW_RESIZE_EDGE_DISTANCE &&
			y < bottom && y >= bottom - A2D_WINDOW_RESIZE_EDGE_DISTANCE)
		{
			aCurrentCursor = LoadCursor(NULL, IDC_SIZENWSE);
			aWinMoveRes = false;
		}
		//top left corner
		else if (x >= left && x < left + A2D_WINDOW_RESIZE_EDGE_DISTANCE &&
			y >= top && y < top + A2D_WINDOW_RESIZE_EDGE_DISTANCE)
		{
			aCurrentCursor = LoadCursor(NULL, IDC_SIZENWSE);
			aWinMoveRes = true;
		}
		//top right corner
		else if (x < right && x >= right - A2D_WINDOW_RESIZE_EDGE_DISTANCE &&
			y >= top && y < top + A2D_WINDOW_RESIZE_EDGE_DISTANCE)
		{
			aCurrentCursor = LoadCursor(NULL, IDC_SIZENESW);
			aWinMoveRes = false;
		}
		//left border
		else if (x >= left && x < left + A2D_WINDOW_RESIZE_EDGE_DISTANCE)
		{
			aCurrentCursor = LoadCursor(NULL, IDC_SIZEWE);
			aWinMoveRes = true;
		}
		//right border
		else if (x < right && x >= right - A2D_WINDOW_RESIZE_EDGE_DISTANCE)
		{
			aCurrentCursor = LoadCursor(NULL, IDC_SIZEWE);
			aWinMoveRes = false;
		}
		//bottom border
		else if (y < bottom && y >= bottom - A2D_WINDOW_RESIZE_EDGE_DISTANCE)
		{
			aCurrentCursor = LoadCursor(NULL, IDC_SIZENS);
			aWinMoveRes = false;
		}
		//top border
		else if (y >= top && y < top + A2D_WINDOW_RESIZE_EDGE_DISTANCE)
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
		float deltaY, deltaX;
		HCURSOR currentCursor;

		GetCursorPos(&p);
		ScreenToClient(xHwnd, &p);

		deltaY = static_cast<float>(aLastDraggedPoint.y - p.y);
		deltaX = static_cast<float>(aLastDraggedPoint.x - p.x);
		currentCursor = GetCursor();

		// Process resizing.

		// Resize up and down.
		if (currentCursor == LoadCursor(NULL, IDC_SIZENS))
		{
			if (aWinMoveRes)
			{
				if (rect.aHeight + deltaY >= aMinDims.aHeight &&
					rect.aHeight + deltaY < aMaxDims.aHeight)
				{
					rect.aY -= (deltaY);
					rect.aHeight += (deltaY);
					p.y += static_cast<long>(deltaY);
				}
			}
			else
			{
				rect.aHeight -= (rect.aHeight - deltaY >= aMinDims.aHeight) && (rect.aHeight - deltaY < aMaxDims.aHeight) ? static_cast<float>(deltaY) : 0;
			}
		}
		// Resize left and right.
		else if (currentCursor == LoadCursor(NULL, IDC_SIZEWE))
		{
			if (aWinMoveRes)
			{
				if (rect.aWidth + deltaX >= aMinDims.aWidth &&
					rect.aWidth + deltaX < aMaxDims.aWidth)
				{
					rect.aX -= (deltaX);
					rect.aWidth += (deltaX);
					p.x += static_cast<long>(deltaX);
				}
			}
			else
			{
				rect.aWidth -= (rect.aWidth - deltaX >= aMinDims.aWidth) && (rect.aWidth - deltaX < aMaxDims.aWidth) ? static_cast<float>(deltaX) : 0;
			}

		}
		// Resize upper right and lower left corners.
		else if (currentCursor == LoadCursor(NULL, IDC_SIZENESW))
		{
			if (aWinMoveRes)
			{
				rect.aHeight -= (rect.aHeight - deltaY >= aMinDims.aHeight) && (rect.aHeight - deltaY < aMaxDims.aHeight) ? static_cast<float>(deltaY) : 0;
				if (rect.aWidth + deltaX >= aMinDims.aWidth &&
					rect.aWidth + deltaX < aMaxDims.aWidth)
				{
					rect.aX -= (deltaX);
					rect.aWidth += (deltaX);
					p.x += static_cast<long>(deltaX);
				}
			}
			else
			{
				rect.aWidth -= (rect.aWidth - deltaX >= aMinDims.aWidth) && (rect.aWidth - deltaX < aMaxDims.aWidth) ? static_cast<float>(deltaX) : 0;
				if (rect.aHeight + deltaY >= aMinDims.aHeight &&
					rect.aHeight + deltaY < aMaxDims.aHeight)
				{
					rect.aY -= (deltaY);
					rect.aHeight += (deltaY);
					p.y += static_cast<long>(deltaY);
				}
			}
		}
		// Resize upper left and lower right corners.
		else if (currentCursor == LoadCursor(NULL, IDC_SIZENWSE))
		{
			if (aWinMoveRes)
			{
				if (rect.aWidth + deltaX >= aMinDims.aWidth &&
					rect.aWidth + deltaX < aMaxDims.aWidth)
				{
					rect.aX -= (deltaX);
					rect.aWidth += (deltaX);
					p.x += static_cast<long>(deltaX);
				}
				if (rect.aHeight + deltaY >= aMinDims.aHeight &&
					rect.aHeight + deltaY < aMaxDims.aHeight)
				{
					rect.aY -= (deltaY);
					rect.aHeight += (deltaY);
					p.y += static_cast<long>(deltaY);
				}
			}
			else
			{
				rect.aWidth -= (rect.aWidth - deltaX >= aMinDims.aWidth) && (rect.aWidth - deltaX < aMaxDims.aWidth) ? static_cast<float>(deltaX) : 0;
				rect.aHeight -= (rect.aHeight - deltaY >= aMinDims.aHeight) && (rect.aHeight - deltaY < aMaxDims.aHeight) ? static_cast<float>(deltaY) : 0;
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
	if (aHResizeWnd != xHwnd)
	{
		return 0;
	}

	ReleaseCapture();
	isDragged = false;
	isResizing = false;

	return S_OK;
}

int A2DWindow::aClassInstances = 0;

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
	wcex.hbrBackground = CreateSolidBrush(RGB(aOptBackgroundColor.aRed, aOptBackgroundColor.aGreen, aOptBackgroundColor.aBlue));;
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = aClassName->c_str();
	wcex.hIconSm = LoadIcon(aHInstance, IDI_APPLICATION);

	return RegisterClassEx(&wcex);
}

void A2DWindow::updateBackgroundCache()
{
	destroyBackgroundResources();
	createBackgroundResources();

	HBRUSH brush = CreateSolidBrush(RGB(aOptBackgroundColor.aRed, aOptBackgroundColor.aGreen, aOptBackgroundColor.aBlue));
	SetClassLongPtr(aParentHWnd, GCLP_HBRBACKGROUND, (LONG)brush);
}

void A2DWindow::updateShadowCache()
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

	graphics.DrawImage(src, FLT_ZERO, FLT_ZERO, srcX, srcY, srcWidth, srcHeight, UnitPixel);
	graphics.DrawImage(src, FLT_ZERO, FLT_ZERO, srcX, srcY, srcWidth, srcHeight, UnitPixel); // Render twice to increase opacity
	graphics.DrawImage(src, FLT_ZERO, FLT_ZERO, srcX, srcY, srcWidth, srcHeight, UnitPixel); // Render twice to increase opacity
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
	float sigmaRoot = (float)sqrt(twoSigmaSquare * M_PI);
	float total = 0.0f;

	for (int i = -xRadius; i <= xRadius; i++)
	{
		float distance = (float)(i * i);
		int index = i + xRadius;
		data[index] = (float)exp(-distance / twoSigmaSquare) / sigmaRoot;
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

	blurred = new Bitmap(src->GetWidth(), src->GetHeight());
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
	SolidBrush blackBrush(*aShadowColor);

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

	spliceToNinePatch(blurred, aTopLeftShadow, FLT_ZERO, FLT_ZERO, radiusSafety, radiusSafety);
	spliceToNinePatch(blurred, aBottomLeftShadow, FLT_ZERO, relativeDim - radiusSafety, radiusSafety, radiusSafety);
	spliceToNinePatch(blurred, aBottomRightShadow, relativeDim - radiusSafety, relativeDim - radiusSafety, radiusSafety, radiusSafety);
	spliceToNinePatch(blurred, aTopRightShadow, relativeDim - radiusSafety, FLT_ZERO, radiusSafety, radiusSafety);

	spliceToNinePatch(blurred, aTopShadow, radiusSafety, FLT_ZERO, FLT_ONE, radius);
	spliceToNinePatch(blurred, aLeftShadow, FLT_ZERO, radiusSafety, radius, FLT_ONE);
	spliceToNinePatch(blurred, aRightShadow, relativeDim - radius, radiusSafety, radius, FLT_ONE);
	spliceToNinePatch(blurred, aBottomShadow, radiusSafety, relativeDim - radius, FLT_ONE, radius);

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
	SolidBrush blackBrush(*aBackgroundColor);

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

	hr = createColorResources();
	if (FAILED(hr)) return hr;

	hr = createBackgroundResources();
	if (FAILED(hr)) return hr;

	hr = createShadowResources();

	return hr;
}

void A2DWindow::destroyResources()
{
	destroyShadowResources();
	destroyBackgroundResources();
	destroyColorResources();
}

void A2DWindow::renderComponentBorder()
{
	if (aOptBorderWidth > 0)
	{
		Pen borderPen(*aBorderColor, aOptBorderWidth);

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

	aTopShadowBrush->TranslateTransform(aShadowPadding, FLT_ZERO);
	aGraphics->FillRectangle(aTopShadowBrush, aShadowPadding, FLT_ZERO, aRelativeWidth - aShadowPadding * 2, aPadding);

	aLeftShadowBrush->TranslateTransform(FLT_ZERO, aShadowPadding);
	aGraphics->FillRectangle(aLeftShadowBrush, FLT_ZERO, aShadowPadding, aPadding, aRelativeHeight - aShadowPadding * 2);

	aRightShadowBrush->TranslateTransform(aRelativeWidth - aPadding, aShadowPadding);
	aGraphics->FillRectangle(aRightShadowBrush, aRelativeWidth - aPadding, aShadowPadding, aPadding, aRelativeHeight - aShadowPadding * 2);

	aBottomShadowBrush->TranslateTransform(aShadowPadding, aRelativeHeight - aPadding);
	aGraphics->FillRectangle(aBottomShadowBrush, aShadowPadding, aRelativeHeight - aPadding, aRelativeWidth - aShadowPadding * 2, aPadding);

	aGraphics->DrawImage(aTopLeftShadow, FLT_ZERO, FLT_ZERO, aShadowPadding, aShadowPadding);
	aGraphics->DrawImage(aBottomLeftShadow, FLT_ZERO, aRelativeHeight - aShadowPadding, aShadowPadding, aShadowPadding);
	aGraphics->DrawImage(aTopRightShadow, aRelativeWidth - aShadowPadding, FLT_ZERO, aShadowPadding, aShadowPadding);
	aGraphics->DrawImage(aBottomRightShadow, aRelativeWidth - aShadowPadding, aRelativeHeight - aShadowPadding, aShadowPadding, aShadowPadding);

	aGraphics->FillRectangle(aBackgroundBrush, aPadding, aPadding, aRealWidth + aOptBorderWidth, aRealHeight + aOptBorderWidth);
}

////////////////////////////////////////////////////////////////////////////////
// A2DABSTRACTWINDOW
////////////////////////////////////////////////////////////////////////////////

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
		update();

		ShowWindow(aChildHWnd, SW_SHOWNORMAL);
		ShowWindow(aParentHWnd, SW_SHOWNORMAL);

		if (aFrame)
		{
			if (!A2DEventQueue::isDispatchingThread(aFrame->id()))
			{
				aFrame->CreateResources();

				initPlatformCompatibleMessageLoop();
			}
		}
	}
	else
	{
		ShowWindow(aChildHWnd, SW_HIDE);
		ShowWindow(aParentHWnd, SW_HIDE);
	}
}

void A2DWindow::setMinimumSize(A2DDims * xSize)
{
	aMinDims.aWidth = xSize->aWidth;
	aMinDims.aHeight = xSize->aHeight;
}

void A2DWindow::setMaximumSize(A2DDims * xSize)
{
	aMaxDims.aWidth = xSize->aWidth;
	aMaxDims.aHeight = xSize->aHeight;
}

void A2DWindow::setSize(A2DDims * xSize)
{
	aRect.aWidth = xSize->aWidth;
	aRect.aHeight = xSize->aHeight;
}

void A2DWindow::setMinimumSize(float xWidth, float xHeight)
{
	aMinDims.aWidth = xWidth;
	aMinDims.aHeight = xHeight;
}

void A2DWindow::setMaximumSize(float xWidth, float xHeight)
{
	aMaxDims.aWidth = xWidth;
	aMaxDims.aHeight = xHeight;
}

void A2DWindow::setSize(float xWidth, float xHeight)
{
	aRect.aWidth = xWidth;
	aRect.aHeight = xHeight;
}

void A2DWindow::setBorderWidth(float xBorderWidth)
{
	aOptBorderWidth = xBorderWidth;
}

void A2DWindow::setShadowRadius(float xShadowRadius)
{
	aOptShadowRadius = xShadowRadius;
}

void A2DWindow::setShadow(A2DColor * xShadowColor, float xShadowRadius)
{
	aOptShadowColor = *xShadowColor;
	aOptShadowRadius = xShadowRadius;
}

void A2DWindow::setBorder(A2DColor * xBorderColor, float xBorderWidth)
{
	aOptBorderColor = *xBorderColor;
	aOptBorderWidth = xBorderWidth;
}

void A2DWindow::setBounds(A2DRect * xRect)
{
	aRect.aWidth = xRect->aWidth;
	aRect.aX = xRect->aX;
	aRect.aY = xRect->aY;
	aRect.aHeight = xRect->aHeight;
}

void A2DWindow::setBounds(float xLeft, float xTop, float xWidth, float xHeight)
{
	aRect.aWidth = xWidth;
	aRect.aX = xLeft;
	aRect.aY = xTop;
	aRect.aHeight = xHeight;
}

void A2DWindow::validate()
{
	// Minimum dimensions has to be greater than border and shadow safety region
	aMinDims.aWidth = max((aOptShadowRadius * A2D_WINDOW_BOX_SHADOW_SAFETY_RATIO) + ((aOptBorderWidth * 2) + 1), aMinDims.aWidth);
	aMinDims.aHeight = max((aOptShadowRadius * A2D_WINDOW_BOX_SHADOW_SAFETY_RATIO) + ((aOptBorderWidth * 2) + 1), aMinDims.aHeight);

	// Minimum dimensions has to be greater than or equal to minimum size
	aMaxDims.aWidth = max(aMinDims.aWidth, aMaxDims.aWidth);
	aMaxDims.aHeight = max(aMinDims.aHeight, aMaxDims.aHeight);

	// Constrain the rect to between min and max
	aRect.aWidth = min(max(aMinDims.aWidth, aRect.aWidth), aMaxDims.aWidth);
	aRect.aHeight = min(max(aMinDims.aHeight, aRect.aHeight), aMaxDims.aHeight);

	// Create resize window pointer.
	aHResizeWnd = aOptBorderWidth < A2D_WINDOW_RESIZE_DEFAULT_DISTANCE ? aChildHWnd : aParentHWnd;

	// Update caches
	updateColorCache();
	updateBackgroundCache();
	updateShadowCache();

	// Mark as validated
	validated();
}

HRESULT A2DWindow::createColorResources()
{
	aBackgroundColor = new Color(aOptBackgroundColor.aAlpha, aOptBackgroundColor.aRed, aOptBackgroundColor.aGreen, aOptBackgroundColor.aBlue);
	aShadowColor = new Color(aOptShadowColor.aAlpha, aOptShadowColor.aRed, aOptShadowColor.aGreen, aOptShadowColor.aBlue);
	aBorderColor = new Color(aOptBorderColor.aAlpha, aOptBorderColor.aRed, aOptBorderColor.aGreen, aOptBorderColor.aBlue);

	return S_OK;
}


void A2DWindow::destroyColorResources()
{
	if (aBackgroundColor)
	{
		delete aBackgroundColor;
		aBackgroundColor = 0;
	}

	if (aShadowColor)
	{
		delete aShadowColor;
		aShadowColor = 0;
	}

	if (aBorderColor)
	{
		delete aBorderColor;
		aBorderColor = 0;
	}
}

void A2DWindow::updateColorCache()
{
	destroyColorResources();
	createColorResources();
}

void A2DWindow::setBorderColor(A2DColor * xBorderColor)
{
	aOptBorderColor = *xBorderColor;
}

void A2DWindow::setShadowed(bool xShadowed)
{
	aShadowed = xShadowed;

	setShadowRadius(FLT_ZERO);
}

void A2DWindow::setShadowColor(A2DColor * xShadowColor)
{
	aOptShadowColor = *xShadowColor;
}

void A2DWindow::setBackgroundColor(A2DColor * xBackgroundColor)
{
	aOptBackgroundColor = *xBackgroundColor;
}

void* A2DWindow::getPlatformCompatibleWindowHandle()
{
	return static_cast<void*>(&aChildHWnd);
}

void A2DWindow::initPlatformCompatibleEventDispatcher(A2DAbstractEventQueue * xEventQueue, A2DAbstractFrame * xFrame)
{
	MSG msg;
	bool& resizing = isResizing;
	bool& visible = aVisible;

	int defaultAllotedAnimationFrames = 10;
	int currentAnimationFrame = 0;

	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (visible)
		{
			// Forced updating of rendering for now
			if (xEventQueue->dispatchNextEvent())
			{
				currentAnimationFrame = defaultAllotedAnimationFrames;
			}
			else if (currentAnimationFrame > 0)
			{
				currentAnimationFrame--;
				xFrame->Update();
			}
			else if (resizing)
			{
				xFrame->Update();
			}
		}
	}
}

void A2DWindow::initPlatformCompatibleMessageLoop()
{
	MSG msg;
	A2DAbstractFrame * frame = aFrame;

	while (isVisible())
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		frame->Update();
	}
}

void A2DWindow::render()
{
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

	if (hdwp) hdwp = DeferWindowPos(hdwp, aParentHWnd, NULL, static_cast<int>(aRelativeX), static_cast<int>(aRelativeY), static_cast<int>(aRelativeWidth), static_cast<int>(aRelativeHeight), SWP_NOZORDER | SWP_NOACTIVATE);

	/***********************************************/

	SIZE size = { static_cast<long>(aRelativeWidth), static_cast<long>(aRelativeHeight) };
	HDC hwndDC = GetDC(aParentHWnd);
	HDC memDC = CreateCompatibleDC(hwndDC);
	POINT ptDst = { static_cast<long>(aRelativeX), static_cast<long>(aRelativeY) };
	POINT ptSrc = { 0, 0 };

	HBITMAP memBitmap = CreateCompatibleBitmap(hwndDC, static_cast<int>(aRelativeWidth), static_cast<int>(aRelativeHeight));
	SelectObject(memDC, memBitmap);

	aGraphics = new Graphics(memDC);

	/***********************************************/

	renderComponent();
	renderComponentBorder();

	/***********************************************/
	
	BLENDFUNCTION blendFunction;
	blendFunction.AlphaFormat = AC_SRC_ALPHA;
	blendFunction.BlendFlags = 0;
	blendFunction.BlendOp = AC_SRC_OVER;
	blendFunction.SourceConstantAlpha = 255;

	UpdateLayeredWindow(aParentHWnd, hwndDC, &ptDst, &size, memDC, &ptSrc, 0, &blendFunction, ULW_ALPHA);

	/***********************************************/

	if (hdwp) hdwp = DeferWindowPos(hdwp, aChildHWnd, aParentHWnd, static_cast<int>(aRealX), static_cast<int>(aRealY), static_cast<int>(aRealWidth), static_cast<int>(aRealHeight), SWP_NOZORDER | SWP_NOACTIVATE);

	EndDeferWindowPos(hdwp);

	// SetWindowPos(aChildHWnd, aParentHWnd, static_cast<int>(aRealX), static_cast<int>(aRealY), static_cast<int>(aRealWidth), static_cast<int>(aRealHeight), SWP_NOZORDER | SWP_NOACTIVATE);

	/***********************************************/

	aGraphics->ReleaseHDC(memDC);
	delete aGraphics;
	aGraphics = 0;

	DeleteObject(memBitmap);
	ReleaseDC(NULL, memDC);
	ReleaseDC(aParentHWnd, hwndDC);
	DeleteDC(hwndDC);
	DeleteDC(memDC);
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

	// Change class name
	aClassInstances++;

	// Update class name
	std::ostringstream stream;
	stream << "A2DWindow - " << aClassInstances;
	std::string className(stream.str());
	aClassName = new std::wstring(className.begin(), className.end());

	// Super
	A2DAbstractWindow::Initialize();

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

	delete aClassName;
	aClassName = 0;
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