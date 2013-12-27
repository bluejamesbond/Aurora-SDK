////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __A2DGLABSTRACTTEXTURE_H__
#define __A2DGLABSTRACTTEXTURE_H__

//+-----------------------------------------------------------------------------
//
//  Class:  
//      A2DGLAbstractTexture
//
//  Synopsis:
//      Texture container class.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "A2DPipelineable.h"
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

class A2DGLAbstractTexture : public A2DPipelineable
{
public:

        A2DGLAbstractTexture(A2DBackBuffer * xBackBuffer);

        ~A2DGLAbstractTexture();

protected:
        // Variables
        A2DBackBuffer                          *        aBackBuffer;

        // Variables
        A2DDims                                         aDims;
        A2DRect                                         aClip;
        unsigned char                          *        aResource; //need this to point instead to loaded texture shader code

public:
        // Accessors
        virtual A2DDims                        *        GetSize();
        virtual A2DRect                        *        GetClip(int xIndex = 0);

        // Mutators
        virtual void                                    SetClip(A2DRect * xClip, int xIndex = 0);

        // Builders
        // { NONE }

        // Factory
        // { NONE }

        // Additional
        // { NONE }

        // Pure Virtual
        // { NONE }

        // Virtual
        ID3D10ShaderResourceView                *       GetResource();
        virtual        bool                             hasAlpha();

public:

        // Implementation
        // { A2DABSTRACTPIPELINECOMPONENT }
        virtual HRESULT                                 CreateResources(void * xArgs[]) = 0;
        virtual void                                    Update(void * xArgs[]) = 0;
        virtual void                                    Render() {};
        virtual void                                    DestroyResources();

public:
        // Implementation
        // { A2DABSTRACT }
        virtual HRESULT                                 Initialize();
        virtual void                                    Deinitialize();
        virtual LPCWSTR                                 GetClass();
        virtual LPCWSTR                                 ToString();
        virtual bool                                    operator==(A2DAbstract * xAbstract);

};

#endif