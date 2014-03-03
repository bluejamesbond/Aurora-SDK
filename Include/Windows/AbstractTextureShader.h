////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __ABSTRACTTEXTURESHADER_H__
#define __ABSTRACTTEXTURESHADER_H__

//+-----------------------------------------------------------------------------
//
//  Class: 
//      ABSTRACTTEXTURESHADER
//
//  Synopsis:
//      Texture shader that uses the AbstractShader. This provides the base
//      for classes that might implement texture and many other things.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////


#include "ExtLibs.h"
#include "DXUtils.h"
#include "Texture.h"
#include "AbstractShader.h"

namespace A2D {

    ////////////////////////////////////////////////////////////////////////////////
    // FORWARD DECLARATIONS
    ////////////////////////////////////////////////////////////////////////////////

    class Abstract;

    ////////////////////////////////////////////////////////////////////////////////
    // DECLARATION
    ////////////////////////////////////////////////////////////////////////////////

    class AbstractTextureShader : public AbstractShader
    {
    public:

        AbstractTextureShader(ID3D10Device ** xDevice);
        virtual ~AbstractTextureShader();

    private:

        static Texture                      *   aTexture;
        static float                        **  aProjectionMatrix;
        static ID3D10Effect                 *   aTextureEffect;
        static ID3D10EffectMatrixVariable   *   aWorldMatrixPtr;
        static ID3D10EffectMatrixVariable   *   aViewMatrixPtr;
        static ID3D10EffectMatrixVariable   *   aProjectionMatrixPtr;
        static ID3D10EffectShaderResourceVariable*   aTexturePtr;

    public:

        void                                    setTexture(Bufferable * xTexture);
        static void                             setViewMatrix(float ** xMatrix);
        static void                             setWorldMatrix(float ** xMatrix);
        static void                             setProjectionMatrix(float ** xMatrix);
        static void                             reloadProjectionMatrix();

    protected:

        virtual ID3D10Effect                **  getEffect();
        virtual LPCWSTR                         getEffectName();
        virtual STATUS                          getUsableVariablePointers(ID3D10Effect * xEffect);
        virtual STATUS                          createPolygonLayout(D3D10_INPUT_ELEMENT_DESC ** xPolygonLayout) IMPLEMENT;
        virtual unsigned int                    getPolygonLayoutElementCount() IMPLEMENT;
        virtual LPCSTR                          getTechniqueName() IMPLEMENT;

    };
}

#endif