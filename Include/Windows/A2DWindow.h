////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __WINDOW_H__
#define __WINDOW_H__

//+-----------------------------------------------------------------------------
//
//  Class:
//      WINDOW
//
//  Synopsis:
//      Differentiates which of the two possible arcs could match the given arc
//      parameters.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "ExtLibs.h"
#include "EventQueue.h"
#include "../Common.h"
#include "../Abstract.h"
#include "../Rect.h"
#include "../Dims.h"
#include "../AbstractWindow.h"

////////////////////////////////////////////////////////////////////////////////
// FORWARD DECLARATIONS
////////////////////////////////////////////////////////////////////////////////

class Frame;
class Abstract;

////////////////////////////////////////////////////////////////////////////////
// DECLARATION
////////////////////////////////////////////////////////////////////////////////

using namespace Gdiplus;

class Window : public AbstractWindow
{

	////////////////////////////////////////////////////////////////////////////////
	// PLATFORM COMPATIBLE IMPLEMENTATION
	////////////////////////////////////////////////////////////////////////////////

public:

	Window(AbstractFrame * xFrame, HINSTANCE  xHInstance);

	~Window();

private:

	int                             aStyle;

	float                           aPadding;
	float                           aShadowPadding;

	float                           aRealX = 0;
	float                           aRealY = 0;
	float                           aRealWidth = 0;
	float                           aRealHeight = 0;

	float                           aRelativeX = 0;
	float                           aRelativeY = 0;
	float                           aRelativeWidth = 0;
	float                           aRelativeHeight = 0;

	bool                            isDragged = false;
	bool                            isResizing = false;
	bool                            aWinMoveRes = false;

	Color					  * 	aBorderColor = NULL;
	Color					  * 	aBackgroundColor = NULL;
	Color					  *	    aShadowColor = NULL;

	Image                     *     aTopShadow = NULL;
	Image                     *     aLeftShadow = NULL;
	Image                     *     aRightShadow = NULL;
	Image                     *     aBottomShadow = NULL;
	Image                     *     aTopLeftShadow = NULL;
	Image                     *     aBottomLeftShadow = NULL;
	Image                     *     aTopRightShadow = NULL;
	Image                     *     aBottomRightShadow = NULL;
	Image                     *     aBackground = NULL;

	TextureBrush              *     aTopShadowBrush = NULL;
	TextureBrush              *     aLeftShadowBrush = NULL;
	TextureBrush              *     aRightShadowBrush = NULL;
	TextureBrush              *     aBottomShadowBrush = NULL;
	TextureBrush              *     aBackgroundBrush = NULL;

	Graphics                  *     aGraphics = NULL;

	HINSTANCE                       aHInstance;
	HWND                            aHResizeWnd;
	HWND                            aParentHWnd;
	HWND                            aChildHWnd;
	HCURSOR                         aCurrentCursor;
	POINT                           aLastDraggedPoint;

	Dims                         aMinSafeDims;

	static int						aClassInstances;

	std::wstring				*	aClassName;

public:

	static LRESULT CALLBACK         wndProc(HWND xHwnd, UINT xMessage, WPARAM xWParam, LPARAM xLParam);
	
private:

	HWND                            createCompatibleWindow(bool isParent);
	HRESULT                         createBackgroundResources();
	HRESULT                         createShadowResources();
	HRESULT                         createColorResources();

	HRESULT                         registerClass();

	HRESULT                         updateOnMouseDown(HWND xHwnd);
	HRESULT                         updateOnMouseMove(HWND xHwnd);
	HRESULT                         updateOnMouseUp(HWND xHwnd);

	void                            destroyBackgroundResources();
	void                            destroyShadowResources();
	void                            destroyColorResources();

	void                            spliceToNinePatch(Image * src, Image * dest, float srcX, float srcY, float srcWidth, float srcHeight);
	float                     *     getGaussianKernel(int xRadius);
	void                            applyHorizontalblur(BitmapData * srcPixels, BitmapData * dstPixels, float * kernel, int radius);
	Bitmap                    *     applyGaussianBlur(Bitmap * src, int radius);
	BitmapData                *     getLockedBitmapData(Bitmap * src);

	void							updateShadowCache();
	void							updateBackgroundCache();
	void							updateColorCache();

	void							renderComponent();
	void							renderComponentBorder();

	HRESULT							createResources();
	void							destroyResources();

	////////////////////////////////////////////////////////////////////////////////
	// ABSTRACTWINDOW
	////////////////////////////////////////////////////////////////////////////////

public:

	virtual void                    setMinimumSize(Dims * xSize);
	virtual void                    setMaximumSize(Dims * xSize);
	virtual void                    setMinimumSize(float xWidth, float xHeight);
	virtual void                    setMaximumSize(float xWidth, float xHeight);
	virtual void					setSize(float xWidth, float xHeight);
	virtual void					setSize(Dims * xSize);
	virtual void					setBounds(Rect * xRect);
	virtual void					setBounds(float xLeft, float xtop, float xWidth, float xHeight);
	virtual void                    setName(LPCWSTR xName);
	virtual void                    setUndecorated(bool xUndecoratedFlag);
	virtual void                    setDefaultCloseOperation(int xCloseOperation);
	virtual void                    setLocationRelativeTo(AbstractWindow * xWindow);
	virtual void                    setVisible(bool xVisible);
	virtual void                    setBorderColor(Color * xBorderColor);
	virtual void                    setBorderWidth(float xBorderWidth);
	virtual void                    setShadowed(bool xShadowFlag);
	virtual void                    setShadowRadius(float xShadowRadius);
	virtual void                    setShadowColor(Color * xShadowColor);
	virtual void                    setBackgroundColor(Color * xBackgroundColor);
	virtual void					setBorder(Color * xBorderColor, float xBorderWidth);
	virtual void					setShadow(Color * xShadowColor, float xShadowRadius);

protected:

	virtual void                    render();
	virtual void					validate();
	HRESULT							onSize(HWND hwnd);
public:

	virtual void              *     getPlatformCompatibleWindowHandle();
	virtual void			  		initPlatformCompatibleEventDispatcher(AbstractEventQueue * xEventQueue);
	
	////////////////////////////////////////////////////////////////////////////////
	// ABSTRACT
	////////////////////////////////////////////////////////////////////////////////

public:

	virtual HRESULT                 Initialize();
	virtual void                    Deinitialize();
	virtual LPCWSTR                 GetClass();
	virtual LPCWSTR                 ToString();
	virtual bool                    operator==(Abstract * xAbstract);

};

#endif
