////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __A2DWINDOW_H__
#define __A2DWINDOW_H__

//+-----------------------------------------------------------------------------
//
//  Class:
//      A2DWINDOW
//
//  Synopsis:
//      Differentiates which of the two possible arcs could match the given arc
//      parameters.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "A2DExtLibs.h"
#include "A2DEventQueue.h"
#include "../A2DCommon.h"
#include "../A2DAbstract.h"
#include "../A2DRect.h"
#include "../A2DDims.h"
#include "../A2DAbstractWindow.h"

////////////////////////////////////////////////////////////////////////////////
// FORWARD DECLARATIONS
////////////////////////////////////////////////////////////////////////////////

class A2DFrame;
class A2DAbstract;

////////////////////////////////////////////////////////////////////////////////
// DECLARATION
////////////////////////////////////////////////////////////////////////////////

using namespace Gdiplus;

class A2DWindow : public A2DAbstractWindow
{

	////////////////////////////////////////////////////////////////////////////////
	// PLATFORM COMPATIBLE IMPLEMENTATION
	////////////////////////////////////////////////////////////////////////////////

public:

	A2DWindow(HINSTANCE  xHInstance);

	~A2DWindow();

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

	A2DDims                         aMinSafeDims;

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
	// A2DABSTRACTWINDOW
	////////////////////////////////////////////////////////////////////////////////

public:

	virtual void                    setMinimumSize(A2DDims * xSize);
	virtual void                    setMaximumSize(A2DDims * xSize);
	virtual void                    setMinimumSize(float xWidth, float xHeight);
	virtual void                    setMaximumSize(float xWidth, float xHeight);
	virtual void					setSize(float xWidth, float xHeight);
	virtual void					setSize(A2DDims * xSize);
	virtual void					setBounds(A2DRect * xRect);
	virtual void					setBounds(float xLeft, float xtop, float xWidth, float xHeight);
	virtual void                    setName(LPCWSTR xName);
	virtual void                    setUndecorated(bool xUndecoratedFlag);
	virtual void                    setDefaultCloseOperation(int xCloseOperation);
	virtual void                    setLocationRelativeTo(A2DAbstractWindow * xWindow);
	virtual void                    setVisible(bool xVisible);
	virtual void                    setBorderColor(A2DColor * xBorderColor);
	virtual void                    setBorderWidth(float xBorderWidth);
	virtual void                    setShadowed(bool xShadowFlag);
	virtual void                    setShadowRadius(float xShadowRadius);
	virtual void                    setShadowColor(A2DColor * xShadowColor);
	virtual void                    setBackgroundColor(A2DColor * xBackgroundColor);
	virtual void					setBorder(A2DColor * xBorderColor, float xBorderWidth);
	virtual void					setShadow(A2DColor * xShadowColor, float xShadowRadius);

protected:

	virtual void                    render();
	virtual void					validate();
	virtual A2DAbstractEventQueue*	createPlatformCompatibleEventQueue();

public:

	virtual void              *     getPlatformCompatibleWindowHandle();

	////////////////////////////////////////////////////////////////////////////////
	// A2DABSTRACT
	////////////////////////////////////////////////////////////////////////////////

public:

	virtual HRESULT                 Initialize();
	virtual void                    Deinitialize();
	virtual LPCWSTR                 GetClass();
	virtual LPCWSTR                 ToString();
	virtual bool                    operator==(A2DAbstract * xAbstract);

};

#endif
