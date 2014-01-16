
#include "../../../Include/Windows/ExtLibs.h"
#include "../../../Include/Windows/Window.h"
#include "../../../Include/Windows/Frame.h"

using namespace A2D;

////////////////////////////////////////////////////////////////////////////////
// PLATFORM COMPATIBLE IMPLEMENTATION
////////////////////////////////////////////////////////////////////////////////

Window::Window(AbstractFrame * xFrame, HINSTANCE xHInstance) : AbstractWindow(xFrame), aHInstance(xHInstance){}

void Window::initPlatformCompatibleEventDispatcher(AbstractEventQueue * xEventQueue)
{
	MSG msg;
	bool& resizing = aIsResizing;
	bool& visible = aVisible;

	int defaultAllotedAnimationFrames = 10;
	int currentAnimationFrame = 0;
	int counter = 0;

	AbstractFrame& frame = *aFrame;
	AbstractEventQueue& eventQueue = *xEventQueue;

	while (true)
	{
		//if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		//{
		//	eventHandler(msg, aEventQueue);
		//}

		if (visible)
		{
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				eventHandler(msg, &eventQueue);
			}

			// Forced updating of rendering for now
			if (eventQueue.dispatchNextEvent())
			{
				currentAnimationFrame = defaultAllotedAnimationFrames;
			}
			else if (currentAnimationFrame > 0)
			{
				currentAnimationFrame--;
				frame.update();
			}
			else
			{
				frame.update();
			}
		}
	}

}

LRESULT Window::eventHandler(MSG xMsg, AbstractEventQueue * xEventQueue)
{
	if (xMsg.message == WM_CREATE)
	{
		return STATUS_OK;
	}
	else
	{
		HWND xHwnd = xMsg.hwnd;
		switch (xMsg.message)
		{
			POINT p;
		case WM_LBUTTONDOWN:

			SetForegroundWindow(xHwnd);

			// Firing window event. Opposite window isnt supported yet!!
			// WM_ACTIVATE doesnt work in eventHandler.
			if (aCurrentState != WindowEvent::WINDOW_ACTIVATED)
			{
				xEventQueue->processWindowEvent(aWindowActivated);
			}

			// Fire MouseEvent
			GetCursorPos(&p);
			ScreenToClient(aChildHWnd, &p);
			aMouseDown->setLocation(p);

			xEventQueue->processMouseEvent(aMouseDown);
			return updateOnMouseDown(xHwnd);

		case WM_MOUSEMOVE:

			//// Fire MouseEvent
			GetCursorPos(&p);
			ScreenToClient(aChildHWnd, &p);
			aMouseMove->setLocation(p);

			if (aIsDragged)
			{
				aMouseDragged->setLocation(p);
				xEventQueue->processMouseMotionEvent(aMouseDragged);
			}
			else
			{
				aMouseMove->setLocation(p);
				xEventQueue->processMouseMotionEvent(aMouseMove);
			}
			return updateOnMouseMove(xHwnd);

		case WM_LBUTTONUP:

			// Fire MouseEvent
			GetCursorPos(&p);
			ScreenToClient(aChildHWnd, &p);
			aMouseUp->setLocation(p);

			xEventQueue->processMouseEvent(aMouseUp);
			return updateOnMouseUp(xHwnd);

		case WM_CLOSE:

			// Fire WindowEvent
			xEventQueue->processWindowEvent(aWindowClosed);

			DestroyWindow(xHwnd);
			return STATUS_OK;

		case WM_SIZE:

			onSize(xHwnd);
			return STATUS_OK;

		case WM_ERASEBKGND:
			// OS must not erase background. DirectX and
			// OpenGL will automatically do its parent
			// (aChildHWnd) window.
			return STATUS_OK;

		default: return DefWindowProc(xHwnd, xMsg.message, xMsg.wParam, xMsg.lParam);
		}

	}
}

LRESULT CALLBACK Window::wndProc(HWND xHwnd, UINT xMessage, WPARAM xWParam, LPARAM xLParam)
{
	Window * aWindow;

	if (xMessage == WM_CREATE)
	{
		CREATESTRUCT *pCreate = reinterpret_cast<CREATESTRUCT*>(xLParam);
		aWindow = reinterpret_cast<Window*>(pCreate->lpCreateParams);
		SetWindowLongPtr(xHwnd, GWLP_USERDATA, (LONG_PTR)aWindow);
		return STATUS_OK;
	}
	else
	{
		switch (xMessage)
		{

		case WM_ACTIVATE:

			aWindow = reinterpret_cast<Window *>(static_cast<LONG_PTR>(GetWindowLongPtrW(xHwnd, GWLP_USERDATA)));

			if (LOWORD(xWParam) == WA_INACTIVE)
			{
				WindowEvent * wEvent = aWindow->aWindowDeactivated;
				if (wEvent)
				{
					Toolkit::getSystemEventQueue(aWindow->aFrame->id())->processWindowEvent(wEvent);
				}
			}
			else
			{
				WindowEvent * wEvent = aWindow->aWindowActivated;
				if (wEvent)
				{
					Toolkit::getSystemEventQueue(aWindow->aFrame->id())->processWindowEvent(wEvent);
				}
			}
			return STATUS_OK;

		case WM_SIZE:
		{
			aWindow = reinterpret_cast<Window *>(static_cast<LONG_PTR>(GetWindowLongPtrW(xHwnd, GWLP_USERDATA)));
			return aWindow->onSize(xHwnd);
		}


		case WM_ERASEBKGND:
		{
			// OS must not erase background. DirectX and
			// OpenGL will automatically do its parent
			// (aChildHWnd) window.
			return STATUS_OK;
		}
		default: return DefWindowProc(xHwnd, xMessage, xWParam, xLParam);
		}
	}
}

STATUS Window::onSize(HWND hwnd)
{
	if (hwnd == aChildHWnd)
		aFrame->invalidate();

	return STATUS_OK;
}

HWND Window::createCompatibleWindow(bool isParent)
{
	HWND            hWnd, hwndParent;
	int             left, top, width, height;
	DWORD           lStyle, lExStyle;
	LPCWSTR titleName;

	left = isParent ? aRect.aX - aOptShadowRadius : aRect.aX + aOptBorderWidth;
	top = isParent ? aRect.aY - aOptShadowRadius : aRect.aY + aOptBorderWidth;
	width = isParent ? aRect.aWidth + aOptShadowRadius * 2 : aRect.aWidth - aOptBorderWidth * 2;
	height = isParent ? aRect.aHeight + aOptShadowRadius * 2 : aRect.aHeight - aOptBorderWidth * 2;
	lStyle = isParent ? WS_POPUP | WS_OVERLAPPED | WS_MINIMIZEBOX : WS_POPUP | WS_CHILD;
	lExStyle = isParent ? WS_EX_LAYERED | WS_EX_APPWINDOW : 0;
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

STATUS Window::updateOnMouseDown(HWND xHwnd)
{
	aIsDragged = true;

	if (aHResizeWnd != xHwnd && aHMoveWnd != xHwnd)
	{
		return 0;
	}

	SetCapture(xHwnd);

	bool isParent = aParentHWnd == xHwnd;
	int left, right, bottom, top;
	int x, y;
	POINT p;

	GetCursorPos(&p);

	x = p.x;
	y = p.y;


	left = (isParent ? aRelativeX + aPadding : aRealX);
	top = (isParent ? aRelativeY + aPadding : aRealY);
	bottom = top + aRect.aHeight;
	right = left + aRect.aWidth;

	if ((x >= left && x < left + _WINDOW_RESIZE_EDGE_DISTANCE ||
		x < right && x >= right - _WINDOW_RESIZE_EDGE_DISTANCE ||
		y < bottom && y >= bottom - _WINDOW_RESIZE_EDGE_DISTANCE ||
		y >= top && y < top + _WINDOW_RESIZE_EDGE_DISTANCE) &&
		!aIsResizing)
	{
		aIsResizing = xHwnd == aHResizeWnd ? true : false;
	}
	else if (y < top + _WINDOW_MOVE_BAR_DISTANCE)
	{
		aIsMoving = xHwnd == aHMoveWnd ? true : false;
	}

	SetCursor(aCurrentCursor);

	return STATUS_OK;
}

STATUS Window::updateOnMouseMove(HWND xHwnd)
{
	if (aHResizeWnd != xHwnd && aHMoveWnd != xHwnd)
	{
		if (xHwnd == aParentHWnd)
		{
			ReleaseCapture();
		}
		return 0;
	}

	bool isParent = aParentHWnd == xHwnd;
	int left, right, bottom, top;
	int x, y;
	POINT p;
	Rect& rect = aRect;

	GetCursorPos(&p);

	x = p.x;
	y = p.y;

	left = (isParent ? aRelativeX + aPadding : aRealX);
	top = (isParent ? aRelativeY + aPadding : aRealY);
	bottom = top + aRect.aHeight;
	right = left + aRect.aWidth;

	if (!aIsResizing && !aIsMoving)
	{
		//bottom left corner
		if (x >= left && x < left + _WINDOW_RESIZE_EDGE_DISTANCE &&
			y < bottom && y >= bottom - _WINDOW_RESIZE_EDGE_DISTANCE)
		{
			aCurrentCursor = LoadCursor(NULL, IDC_SIZENESW);
			aWinMoveRes = true;
		}
		//bottom right corner
		else if (x < right && x >= right - _WINDOW_RESIZE_EDGE_DISTANCE &&
			y < bottom && y >= bottom - _WINDOW_RESIZE_EDGE_DISTANCE)
		{
			aCurrentCursor = LoadCursor(NULL, IDC_SIZENWSE);
			aWinMoveRes = false;
		}
		//top left corner
		else if (x >= left && x < left + _WINDOW_RESIZE_EDGE_DISTANCE &&
			y >= top && y < top + _WINDOW_RESIZE_EDGE_DISTANCE)
		{
			aCurrentCursor = LoadCursor(NULL, IDC_SIZENWSE);
			aWinMoveRes = true;
		}
		//top right corner
		else if (x < right && x >= right - _WINDOW_RESIZE_EDGE_DISTANCE &&
			y >= top && y < top + _WINDOW_RESIZE_EDGE_DISTANCE)
		{
			aCurrentCursor = LoadCursor(NULL, IDC_SIZENESW);
			aWinMoveRes = false;
		}
		//left border
		else if (x >= left && x < left + _WINDOW_RESIZE_EDGE_DISTANCE &&
			y >= top + _WINDOW_RESIZE_EDGE_DISTANCE &&
			y < bottom - _WINDOW_RESIZE_EDGE_DISTANCE)
		{
			aCurrentCursor = LoadCursor(NULL, IDC_SIZEWE);
			aWinMoveRes = true;
		}
		//right border
		else if (x < right && x >= right - _WINDOW_RESIZE_EDGE_DISTANCE &&
			y >= top + _WINDOW_RESIZE_EDGE_DISTANCE &&
			y < bottom - _WINDOW_RESIZE_EDGE_DISTANCE)
		{
			aCurrentCursor = LoadCursor(NULL, IDC_SIZEWE);
			aWinMoveRes = false;
		}
		//bottom border
		else if (y < bottom && y >= bottom - _WINDOW_RESIZE_EDGE_DISTANCE  &&
			x >= left + _WINDOW_RESIZE_EDGE_DISTANCE &&
			x < right - _WINDOW_RESIZE_EDGE_DISTANCE)
		{
			aCurrentCursor = LoadCursor(NULL, IDC_SIZENS);
			aWinMoveRes = false;
		}
		//top border
		else if (y >= top && y < top + _WINDOW_RESIZE_EDGE_DISTANCE  &&
			x >= left + _WINDOW_RESIZE_EDGE_DISTANCE &&
			x < right - _WINDOW_RESIZE_EDGE_DISTANCE)
		{
			aCurrentCursor = LoadCursor(NULL, IDC_SIZENS);
			aWinMoveRes = true;
		}
		//default
		else
		{
			aCurrentCursor = LoadCursor(NULL, IDC_ARROW);
			// Handle the window movement here.
			aWinMoveRes = false;
		}

		SetCursor(aCurrentCursor);
	}

	if (!aIsDragged)
	{
		GetCursorPos(&aLastDraggedPoint);
		ScreenToClient(xHwnd, &aLastDraggedPoint);
	}

	if (aIsDragged && (aIsResizing || aIsMoving))
	{
		int deltaY, deltaX;
		HCURSOR currentCursor;

		GetCursorPos(&p);
		ScreenToClient(xHwnd, &p);

		aOffsetY = deltaY = INT(aLastDraggedPoint.y - p.y);
		aOffsetX = deltaX = INT(aLastDraggedPoint.x - p.x);
		currentCursor = GetCursor();
		
		if (aOffsetY < -2000)
		{
			aOffsetY = 0;
			deltaY = 0;
		}
		
		memcpy(&aLastRect, &aRect, sizeof(Rect));

		// Process resizing.
		if (aIsResizing)
		{
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
						p.y += LONG(deltaY);
						aFramebufferInterpolation = true;
					}
				}
				else
				{
					rect.aHeight -= (rect.aHeight - deltaY >= aMinDims.aHeight) && (rect.aHeight - deltaY < aMaxDims.aHeight) ? deltaY : 0;
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
						p.x += LONG(deltaX);
						aFramebufferInterpolation = true;
					}
				}
				else
				{
					rect.aWidth -= (rect.aWidth - deltaX >= aMinDims.aWidth) && (rect.aWidth - deltaX < aMaxDims.aWidth) ? deltaX : 0;
				}

			}
			// Resize upper right and lower left corners.
			else if (currentCursor == LoadCursor(NULL, IDC_SIZENESW))
			{
				if (aWinMoveRes)
				{
					rect.aHeight -= (rect.aHeight - deltaY >= aMinDims.aHeight) && (rect.aHeight - deltaY < aMaxDims.aHeight) ? deltaY : 0;
					if (rect.aWidth + deltaX >= aMinDims.aWidth &&
						rect.aWidth + deltaX < aMaxDims.aWidth)
					{
						rect.aX -= (deltaX);
						rect.aWidth += (deltaX);
						p.x += LONG(deltaX);
						aFramebufferInterpolation = true;

					}
				}
				else
				{
					rect.aWidth -= (rect.aWidth - deltaX >= aMinDims.aWidth) && (rect.aWidth - deltaX < aMaxDims.aWidth) ? deltaX : 0;
					if (rect.aHeight + deltaY >= aMinDims.aHeight &&
						rect.aHeight + deltaY < aMaxDims.aHeight)
					{
						rect.aY -= (deltaY);
						rect.aHeight += (deltaY);
						p.y += LONG(deltaY);
						aFramebufferInterpolation = true;
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
						p.x += LONG(deltaX);
						aFramebufferInterpolation = true;
					}
					if (rect.aHeight + deltaY >= aMinDims.aHeight &&
						rect.aHeight + deltaY < aMaxDims.aHeight)
					{
						rect.aY -= (deltaY);
						rect.aHeight += (deltaY);
						p.y += LONG(deltaY);
						aFramebufferInterpolation = true;
					}

				}
				else
				{
					rect.aWidth -= (rect.aWidth - deltaX >= aMinDims.aWidth) && (rect.aWidth - deltaX < aMaxDims.aWidth) ? deltaX : 0;
					rect.aHeight -= (rect.aHeight - deltaY >= aMinDims.aHeight) && (rect.aHeight - deltaY < aMaxDims.aHeight) ? deltaY : 0;
				}
			}

			// DEFER REGION //

			render();

			// DEFER REGION //

		}
		// Process window movement.
		else if (aIsMoving)
		{
			rect.aX -= deltaX;
			rect.aY -= deltaY;
			p.x += LONG(deltaX);
			p.y += LONG(deltaY); 

			// DEFER REGION //

			updateLocation();

			// DEFER REGION //
		}

		aLastDraggedPoint = p;
	}
	return STATUS_OK;
}

STATUS Window::updateOnMouseUp(HWND xHwnd)
{
	aIsDragged = false;

	if (aHResizeWnd != xHwnd && aHMoveWnd != xHwnd)
	{
		return 0;
	}

	ReleaseCapture();
	
	// Give one more render request
	if (aIsResizing)
	{
		render();
	}

	// Disable everything
	aIsResizing = false;
	aIsMoving = false;

	aFramebufferInterpolation = false;

	return STATUS_OK;
}

int Window::aClassInstances = 0;

ATOM Window::registerClass()
{
	WNDCLASSEX wcex = { sizeof(WNDCLASSEX) };
	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wcex.lpfnWndProc = Window::wndProc;
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

void Window::updateBackgroundCache()
{
	destroyBackgroundResources();
	createBackgroundResources();

	HBRUSH brush = CreateSolidBrush(RGB(aOptBackgroundColor.aRed, aOptBackgroundColor.aGreen, aOptBackgroundColor.aBlue));
	SetClassLongPtr(aParentHWnd, GCLP_HBRBACKGROUND, (LONG)brush);
}

void Window::updateShadowCache()
{
	destroyShadowResources();
	createShadowResources();
}

void Window::destroyShadowResources()
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

void Window::spliceToNinePatch(Gdiplus::Image * src, Gdiplus::Image * dest, float srcX, float srcY, float srcWidth, float srcHeight)
{
	Gdiplus::Graphics graphics(dest);
	
	graphics.DrawImage(src, FLT_ZERO, FLT_ZERO, srcX, srcY, srcWidth, srcHeight, Gdiplus::UnitPixel);
	graphics.DrawImage(src, FLT_ZERO, FLT_ZERO, srcX, srcY, srcWidth, srcHeight, Gdiplus::UnitPixel); // Render twice to increase opacity
	graphics.DrawImage(src, FLT_ZERO, FLT_ZERO, srcX, srcY, srcWidth, srcHeight, Gdiplus::UnitPixel); // Render twice to increase opacity
}

float* Window::getGaussianKernel(int xRadius)
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

Gdiplus::Bitmap * Window::applyGaussianBlur(Gdiplus::Bitmap * src, int radius)
{
	// NOTE: There could be memory leaks if the Gdiplus::BitmapData is NULL
	// PLEASE FIX!

	float * kernel;
	Gdiplus::Bitmap * blurred, *rotated;
	Gdiplus::BitmapData * rotatedData, *srcData, *blurredData;

	kernel = getGaussianKernel(radius);

	blurred = new Gdiplus::Bitmap(src->GetWidth(), src->GetHeight());
	rotated = new Gdiplus::Bitmap(src->GetHeight(), src->GetWidth());
	
	// horizontal pass 0
	srcData = getLockedBitmapData(src);
	if (!srcData) return NULL;

	blurredData = getLockedBitmapData(blurred);
	if (!blurredData) return NULL;

	applyHorizontalblur(srcData, blurredData, kernel, radius);

	src->UnlockBits(srcData);

	blurred->UnlockBits(blurredData);
	blurred->RotateFlip(Gdiplus::Rotate90FlipNone);

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

void  Window::applyHorizontalblur(Gdiplus::BitmapData * srcPixels, Gdiplus::BitmapData * dstPixels, float * kernel, int radius)
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

			ca = INT(a + 0.5f);
			cr = INT(r + 0.5f);
			cg = INT(g + 0.5f);
			cb = INT(b + 0.5f);

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

Gdiplus::BitmapData * Window::getLockedBitmapData(Gdiplus::Bitmap * src)
{
	int srcWidth = src->GetWidth();
	int srcHeight = src->GetHeight();

	Gdiplus::BitmapData * bitmapData = new Gdiplus::BitmapData();

	Gdiplus::Status ret = src->LockBits(new Gdiplus::Rect(0, 0, srcWidth, srcHeight),
		Gdiplus::ImageLockMode::ImageLockModeRead | Gdiplus::ImageLockMode::ImageLockModeWrite,
		src->GetPixelFormat(),
		bitmapData);

	if (ret) return NULL;

	return bitmapData;
}

STATUS Window::createShadowResources()
{
	Gdiplus::Bitmap * solid, *blurred;
	Gdiplus::Graphics * graphics;
	Gdiplus::SolidBrush blackBrush(*aShadowColor);

	int radius = aOptShadowRadius;
	int radiusSafety = radius * _WINDOW_BOX_SHADOW_SAFELYTY_RATIO;
	int realDim = radius * 3;
	int relativeDim = realDim + radius * 2;

	int radiusAsInt = radius;
	int radiusSafetyAsInt = radiusSafety;
	int relativeDimAsInt = relativeDim;

	aTopLeftShadow = new Gdiplus::Bitmap(radiusSafetyAsInt, radiusSafetyAsInt);
	aBottomLeftShadow = new Gdiplus::Bitmap(radiusSafetyAsInt, radiusSafetyAsInt);
	aTopRightShadow = new Gdiplus::Bitmap(radiusSafetyAsInt, radiusSafetyAsInt);
	aBottomRightShadow = new Gdiplus::Bitmap(radiusSafetyAsInt, radiusSafetyAsInt);

	aTopShadow = new Gdiplus::Bitmap(1, radiusAsInt);
	aLeftShadow = new Gdiplus::Bitmap(radiusAsInt, 1);
	aRightShadow = new Gdiplus::Bitmap(radiusAsInt, 1);
	aBottomShadow = new Gdiplus::Bitmap(1, radiusAsInt);

	solid = new Gdiplus::Bitmap(relativeDimAsInt, relativeDimAsInt);
	graphics = new Gdiplus::Graphics(solid);

	// Draw base shape

	graphics->FillRectangle(&blackBrush, radius, radius, realDim, realDim);

	// Create box shadow

	blurred = applyGaussianBlur(solid, radiusAsInt);

	// Cache as 9-patch

	spliceToNinePatch(blurred, aTopLeftShadow, FLT_ZERO, FLT_ZERO, FLOAT(radiusSafety), FLOAT(radiusSafety));
	spliceToNinePatch(blurred, aBottomLeftShadow, FLT_ZERO, FLOAT(relativeDim - radiusSafety), FLOAT(radiusSafety), FLOAT(radiusSafety));
	spliceToNinePatch(blurred, aBottomRightShadow, FLOAT(relativeDim - radiusSafety), FLOAT(relativeDim - radiusSafety), FLOAT(radiusSafety), FLOAT(radiusSafety));
	spliceToNinePatch(blurred, aTopRightShadow, FLOAT(relativeDim - radiusSafety), FLT_ZERO, FLOAT(radiusSafety), FLOAT(radiusSafety));

	spliceToNinePatch(blurred, aTopShadow, FLOAT(radiusSafety), FLT_ZERO, FLT_ONE, FLOAT(radius));
	spliceToNinePatch(blurred, aLeftShadow, FLT_ZERO, FLOAT(radiusSafety), FLOAT(radius), FLT_ONE);
	spliceToNinePatch(blurred, aRightShadow, FLOAT(relativeDim - radius), FLOAT(radiusSafety), FLOAT(radius), FLT_ONE);
	spliceToNinePatch(blurred, aBottomShadow, FLOAT(radiusSafety), FLOAT(relativeDim - radius), FLT_ONE, FLOAT(radius));

	aTopShadowBrush = new Gdiplus::TextureBrush(aTopShadow);
	aLeftShadowBrush = new Gdiplus::TextureBrush(aLeftShadow);
	aRightShadowBrush = new Gdiplus::TextureBrush(aRightShadow);
	aBottomShadowBrush = new Gdiplus::TextureBrush(aBottomShadow);

	// update values
	aPadding = radius;
	aShadowPadding = radiusSafety;

	delete graphics;
	delete blurred;
	delete solid;

	return STATUS_OK;
}

STATUS Window::createBackgroundResources()
{
	aBackground = new Gdiplus::Bitmap(1, 1);

	Gdiplus::Graphics graphics(aBackground);
	Gdiplus::SolidBrush blackBrush(*aBackgroundColor);

	graphics.FillRectangle(&blackBrush, 0, 0, 1, 1);

	aBackgroundBrush = new Gdiplus::TextureBrush(aBackground);

	return STATUS_OK;
}

void Window::destroyBackgroundResources()
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

STATUS Window::createResources()
{
	SAFELY(createColorResources());
	SAFELY(createBackgroundResources());
	SAFELY(createShadowResources());

	return STATUS_OK;
}

void Window::destroyResources()
{
	destroyShadowResources();
	destroyBackgroundResources();
	destroyColorResources();
}

void Window::paintComponentBorder(Gdiplus::Graphics& graphics)
{
	int padding = aPadding;
	int optBorderWidth = aOptBorderWidth;
	int realWidth = aRealWidth;
	int realHeight = aRealHeight;

	Gdiplus::Color& borderColor = *aBorderColor;

	if (optBorderWidth > 0)
	{
		Gdiplus::Pen borderPen(borderColor, FLOAT(optBorderWidth));

		graphics.DrawRectangle(&borderPen, FLOAT(padding + optBorderWidth / 2), FLOAT(padding + optBorderWidth / 2), FLOAT(aRealWidth + optBorderWidth), FLOAT(realHeight + optBorderWidth));

		DeleteObject(&borderPen);
	}
}

void Window::paintComponent(Gdiplus::Graphics& graphics)
{
	int padding = aPadding;
	int optBorderWidth = aOptBorderWidth;
	int shadowPadding = aShadowPadding;
	int relativeWidth = aRelativeWidth;
	int relativeHeight = aRelativeHeight;
	int realWidth = aRealWidth;
	int realHeight = aRealHeight;

	Gdiplus::TextureBrush * topShadowBrush = aTopShadowBrush;
	Gdiplus::TextureBrush * leftShadowBrush = aLeftShadowBrush;
	Gdiplus::TextureBrush * rightShadowBrush = aRightShadowBrush;
	Gdiplus::TextureBrush * bottomShadowBrush = aBottomShadowBrush;
	Gdiplus::TextureBrush * backgroundBrush = aBackgroundBrush;

	Gdiplus::Image * topLeftShadow = aTopLeftShadow;
	Gdiplus::Image * bottomLeftShadow = aBottomLeftShadow;
	Gdiplus::Image * topRightShadow = aTopRightShadow;
	Gdiplus::Image * bottomRightShadow = aBottomRightShadow;

	topShadowBrush->ResetTransform();
	leftShadowBrush->ResetTransform();
	rightShadowBrush->ResetTransform();
	bottomShadowBrush->ResetTransform();

	topShadowBrush->TranslateTransform(FLOAT(shadowPadding), FLT_ZERO);
	graphics.FillRectangle(topShadowBrush, FLOAT(shadowPadding), FLT_ZERO, FLOAT(relativeWidth - shadowPadding * 2), FLOAT(padding));

	leftShadowBrush->TranslateTransform(FLT_ZERO, FLOAT(shadowPadding));
	graphics.FillRectangle(leftShadowBrush, FLT_ZERO, FLOAT(shadowPadding), FLOAT(padding), FLOAT(relativeHeight - shadowPadding * 2));

	rightShadowBrush->TranslateTransform(FLOAT(relativeWidth - padding), FLOAT(shadowPadding));
	graphics.FillRectangle(rightShadowBrush, FLOAT(relativeWidth - padding), FLOAT(shadowPadding), FLOAT(padding), FLOAT(relativeHeight - shadowPadding * 2));

	bottomShadowBrush->TranslateTransform(FLOAT(shadowPadding), FLOAT(relativeHeight - padding));
	graphics.FillRectangle(bottomShadowBrush, FLOAT(shadowPadding), FLOAT(relativeHeight - padding), FLOAT(relativeWidth - shadowPadding * 2), FLOAT(padding));

	graphics.DrawImage(topLeftShadow, FLT_ZERO, FLT_ZERO, FLOAT(shadowPadding), FLOAT(shadowPadding));
	graphics.DrawImage(bottomLeftShadow, FLT_ZERO, FLOAT(relativeHeight - shadowPadding), FLOAT(shadowPadding), FLOAT(shadowPadding));
	graphics.DrawImage(topRightShadow, FLOAT(relativeWidth - shadowPadding), FLT_ZERO, FLOAT(shadowPadding), FLOAT(shadowPadding));
	graphics.DrawImage(bottomRightShadow, FLOAT(relativeWidth - shadowPadding), FLOAT(relativeHeight - shadowPadding), FLOAT(shadowPadding), FLOAT(shadowPadding));

	graphics.FillRectangle(backgroundBrush, FLOAT(padding), FLOAT(padding), FLOAT(realWidth + optBorderWidth), FLOAT(realHeight + optBorderWidth));
}

////////////////////////////////////////////////////////////////////////////////
// ABSTRACTWINDOW
////////////////////////////////////////////////////////////////////////////////

void Window::setName(LPCWSTR xName)
{
	aName = xName;

	SetWindowText(aChildHWnd, aName);
	SetWindowText(aParentHWnd, aName);
}

void Window::setUndecorated(bool xUndecorated)
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

void Window::setDefaultCloseOperation(int xDefaultCloseOperation)
{
	aDefaultCloseOperation = xDefaultCloseOperation;
}

void Window::setLocationRelativeTo(AbstractWindow * xRelativeWindow)
{
	aRelativeWindow = xRelativeWindow;

	if (aRelativeWindow == NULL)
	{
		aRect.aX = (GetSystemMetrics(SM_CXSCREEN) - aRect.aWidth) / 2;
		aRect.aY = (GetSystemMetrics(SM_CYSCREEN) - aRect.aHeight) / 2;
	}
}

void Window::setVisible(bool xVisible)
{
	aVisible = xVisible;

	if (aVisible)
	{
		update();

		ShowWindow(aChildHWnd, SW_SHOWNORMAL);
		ShowWindow(aParentHWnd, SW_SHOWNORMAL);
		// Fire WindowEvent
		Toolkit::getSystemEventQueue(aFrame->id())->processWindowEvent(aWindowOpened);
	}
	else
	{
		ShowWindow(aChildHWnd, SW_HIDE);
		ShowWindow(aParentHWnd, SW_HIDE);
	}
}

void Window::setMinimumSize(Dims * xSize)
{
	aMinDims.aWidth = xSize->aWidth;
	aMinDims.aHeight = xSize->aHeight;
}

void Window::setMaximumSize(Dims * xSize)
{
	aMaxDims.aWidth = xSize->aWidth;
	aMaxDims.aHeight = xSize->aHeight;
}

void Window::setSize(Dims * xSize)
{
	aRect.aWidth = xSize->aWidth;
	aRect.aHeight = xSize->aHeight;
}

void Window::setMinimumSize(int xWidth, int xHeight)
{
	aMinDims.aWidth = xWidth;
	aMinDims.aHeight = xHeight;
}

void Window::setMaximumSize(int xWidth, int xHeight)
{
	aMaxDims.aWidth = xWidth;
	aMaxDims.aHeight = xHeight;
}

void Window::setSize(int xWidth, int xHeight)
{
	aRect.aWidth = xWidth;
	aRect.aHeight = xHeight;
}

void Window::setBorderWidth(int xBorderWidth)
{
	aOptBorderWidth = xBorderWidth;
}

void Window::setShadowRadius(int xShadowRadius)
{
	aOptShadowRadius = xShadowRadius;
}

void Window::setShadow(Color * xShadowColor, int xShadowRadius)
{
	aOptShadowColor = *xShadowColor;
	aOptShadowRadius = xShadowRadius;
}

void Window::setBorder(Color * xBorderColor, int xBorderWidth)
{
	aOptBorderColor = *xBorderColor;
	aOptBorderWidth = xBorderWidth;
}

void Window::setBounds(Rect * xRect)
{
	aRect.aWidth = xRect->aWidth;
	aRect.aX = xRect->aX;
	aRect.aY = xRect->aY;
	aRect.aHeight = xRect->aHeight;
}

void Window::setBounds(int xLeft, int xTop, int xWidth, int xHeight)
{
	aRect.aWidth = xWidth;
	aRect.aX = xLeft;
	aRect.aY = xTop;
	aRect.aHeight = xHeight;
}

void Window::validate()
{
	// Minimum dimensions has to be greater than border and shadow safety region
	aMinDims.aWidth = _max((aOptShadowRadius * _WINDOW_BOX_SHADOW_SAFELYTY_RATIO) + ((aOptBorderWidth * 2) + 1), aMinDims.aWidth);
	aMinDims.aHeight = _max((aOptShadowRadius * _WINDOW_BOX_SHADOW_SAFELYTY_RATIO) + ((aOptBorderWidth * 2) + 1), aMinDims.aHeight);

	// Minimum dimensions has to be greater than or equal to minimum size
	aMaxDims.aWidth = _max(aMinDims.aWidth, aMaxDims.aWidth);
	aMaxDims.aHeight = _max(aMinDims.aHeight, aMaxDims.aHeight);

	// Constrain the rect to between min and max
	aRect.aWidth = _min(_max(aMinDims.aWidth, aRect.aWidth), aMaxDims.aWidth);
	aRect.aHeight = _min(_max(aMinDims.aHeight, aRect.aHeight), aMaxDims.aHeight);

	// Create resize window pointer.
	aHResizeWnd = aOptBorderWidth < _WINDOW_RESIZE_DEFAULT_DISTANCE ? aChildHWnd : aParentHWnd;
	aHMoveWnd = aOptBorderWidth < _WINDOW_MOVE_DEFAULT_DISTANCE ? aChildHWnd : aParentHWnd;

	// Update caches
	updateColorCache();
	updateBackgroundCache();
	updateShadowCache();

	// Mark as validated
	validated();
}

STATUS Window::createColorResources()
{
	aBackgroundColor = new Gdiplus::Color(aOptBackgroundColor.aAlpha, aOptBackgroundColor.aRed, aOptBackgroundColor.aGreen, aOptBackgroundColor.aBlue);
	aShadowColor = new Gdiplus::Color(aOptShadowColor.aAlpha, aOptShadowColor.aRed, aOptShadowColor.aGreen, aOptShadowColor.aBlue);
	aBorderColor = new Gdiplus::Color(aOptBorderColor.aAlpha, aOptBorderColor.aRed, aOptBorderColor.aGreen, aOptBorderColor.aBlue);

	return STATUS_OK;
}


void Window::destroyColorResources()
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

void Window::updateColorCache()
{
	destroyColorResources();
	createColorResources();
}

void Window::setBorderColor(Color * xBorderColor)
{
	aOptBorderColor = *xBorderColor;
}

void Window::setShadowed(bool xShadowed)
{
	aShadowed = xShadowed;

	setShadowRadius(0);
}

void Window::setShadowColor(Color * xShadowColor)
{
	aOptShadowColor = *xShadowColor;
}

void Window::setBackgroundColor(Color * xBackgroundColor)
{
	aOptBackgroundColor = *xBackgroundColor;
}

void* Window::getPlatformCompatibleWindowHandle()
{
	return static_cast<void*>(&aChildHWnd);
}
void Window::render()
{
	// Cache variables to ensure that these variables
	// won't be changed in the middle of update() via concurrent
	// threads.

	int padding = aPadding;
	int optBorderWidth = aOptBorderWidth;

	int realX = aRealX = aRect.aX + aOptBorderWidth;
	int realY = aRealY = aRect.aY + aOptBorderWidth;
	int realWidth = aDrawableRegion.aWidth = aRealWidth = aRect.aWidth - aOptBorderWidth * 2;
	int realHeight = aDrawableRegion.aHeight = aRealHeight = aRect.aHeight - aOptBorderWidth * 2;
	int relativeX = aRelativeX = aRect.aX - aPadding;
	int relativeY = aRelativeY = aRect.aY - aPadding;
	int relativeWidth = aRelativeWidth = aRect.aWidth + aPadding * 2;
	int relativeHeight = aRelativeHeight = aRect.aHeight + aPadding * 2;

	/***********************************************/
	
	SIZE size = { LONG(relativeWidth), LONG(relativeHeight) };
	HDC memDCChild, hwndDC = GetDC(aParentHWnd), memDC = CreateCompatibleDC(hwndDC);
	HBITMAP memBitmapChild;
	POINT ptDst = { LONG(relativeX), LONG(relativeY) }, ptSrc = { 0, 0 };
	
	if (aFramebufferInterpolation)
	{

		memDCChild = CreateCompatibleDC(hwndDC);
		// Create secondary DC
		memBitmapChild = CreateCompatibleBitmap(hwndDC, INT(relativeWidth), INT(relativeHeight));
		SelectObject(memDCChild, memBitmapChild);

		// Request copy of frameBuffer
		PrintWindow(aChildHWnd, memDCChild, 0);
	}

	HBITMAP memBitmap = CreateCompatibleBitmap(hwndDC, INT(relativeWidth), INT(relativeHeight));
	SelectObject(memDC, memBitmap);

	Gdiplus::Graphics graphics(memDC);

	/***********************************************/

	paintComponent(graphics);
	paintComponentBorder(graphics);

	/***********************************************/
	if (aFramebufferInterpolation)
	{
		// Paint from frameBuffer of the child HWND into the 
		// the parent HWND
		StretchBlt(memDC, 
			aOptBorderWidth + aPadding,
			aOptBorderWidth + aPadding,
			realWidth,
			realHeight,
			memDCChild,
			0, 0,
			aLastRect.aWidth - aOptBorderWidth * 2 + (aOffsetX < 0 ? aOffsetX : 0),
			aLastRect.aHeight - aOptBorderWidth * 2 + (aOffsetY < 0 ? aOffsetY : 0),
			SRCCOPY);

		ReleaseDC(aParentHWnd, memDCChild);
		DeleteObject(memBitmapChild);
		DeleteObject(memDCChild);
	}

	/***********************************************/

	BLENDFUNCTION blendFunction;
	blendFunction.AlphaFormat = AC_SRC_ALPHA;
	blendFunction.BlendFlags = 0;
	blendFunction.BlendOp = AC_SRC_OVER;
	blendFunction.SourceConstantAlpha = 255;

	/***********************************************/

	UpdateLayeredWindow(aParentHWnd, hwndDC, &ptDst, &size, memDC, &ptSrc, 0, &blendFunction, ULW_ALPHA);

	/***********************************************/

	HDWP hdwp = BeginDeferWindowPos(2);
	
	if (hdwp) hdwp = DeferWindowPos(hdwp, aParentHWnd, aChildHWnd, relativeX, relativeY, relativeWidth, relativeHeight, SWP_NOCOPYBITS);
	
	if (hdwp) hdwp = DeferWindowPos(hdwp, aChildHWnd, NULL, realX, realY - (aFramebufferInterpolation ? 3000 : 0), realWidth, realHeight, SWP_NOCOPYBITS | SWP_NOREDRAW);

	EndDeferWindowPos(hdwp);

	/***********************************************/
	
	graphics.ReleaseHDC(memDC);
	DeleteObject(memBitmap);
	ReleaseDC(aParentHWnd, memDC);
	ReleaseDC(aParentHWnd, hwndDC);
	DeleteDC(hwndDC);
	DeleteDC(memDC);
}

void Window::updateLocation()
{
	int relativeX = aRelativeX = aRect.aX - aPadding;
	int relativeY = aRelativeY = aRect.aY - aPadding;
	int realX = aRealX = aRect.aX + aOptBorderWidth;
	int realY = aRealY = aRect.aY + aOptBorderWidth;

	HDWP hdwp = BeginDeferWindowPos(2);

	if (hdwp) hdwp = DeferWindowPos(hdwp, aParentHWnd, aChildHWnd, relativeX, relativeY, 0, 0, SWP_NOZORDER | SWP_NOSIZE);

	if (hdwp) hdwp = DeferWindowPos(hdwp, aChildHWnd, NULL, realX, realY, 0, 0, SWP_NOZORDER | SWP_NOSIZE);

	EndDeferWindowPos(hdwp);
}

////////////////////////////////////////////////////////////////////////////////
// ABSTRACT
////////////////////////////////////////////////////////////////////////////////

STATUS Window::initialize()
{
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;

	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	// Change class name
	aClassInstances++;

	// Update class name
	std::ostringstream stream;
	stream << "Window - " << aClassInstances;
	std::string className(stream.str());
	aClassName = new std::wstring(className.begin(), className.end());

	// Super
	AbstractWindow::initialize();

	NULLCHECK(registerClass());
	NULLCHECK((aParentHWnd = createCompatibleWindow(true)));
	NULLCHECK((aChildHWnd = createCompatibleWindow(false)));
	SAFELY(createResources());

	update();

	return STATUS_OK;
}

Window::~Window()
{
	destroyResources();

	aParentHWnd = NULL;
	aChildHWnd = NULL;

	delete aClassName;
	aClassName = 0;
}