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
#include "Common.h"
#include "AbstractEventQueue.h"

namespace A2D {

	////////////////////////////////////////////////////////////////////////////////
	// FORWARD DECLARATIONS
	////////////////////////////////////////////////////////////////////////////////

	class AbstractFrame;

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

	class AbstractWindow
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

		LPCWSTR						aName;

		Rect                         aRect;
		AbstractFrame          *     aFrame = NULL;
		AbstractWindow         *     aRelativeWindow;

	private:

		bool							aValidatedContents;

	public:

		void                         update();
		void						 invalidate();
		void						 revalidate();

	protected:

		void							validated();

	public:

		Dims					  *		getSizeAsPtr(); // internal use only
		Dims							getMinimumSize();
		Dims							getMaximumSize();
		Rect							getBounds();
		Dims					  		getSize();
		LPCWSTR                         getName();
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

		////////////////////////////////////////////////////////////////////////////////
		// PLATFORM COMPATIBLE IMPLEMENTATION
		////////////////////////////////////////////////////////////////////////////////

	protected:

        virtual void                    render() = 0;
        virtual void					validate() {}
        virtual void              *     getPlatformCompatibleWindowHandle() = 0;
        virtual void			  		initPlatformCompatibleEventDispatcher(AbstractEventQueue * xEventQueue) {}

	public:

        virtual void                    setMinimumSize(Dims * xSize) {}
        virtual void                    setMaximumSize(Dims * xSize) {}
        virtual void					setBounds(Rect * xRect) {}
        virtual void					setBounds(float xLeft, float xtop, float xWidth, float xHeight) {}
        virtual void					setSize(Dims * xSize) {}
        virtual void                    setMinimumSize(float xWidth, float xHeight) {}
        virtual void                    setMaximumSize(float xWidth, float xHeight) {}
        virtual void					setSize(float xWidth, float xHeight) {}
        virtual void                    setName(LPCWSTR xName) {}
        virtual void                    setUndecorated(bool xUndecoratedFlag) {}
        virtual void                    setDefaultCloseOperation(int xCloseOperation) {}
        virtual void                    setLocationRelativeTo(AbstractWindow * xWindow) {}
        virtual void                    setVisible(bool xVisible) {}
        virtual void                    setShadowed(bool xShadowFlag) {}
        virtual void                    setBorderColor(Color * xBorderColor) {}
        virtual void                    setShadowRadius(float xShadowRadius) {}
        virtual void                    setShadowColor(Color * xShadowColor) {}
        virtual void                    setBackgroundColor(Color * xShadowColor) {}
        virtual void                    setBorderWidth(float xBorderWidth) {}
        virtual void					setBorder(Color * xBorderColor, float xBorderWidth) {}
        virtual void					setShadow(Color * xShadowColor, float xShadowRadius) {}

	public:

		virtual HRESULT                 initialize();

    };
}

#endif
