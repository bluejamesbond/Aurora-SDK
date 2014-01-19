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
		Color3D  m_color;
		float m_width;
	
		Border() :
			m_width(10.0f)
		{
			Color3D::from(m_color, Color3D::AMETHYST);
		}
	};

	struct BorderSet
	{
		Border m_left;
		Border m_top;
		Border m_right;
		Border m_bottom;

		bool m_inset; // unused

		BorderSet() : 
			m_inset(false)
		{
			Color3D::from(m_left.m_color, Color3D::RED);
			Color3D::from(m_top.m_color, Color3D::BLUE);
			Color3D::from(m_right.m_color, Color3D::YELLOW);
			Color3D::from(m_bottom.m_color, Color3D::RED);
		}
	};
}

#endif