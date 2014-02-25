////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __ABSTRACTSHADER_H__
#define __ABSTRACTSHADER_H__

//+-----------------------------------------------------------------------------
//
//  Class: 
//      ABSTRACTSHADER
//
//  Synopsis:
//      Uses the DX Effect framework to create a basic system for creating
//      shaders from FX files. This is different from "vanilla" DX.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "../Core/Pipelineable.h"

#include "ExtLibs.h"
#include "DXUtils.h"
#include "Texture.h"
#include "VertexTypes.h"

namespace A2D {

    ////////////////////////////////////////////////////////////////////////////////
    // DECLARATION
    ////////////////////////////////////////////////////////////////////////////////

    class AbstractShader : public Pipelineable
    {
    public:

        AbstractShader(ID3D10Device ** xDevice);
        virtual ~AbstractShader();

    protected:

        // Pull out and cache device
        ID3D10Device                **  aDevice;
        ID3D10EffectTechnique       *   aTechnique;
        ID3D10InputLayout           *   aLayout;
        bool                            aHasAlpha = false;


    private:
        
        static ID3D10BlendState     *   aBlendState;
        static ID3D10BlendState     *   aBlendDisabledState;
        
    public:

        void                            renderShader();

    protected:

        virtual STATUS                  createPolygonLayout(D3D10_INPUT_ELEMENT_DESC ** xPolygonLayout) IMPLEMENT;
        virtual unsigned int            getPolygonLayoutElementCount() IMPLEMENT;
        virtual LPCSTR                  getTechniqueName() IMPLEMENT;
        virtual ID3D10Effect        **  getEffect() IMPLEMENT;
        virtual LPCWSTR                 getEffectName() IMPLEMENT;
        virtual STATUS                  getUsableVariablePointers(ID3D10Effect * xEffect) IMPLEMENT;

    public:

        //////////////////////////////////////////////////////////
        // ABSTRACT IMPLEMENTATION
        //////////////////////////////////////////////////////////

        virtual STATUS                  initialize();
    };
}

#endif