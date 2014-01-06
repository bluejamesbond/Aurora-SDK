////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __A2DGLTEXTURE_H__
#define __A2DGLTEXTURE_H__

//+-----------------------------------------------------------------------------
//
//  Class:  
//      A2DGLTexture
//
//  Synopsis:
//      Texture container class.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "A2DRenderData.h"
#include "A2DGLBackBuffer.h"
#include "A2DGLAbstractTexture.h"
#include "A2DRect.h"

////////////////////////////////////////////////////////////////////////////////
// FORWARD DECLARATIONS
////////////////////////////////////////////////////////////////////////////////

class A2D;
class A2DAbstract;
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

class A2DGLTexture : public A2DGLAbstractTexture
{
public:
        // Constructor
        A2DGLTexture(A2DGLBackBuffer * xBackBuffer, LPCWSTR * xFilename);

        // Deconstructor
        ~A2DGLTexture();

        // Variables
        char                                        *                aSrc;

        // Accessors
        char                                        *                GetSrc();

        // Mutators
        // { NONE }

        // Builders
        // { NONE }

        // Factory
        // { NONE }

        // Additional

        // Pure Virtual
        // { NONE }

        // Virtual
        virtual        bool                                        HasAlpha();

public:

        // Implementation
        // { A2DABSTRACTTEXTURE }
        virtual HRESULT                                        CreateResources(void * xArgs[]);
        virtual void                                        Update(void * xArgs[]);
        virtual void                                        DestroyResources() {};

public:
        // Implementation
        // { A2DABSTRACT }
        virtual LPCWSTR                 GetClass();
        virtual LPCWSTR                 ToString();
        virtual bool                    operator==(A2DAbstract * xAbstract);

};


#endif