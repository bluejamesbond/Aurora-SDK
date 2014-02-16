////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __SRECT_H__
#define __SRECT_H__

//+-----------------------------------------------------------------------------
//
//  Class:  
//      SRECT
//
//  Synopsis:
//      Texture container class.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "S_Point.h"

////////////////////////////////////////////////////////////////////////////////
// DECLARATION
////////////////////////////////////////////////////////////////////////////////

namespace A2D {

	struct SRect : public SPoint
	{
		float m_x2, m_y2;

		inline SRect() :
			SPoint(),
			m_x2(0.0f),
			m_y2(0.0f)
		{
		}

		inline SRect(float a, float b, float c, float d) :
			SPoint(a, b),
			m_x2(c),
			m_y2(d)
		{
		}
	};
}

#endif