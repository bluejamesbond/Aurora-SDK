////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __XWINDOW_H__
#define __XWINDOW_H__

//+-----------------------------------------------------------------------------
//
//  Class:
//      XWindow
//
//  Synopsis:
//      Differentiates which of the two possible arcs could match the given arc
//      parameters.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

//#include "ExtLibs.h"
#include "../GLXExtLibs.h"
//#include "EventQueue.h"
#include "../Common.h"
#include "../Abstract.h"
#include "../Rect.h"
#include "../Dims.h"
#include "../AbstractWindow.h"

namespace A2D {

	////////////////////////////////////////////////////////////////////////////////
	// FORWARD DECLARATIONS
	////////////////////////////////////////////////////////////////////////////////

	class Frame;
	class Abstract;

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

	class XWindow : public AbstractWindow
	{

		////////////////////////////////////////////////////////////////////////////////
		// PLATFORM COMPATIBLE IMPLEMENTATION
		////////////////////////////////////////////////////////////////////////////////

	public:

		Window(AbstractFrame * xFrame, HINSTANCE  xHInstance);

		~Window();

	protected:

        Window                          aChildHWnd;
        Window                          aWin;
        Display*                        aDis;
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
/*
		Gdiplus::Color					  * 	aBorderColor = NULL;
		Gdiplus::Color					  * 	aBackgroundColor = NULL;
		Gdiplus::Color					  *	    aShadowColor = NULL;

		Gdiplus::Image                     *     aTopShadow = NULL;
		Gdiplus::Image                     *     aLeftShadow = NULL;
		Gdiplus::Image                     *     aRightShadow = NULL;
		Gdiplus::Image                     *     aBottomShadow = NULL;
		Gdiplus::Image                     *     aTopLeftShadow = NULL;
		Gdiplus::Image                     *     aBottomLeftShadow = NULL;
		Gdiplus::Image                     *     aTopRightShadow = NULL;
		Gdiplus::Image                     *     aBottomRightShadow = NULL;
		Gdiplus::Image                     *     aBackground = NULL;

		Gdiplus::TextureBrush              *     aTopShadowBrush = NULL;
		Gdiplus::TextureBrush              *     aLeftShadowBrush = NULL;
		Gdiplus::TextureBrush              *     aRightShadowBrush = NULL;
		Gdiplus::TextureBrush              *     aBottomShadowBrush = NULL;
		Gdiplus::TextureBrush              *     aBackgroundBrush = NULL;

		Gdiplus::Graphics                  *     aGraphics = NULL;

		HINSTANCE                       aHInstance;
		HWND                            aHResizeWnd;
		HWND                            aParentHWnd;
		HCURSOR                         aCurrentCursor;
		POINT                           aLastDraggedPoint;
*/
		Dims							aMinSafeDims;

		static int						aClassInstances;

		std::wstring				*	aClassName;

	public:

//		static LRESULT CALLBACK         wndProc(HWND xHwnd, UINT xMessage, WPARAM xWParam, LPARAM xLParam);

	private:

        Window                     createCompatibleWindow(bool isParent);
		HRESULT                         createBackgroundResources();
		HRESULT                         createShadowResources();
		HRESULT                         createColorResources();

//		ATOM	                        registerClass();

		HRESULT                         updateOnMouseDown(HWND xHwnd);
		HRESULT                         updateOnMouseMove(HWND xHwnd);
		HRESULT                         updateOnMouseUp(HWND xHwnd);

		void                            destroyBackgroundResources();
		void                            destroyShadowResources();
		void                            destroyColorResources();

//		void                            spliceToNinePatch(Gdiplus::Image * src, Gdiplus::Image * dest, float srcX, float srcY, float srcWidth, float srcHeight);
//		float                     *     getGaussianKernel(int xRadius);
//		void                            applyHorizontalblur(Gdiplus::BitmapData * srcPixels, Gdiplus::BitmapData * dstPixels, float * kernel, int radius);
//		Gdiplus::Bitmap           *     applyGaussianBlur(Gdiplus::Bitmap * src, int radius);
//		Gdiplus::BitmapData       *     getLockedBitmapData(Gdiplus::Bitmap * src);

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

		virtual HRESULT                 initialize();
		virtual LPCWSTR                 getClass();
		virtual LPCWSTR                 toString();

	};
}
#endif
