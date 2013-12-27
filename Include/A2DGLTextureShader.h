////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __A2DGLTEXTURESHADER_H__
#define __A2DGLTEXTURESHADER_H__

//+-----------------------------------------------------------------------------
//
//  Class: 
//      A2DGLTextureShader
//
//  Synopsis:
//      Texture quad.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "A2DExtLibs.h"
#include "A2DGLAbstractShader.h"
#include "A2DGLTexture.h"

////////////////////////////////////////////////////////////////////////////////
// FORWARD DECLARATIONS
////////////////////////////////////////////////////////////////////////////////

class A2D;
class A2DAbstract;

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

class A2DGLTextureShader : public A2DGLAbstractShader
{
public:
        A2DGLTextureShader(A2DGLBackBuffer * xBackBuffer);
        ~A2DGLTextureShader();

/*        ID3D10EffectMatrixVariable        *        aWorldMatrixPtr;
        ID3D10EffectMatrixVariable        *        aViewMatrixPtr;
        ID3D10EffectMatrixVariable        *        aProjectionMatrixPtr;
        ID3D10EffectShaderResourceVariable*        aTexturePtr;
        ID3D10EffectScalarVariable        *        aScreenHeightPtr;
        ID3D10EffectScalarVariable        *        aScreenWidthPtr;
*/
        virtual HRESULT                                     CreateResources(void * xArgs[]);
        virtual void                                        Update(void * xArgs[]);
        virtual void                                        DestroyResources();

public:

        //////////////////////////////////////////////////////////
        // A2DABSTRACT IMPLEMENTATION
        //////////////////////////////////////////////////////////

        virtual LPCWSTR                                     GetClass();
        virtual LPCWSTR                                     ToString();
        virtual bool                                        operator==(A2DAbstract * xAbstract);
};



#endif