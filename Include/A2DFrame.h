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

#include "A2DAbstract.h"
#include "A2DWindow.h"
#include "A2DMSWindow.h"
#include "A2DRect.h"
#include "A2DDims.h"

////////////////////////////////////////////////////////////////////////////////
// FORWARD DECLARATIONS
////////////////////////////////////////////////////////////////////////////////

class	A2DAbstract;
class	A2DRect;
class	A2DDims;

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

	#ifdef _WIN32

	A2DWindow<HWND, LPCWSTR>  *     aWindow;

	#elif __UNIX

	A2DWindow<WINDOWX, STRING>  *     aWindow;

	#endif

    // Accessors
    // { NONE }

public:

    // Mutators
	void							SetVisible(bool xVisibility);
	void							SetName(LPCWSTR xName);									// Set window name
	void							SetBounds(A2DRect * xRect);									// Edits A2DPreferences#WindowProperties via float
	void							SetBounds(float xLeft, float xTop, float xWidth, float xHeight);    // Edits A2DPreferences#WindowProperties via Rect
	void							SetSize(float xWidth, float xHeight);							// Edits A2DPreferences#WindowProperties float
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
    // { NONE }

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
