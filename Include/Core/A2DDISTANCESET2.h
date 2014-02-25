////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __A2DDISTANCESET2_H__
#define __A2DDISTANCESET2_H__

//+-----------------------------------------------------------------------------
//
//  Class:  
//      A2DDISTANCESET2
//
//  Synopsis:
//      Contains Component styles
//
//------------------------------------------------------------------------------

#include "Style.h"

namespace A2D
{
	struct A2DDISTANCESET2
	{
		Style::Units                m_widthUnits;
		Style::Units                m_heightUnits;

		float                       m_width;
		float                       m_height;

		A2DDISTANCESET2() :
			m_widthUnits(Style::Units::PIXEL),
			m_heightUnits(Style::Units::PIXEL),
			m_width(0.0f),
			m_height(0.0f)
		{
		}
	};
}

#endif