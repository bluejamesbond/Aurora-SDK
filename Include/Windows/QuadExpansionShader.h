////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __QUADEXPANSIONSHADER_H__
#define __QUADEXPANSIONSHADER_H__

//+-----------------------------------------------------------------------------
//
//  Class: 
//      ABSTRACTTEXTURESHADER
//
//  Synopsis:
//      Texture quad.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "../_A2DCommon.h"

#include "../Core/Drawable.h"

#include "ExtLibs.h"
#include "Texture.h"
#include "AbstractShader.h"

namespace A2D {

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

	class QuadExpansionShader : public AbstractShader, ChangeListener
	{
	public:

		QuadExpansionShader(ID3D10Device ** xDevice);
		virtual ~QuadExpansionShader();
		
	private:

		ID3D10Effect*				aQuadEffect;
		ID3D10EffectShaderResourceVariable*   aTexturePtr;
		Texture*						aTexture;

		static QuadExpansionShader*	m_singelton;

	public:

		ID3D10EffectMatrixVariable*		m_positionMatrixPtr;
		void							updatePositionMatrix(D3DXMATRIX * x_position_matrix);
		virtual void					update(void * x_param, int x_id);

		///////////////////////////////////////////////////////////
		// INLINE FUNCTION
		///////////////////////////////////////////////////////////

		inline void QuadExpansionShader::setTexture(Texture * xTexture)
		{
			aTexture = xTexture;
			aHasAlpha = xTexture->hasAlpha();
			
			// Bind and update the texture.
			// Also cache the texture while doing so.!!!!
			aTexturePtr->SetResource(static_cast<ID3D10ShaderResourceView*>(xTexture->getPlatformCompatibleResource()));
		}

	protected:

		virtual ID3D10Effect		**	getEffect();
		virtual LPCWSTR					getEffectName();
		virtual STATUS					getUsableVariablePointers(ID3D10Effect * xEffect);
		virtual STATUS					createPolygonLayout(D3D10_INPUT_ELEMENT_DESC ** xPolygonLayout);
		virtual unsigned int			getPolygonLayoutElementCount();
		virtual	LPCSTR					getTechniqueName();
	};
}

#endif