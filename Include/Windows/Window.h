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

#include "../Core/../_A2DCommon.h"
#include "../Core/Rect.h"
#include "../Core/Dims.h"
#include "../Core/AbstractWindow.h"

#include "ExtLibs.h"
#include "EventQueue.h"

namespace A2D {

	////////////////////////////////////////////////////////////////////////////////
	// FORWARD DECLARATIONS
	////////////////////////////////////////////////////////////////////////////////

	class Frame;

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

	class Window : public AbstractWindow
	{
		friend class Component; // remove later if not needed
		////////////////////////////////////////////////////////////////////////////////
		// PLATFORM COMPATIBLE IMPLEMENTATION
		////////////////////////////////////////////////////////////////////////////////

	public:

		Window(AbstractFrame * xFrame, HINSTANCE  xHInstance);

		~Window();
		
	protected:

		HWND                            aChildHWnd;

	private:

		int                             aStyle;

		int							    aPadding;
		int							    aShadowPadding;

		int							     aRealX = 0;
		int							     aRealY = 0;
		int							     aRealWidth = 0;
		int							     aRealHeight = 0;

		int							     aRelativeX = 0;
		int							     aRelativeY = 0;
		int							     aRelativeWidth = 0;
		int							     aRelativeHeight = 0;

		int								aOffsetX = 0;
		int								aOffsetY = 0;

		bool                            aIsDragged = false;
		bool                            aIsResizing = false;
		bool							aIsMoving = false;
		bool                            aWinMoveRes = false;


		bool							aFramebufferInterpolation = false;

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
		
		HINSTANCE                       aHInstance;
		HWND                            aHResizeWnd;
		HWND							aHMoveWnd;
		HWND                            aParentHWnd;
		HCURSOR                         aCurrentCursor;
		POINT                           aLastDraggedPoint;

		Rect							aLastRect;
		Dims							aMinSafeDims;

		static int						aClassInstances;

		std::wstring				*	aClassName;

	public:

		LRESULT							eventHandler(MSG xMsg, AbstractEventQueue * xEventQueue);
		static LRESULT CALLBACK         wndProc(HWND xHwnd, UINT xMessage, WPARAM xWParam, LPARAM xLParam);

	private:

		HWND                            createCompatibleWindow(bool isParent);
		STATUS                         createBackgroundResources();
		STATUS                         createShadowResources();
		STATUS                         createColorResources();

		ATOM	                        registerClass();

		inline STATUS                  updateOnMouseDown(HWND xHwnd);
		inline STATUS                  updateOnMouseMove(HWND xHwnd);
		inline STATUS                  updateOnMouseUp(HWND xHwnd);
		STATUS							onSize(HWND hwnd);

		void                            destroyBackgroundResources();
		void                            destroyShadowResources();
		void                            destroyColorResources();

		void                            spliceToNinePatch(Gdiplus::Image * src, Gdiplus::Image * dest, float srcX, float srcY, float srcWidth, float srcHeight);
		float                     *     getGaussianKernel(int xRadius);
		void                            applyHorizontalblur(Gdiplus::BitmapData * srcPixels, Gdiplus::BitmapData * dstPixels, float * kernel, int radius);
		Gdiplus::Bitmap           *     applyGaussianBlur(Gdiplus::Bitmap * src, int radius);
		Gdiplus::BitmapData       *     getLockedBitmapData(Gdiplus::Bitmap * src);

		void							updateShadowCache();
		void							updateBackgroundCache();
		void							updateColorCache();

		inline void						paintComponent(Gdiplus::Graphics& graphics);
		inline void						paintComponentBorder(Gdiplus::Graphics& graphics);

		STATUS							createResources();
		void							destroyResources();
		void							updateLocation();

		////////////////////////////////////////////////////////////////////////////////
		// ABSTRACTWINDOW
		////////////////////////////////////////////////////////////////////////////////

	public:

		virtual void                    setMinimumSize(Dims * xSize);
		virtual void                    setMaximumSize(Dims * xSize);
		virtual void                    setMinimumSize(int xWidth, int xHeight);
		virtual void                    setMaximumSize(int xWidth, int xHeight);
		virtual void					setSize(int xWidth, int xHeight);
		virtual void					setSize(Dims * xSize);
		virtual void					setBounds(Rect * xRect);
		virtual void					setBounds(int xLeft, int xtop, int xWidth, int xHeight);
		virtual void                    setName(LPCWSTR xName);
		virtual void                    setUndecorated(bool xUndecoratedFlag);
		virtual void                    setDefaultCloseOperation(int xCloseOperation);
		virtual void                    setLocationRelativeTo(AbstractWindow * xWindow);
		virtual void                    setVisible(bool xVisible);
		virtual void                    setBorderColor(Color * xBorderColor);
		virtual void                    setBorderWidth(int xBorderWidth);
		virtual void                    setShadowed(bool xShadowFlag);
		virtual void                    setShadowRadius(int xShadowRadius);
		virtual void                    setShadowColor(Color * xShadowColor);
		virtual void                    setBackgroundColor(Color * xBackgroundColor);
		virtual void					setBorder(Color * xBorderColor, int xBorderWidth);
		virtual void					setShadow(Color * xShadowColor, int xShadowRadius);

	protected:

		virtual void                    render();
		virtual void					validate();
		virtual void              *     getPlatformCompatibleWindowHandle();
		virtual void			  		initPlatformCompatibleEventDispatcher(AbstractEventQueue * xEventQueue);

		////////////////////////////////////////////////////////////////////////////////
		// ABSTRACT
		////////////////////////////////////////////////////////////////////////////////

	public:

		virtual STATUS                 initialize();

	};
}
#endif
