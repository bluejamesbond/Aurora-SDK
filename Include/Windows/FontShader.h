////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __FONTSHADER_H__
#define __FONTSHADER_H__

//+-----------------------------------------------------------------------------
//
//  Class: 
//      FONTSHADER
//
//  Synopsis:
//      Shader used for rendering fonts.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "AbstractTextureShader.h"

namespace A2D {

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

	class FontShader : public AbstractTextureShader
	{
	public:

		FontShader(ID3D10Device ** xDevice);

	private:

		//static Color 						*	aFontColor;
		
		Texture								*	aTexture = 0;
		ID3D10EffectShaderResourceVariable	*   aTexturePtr = 0;

		ID3D10Effect						*	aFontEffect = 0;
		ID3D10EffectVectorVariable			*	aPixelColorPtr = 0;
		ID3D10EffectVectorVariable			*	aShadowColorPtr = 0;

	protected:

		virtual ID3D10Effect				**	getEffect();
		virtual LPCWSTR							getEffectName();
		virtual STATUS							getUsableVariablePointers(ID3D10Effect * xEffect);
		virtual	LPCSTR							getTechniqueName();

		virtual STATUS							createPolygonLayout(D3D10_INPUT_ELEMENT_DESC ** xPolygonLayout);
		virtual unsigned int					getPolygonLayoutElementCount();

	public:

		void									renderShader(int xIndexCount);
		void									setTexture(Texture * xTexture);
		void									setTextColor(Color * xColor);
		void									setShadowColor(Color * xColor);
		void									setTextColor(float r, float b, float y, float a);
		void									setShadowColor(float r, float b, float y, float a);

	};
}

#endif