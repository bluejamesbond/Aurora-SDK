////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __A2DBORDERSET4_H__
#define __A2DBORDERSET4_H__

//+-----------------------------------------------------------------------------
//
//  Class:  
//      A2DBORDERSET4
//
//  Synopsis:
//      Contains Component styles
//
//------------------------------------------------------------------------------

#include "Style.h"
#include "A2DDISTANCESET4.h"
#include "A2DPIXELDISTANCESETUINT4.h"

namespace A2D{

	struct A2DBORDERSET4
	{
		Color3D m_leftColor;
		Color3D m_topColor;
		Color3D m_rightColor;
		Color3D m_bottomColor;

		A2DDISTANCESET4 m_borderWidths;
		A2DPIXELDISTANCESETUINT4 m_precalculatedBorderWidths;

		bool m_inset; // unused

		A2DBORDERSET4() :
			m_inset(false)
		{
			Color3D::from(m_leftColor, Color3D::RED);
			Color3D::from(m_topColor, Color3D::BLUE);
			Color3D::from(m_rightColor, Color3D::YELLOW);
			Color3D::from(m_bottomColor, Color3D::GREEN_SEA);
		}
	};
}

#endif