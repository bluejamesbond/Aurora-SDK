////////////////////////////////////////////////////////////////////////////////
// GUARDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __ABSTRACTWINDOW_H__
#define __ABSTRACTWINDOW_H__

//+-----------------------------------------------------------------------------
//
//  Abstract Class:
//      ABSTRACTWINDOW
//
//  Synopsis:
//      Abstract Class to allow cross-patform implementation of AbstractWindow. 
//      Currently compatible with Windows and Linux.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "ExtLibs.h"
#include "Rect.h"
#include "Color.h"
#include "../_A2DCommon.h"
#include "AbstractEventQueue.h"
#include "WindowListener.h"
#include "EventSource.h"

namespace A2D {

	////////////////////////////////////////////////////////////////////////////////
	// FORWARD DECLARATIONS
	////////////////////////////////////////////////////////////////////////////////

	class AbstractFrame;

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

	class AbstractWindow : public EventSource
	{
	
		friend class AbstractFrame;
		friend class AbstractEventQueue;
		friend class BackBuffer;

	public:

		AbstractWindow(AbstractFrame * xFrame);

	protected:

		Dims                         aMinDims;
		Dims                         aMaxDims;

		int							 aOptShadowRadius;
		int						     aOptBorderWidth;

		Color                        aOptBorderColor;
		Color                        aOptBackgroundColor;
		Color                        aOptShadowColor;

		int                          aDefaultCloseOperation;

		bool                         aVisible;
		bool                         aShadowed;
		bool                         aUndecorated;

		LPCWSTR						 aName;

		Dims						 aDrawableRegion;
		Rect                         aRect;
		AbstractFrame          *     aFrame = NULL;
		AbstractWindow         *     aRelativeWindow;

	private:

		bool						 aValidatedContents;

	public:

		void                         update();
		void						 invalidate();
		void						 revalidate();

	protected:

		void							validated();

	public:

		Dims&					  		getSizeAsPtr(); // internal use only
		Dims&					  		getDrawableRegionAsPtr(); // internal use only
		Dims							getMinimumSize();
		Dims							getMaximumSize();
		Rect							getBounds();
		Dims					  		getSize();
		LPCWSTR                         getName();
		AbstractFrame		   *		getFrame();
		bool                            isUndecorated();
		int                             getDefaultCloseOperation();
		AbstractWindow         *		getLocationRelativeTo();
		bool                            isVisible();
		bool                            isShadowed();
		Color							getBorderColor();
		int                             getShadowRadius();
		Color							getShadowColor();
		Color							getBackgroundColor();
		int                             getBorderWidth();

		friend							AbstractEventQueue;
		STATUS							processWindowEvent(WindowEvent * xEvent);
		STATUS							addWindowListener(WindowListener * xListener);
		Rect				    *		getEventRegion();

	protected:

		virtual STATUS					addListener(AbstractListener * xListener);
		virtual STATUS					removeListener(AbstractListener * xListener);

		WindowEvent				*		aWindowOpened = 0;
		WindowEvent				*		aWindowClosed = 0;
		WindowEvent				*		aWindowActivated = 0;
		WindowEvent				*		aWindowDeactivated = 0;

		MouseEvent			    *		aMouseDown = 0;
		MouseEvent			    *		aMouseUp = 0;
		MouseEvent			    *		aMouseMove = 0;
		MouseEvent			    * 		aMouseDragged = 0;

		int								aCurrentState = 0;

		////////////////////////////////////////////////////////////////////////////////
		// PLATFORM COMPATIBLE IMPLEMENTATION
		////////////////////////////////////////////////////////////////////////////////

	protected:

		virtual void                    render() = 0;
		virtual void					validate() = 0;
		virtual void              *     getPlatformCompatibleWindowHandle() = 0;
		virtual void			  		initPlatformCompatibleEventDispatcher(AbstractEventQueue * xEventQueue) = 0;

	public:

		virtual void                    setMinimumSize(Dims * xSize) = 0;
		virtual void                    setMaximumSize(Dims * xSize) = 0;
		virtual void					setBounds(Rect * xRect) = 0;
		virtual void					setBounds(int xLeft, int xtop, int xWidth, int xHeight) = 0;
		virtual void					setSize(Dims * xSize) = 0;
		virtual void                    setMinimumSize(int xWidth, int xHeight) = 0;
		virtual void                    setMaximumSize(int xWidth, int xHeight) = 0;
		virtual void					setSize(int xWidth, int xHeight) = 0;
		virtual void                    setName(LPCWSTR xName) = 0;
		virtual void                    setUndecorated(bool xUndecoratedFlag) = 0;
		virtual void                    setDefaultCloseOperation(int xCloseOperation) = 0;
		virtual void                    setLocationRelativeTo(AbstractWindow * xWindow) = 0;
		virtual void                    setVisible(bool xVisible) = 0;
		virtual void                    setShadowed(bool xShadowFlag) = 0;
		virtual void                    setBorderColor(Color * xBorderColor) = 0;
		virtual void                    setShadowRadius(int xShadowRadius) = 0;
		virtual void                    setShadowColor(Color * xShadowColor) = 0;
		virtual void                    setBackgroundColor(Color * xShadowColor) = 0;
		virtual void                    setBorderWidth(int xBorderWidth) = 0;
		virtual void					setBorder(Color * xBorderColor, int xBorderWidth) = 0;
		virtual void					setShadow(Color * xShadowColor, int xShadowRadius) = 0;

	public:

		virtual STATUS                 initialize();

	};
}

#endif