////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __A2DPIXELDISTANCESETUINT4_H__
#define __A2DPIXELDISTANCESETUINT4_H__

//+-----------------------------------------------------------------------------
//
//  Class:  
//      A2DPIXELDISTANCESETUINT4
//
//  Synopsis:
//      Contains Component styles
//
//------------------------------------------------------------------------------

#include "Style.h"

namespace A2D
{

	struct A2DPIXELDISTANCESETUINT4
	{
		unsigned int				m_left;
		unsigned int				m_top;
		unsigned int				m_bottom;
		unsigned int				m_right;

		A2DPIXELDISTANCESETUINT4() :
			m_left(0),
			m_top(0),
			m_bottom(0),
			m_right(0)
		{
		}
	};
}

#endif