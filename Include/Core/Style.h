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

#include "Color3D.h"

namespace A2D{

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

	class Style
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

		struct DISTANCESET2
		{
			Style::Units                m_widthUnits;
			Style::Units                m_heightUnits;

			float                       m_width;
			float                       m_height;

			DISTANCESET2() :
				m_widthUnits(Style::Units::PIXEL),
				m_heightUnits(Style::Units::PIXEL),
				m_width(0.0f),
				m_height(0.0f)
			{
			}
		};

		struct PIXELDISTANCESETUINT2
		{
			unsigned int                m_width;
			unsigned int                m_height;

			PIXELDISTANCESETUINT2() :
				m_width(0),
				m_height(0)
			{
			}
		};


		struct DISTANCESET4
		{
			Style::Units                m_leftUnits;
			Style::Units                m_topUnits;
			Style::Units                m_bottomUnits;
			Style::Units                m_rightUnits;
			
			float                       m_left;
			float                       m_top;
			float                       m_bottom;
			float                       m_right;

			DISTANCESET4() :
				m_leftUnits(Style::Units::PIXEL),
				m_topUnits(Style::Units::PIXEL),
				m_bottomUnits(Style::Units::PIXEL),
				m_rightUnits(Style::Units::PIXEL),
				m_left(0.0f),
				m_top(0.0f),
				m_bottom(0.0f),
				m_right(0.0f)
			{
			}
		};

		struct PIXELDISTANCESETUINT4
		{
			unsigned int				m_left;
			unsigned int				m_top;
			unsigned int				m_bottom;
			unsigned int				m_right;

			PIXELDISTANCESETUINT4() :
				m_left(0),
				m_top(0),
				m_bottom(0),
				m_right(0)
			{
			}
		};

		struct PIXELDISTANCESETINT4
		{
			int							m_left;
			int							m_top;
			int							m_bottom;
			int							m_right;

			PIXELDISTANCESETINT4() :
				m_left(0),
				m_top(0),
				m_bottom(0),
				m_right(0)
			{
			}
		};

		struct BORDERSET4
		{
			Color3D m_leftColor;
			Color3D m_topColor;
			Color3D m_rightColor;
			Color3D m_bottomColor;

			DISTANCESET4 m_borderWidths;
			PIXELDISTANCESETUINT4 m_borderWidthsInPixels;

			bool m_inset; // unused

			BORDERSET4() :
				m_inset(false)
			{
				Color3D::from(m_leftColor, Color3D::RED);
				Color3D::from(m_topColor, Color3D::BLUE);
				Color3D::from(m_rightColor, Color3D::YELLOW);
				Color3D::from(m_bottomColor, Color3D::RED);
			}
		};

		static float AUTO;
		
		struct Background
		{
			enum Layout
			{
				REPEAT,
				STRETCH,
				COVER,
				NORMAL
			};

			enum Position
			{
				CENTER,
				LEFT,
				TOP,
				BOTTOM,
				RIGHT,
				CUSTOM
			};

			enum Repeat
			{
				X,
				Y,
				X_Y,
				NONE
			};

			/**************************************/

			Layout m_layout;

			/**************************************/

			Units m_customPositionXUnits;
			Units m_customPositionYUnits;

			float m_customPositionX;
			float m_customPositionY;

			/**************************************/

			Units m_customSizeWidthUnits;
			Units m_customSizeHeightUnits;

			float m_customSizeWidth;
			float m_customSizeHeight;

			/**************************************/

			Repeat m_repeat;

			/**************************************/

			Position m_positionX;
			Position m_positionY;

			/**************************************/

			Background() :
				m_layout(Layout::COVER),
				m_positionX(Position::CENTER),
				m_positionY(Position::CENTER),
				m_customPositionX(0),
				m_customPositionY(0)
			{
			}

			inline void setStyle(Layout x_layout)
			{
				m_layout = x_layout;
			}

			inline void setPosition(Position x_positionX, Position x_positionY)
			{
				m_positionX = x_positionX;
				m_positionY = x_positionY;
			}

			inline void setCustomPosition(Units x_customPositionXUnits, float x_customPositionX, Units x_customPositionYUnits, float x__customPositionY)
			{
				// Note that customPosition will only be taken into consideration
				// iff BackgroundPosition is set to PRECISE
				m_customPositionXUnits = x_customPositionXUnits;
				m_customPositionYUnits = x_customPositionYUnits;

				m_customPositionX = x_customPositionX;
				m_customPositionY = x__customPositionY;
			}

			inline void setSize(Units Width_customSizeWidthUnits, float Width_customSizeWidth, Units Width_customSizeHeightUnits, float Width__customSizeHeight)
			{
				m_customSizeWidthUnits = Width_customSizeWidthUnits;
				m_customSizeHeightUnits = Width_customSizeHeightUnits;

				m_customSizeWidth = Width_customSizeWidth;
				m_customSizeHeight = Width__customSizeHeight;
			}

			inline void setRepeat(Repeat x_repeat)
			{
				m_repeat = x_repeat;
			}
		};
	};
}

#endif