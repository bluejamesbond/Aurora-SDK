////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __STYLES_H__
#define __STYLES_H__

//+-----------------------------------------------------------------------------
//
//  Class:  
//      STYLES
//
//  Synopsis:
//      Contains Component styles
//
//------------------------------------------------------------------------------

#include "../_A2DCommon.h"

namespace A2D{

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

	class Styles
	{
	public:

		enum Position
		{
			RELATIVE_,
			ABSOLUTE_,
			FIXED
		};

		enum Display
		{
			INLINE_BLOCK,
			BLOCK
		};

		enum Float
		{
			LEFT,
			RIGHT,
			CENTER
		};

		enum Units
		{
			PIXEL,
			PERCENTAGE
		};

		enum Background
		{
			REPEAT,
			STRETCH,
			COVER
		};

		enum BackgroundPosition
		{
			CENTER,
			LEFT,
			TOP,
			BOTTOM,
			RIGHT,
			CUSTOM
		};

		enum BackgroundRepeat
		{
			X,
			Y,
			X_Y,
			NONE
		};

		static float AUTO;
		
		struct BackgroundProperties
		{
			Background m_style;

			/**************************************/

			Units m_customPositionXUnits;
			Units m_customPositionYUnits;

			int m_customPositionX;
			int m_customPositionY;

			/**************************************/

			Units m_customSizeWidthUnits;
			Units m_customSizeHeightUnits;

			int m_customSizeWidth;
			int m_customSizeHeight;

			/**************************************/

			BackgroundPosition m_positionX;
			BackgroundPosition m_positionY;

			BackgroundProperties() :
				m_style(Background::COVER),
				m_positionX(BackgroundPosition::CENTER),
				m_positionY(BackgroundPosition::CENTER),
				m_customPositionX(0),
				m_customPositionY(0)
			{
			}

			void setStyle(Background x_style)
			{
				m_style = x_style;
			}

			void setPosition(BackgroundPosition x_positionX, BackgroundPosition x_positionY)
			{
				m_positionX = x_positionX;
				m_positionY = x_positionY;
			}

			void setCustomPosition(int x_customPositionX, int x__customPositionY)
			{
				// Note that customPosition will only be taken into consideration
				// iff BackgroundPosition is set to PRECISE
				m_customPositionX = x_customPositionX;
				m_customPositionY = x__customPositionY;
			}
		};
	};
}

#endif