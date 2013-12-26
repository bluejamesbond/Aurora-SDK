////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __A2DGLABSTRACTSHADER_H__
#define __A2DGLABSTRACTSHADER_H__

//+-----------------------------------------------------------------------------
//
//  Class: 
//      A2DGLAbstractShader
//
//  Synopsis:
//      Texture quad.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "A2DExtLibs.h"
#include "A2DPipelineable.h"
#include "A2DGLBackBuffer.h"

////////////////////////////////////////////////////////////////////////////////
// FORWARD DECLARATIONS
////////////////////////////////////////////////////////////////////////////////

class A2D;
class A2DAbstract;
class A2DPipelineable;

////////////////////////////////////////////////////////////////////////////////
// DEFINE
////////////////////////////////////////////////////////////////////////////////

#define HRESULT int 
#define S_OK 0
#define E_FAIL 1
#define FAILED(x) !x

////////////////////////////////////////////////////////////////////////////////
// DECLARATION
////////////////////////////////////////////////////////////////////////////////

class A2DGLAbstractShader : public A2DPipelineable
{
public:

    A2DGLAbstractShader(A2DGLBackBuffer * xBackBuffer);

    ~A2DGLAbstractShader();

protected:
        // Variables
 
protected:

    GLuint                                   LoadShaders(const char * vertex_file_path,const char * fragment_file_path);
    //Before the main loop, call our LoadShaders function 
    //then tell opengl to use our shader glUseProgram(programID);
    //then draw triangle
    virtual HRESULT                          CreateResources(void * xArgs[]);
    virtual void                             Render(); // Render should be defined seperately but called inside Update
    HRESULT                                  LoadFromFile(LPCWSTR  xFilename);
    HRESULT                                  CreateBlendStates();
    void                                     SysOut(ID3D10Blob * xErrorMessage, LPCWSTR * xFilename);

//////////////////////////////////////////////////////////
// A2DABSTRACT IMPLEMENTATION
//////////////////////////////////////////////////////////

public:

    virtual HRESULT                          Initialize();
    virtual void                             Deinitialize();
    virtual LPCWSTR                          GetClass();
    virtual LPCWSTR                          ToString();
    virtual bool                             operator==(A2DAbstract * xAbstract);

};

#endif