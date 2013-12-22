////////////////////////////////////////////////////////////////////////////////
// GUARDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __A2DNATIVEWINDOW_H__
#define __A2DNATIVEWINDOW_H__

//+-----------------------------------------------------------------------------
//
//  Abstract Class:
//      A2DNATIVEWINDOW
//
//  Synopsis:
//      Abstract Class to allow cross-patform implementation of A2DNativeWindow. 
//      Currently compatible with Windows and Linux.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "A2DAbstract.h"
#include "A2DRect.h"
#include "A2DCommon.h"

////////////////////////////////////////////////////////////////////////////////
// FORWARD DECLARATIONS
////////////////////////////////////////////////////////////////////////////////
class A2DFrame;
class A2D;
class A2DAbstract;
class A2DRenderable;
class A2DAbstractComponent;
class A2DCamera;
struct A2DCameraProperties;
struct A2DRenderData;
class A2DBackBuffer;
class A2DMatrixFactory;
class A2DModelFactory;
class A2DRootPane;
class A2DImagePanel;

////////////////////////////////////////////////////////////////////////////////
// DEFINE
////////////////////////////////////////////////////////////////////////////////

#define HNWND	HWND
#define HSTRING	LPCWSTR

////////////////////////////////////////////////////////////////////////////////
// DECLARATION
////////////////////////////////////////////////////////////////////////////////

using namespace Gdiplus;

class A2DNativeWindow : public A2DAbstract
{

public:

    // Constructor
    // A2DNativeWindow(); // <-- WILL ALWAYS CENTER THE WINDOW FOR NOW
        //A2DCPInstanceHWnd will be defined later as custom type for HINSTANCE + linux type
    // Deconstructor
    // ~A2DNativeWindow(); 

protected:

    // Variables


    /*********************************************************************/
    /*                                OPTIONS                            */
    /*********************************************************************/
    A2DDims                         aMinDims;
    A2DDims                         aMaxDims;

    float                           aOptBoxShadowRadius;
    float                           aOptBorderWidth;

    Color                           aOptBorderColor;
    Color                           aOptBackgroundColor;
    Color                           aOptBoxShadowColor;

protected:

    // Variables - NOTE: No need to use the acronym aOpt since variables are PRIVATE!
    int                             aDefaultCloseOperation;

    bool                            aVisible;
    bool                            aShadowed;
    bool                            aUndecorated;
    
    HNWND                           aHNWnd;
    HSTRING                         aName;
        
    A2DFrame                  *     aFrame;

    A2DNativeWindow                 *     aRelativeWindow;

    A2DRect                         aRect;

public:

    // Accessors and mutators
    // These don't need mutators because we are giving direct access to the structs

    virtual void                            setMinimumSize(A2DDims * xSize);
    virtual A2DDims                   *     getMinimumSize();
    virtual void                            setMaximumSize(float xWidth, float xHeight);
    virtual A2DDims                   *     getMaximumSize();

    virtual A2DRect                   *     getBounds();

    // Accessing internal variables. Do not provide mutators for these.
    virtual HNWND                           getHNWnd();

    virtual HSTRING                         getName(); // Fix this, should we use pointer or not?
    virtual void                            setName(HSTRING xName); // Fix this, should we use pointer or not?

    virtual A2DFrame                  *     getFrame(); // GET
    virtual void                            setFrame(A2DFrame * xFrame); // SET

    virtual bool                            isUndecorated(); // Get
    virtual void                            setUndecorated(bool xUndecoratedFlag); // SET

    virtual int                             getDefaultCloseOperation();
    virtual void                            setDefaultCloseOperation(int xCloseOperation);

    virtual void                            setLocationRelativeTo(A2DNativeWindow * xWindow);

    virtual bool                            isVisible();
    virtual void                            setVisible(bool xVisible);

    virtual bool                            isShadowed();
    virtual void                            setShadowed(bool xShadowFlag);

    virtual Color                           getBorderColor();
    virtual void                            setBorderColor(Color xBorderColor);

    virtual float                           getBoxShadowRadius();
    virtual void                            setBoxShadowRadius(float xBoxShadowRadius); //overloaded in mswindow + lin

    virtual Color                           getBoxShadowColor();
    virtual void                            setBoxShadowColor(Color xBoxShadowColor);

    virtual Color                           getBackgroundColor();
    virtual void                            setBackgroundColor(Color xBoxShadowColor);

    // Additional
    virtual void                            Update();
    void                                    Render(); 
    virtual void                            RenderComponent() = 0;
    virtual void                            RenderComponentBorder() = 0;
    virtual HRESULT                         CreateResources() = 0;
    virtual void                            DestroyResources() = 0;
    virtual void                            updateAndCacheBoxShadow()=0;
    virtual void                            UpdateAndCacheBackground()=0;

    // Implementation
    // { A2DABSTRACT }
    virtual HRESULT                         Initialize() = 0;
    virtual void                            Deinitialize() = 0;
    virtual LPCWSTR                         GetClass() = 0;
    virtual LPCWSTR                         ToString() = 0;
    virtual bool                            operator==(A2DAbstract * xAbstract) = 0;

protected:
    virtual void                            setBorderWidth(float xBorderWidth);
    virtual float                           getBorderWidth();
};

#endif