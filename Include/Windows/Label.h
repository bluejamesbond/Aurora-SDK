////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __LABEL_H__
#define __LABEL_H__

//+-----------------------------------------------------------------------------
//
//  Class: 
//      LABEL
//
//  Synopsis:
//      Label class to be rendered.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "../_A2DCommon.h"
#include "../Core/Component.h"
#include "ExtLibs.h"

using namespace std;

namespace A2D {

	////////////////////////////////////////////////////////////////////////////////
	// DEFINE
	////////////////////////////////////////////////////////////////////////////////

	#define A2D_LABEL_DEFAULT_FONTSIZE			2

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

	class Label : public Component
	{

	public:

		Label();
		Label(string xLabel, Fonts * xFont);
		~Label();

		STATUS							initialize();

		void							setText(string * xLabel);
		void							setText(const char * xText);
		void							setDrawLineLocation(float xDrawLocation);
		void							setFont(Fonts * xFont);
		void							setFontSize(float xPixelSize);
		void							setShadowColor(Color3D * xColor);
		void							setTextColor(Color3D * xColor);

		string					*		getText();
		float							getDrawLineLocation();
		Fonts					*		getFont();
		float							getFontSize();
		Color3D					*		getShadowColor();
		Color3D					*		getTextColor();

	protected:

		virtual void					paintComponent();

	private:

		Fonts					*		aFont = 0;
		Pipeline				*		aPipeline = NULL;
		float							aFontSize = 0;
		string							aText;

		Color3D					*		aTextColor;
		Color3D					*		aShadowColor;

		float							translationX = 0;
		float							translationXG1 = 10;
		float							translationYG1 = 10;
		float							translationY = 0;
		float							translationYDirection = 1;
		float							translationXDirection = 1;
		float							translationXDirectionG1 = 1;
		float							translationYDirectionG1 = 1;

	};

}





#endif