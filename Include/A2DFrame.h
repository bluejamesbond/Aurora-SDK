////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __A2DFRAME_H__
#define __A2DFRAME_H__

//+-----------------------------------------------------------------------------
//
//  Class:
//      A2DFRAME
//
//  Synopsis:
//      Differentiates which of the two possible arcs could match the given arc
//      parameters.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "A2DGraphics.h"
#include "A2DAbstract.h"
#include "A2DRenderable.h"
#include "A2DAbstractComponent.h"
#include "A2DPipelineComponent.h"
#include "A2DAbstractTexture.h"
#include "A2DComponent.h"
#include "A2DPanel.h"
#include "A2DCamera.h"
#include "A2DCameraProperties.h"
#include "A2DRenderData.h"
#include "A2DBackBuffer.h"
#include "A2DMatrixFactory.h"
#include "A2DRootPane.h"
#include "A2DWindow.h"
#include "A2DGXSettings.h"

////////////////////////////////////////////////////////////////////////////////
// FORWARD DECLARATIONS
////////////////////////////////////////////////////////////////////////////////

class	A2DAbstract;
class	A2DRenderable;
class	A2DAbstractComponent;
class	A2DCamera;
struct	A2DCameraProperties;
struct	A2DRenderData;
class	A2DMatrixFactory;
class	A2DBackBuffer;
struct	A2DBufferData;
class	A2DMatrixFactory;
class	A2DRootPane;
class	A2DWindow;

////////////////////////////////////////////////////////////////////////////////
// DEFINE
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// DECLARATION
////////////////////////////////////////////////////////////////////////////////

class A2DFrame : public A2DAbstract
{

public:
    
    // Constructor
	A2DFrame(HINSTANCE  xHInstance);

    // Deconstructor
	~A2DFrame();

private:

    // Variables
	HINSTANCE				  		aHInstance;
    A2DRootPane               *     aRootPane;
	A2DBackBuffer             *     aBackBuffer;
	A2DTextureBuffer          *     aTextureBuffer;
	A2DTextureBuffer          *     aBlurBuffer;
	A2DWindow                 *     aWindow;
    A2DCamera                 *     aCamera;
    A2DRenderData             *     aRenderData;
	A2DGXSettings			  		aGXSettings;

    // Accessors
    // { NONE }

public:

    // Mutators
	void							SetVisible(bool xVisibility);
	void							SetName(LPCWSTR  xName);									// Set window name
	void							SetBounds(A2DRect * xRect);									// Edits A2DPreferences#WindowProperties via float
	void							SetBounds(int xLeft, int xTop, int xWidth, int xHeight);    // Edits A2DPreferences#WindowProperties via Rect
	void							SetSize(int xWidth, int xHeight);							// Edits A2DPreferences#WindowProperties float
	void							SetSize(A2DDims * xDims);									// Edits A2DPreferences#WindowProperties via Dim
	void							SetUndecorated(bool xDecorated);							// Back to switching thing now...lol
	void							SetLocationRelativeTo(A2DFrame * xFrame);					// NULL means just center it. Dont worry about other cases.
	void							SetVsync(bool xVsync);										// A2DPreferences#WindowProperties + Set default values for these (A2DCommons.h), but can be edited by user during runtime.
	void							SetDefaultCloseOperation(int xOperation);					// Close the whole application on disposing of frame (Look at Java#JFrame)

public:

    // Builders
    // { NONE }

    // Factory
    // { NONE }

public:
	// Additional
	LRESULT							PumpWindowMsg(HWND * xHwnd, UINT * xMessage, WPARAM * xWParam, LPARAM * xLParam);

public:

    // Accessors
    A2DRootPane               *     GetRootPane();
    A2DCamera                 *     GetCamera();
    A2DRenderData             *     GetRenderData();

public:

    // Additional
	HRESULT                         CreateResources();
	void                            Update();

    // Pure Virtual
    // { NONE }

    // Virtual
    // { NONE }

public:

    // Implementation
    // { A2DABSTRACT }
    virtual HRESULT                 Initialize();
    virtual void                    Deinitialize();
    virtual LPCWSTR                 GetClass();
    virtual LPCWSTR                 ToString();
    virtual bool                    operator==(A2DAbstract * xAbstract);

};

#endif
