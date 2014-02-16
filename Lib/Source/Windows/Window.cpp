
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
	int& animating = xEventQueue->m_animating;

    int defaultAllotedAnimationFrames = 10;
    int currentAnimationFrame = 0;
    int counter = 0;

    AbstractFrame& frame = *aFrame;
    AbstractEventQueue& eventQueue = *xEventQueue;

	double lastTime = kerneltimehp__;
	double timeBetweenFrames = 1.0 / SDOUBLE(A2D_FPS);
	double currentTime;
	
    while (true)
	{
		if (eventQueue.dispatchNextEvent())
		{
			currentAnimationFrame = defaultAllotedAnimationFrames;
		}

        if (visible)
        {
            if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
            {
                TranslateMessage(&msg);
                eventHandler(msg, &eventQueue);
            }			
			
			if ((currentTime = kerneltimehp__) - lastTime < timeBetweenFrames && !resizing)
			{
				continue;
			}
			else
			{
				lastTime = currentTime;

				if (animating)
				{
					frame.update();
				}
				else if (resizing)
				{
					frame.update();
				}
				else if (currentAnimationFrame > 0)
				{
					currentAnimationFrame--;
					frame.update();
				}
				else
				{
					// Do caching here!

					if (GetMessage(&msg, NULL, 0x114, UINT_MAX) > 0)
					{
						TranslateMessage(&msg);
						eventHandler(msg, &eventQueue);
					}
				}
			}
		}
		else
		{
			Sleep(500);
		}
    }
}

LRESULT _fastcall Window::eventHandler(MSG xMsg, AbstractEventQueue * xEventQueue)
{
    if (xMsg.message == WM_CREATE)
    {
        return STATUS_OK;
    }
    else
    {
        HWND xHwnd = xMsg.hwnd;
        Point point;

        switch (xMsg.message)
        {
        case WM_LBUTTONDOWN:

            SetForegroundWindow(xHwnd);

            // Firing window event. Opposite window isnt supported yet!!
            // WM_ACTIVATE doesnt work in eventHandler.
            if (aCurrentState != WindowEvent::WINDOW_ACTIVATED)
            {
                xEventQueue->processWindowEvent(aWindowActivated);
            }

            // Fire MouseEvent
			point.m_x = SFLOAT(LOW16UINT32(xMsg.lParam));
			point.m_y = SFLOAT(HI16UINT32(xMsg.lParam));

            aMouseDown->setLocation(point);

            xEventQueue->processMouseEvent(aMouseDown);
            return updateOnMouseDown(xHwnd);

        case WM_MOUSEMOVE:

            // Fire MouseEvent
			point.m_x = SFLOAT(LOW16UINT32(xMsg.lParam));
			point.m_y = SFLOAT(HI16UINT32(xMsg.lParam));

            aMouseMove->setLocation(point);

            if (aIsDragged)
            {
                aMouseDragged->setLocation(point);
                xEventQueue->processMouseMotionEvent(aMouseDragged);
            }
            else
            {
                aMouseMove->setLocation(point);
                xEventQueue->processMouseMotionEvent(aMouseMove);
            }
            return updateOnMouseMove(xHwnd);

        case WM_LBUTTONUP:

            // Fire MouseEvent

			point.m_x = SFLOAT(LOW16UINT32(xMsg.lParam));
			point.m_y = SFLOAT(HI16UINT32(xMsg.lParam));

            aMouseUp->setLocation(point);

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
		{
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
		}
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
    LPCWSTR         titleName;

    left = SINT(isParent ? aRect.m_x - aOptShadowRadius : aRect.m_x + aOptBorderWidth);
    top = SINT(isParent ? aRect.m_y - aOptShadowRadius : aRect.m_y + aOptBorderWidth);
    width = SINT(isParent ? aRect.m_width + aOptShadowRadius * 2 : aRect.m_width - aOptBorderWidth * 2);
    height = SINT(isParent ? aRect.m_height + aOptShadowRadius * 2 : aRect.m_height - aOptBorderWidth * 2);
    lStyle = SINT(isParent ? WS_POPUP | WS_OVERLAPPED | WS_MINIMIZEBOX : WS_POPUP | WS_CHILD);
	lExStyle = SINT(isParent ? WS_EX_LAYERED | WS_EX_APPWINDOW : 0);
    hwndParent = isParent ? HWND_DESKTOP : aParentHWnd;
    titleName = aName;

    hWnd = CreateWindowEx(lExStyle, aClassName->c_str(), titleName, lStyle, left, top, width, height, hwndParent, NULL, aHInstance, this);
	
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
    float left, right, bottom, top;
    int x, y;
    POINT p;

    GetCursorPos(&p);

    x = p.x;
    y = p.y;


    left = (isParent ? aRelativeX + aPadding : aRealX);
    top = (isParent ? aRelativeY + aPadding : aRealY);
    bottom = top + aRect.m_height;
    right = left + aRect.m_width;

    if ((x >= left && x < left + A2D_WINDOW_RESIZE_EDGE_DISTANCE ||
        x < right && x >= right - A2D_WINDOW_RESIZE_EDGE_DISTANCE ||
        y < bottom && y >= bottom - A2D_WINDOW_RESIZE_EDGE_DISTANCE ||
        y >= top && y < top + A2D_WINDOW_RESIZE_EDGE_DISTANCE) &&
        !aIsResizing)
    {
        aIsResizing = xHwnd == aHResizeWnd ? true : false;
    }
    else if (y < top + A2D_WINDOW_MOVE_BAR_DISTANCE)
    {
        aIsMoving = xHwnd == aHMoveWnd ? true : false;
    }

    SetCursor(aCurrentCursor);

    return STATUS_OK;
}

HCURSOR Window::CURSOR_IDC_SIZENWSE = LoadCursor(NULL, IDC_SIZENWSE);
HCURSOR Window::CURSOR_IDC_SIZENESW = LoadCursor(NULL, IDC_SIZENESW);
HCURSOR Window::CURSOR_IDC_SIZENS = LoadCursor(NULL, IDC_SIZENS);
HCURSOR Window::CURSOR_IDC_SIZEWE = LoadCursor(NULL, IDC_SIZEWE);
HCURSOR Window::CURSOR_IDC_ARROW = LoadCursor(NULL, IDC_ARROW);

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
    float left, right, bottom, top;
    int x, y;
    POINT p;
    Rect& rect = aRect;

    GetCursorPos(&p);

    x = p.x;
    y = p.y;

    left = (isParent ? aRelativeX + aPadding : aRealX);
    top = (isParent ? aRelativeY + aPadding : aRealY);
    bottom = top + aRect.m_height;
    right = left + aRect.m_width;

    if (!aIsResizing && !aIsMoving)
    {
        //bottom left corner
        if (x >= left && x < left + A2D_WINDOW_RESIZE_EDGE_DISTANCE &&
            y < bottom && y >= bottom - A2D_WINDOW_RESIZE_EDGE_DISTANCE)
        {
			aCurrentCursor = Window::CURSOR_IDC_SIZENESW;
			aCursor = Cursor::RESIZE_NORTH_EAST_SOUTH_WEST;
            aWinMoveRes = true;
        }
        //bottom right corner
        else if (x < right && x >= right - A2D_WINDOW_RESIZE_EDGE_DISTANCE &&
            y < bottom && y >= bottom - A2D_WINDOW_RESIZE_EDGE_DISTANCE)
        {
			aCurrentCursor = Window::CURSOR_IDC_SIZENWSE;
			aCursor = Cursor::RESIZE_NORTH_WEST_SOUTH_EAST;
            aWinMoveRes = false;
        }
        //top left corner
        else if (x >= left && x < left + A2D_WINDOW_RESIZE_EDGE_DISTANCE &&
            y >= top && y < top + A2D_WINDOW_RESIZE_EDGE_DISTANCE)
        {
			aCurrentCursor = Window::CURSOR_IDC_SIZENWSE;
			aCursor = Cursor::RESIZE_NORTH_WEST_SOUTH_EAST;
            aWinMoveRes = true;
        }
        //top right corner
        else if (x < right && x >= right - A2D_WINDOW_RESIZE_EDGE_DISTANCE &&
            y >= top && y < top + A2D_WINDOW_RESIZE_EDGE_DISTANCE)
        {
			aCurrentCursor = Window::CURSOR_IDC_SIZENESW;
			aCursor = Cursor::RESIZE_NORTH_EAST_SOUTH_WEST;
            aWinMoveRes = false;
        }
        //left border
        else if (x >= left && x < left + A2D_WINDOW_RESIZE_EDGE_DISTANCE &&
            y >= top + A2D_WINDOW_RESIZE_EDGE_DISTANCE &&
            y < bottom - A2D_WINDOW_RESIZE_EDGE_DISTANCE)
        {
			aCurrentCursor = Window::CURSOR_IDC_SIZEWE;
			aCursor = Cursor::RESIZE_SIZE_WEST_EAST;
            aWinMoveRes = true;
        }
        //right border
        else if (x < right && x >= right - A2D_WINDOW_RESIZE_EDGE_DISTANCE &&
            y >= top + A2D_WINDOW_RESIZE_EDGE_DISTANCE &&
            y < bottom - A2D_WINDOW_RESIZE_EDGE_DISTANCE)
        {
			aCurrentCursor = Window::CURSOR_IDC_SIZEWE;
			aCursor = Cursor::RESIZE_SIZE_WEST_EAST;
            aWinMoveRes = false;
        }
        //bottom border
        else if (y < bottom && y >= bottom - A2D_WINDOW_RESIZE_EDGE_DISTANCE  &&
            x >= left + A2D_WINDOW_RESIZE_EDGE_DISTANCE &&
            x < right - A2D_WINDOW_RESIZE_EDGE_DISTANCE)
        {
			aCurrentCursor = Window::CURSOR_IDC_SIZENS;
			aCursor = Cursor::RESIZE_NORTH_SOUTH;
            aWinMoveRes = false;
        }
        //top border
        else if (y >= top && y < top + A2D_WINDOW_RESIZE_EDGE_DISTANCE  &&
            x >= left + A2D_WINDOW_RESIZE_EDGE_DISTANCE &&
            x < right - A2D_WINDOW_RESIZE_EDGE_DISTANCE)
        {
			aCurrentCursor = Window::CURSOR_IDC_SIZENS;
			aCursor = Cursor::RESIZE_NORTH_SOUTH;
            aWinMoveRes = true;
        }
        //default
        else
        {
			aCurrentCursor = Window::CURSOR_IDC_ARROW;
			aCursor = Cursor::NORMAL;
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
        float deltm_y, deltm_x;

        GetCursorPos(&p);
        ScreenToClient(xHwnd, &p);

        aOffsetY = deltm_y = SFLOAT(aLastDraggedPoint.y - p.y);
        aOffsetX = deltm_x = SFLOAT(aLastDraggedPoint.x - p.x);
        
        if (aOffsetY < -2000.0f)
        {
            aOffsetY = 0.0f;
            deltm_y = 0.0f;
        }
        
        memcpy(&aLastRect, &aRect, sizeof(Rect));

        // Process resizing.
        if (aIsResizing)
        {
			switch (aCursor)
			{
				case Cursor::RESIZE_NORTH_SOUTH:
				{
					if (aWinMoveRes)
					{
						if (rect.m_height + deltm_y >= aMinDims.m_height &&
							rect.m_height + deltm_y < aMaxDims.m_height)
						{
							rect.m_y -= (deltm_y);
							rect.m_height += (deltm_y);
							p.y += SLONG(deltm_y);
							aFramebufferInterpolation = true;
						}
					}
					else
					{
						rect.m_height -= (rect.m_height - deltm_y >= aMinDims.m_height) && (rect.m_height - deltm_y < aMaxDims.m_height) ? SFLOAT(deltm_y) : 0;
					}

					break;
				}
				case Cursor::RESIZE_SIZE_WEST_EAST:
				{
					// Resize left and right.
					if (aWinMoveRes)
					{
						if (rect.m_width + deltm_x >= aMinDims.m_width &&
							rect.m_width + deltm_x < aMaxDims.m_width)
						{
							rect.m_x -= (deltm_x);
							rect.m_width += (deltm_x);
							p.x += SLONG(deltm_x);
							aFramebufferInterpolation = true;
						}
					}
					else
					{
						rect.m_width -= (rect.m_width - deltm_x >= aMinDims.m_width) && (rect.m_width - deltm_x < aMaxDims.m_width) ? SFLOAT(deltm_x) : 0;
					}

					break;
				}
				case Cursor::RESIZE_NORTH_EAST_SOUTH_WEST:
				{
					// Resize upper right and lower left corners.
					if (aWinMoveRes)
					{
						rect.m_height -= (rect.m_height - deltm_y >= aMinDims.m_height) && (rect.m_height - deltm_y < aMaxDims.m_height) ? SFLOAT(deltm_y) : 0;
						if (rect.m_width + deltm_x >= aMinDims.m_width &&
							rect.m_width + deltm_x < aMaxDims.m_width)
						{
							rect.m_x -= (deltm_x);
							rect.m_width += (deltm_x);
							p.x += SLONG(deltm_x);
							aFramebufferInterpolation = true;

						}
					}
					else
					{
						rect.m_width -= (rect.m_width - deltm_x >= aMinDims.m_width) && (rect.m_width - deltm_x < aMaxDims.m_width) ? SFLOAT(deltm_x) : 0;
						if (rect.m_height + deltm_y >= aMinDims.m_height &&
							rect.m_height + deltm_y < aMaxDims.m_height)
						{
							rect.m_y -= (deltm_y);
							rect.m_height += (deltm_y);
							p.y += SLONG(deltm_y);
							aFramebufferInterpolation = true;
						}
					}
					break;
				}
				case Cursor::RESIZE_NORTH_WEST_SOUTH_EAST:
				{	// Resize upper left and lower right corners.
					if (aWinMoveRes)
					{
						if (rect.m_width + deltm_x >= aMinDims.m_width &&
							rect.m_width + deltm_x < aMaxDims.m_width)
						{
							rect.m_x -= (deltm_x);
							rect.m_width += (deltm_x);
							p.x += SLONG(deltm_x);
							aFramebufferInterpolation = true;
						}
						if (rect.m_height + deltm_y >= aMinDims.m_height &&
							rect.m_height + deltm_y < aMaxDims.m_height)
						{
							rect.m_y -= (deltm_y);
							rect.m_height += (deltm_y);
							p.y += SLONG(deltm_y);
							aFramebufferInterpolation = true;
						}

					}
					else
					{
						rect.m_width -= (rect.m_width - deltm_x >= aMinDims.m_width) && (rect.m_width - deltm_x < aMaxDims.m_width) ? SFLOAT(deltm_x) : 0;
						rect.m_height -= (rect.m_height - deltm_y >= aMinDims.m_height) && (rect.m_height - deltm_y < aMaxDims.m_height) ? SFLOAT(deltm_y) : 0;
					}

					break;
				}
			}

            // DEFER REGION //

            render();

            // DEFER REGION //

        }
        // Process window movement.
        else if (aIsMoving)
        {
            rect.m_x -= deltm_x;
            rect.m_y -= deltm_y;
            p.x +=SLONG(deltm_x);
            p.y +=SLONG(deltm_y); 

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
    // FIXME Why is this here? Why would Dragged be set to false
    // and the rest of the variables be true?
    aIsDragged = false;

    // FIXME Why is this here? Doesn't this mean that the remaining
    // things inside the code is not done?
    if (aHResizeWnd != xHwnd && aHMoveWnd != xHwnd)
    {
        return 0;
    }

    // Release accurate mouse capture
    ReleaseCapture();
    
    // Give one more render request to ensure the 
    // child comes into view again.
    if (aIsResizing && aFramebufferInterpolation)
    {
        // Mark as disabled so that the child is forced
        // back onto the screen.
        aFramebufferInterpolation = false;
        render();
    }

    // Disable everything
    aIsResizing = false;
    aIsMoving = false;

    // Disable StretchBilt
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
    
    graphics.DrawImage(src, 0.0f, 0.0f, srcX, srcY, srcWidth, srcHeight, Gdiplus::UnitPixel);
    graphics.DrawImage(src, 0.0f, 0.0f, srcX, srcY, srcWidth, srcHeight, Gdiplus::UnitPixel); // Render twice to increase opacity
    graphics.DrawImage(src, 0.0f, 0.0f, srcX, srcY, srcWidth, srcHeight, Gdiplus::UnitPixel); // Render twice to increase opacity
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

            ca = SINT(a + 0.5f);
            cr = SINT(r + 0.5f);
            cg = SINT(g + 0.5f);
            cb = SINT(b + 0.5f);

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

    float radius = aOptShadowRadius;
    float radiusSafety = radius * A2D_WINDOW_BOX_SHADOW_SAFELYTY_RATIO;
    float realDim = radius * 3;
    float relativeDim = realDim + radius * 2;

    int radiusAsInt = SINT(radius);
    int radiusSafetyAsInt = SINT(radiusSafety);
    int relativeDimAsInt = SINT(relativeDim);

    aTopLeftShadow = new Gdiplus::Bitmap(radiusSafetyAsInt, radiusSafetyAsInt, PixelFormat32bppPARGB);
    aBottomLeftShadow = new Gdiplus::Bitmap(radiusSafetyAsInt, radiusSafetyAsInt, PixelFormat32bppPARGB);
    aTopRightShadow = new Gdiplus::Bitmap(radiusSafetyAsInt, radiusSafetyAsInt, PixelFormat32bppPARGB);
    aBottomRightShadow = new Gdiplus::Bitmap(radiusSafetyAsInt, radiusSafetyAsInt, PixelFormat32bppPARGB);

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

    spliceToNinePatch(blurred, aTopLeftShadow, 0.0f, 0.0f, radiusSafety, radiusSafety);
    spliceToNinePatch(blurred, aBottomLeftShadow, 0.0f, relativeDim - radiusSafety, radiusSafety, radiusSafety);
    spliceToNinePatch(blurred, aBottomRightShadow, relativeDim - radiusSafety, relativeDim - radiusSafety, radiusSafety, radiusSafety);
    spliceToNinePatch(blurred, aTopRightShadow, relativeDim - radiusSafety, 0.0f, radiusSafety, radiusSafety);

    spliceToNinePatch(blurred, aTopShadow, radiusSafety, 0.0f, 1.0f, radius);
    spliceToNinePatch(blurred, aLeftShadow, 0.0f, radiusSafety, radius, 1.0f);
    spliceToNinePatch(blurred, aRightShadow, relativeDim - radius, radiusSafety, radius, 1.0f);
    spliceToNinePatch(blurred, aBottomShadow, radiusSafety, relativeDim - radius, 1.0f, radius);

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
    float padding = aPadding;
    float optBorderWidth = aOptBorderWidth;
    float realWidth = aRealWidth;
    float realHeight = aRealHeight;

    Gdiplus::Color& borderColor = *aBorderColor;
    Gdiplus::Pen borderPen(borderColor, optBorderWidth);

    graphics.DrawRectangle(&borderPen, padding + optBorderWidth / 2, padding + optBorderWidth / 2, aRealWidth + optBorderWidth, realHeight + optBorderWidth);
}

void Window::paintComponent(Gdiplus::Graphics& graphics)
{
    float padding = aPadding;
    float optBorderWidth = aOptBorderWidth;
    float shadowPadding = aShadowPadding;
    float relativeWidth = aRelativeWidth;
    float relativeHeight = aRelativeHeight;
    float realWidth = aRealWidth;
    float realHeight = aRealHeight;

    Gdiplus::TextureBrush * topShadowBrush = aTopShadowBrush;
    Gdiplus::TextureBrush * leftShadowBrush = aLeftShadowBrush;
    Gdiplus::TextureBrush * rightShadowBrush = aRightShadowBrush;
    Gdiplus::TextureBrush * bottomShadowBrush = aBottomShadowBrush;
    Gdiplus::TextureBrush * backgroundBrush = aBackgroundBrush;
	
	topShadowBrush->ResetTransform();
    topShadowBrush->TranslateTransform(shadowPadding, 0.0f);
    graphics.FillRectangle(topShadowBrush, shadowPadding, 0.0f, relativeWidth - shadowPadding * 2, padding);

	leftShadowBrush->ResetTransform();
    leftShadowBrush->TranslateTransform(0.0f, shadowPadding);
    graphics.FillRectangle(leftShadowBrush, 0.0f, shadowPadding, padding, relativeHeight - shadowPadding * 2);

	rightShadowBrush->ResetTransform();
    rightShadowBrush->TranslateTransform(relativeWidth - padding, shadowPadding);
    graphics.FillRectangle(rightShadowBrush, relativeWidth - padding, shadowPadding, padding, relativeHeight - shadowPadding * 2);

	bottomShadowBrush->ResetTransform();
    bottomShadowBrush->TranslateTransform(shadowPadding, relativeHeight - padding);
    graphics.FillRectangle(bottomShadowBrush, shadowPadding, relativeHeight - padding, relativeWidth - shadowPadding * 2, padding);

	graphics.DrawImage(aTopLeftShadow, 0.0f, 0.0f);
	graphics.DrawImage(aBottomLeftShadow, 0.0f, relativeHeight - shadowPadding);
	graphics.DrawImage(aTopRightShadow, relativeWidth - shadowPadding, 0.0f);
	graphics.DrawImage(aBottomRightShadow, relativeWidth - shadowPadding, relativeHeight - shadowPadding);

    // ## THIS IS A VERY SLOW PROCESS
    //graphics.FillRectangle(backgroundBrush, padding, padding, realWidth + optBorderWidth, realHeight + optBorderWidth);
}

////////////////////////////////////////////////////////////////////////////////
// ABSTRACTWINDOW
////////////////////////////////////////////////////////////////////////////////

void Window::setName(wchar_t * xName)
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
        aRect.m_x = (GetSystemMetrics(SM_CXSCREEN) - aRect.m_width) / 2;
        aRect.m_y = (GetSystemMetrics(SM_CYSCREEN) - aRect.m_height) / 2;
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
    aMinDims.m_width = xSize->m_width;
    aMinDims.m_height = xSize->m_height;
}

void Window::setMaximumSize(Dims * xSize)
{
    aMaxDims.m_width = xSize->m_width;
    aMaxDims.m_height = xSize->m_height;
}

void Window::setSize(Dims * xSize)
{
    aRect.m_width = xSize->m_width;
    aRect.m_height = xSize->m_height;
}

void Window::setMinimumSize(float xWidth, float xHeight)
{
    aMinDims.m_width = xWidth;
    aMinDims.m_height = xHeight;
}

void Window::setMaximumSize(float xWidth, float xHeight)
{
    aMaxDims.m_width = xWidth;
    aMaxDims.m_height = xHeight;
}

void Window::setSize(float xWidth, float xHeight)
{
    aRect.m_width = xWidth;
    aRect.m_height = xHeight;
}

void Window::setBorderWidth(float xBorderWidth)
{
    aOptBorderWidth = xBorderWidth;
}

void Window::setShadowRadius(float xShadowRadius)
{
    aOptShadowRadius = xShadowRadius;
}

void Window::setShadow(Color * xShadowColor, float xShadowRadius)
{
    aOptShadowColor = *xShadowColor;
    aOptShadowRadius = xShadowRadius;
}

void Window::setBorder(Color * xBorderColor, float xBorderWidth)
{
    aOptBorderColor = *xBorderColor;
    aOptBorderWidth = xBorderWidth;
}

void Window::setBounds(Rect * xRect)
{
    aRect.m_width = xRect->m_width;
    aRect.m_x = xRect->m_x;
    aRect.m_y = xRect->m_y;
    aRect.m_height = xRect->m_height;
}

void Window::setBounds(float xLeft, float xTop, float xWidth, float xHeight)
{
    aRect.m_width = xWidth;
    aRect.m_x = xLeft;
    aRect.m_y = xTop;
    aRect.m_height = xHeight;
}

void Window::validate()
{
    // Minimum dimensions has to be greater than border and shadow safety region
    aMinDims.m_width = max__((aOptShadowRadius * A2D_WINDOW_BOX_SHADOW_SAFELYTY_RATIO) + ((aOptBorderWidth * 2) + 1), aMinDims.m_width);
    aMinDims.m_height = max__((aOptShadowRadius * A2D_WINDOW_BOX_SHADOW_SAFELYTY_RATIO) + ((aOptBorderWidth * 2) + 1), aMinDims.m_height);

    // Minimum dimensions has to be greater than or equal to minimum size
    aMaxDims.m_width = max__(aMinDims.m_width, aMaxDims.m_width);
    aMaxDims.m_height = max__(aMinDims.m_height, aMaxDims.m_height);

    // Constrain the rect to between min and max
    aRect.m_width = min__(max__(aMinDims.m_width, aRect.m_width), aMaxDims.m_width);
    aRect.m_height = min__(max__(aMinDims.m_height, aRect.m_height), aMaxDims.m_height);

    // Create resize window pointer.
    aHResizeWnd = aOptBorderWidth < A2D_WINDOW_RESIZE_DEFAULT_DISTANCE ? aChildHWnd : aParentHWnd;
    aHMoveWnd = aOptBorderWidth < A2D_WINDOW_MOVE_DEFAULT_DISTANCE ? aChildHWnd : aParentHWnd;

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

    setShadowRadius(0.0f);
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
    //------------------------------------------------------------------------------
    float padding = aPadding;
    float optBorderWidth = aOptBorderWidth;

    float realX = aRealX = aRect.m_x + aOptBorderWidth;
    float realY = aRealY = aRect.m_y + aOptBorderWidth;
    float realWidth = aDrawableRegion.m_width = aRealWidth = aRect.m_width - aOptBorderWidth * 2;
    float realHeight = aDrawableRegion.m_height = aRealHeight = aRect.m_height - aOptBorderWidth * 2;
    float relativeX = aRelativeX = aRect.m_x - aPadding;
    float relativeY = aRelativeY = aRect.m_y - aPadding;
    float relativeWidth = aRelativeWidth = aRect.m_width + aPadding * 2;
    float relativeHeight = aRelativeHeight = aRect.m_height + aPadding * 2;

    // Paint options
    //------------------------------------------------------------------------------
    bool flickerRemoval = true, highPerformance = false;

    if (!highPerformance)
    {
        SIZE size = {SLONG(relativeWidth),SLONG(relativeHeight) };
        HDC memDCChild = NULL, hwndDC = GetDC(aParentHWnd), memDC = CreateCompatibleDC(hwndDC);
        POINT ptDst = {SLONG(relativeX),SLONG(relativeY) }, ptSrc = { 0, 0 };

        if (flickerRemoval)
		{
            // Request copy of frameBuffer
			memDCChild = GetDC(aChildHWnd);
        }

        // Create Bitmap to render to
        //------------------------------------------------------------------------------
        HBITMAP memBitmap = CreateCompatibleBitmap(hwndDC, SINT(relativeWidth), SINT(relativeHeight));
        SelectObject(memDC, memBitmap);
        Gdiplus::Graphics graphics(memDC);

        // Apply highspeed settings for GDI+
        //------------------------------------------------------------------------------
        graphics.SetCompositingMode(Gdiplus::CompositingModeSourceCopy);
        graphics.SetCompositingQuality(Gdiplus::CompositingQualityHighSpeed);
        graphics.SetPixelOffsetMode(Gdiplus::PixelOffsetModeNone);
        graphics.SetSmoothingMode(Gdiplus::SmoothingModeNone);
        graphics.SetInterpolationMode(Gdiplus::InterpolationModeDefault);

        // Paint the component
        //------------------------------------------------------------------------------
        paintComponent(graphics);        

        // Paint from frameBuffer of the child HWND into the 
        // the parent HWND
        //------------------------------------------------------------------------------
        if (flickerRemoval)
        {
			SetStretchBltMode(memDC, BLACKONWHITE);

            StretchBlt(memDC,
                SINT(aOptBorderWidth + aPadding),
                SINT(aOptBorderWidth + aPadding),
                SINT(realWidth),
                SINT(realHeight),
                memDCChild,
                0, 0,
                SINT(aLastRect.m_width - aOptBorderWidth * 2 + (aOffsetX < 0 ? aOffsetX : 0)),
                SINT(aLastRect.m_height - aOptBorderWidth * 2 + (aOffsetY < 0 ? aOffsetY : 0)),
                SRCCOPY);

            DeleteObject(memDCChild);
		}

		// Paint the component border
		//------------------------------------------------------------------------------
		if (aOptBorderWidth > 0)
		{
			paintComponentBorder(graphics);
		}
        
        // Blend function required for UpdateLayeredWindow and updat the data
        //------------------------------------------------------------------------------
        BLENDFUNCTION blendFunction = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };

        UpdateLayeredWindow(aParentHWnd, hwndDC, &ptDst, &size, memDC, &ptSrc, 0, &blendFunction, ULW_ALPHA);

        // Release and destroy objects
        //------------------------------------------------------------------------------
        graphics.ReleaseHDC(memDC);
        DeleteObject(memBitmap);
        ReleaseDC(aParentHWnd, memDC);
        ReleaseDC(aParentHWnd, hwndDC);
        DeleteDC(hwndDC);
        DeleteDC(memDC);
    }

    HDWP hdwp = BeginDeferWindowPos(2);
    
    DeferWindowPos(hdwp, aParentHWnd, NULL, SINT(relativeX), SINT(relativeY), SINT(relativeWidth), SINT(relativeHeight), SWP_NOCOPYBITS);
    DeferWindowPos(hdwp, aChildHWnd, aParentHWnd, SINT(realX), SINT(realY) - ((aFramebufferInterpolation && flickerRemoval) ? 3000 : 0), SINT(realWidth), SINT(realHeight), SWP_NOCOPYBITS | SWP_NOREDRAW);

    EndDeferWindowPos(hdwp);
}

void Window::updateLocation()
{
    float relativeX = aRelativeX = aRect.m_x - aPadding;
    float relativeY = aRelativeY = aRect.m_y - aPadding;
    float realX = aRealX = aRect.m_x + aOptBorderWidth;
    float realY = aRealY = aRect.m_y + aOptBorderWidth;

    HDWP hdwp = BeginDeferWindowPos(2);

    DeferWindowPos(hdwp, aParentHWnd, NULL, SINT(relativeX), SINT(relativeY), 0, 0, SWP_NOSIZE);
    DeferWindowPos(hdwp, aChildHWnd, aParentHWnd, SINT(realX), SINT(realY), 0, 0, SWP_NOSIZE);

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