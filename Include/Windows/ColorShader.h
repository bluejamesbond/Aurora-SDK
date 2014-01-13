////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __COLORSHADER_H__
#define __COLORSHADER_H__

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

#include "ExtLibs.h"
#include "Texture.h"
#include "AbstractShader.h"

namespace A2D {

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

	class ColorShader : public AbstractShader
	{
	public:

		ColorShader(ID3D10Device ** xDevice);
		virtual ~ColorShader();
		
	private:

		static ID3D10Effect			*	aColorEffect;

		static float				**	aProjectionMatrix;
		static ID3D10EffectMatrixVariable	*	aWorldMatrixPtr;
		static ID3D10EffectMatrixVariable	*	aViewMatrixPtr;
		static ID3D10EffectMatrixVariable	*	aProjectionMatrixPtr;

	public:

		static void								setViewMatrix(float ** xMatrix);
		static void								setWorldMatrix(float ** xMatrix);
		static void								setProjectionMatrix(float ** xMatrix);
		static void								reloadProjectionMatrix();

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