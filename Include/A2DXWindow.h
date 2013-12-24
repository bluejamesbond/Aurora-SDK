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

typedef struct
{
    unsigned long flags;
    unsigned long functions;
    unsigned long decorations;
    long input_mode;
    unsigned long status;
} MotifWmHints;

typedef BOOL (WINAPI * PFNWGLCHOOSEPIXELFORMATARBPROC) (HDC hdc, const int *piAttribIList, const FLOAT *pfAttribFList, UINT nMaxFormats, int *piFormats, UINT *nNumFormats);
typedef HGLRC (WINAPI * PFNWGLCREATECONTEXTATTRIBSARBPROC) (HDC hDC, HGLRC hShareContext, const int *attribList);
typedef BOOL (WINAPI * PFNWGLSWAPINTERVALEXTPROC) (int interval);
typedef void (APIENTRY * PFNGLATTACHSHADERPROC) (GLuint program, GLuint shader);
typedef void (APIENTRY * PFNGLBINDBUFFERPROC) (GLenum target, GLuint buffer);
typedef void (APIENTRY * PFNGLBINDVERTEXARRAYPROC) (GLuint array);
typedef void (APIENTRY * PFNGLBUFFERDATAPROC) (GLenum target, ptrdiff_t size, const GLvoid *data, GLenum usage);
typedef void (APIENTRY * PFNGLCOMPILESHADERPROC) (GLuint shader);
typedef GLuint (APIENTRY * PFNGLCREATEPROGRAMPROC) (void);
typedef GLuint (APIENTRY * PFNGLCREATESHADERPROC) (GLenum type);
typedef void (APIENTRY * PFNGLDELETEBUFFERSPROC) (GLsizei n, const GLuint *buffers);
typedef void (APIENTRY * PFNGLDELETEPROGRAMPROC) (GLuint program);
typedef void (APIENTRY * PFNGLDELETESHADERPROC) (GLuint shader);
typedef void (APIENTRY * PFNGLDELETEVERTEXARRAYSPROC) (GLsizei n, const GLuint *arrays);
typedef void (APIENTRY * PFNGLDETACHSHADERPROC) (GLuint program, GLuint shader);
typedef void (APIENTRY * PFNGLENABLEVERTEXATTRIBARRAYPROC) (GLuint index);
typedef void (APIENTRY * PFNGLGENBUFFERSPROC) (GLsizei n, GLuint *buffers);
typedef void (APIENTRY * PFNGLGENVERTEXARRAYSPROC) (GLsizei n, GLuint *arrays);
typedef GLint (APIENTRY * PFNGLGETATTRIBLOCATIONPROC) (GLuint program, const char *name);
typedef void (APIENTRY * PFNGLGETPROGRAMINFOLOGPROC) (GLuint program, GLsizei bufSize, GLsizei *length, char *infoLog);
typedef void (APIENTRY * PFNGLGETPROGRAMIVPROC) (GLuint program, GLenum pname, GLint *params);
typedef void (APIENTRY * PFNGLGETSHADERINFOLOGPROC) (GLuint shader, GLsizei bufSize, GLsizei *length, char *infoLog);
typedef void (APIENTRY * PFNGLGETSHADERIVPROC) (GLuint shader, GLenum pname, GLint *params);
typedef void (APIENTRY * PFNGLLINKPROGRAMPROC) (GLuint program);
typedef void (APIENTRY * PFNGLSHADERSOURCEPROC) (GLuint shader, GLsizei count, const char* *string, const GLint *length);
typedef void (APIENTRY * PFNGLUSEPROGRAMPROC) (GLuint program);
typedef void (APIENTRY * PFNGLVERTEXATTRIBPOINTERPROC) (GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid *pointer);
typedef void (APIENTRY * PFNGLBINDATTRIBLOCATIONPROC) (GLuint program, GLuint index, const char *name);
typedef GLint (APIENTRY * PFNGLGETUNIFORMLOCATIONPROC) (GLuint program, const char *name);
typedef void (APIENTRY * PFNGLUNIFORMMATRIX4FVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (APIENTRY * PFNGLACTIVETEXTUREPROC) (GLenum texture);
typedef void (APIENTRY * PFNGLUNIFORM1IPROC) (GLint location, GLint v0);
typedef void (APIENTRY * PFNGLGENERATEMIPMAPPROC) (GLenum target);
typedef void (APIENTRY * PFNGLDISABLEVERTEXATTRIBARRAYPROC) (GLuint index);
typedef void (APIENTRY * PFNGLUNIFORM3FVPROC) (GLint location, GLsizei count, const GLfloat *value);
typedef void (APIENTRY * PFNGLUNIFORM4FVPROC) (GLint location, GLsizei count, const GLfloat *value);
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
