////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __BORDERSET_H__
#define __BORDERSET_H__

//+-----------------------------------------------------------------------------
//
//  Struct:
//      BORDERSET
//
//  Synopsis:
//      Differentiates which of the two possible arcs could match the given arc
//      parameters.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "Color3D.h"

namespace A2D {

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

	struct Border
	{
		Color3D  m_leftBorderColor;
		Color3D  m_topBorderColor;
		Color3D  m_rightBorderColor;
		Color3D  m_bottomBorderColor;

		unsigned int m_leftBorderWidthPixels;
		unsigned int m_topBorderWidthPixels;
		unsigned int m_rightBorderWidthPixels;
		unsigned int m_bottomBorderWidthPixels;

		Border() :
			m_leftBorderWidthPixels(1),
			m_topBorderWidthPixels(1),
			m_rightBorderWidthPixels(1),
			m_bottomBorderWidthPixels(1)
		{
		}		
	};

	struct BorderSet
	{
		Border m_leftBorder;
		Border m_topBorder;
		Border m_rightBorder;
		Border m_bottomBorder;
	};
}

#endif