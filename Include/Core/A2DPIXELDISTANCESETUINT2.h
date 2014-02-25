////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __A2DPIXELDISTANCESETUINT2_H__
#define __A2DPIXELDISTANCESETUINT2_H__

//+-----------------------------------------------------------------------------
//
//  Class:  
//      A2DPIXELDISTANCESETUINT2
//
//  Synopsis:
//      Contains Component styles
//
//------------------------------------------------------------------------------

#include "Style.h"

namespace A2D
{
	struct A2DPIXELDISTANCESETUINT2
	{
		unsigned int                m_width;
		unsigned int                m_height;

		A2DPIXELDISTANCESETUINT2() :
			m_width(0),
			m_height(0)
		{
		}
	};
}

#endif