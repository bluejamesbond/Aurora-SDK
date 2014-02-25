////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __A2DPIXELDISTANCESETINT4_H__
#define __A2DPIXELDISTANCESETINT4_H__

//+-----------------------------------------------------------------------------
//
//  Class:  
//      A2DPIXELDISTANCESETINT4
//
//  Synopsis:
//      Contains Component styles
//
//------------------------------------------------------------------------------

#include "Style.h"

namespace A2D
{
	struct A2DPIXELDISTANCESETINT4
	{
		int							m_left;
		int							m_top;
		int							m_bottom;
		int							m_right;

		A2DPIXELDISTANCESETINT4() :
			m_left(0),
			m_top(0),
			m_bottom(0),
			m_right(0)
		{
		}
	};
}

#endif