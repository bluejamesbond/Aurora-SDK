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
#include "Abstract.h"
#include "Rect.h"
#include "Color.h"
#include "Common.h"
#include "AbstractEventQueue.h"
#include "EventSource.h"

#include "WindowListener.h"

namespace A2D {

	////////////////////////////////////////////////////////////////////////////////
	// FORWARD DECLARATIONS
	////////////////////////////////////////////////////////////////////////////////

	class AbstractFrame;
	class EventSource;
	class WindowEvent;

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

	class AbstractWindow : public EventSource
	{

	public:

		AbstractWindow(AbstractFrame * xFrame);

	protected:

		Dims                         aMinDims;
		Dims                         aMaxDims;

		float                           aOptShadowRadius;
		float                           aOptBorderWidth;

		Color                        aOptBorderColor;
		Color                        aOptBackgroundColor;
		Color                        aOptShadowColor;

		int                             aDefaultCloseOperation;

		bool                            aVisible;
		bool                            aShadowed;
		bool                            aUndecorated;

		LPCWSTR							aName;

		Rect                         aRect;
		AbstractFrame          *     aFrame = NULL;
		AbstractWindow         *     aRelativeWindow;

	private:

		bool							aValidatedContents;

	public:

		void                            update();
		void							invalidate();
		void							revalidate();

	protected:

		void							validated();

	public:

		Dims					  *		_getSize(); // internal use only
		Dims							getMinimumSize();
		Dims							getMaximumSize();
		Rect							getBounds();
		Dims					  		getSize();
		LPCWSTR                         getName();
		AbstractFrame			  *     getFrame();
		bool                            isUndecorated();
		int                             getDefaultCloseOperation();
		AbstractWindow			  *     getLocationRelativeTo();
		bool                            isVisible();
		bool                            isShadowed();
		Color							getBorderColor();
		float                           getShadowRadius();
		Color							getShadowColor();
		Color							getBackgroundColor();
		float                           getBorderWidth();

		// Window Events/Listeners
		friend							AbstractEventQueue;
		HRESULT							processWindowEvent(WindowEvent * xEvent);
		HRESULT							addWindowListener(WindowListener * xListener);
		Rect					  *		getEventRegion();

	protected:

		virtual HRESULT					addListener(AbstractListener * xListener);
		virtual HRESULT					removeListener(AbstractListener * xListener);

		WindowEvent					*	aWindowOpened = 0;
		WindowEvent					*	aWindowClosed = 0;
		WindowEvent					*	aWindowActivated = 0;
		WindowEvent					*	aWindowDeactivated = 0;

		int								aCurrentState = 0;

		////////////////////////////////////////////////////////////////////////////////
		// PLATFORM COMPATIBLE IMPLEMENTATION
		////////////////////////////////////////////////////////////////////////////////

	protected:

		virtual void                    render() = 0;
		virtual void					validate() = 0;

	public:

		virtual void              *     getPlatformCompatibleWindowHandle() = 0;
		virtual void			  		initPlatformCompatibleEventDispatcher(AbstractEventQueue * xEventQueue) = 0;

	public:

		virtual void                    setMinimumSize(Dims * xSize) = 0;
		virtual void                    setMaximumSize(Dims * xSize) = 0;
		virtual void					setBounds(Rect * xRect) = 0;
		virtual void					setBounds(float xLeft, float xtop, float xWidth, float xHeight) = 0;
		virtual void					setSize(Dims * xSize) = 0;
		virtual void                    setMinimumSize(float xWidth, float xHeight) = 0;
		virtual void                    setMaximumSize(float xWidth, float xHeight) = 0;
		virtual void					setSize(float xWidth, float xHeight) = 0;
		virtual void                    setName(LPCWSTR xName) = 0;
		virtual void                    setUndecorated(bool xUndecoratedFlag) = 0;
		virtual void                    setDefaultCloseOperation(int xCloseOperation) = 0;
		virtual void                    setLocationRelativeTo(AbstractWindow * xWindow) = 0;
		virtual void                    setVisible(bool xVisible) = 0;
		virtual void                    setShadowed(bool xShadowFlag) = 0;
		virtual void                    setBorderColor(Color * xBorderColor) = 0;
		virtual void                    setShadowRadius(float xShadowRadius) = 0;
		virtual void                    setShadowColor(Color * xShadowColor) = 0;
		virtual void                    setBackgroundColor(Color * xShadowColor) = 0;
		virtual void                    setBorderWidth(float xBorderWidth) = 0;
		virtual void					setBorder(Color * xBorderColor, float xBorderWidth) = 0;
		virtual void					setShadow(Color * xShadowColor, float xShadowRadius) = 0;

	public:

		virtual HRESULT                 initialize();
		virtual LPCWSTR                 getClass() = 0;
		virtual LPCWSTR                 toString() = 0;

	};
}

#endif