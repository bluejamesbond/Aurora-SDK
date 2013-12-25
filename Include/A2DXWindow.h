////////////////////////////////////////////////////////////////////////////////

#ifndef __A2DXWindow_H__
#define __A2DXWindow_H__

//+-----------------------------------------------------------------------------
//
//  Class:
//      A2DXWindow
//
//  Synopsis:
//      Custom LINUX/UNIX implmentation of A2DXWindow
//
//------------------------------------------------------------------------------


////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////
#include "A2DFrame.h"
#include "A2DAbstract.h"
#include "A2DRect.h"
#include "A2DAbstractWindow.h"

////////////////////////////////////////////////////////////////////////////////
// FORWARD DECLARATIONS
////////////////////////////////////////////////////////////////////////////////

class A2DFrame;
class A2DAbstract;
class A2DXWindow;
class A2DAbstractWindow;

////////////////////////////////////////////////////////////////////////////////
// DECLARATIONS
////////////////////////////////////////////////////////////////////////////////
#define HRESULT int 
#define S_OK 0
#define E_FAIL 1
#define FAILED(x) !x

typedef struct
{
    unsigned long flags;
    unsigned long functions;
    unsigned long decorations;
    long input_mode;
    unsigned long status;
} MotifWmHints;

////////////////////////////////////////////////////////////////////////////////
// DECLARATIONS
////////////////////////////////////////////////////////////////////////////////

using namespace Gdiplus;

class A2DXWindow : public A2DAbstractWindow     //Xlib implemntation of Window, extends AbstractWindow
{

protected:

    A2DDims                         aMinDims;
    A2DDims                         aMaxDims;   //Max and Min Dimensions of Window (what determines this? why necessary?)

    float                           aOptShadowRadius;
    float                           aOptBorderWidth;    //Shadow's set radius, Border's set width

    Color                           aOptBorderColor;
    Color                           aOptBackgroundColor;
    Color                           aOptShadowColor;    //Set Color vectors (need to confirm that Color is a type in Xlib)

    int                             aDefaultCloseOperation; //set type of close operation

    bool                            aVisible;   
    bool                            aShadowed;
    bool                            aUndecorated;   //sets if visible, if shadowed, or if undecorated (what does that mean?)
        
    LPCWSTR                         aName;          //name of window

    A2DRect                         aRect;          //rect enclosure of window (diff. from Dims how?)
    A2DAbstractFrame          *     aFrame;         //Frame overarching object (controller)
    A2DXWindow                *     aRelativeWindow;    //related window (not sure what relationship)

private:

    bool                            aValidatedContents;     //whether contents are valid
    Display*                        aDis;
    Window                          aWin;
    A2DDims                         aCurrentSize;
    PFNGLATTACHSHADERPROC glAttachShader;
    PFNGLBINDBUFFERPROC glBindBuffer;
    PFNGLBINDVERTEXARRAYPROC glBindVertexArray;
    PFNGLBUFFERDATAPROC glBufferData;
    PFNGLCOMPILESHADERPROC glCompileShader;
    PFNGLCREATEPROGRAMPROC glCreateProgram;
    PFNGLCREATESHADERPROC glCreateShader;
    PFNGLDELETEBUFFERSPROC glDeleteBuffers;
    PFNGLDELETEPROGRAMPROC glDeleteProgram;
    PFNGLDELETESHADERPROC glDeleteShader;
    PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays;
    PFNGLDETACHSHADERPROC glDetachShader;
    PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
    PFNGLGENBUFFERSPROC glGenBuffers;
    PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
    PFNGLGETATTRIBLOCATIONPROC glGetAttribLocation;
    PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
    PFNGLGETPROGRAMIVPROC glGetProgramiv;
    PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
    PFNGLGETSHADERIVPROC glGetShaderiv;
    PFNGLLINKPROGRAMPROC glLinkProgram;
    PFNGLSHADERSOURCEPROC glShaderSource;
    PFNGLUSEPROGRAMPROC glUseProgram;
    PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
    PFNGLBINDATTRIBLOCATIONPROC glBindAttribLocation;
    PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
    PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv;
    PFNGLACTIVETEXTUREPROC glActiveTexture;
    PFNGLUNIFORM1IPROC glUniform1i;
    PFNGLGENERATEMIPMAPPROC glGenerateMipmap;
    PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray;
    PFNGLUNIFORM3FVPROC glUniform3fv;
    PFNGLUNIFORM4FVPROC glUniform4fv;

////////////////////////////////////////////////////////////////////////////////
// PLATFORM COMPATIBLE IMPLEMENTATION
////////////////////////////////////////////////////////////////////////////////

protected:

    virtual void                    render();
    virtual void                    validate();
    virtual void              *     getPlatformCompatibleWindowHandle(); 

public:

    virtual void                    setMinimumSize(A2DDims * xSize);
    virtual void                    setMaximumSize(A2DDims * xSize);
    virtual void                    setSize(A2DDims * xSize);
    virtual void                    setMinimumSize(float xWidth, float xHeight);
    virtual void                    setMaximumSize(float xWidth, float xHeight);
    virtual void                    setSize(float xWidth, float xHeight);
    virtual void                    setName(LPCWSTR xName);
    virtual void                    setUndecorated(bool xUndecoratedFlag);
    virtual void                    setDefaultCloseOperation(int xCloseOperation);
    virtual void                    setLocationRelativeTo(A2DXWindow * xWindow);
    virtual void                    setVisible(bool xVisible);
    virtual void                    setShadowed(bool xShadowFlag);
    virtual void                    setBorderColor(Color xBorderColor);
    virtual void                    setShadowRadius(float xShadowRadius);
    virtual void                    setShadowColor(Color xShadowColor);
    virtual void                    setBackgroundColor(Color xBackgroundColor);
    virtual void                    setBorderWidth(float xBorderWidth);
    virtual void                    setBorder(Color xBorderColor, float xBorderWidth);
    virtual void                    setShadow(Color xShadowColor, float xShadowRadius);

public:

    virtual HRESULT                 Initialize();
    virtual void                    Deinitialize();
    virtual LPCWSTR                 GetClass();
    virtual LPCWSTR                 ToString();
    virtual bool                    operator==(A2DAbstract * xAbstract);

};

#endif
