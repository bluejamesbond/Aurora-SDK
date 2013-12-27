////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __A2DGLTEXTUREBUFFER_H__
#define __A2DGLTEXTUREBUFFER_H__

//+-----------------------------------------------------------------------------
//
//  Struct:
//      A2DGLTEXTUREBUFFER
//
//  Synopsis:
//      Differentiates which of the two possible arcs could match the given arc
//      parameters.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "A2DCommon.h"
#include "A2DVertexData.h"
#include "A2DBackBuffer.h"
#include "A2DGLAbstractTexture.h"
#include "A2DImageProperties.h"
#include "A2DRect.h"

////////////////////////////////////////////////////////////////////////////////
// FORWARD DECLARATIONS
////////////////////////////////////////////////////////////////////////////////

class A2D;
class A2DGLTexture;
class A2DGLAbstractTexture;

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

class A2DGLTextureBuffer : public A2DGLAbstractTexture
{

public:

        // Constructor
        A2DGLTextureBuffer(A2DGLBackBuffer * xBackBuffer, A2DDims * xSize);

        // Deconstructor
        ~A2DGLTextureBuffer();
        
        // Variables
        ID3D10Texture2D                           *        aDXRenderTargetTexture;
        ID3D10RenderTargetView                    *        aDXRenderTargetView;
        ID3D10DepthStencilState                   *        aDXDepthStencilState;

        // Accessors
        virtual bool                                        hasAlpha();

        // Mutators
        void                                                SetActive();

        // Additional
        void                                                Clear();

public:

        // Implementation
        // { A2DABSTRACTTEXTURE }
        virtual HRESULT                                     CreateResources(void * xArgs[]);
        virtual void                                        Update(void * xArgs[]);
        virtual void                                        Render(); // Render should be defined seperately but called inside Update
        virtual void                                        DestroyResources();
        
public:
        // Implementation
        // { A2DABSTRACT }
        virtual LPCWSTR                                     GetClass();
        virtual LPCWSTR                                     ToString();
        virtual bool                                        operator==(A2DAbstract * xAbstract);

};


#endif