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

#include "TextureShader.h"

namespace A2D {

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

	class FontShader : public TextureShader
	{
	public:

		FontShader(ID3D10Device ** xDevice);
		virtual ~FontShader();

	private:

		//static Color 						*	aFontColor;
		
		static Texture						*	aTexture;
		static ID3D10EffectShaderResourceVariable*   aTexturePtr;

		static ID3D10Effect					*	aFontEffect;
		static ID3D10EffectVectorVariable	*	aPixelColorPtr;

	protected:

		virtual ID3D10Effect				**	getEffect();
		virtual LPCWSTR							getEffectName();
		virtual STATUS							getUsableVariablePointers(ID3D10Effect * xEffect);
		virtual	LPCSTR							getTechniqueName();

	public:

		void									renderShader(int xIndexCount);
		void									setTexture(Texture * xTexture);
		void									setColor(Color * xColor);
		void									setColor(float r, float b, float y, float a);

	};
}

#endif