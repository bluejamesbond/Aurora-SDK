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
#include "A2DCommon.h"

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

protected:

    A2DDims                         aMinDims;
    A2DDims                         aMaxDims;

    float                           aOptShadowRadius;
    float                           aOptBorderWidth;

    Color                           aOptBorderColor;
    Color                           aOptBackgroundColor;
    Color                           aOptShadowColor;

    int                             aDefaultCloseOperation;

    bool                            aVisible;
    bool                            aShadowed;
    bool                            aUndecorated;
	
	LPCWSTR							aName;

    A2DRect                         aRect;
	A2DAbstractFrame          *     aFrame;
    A2DAbstractWindow         *     aRelativeWindow;

public:

    void                            update();
    A2DDims                   *     getMinimumSize();
    A2DDims                   *     getMaximumSize();
    A2DRect                   *     getBounds();
    LPCWSTR                         getName(); 
	A2DAbstractFrame          *     getFrame();
    bool                            isUndecorated();
    int                             getDefaultCloseOperation();
    A2DAbstractWindow         *     getLocationRelativeTo();
    bool                            isVisible();
    bool                            isShadowed();
    Color                           getBorderColor();
    float                           getShadowRadius();
    Color                           getShadowColor();
    Color                           getBackgroundColor();
    float                           getBorderWidth();
	void                            setFrame(A2DAbstractFrame * xFrame);
	void							renderGX();
	void							createGXResources();

////////////////////////////////////////////////////////////////////////////////
// PLATFORM COMPATIBLE IMPLEMENTATION
////////////////////////////////////////////////////////////////////////////////

protected:

	virtual void                    render() = 0;

public:

    virtual void              *     getPlatformCompatibleWindowHandle() = 0;

public:

    virtual void                    setMinimumSize(A2DDims * xSize) = 0;
    virtual void                    setMaximumSize(A2DDims * xSize) = 0;
    virtual void                    setName(LPCWSTR xName) = 0;
    virtual void                    setUndecorated(bool xUndecoratedFlag) = 0;
    virtual void                    setDefaultCloseOperation(int xCloseOperation) = 0;
    virtual void                    setLocationRelativeTo(A2DAbstractWindow * xWindow) = 0;
    virtual void                    setVisible(bool xVisible) = 0;
    virtual void                    setShadowed(bool xShadowFlag) = 0;
    virtual void                    setBorderColor(Color xBorderColor) = 0;
    virtual void                    setShadowRadius(float xShadowRadius) = 0;
    virtual void                    setShadowColor(Color xShadowColor) = 0;
    virtual void                    setBackgroundColor(Color xShadowColor) = 0;
    virtual void                    setBorderWidth(float xBorderWidth) = 0;

public:

    virtual HRESULT                 Initialize() = 0;
    virtual void                    Deinitialize() = 0;
    virtual LPCWSTR                 GetClass() = 0;
    virtual LPCWSTR                 ToString() = 0;
    virtual bool                    operator==(A2DAbstract * xAbstract) = 0;

};

#endif