////////////////////////////////////////////////////////////////////////////////
// GUARDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __A2DABSTRACTWINDOW_H__
#define __A2DABSTRACTWINDOW_H__

//+-----------------------------------------------------------------------------
//
//  Abstract Class:
//      A2DABSTRACTWINDOW
//
//  Synopsis:
//      Abstract Class to allow cross-patform implementation of A2DAbstractWindow. 
//      Currently compatible with Windows and Linux.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "A2DExtLibs.h"
#include "A2DAbstract.h"
#include "A2DRect.h"
#include "A2DColor.h"
#include "A2DCommon.h"
#include "A2DAbstractEventQueue.h"

////////////////////////////////////////////////////////////////////////////////
// FORWARD DECLARATIONS
////////////////////////////////////////////////////////////////////////////////

class A2DAbstractFrame;

////////////////////////////////////////////////////////////////////////////////
// DECLARATION
////////////////////////////////////////////////////////////////////////////////

using namespace Gdiplus;

class A2DAbstractWindow : public A2DAbstract
{
public:

	A2DAbstractWindow(A2DAbstractFrame * xFrame);

protected:

	A2DDims                         aMinDims;
	A2DDims                         aMaxDims;

	float                           aOptShadowRadius;
	float                           aOptBorderWidth;

	A2DColor                        aOptBorderColor;
	A2DColor                        aOptBackgroundColor;
	A2DColor                        aOptShadowColor;

	int                             aDefaultCloseOperation;

	bool                            aVisible;
	bool                            aShadowed;
	bool                            aUndecorated;

	LPCWSTR							aName;

	A2DRect                         aRect;
	A2DAbstractFrame          *     aFrame = NULL;
	A2DAbstractWindow         *     aRelativeWindow;

private:

	bool							aValidatedContents;

public:

	void                            update();
	void							invalidate();
	void							validated();
	void							revalidate();

	A2DDims                         getMinimumSize();
	A2DDims                         getMaximumSize();
	A2DRect                         getBounds();
	A2DDims					  		getSize();
	LPCWSTR                         getName();
	A2DAbstractFrame          *     getFrame();
	bool                            isUndecorated();
	int                             getDefaultCloseOperation();
	A2DAbstractWindow         *     getLocationRelativeTo();
	bool                            isVisible();
	bool                            isShadowed();
	A2DColor                        getBorderColor();
	float                           getShadowRadius();
	A2DColor                        getShadowColor();
	A2DColor                        getBackgroundColor();
	float                           getBorderWidth();

	////////////////////////////////////////////////////////////////////////////////
	// PLATFORM COMPATIBLE IMPLEMENTATION
	////////////////////////////////////////////////////////////////////////////////

protected:

	virtual void                    render() = 0;
	virtual void					validate() = 0;

public:

	virtual void              *     getPlatformCompatibleWindowHandle() = 0;
	virtual void			  		initPlatformCompatibleEventDispatcher(A2DAbstractEventQueue * xEventQueue) = 0;
	
public:

	virtual void                    setMinimumSize(A2DDims * xSize) = 0;
	virtual void                    setMaximumSize(A2DDims * xSize) = 0;
	virtual void					setBounds(A2DRect * xRect) = 0;
	virtual void					setBounds(float xLeft, float xtop, float xWidth, float xHeight) = 0;
	virtual void					setSize(A2DDims * xSize) = 0;
	virtual void                    setMinimumSize(float xWidth, float xHeight) = 0;
	virtual void                    setMaximumSize(float xWidth, float xHeight) = 0;
	virtual void					setSize(float xWidth, float xHeight) = 0;
	virtual void                    setName(LPCWSTR xName) = 0;
	virtual void                    setUndecorated(bool xUndecoratedFlag) = 0;
	virtual void                    setDefaultCloseOperation(int xCloseOperation) = 0;
	virtual void                    setLocationRelativeTo(A2DAbstractWindow * xWindow) = 0;
	virtual void                    setVisible(bool xVisible) = 0;
	virtual void                    setShadowed(bool xShadowFlag) = 0;
	virtual void                    setBorderColor(A2DColor * xBorderColor) = 0;
	virtual void                    setShadowRadius(float xShadowRadius) = 0;
	virtual void                    setShadowColor(A2DColor * xShadowColor) = 0;
	virtual void                    setBackgroundColor(A2DColor * xShadowColor) = 0;
	virtual void                    setBorderWidth(float xBorderWidth) = 0;
	virtual void					setBorder(A2DColor * xBorderColor, float xBorderWidth) = 0;
	virtual void					setShadow(A2DColor * xShadowColor, float xShadowRadius) = 0;

public:

	virtual HRESULT                 Initialize();
	virtual void                    Deinitialize() = 0;
	virtual LPCWSTR                 GetClass() = 0;
	virtual LPCWSTR                 ToString() = 0;
	virtual bool                    operator==(A2DAbstract * xAbstract) = 0;

};

#endif