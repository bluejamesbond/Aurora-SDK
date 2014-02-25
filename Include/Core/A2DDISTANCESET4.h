////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __A2DDISTANCESET4_H__
#define __A2DDISTANCESET4_H__

//+-----------------------------------------------------------------------------
//
//  Class:  
//      A2DDISTANCESET4
//
//  Synopsis:
//      Contains Component styles
//
//------------------------------------------------------------------------------

#include "Style.h"

namespace A2D
{

	struct A2DDISTANCESET4
	{
		Style::Units                m_leftUnits;
		Style::Units                m_topUnits;
		Style::Units                m_bottomUnits;
		Style::Units                m_rightUnits;

		float                       m_left;
		float                       m_top;
		float                       m_bottom;
		float                       m_right;

		A2DDISTANCESET4() :
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
}

#endif