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

#include "../_A2DCommon.h"

#include "ExtLibs.h"
#include "Rect.h"
#include "Color.h"
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

		float                        aOptShadowRadius;
		float                        aOptBorderWidth;

		Color                        aOptBorderColor;
		Color                        aOptBackgroundColor;
		Color                        aOptShadowColor;

		int                          aDefaultCloseOperation;

		bool                         aVisible;
		bool                         aShadowed;
		bool                         aUndecorated;

		wchar_t *					 aName;

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

		const Dims&				  		getSizeAsPtr(); // internal use only
		Dims&					  		getDrawableRegionAsPtr(); // internal use only
		Dims							getMinimumSize();
		Dims							getMaximumSize();
		Rect							getBounds();
		Dims					  		getSize();
		wchar_t *                       getName();
		AbstractFrame		   *		getFrame();
		bool                            isUndecorated();
		int                             getDefaultCloseOperation();
		AbstractWindow         *		getLocationRelativeTo();
		bool                            isVisible();
		bool                            isShadowed();
		Color							getBorderColor();
		float                           getShadowRadius();
		Color							getShadowColor();
		Color							getBackgroundColor();
		float                           getBorderWidth();

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

		virtual void                    render() IMPLEMENT;
		virtual void					validate() IMPLEMENT;
		virtual void              *     getPlatformCompatibleWindowHandle() IMPLEMENT;
		virtual void			  		initPlatformCompatibleEventDispatcher(AbstractEventQueue * xEventQueue) IMPLEMENT;

	public:

		virtual void                    setMinimumSize(Dims * xSize) IMPLEMENT;
		virtual void                    setMaximumSize(Dims * xSize) IMPLEMENT;
		virtual void					setBounds(Rect * xRect) IMPLEMENT;
		virtual void					setBounds(float xLeft, float xtop, float xWidth, float xHeight) IMPLEMENT;
		virtual void					setSize(Dims * xSize) IMPLEMENT;
		virtual void                    setMinimumSize(float xWidth, float xHeight) IMPLEMENT;
		virtual void                    setMaximumSize(float xWidth, float xHeight) IMPLEMENT;
		virtual void					setSize(float xWidth, float xHeight) IMPLEMENT;
		virtual void                    setName(wchar_t * xName) IMPLEMENT;
		virtual void                    setUndecorated(bool xUndecoratedFlag) IMPLEMENT;
		virtual void                    setDefaultCloseOperation(int xCloseOperation) IMPLEMENT;
		virtual void                    setLocationRelativeTo(AbstractWindow * xWindow) IMPLEMENT;
		virtual void                    setVisible(bool xVisible) IMPLEMENT;
		virtual void                    setShadowed(bool xShadowFlag) IMPLEMENT;
		virtual void                    setBorderColor(Color * xBorderColor) IMPLEMENT;
		virtual void                    setShadowRadius(float xShadowRadius) IMPLEMENT;
		virtual void                    setShadowColor(Color * xShadowColor) IMPLEMENT;
		virtual void                    setBackgroundColor(Color * xShadowColor) IMPLEMENT;
		virtual void                    setBorderWidth(float xBorderWidth) IMPLEMENT;
		virtual void					setBorder(Color * xBorderColor, float xBorderWidth) IMPLEMENT;
		virtual void					setShadow(Color * xShadowColor, float xShadowRadius) IMPLEMENT;

	public:

		virtual STATUS                 initialize();

	};
}

#endif