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

		Texture                      *   aTexture = NULL;
		float                        **  aProjectionMatrix = NULL;
		ID3D10Effect                 *   aTextureEffect = NULL;
        ID3D10EffectMatrixVariable   *   aWorldMatrixPtr = NULL;
		ID3D10EffectMatrixVariable   *   aViewMatrixPtr = NULL;
		ID3D10EffectMatrixVariable   *   aProjectionMatrixPtr = NULL;
		ID3D10EffectShaderResourceVariable*   aTexturePtr = NULL;

    public:

        void                             setTexture(Bufferable * xTexture);
        void                             setViewMatrix(float ** xMatrix);
        void                             setWorldMatrix(float ** xMatrix);
        void                             setProjectionMatrix(float ** xMatrix);
        void                             reloadProjectionMatrix();

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