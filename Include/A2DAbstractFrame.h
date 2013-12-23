////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __A2DABSTRACTFRAME_H__
#define __A2DABSTRACTFRAME_H__

//+-----------------------------------------------------------------------------
//
//  Class:
//      A2DABSTRACTFRAME
//
//  Synopsis:
//      Differentiates which of the two possible arcs could match the given arc
//      parameters.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "A2DAbstract.h"
#include "A2DGraphics.h"
#include "A2DRenderable.h"
#include "A2DAbstractComponent.h"
#include "A2DPipelineable.h"
#include "A2DAbstractTexture.h"
#include "A2DComponent.h"
#include "A2DPanel.h"
#include "A2DCamera.h"
#include "A2DCameraProperties.h"
#include "A2DRenderData.h"
#include "A2DBackBuffer.h"
#include "A2DMatrixFactory.h"
#include "A2DRootPane.h"
#include "A2DAbstractWindow.h"
#include "A2DGXSettings.h"
#include "A2DRect.h"

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

////////////////////////////////////////////////////////////////////////////////
// DECLARATION
////////////////////////////////////////////////////////////////////////////////

class A2DAbstractFrame : public A2DAbstract
{
	
private:

    A2DRootPane               *     aRootPane;
	A2DBackBuffer             *     aBackBuffer;
	A2DTextureBuffer          *     aTextureBuffer;
	A2DTextureBuffer          *     aBlurBuffer;
    A2DCamera                 *     aCamera;
    A2DRenderData             *     aRenderData;
	A2DGXSettings			  		aGXSettings;
	A2DAbstractWindow	  	  * 	aWindow;

public:

	LRESULT							PumpWindowMsg(HWND * xHwnd, UINT * xMessage, WPARAM * xWParam, LPARAM * xLParam);

	A2DRootPane               *     GetRootPane();
	A2DCamera                 *     GetCamera();
	A2DRenderData             *     GetRenderData();

	HRESULT                         CreateResources();
	void                            Update();

	void							SetVisible(bool xVisibility);
	void							SetName(LPCWSTR  xName);
	void							SetBounds(A2DRect * xRect);
	void							SetBounds(float xLeft, float xTop, float xWidth, float xHeight);
	void							SetSize(float xWidth, float xHeight);
	void							SetSize(A2DDims * xDims);
	void							SetUndecorated(bool xDecorated);
	void							SetLocationRelativeTo(A2DAbstractFrame * xFrame);
	void							SetVsync(bool xVsync);
	void							SetDefaultCloseOperation(int xOperation);

////////////////////////////////////////////////////////////////////////////////
// PLATFORM COMPATIBLE IMPLEMENTATION
////////////////////////////////////////////////////////////////////////////////

protected:

	virtual A2DAbstractWindow *		createPlatformCompatibleWindow() = 0;

////////////////////////////////////////////////////////////////////////////////
// A2DABSTRACT
////////////////////////////////////////////////////////////////////////////////

public:

	virtual HRESULT                 Initialize();
	virtual void                    Deinitialize();
	virtual LPCWSTR                 GetClass();
	virtual LPCWSTR                 ToString();
	virtual bool                    operator==(A2DAbstract * xAbstract);

};

#endif
