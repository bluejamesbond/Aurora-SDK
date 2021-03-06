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

#include "SETPOINT.h"

////////////////////////////////////////////////////////////////////////////////
// DECLARATION
////////////////////////////////////////////////////////////////////////////////

namespace A2D {

	struct SETRECT : public SETPOINT
	{
		float m_x2, m_y2;

		inline SETRECT() :
			SETPOINT(),
			m_x2(0.0f),
			m_y2(0.0f)
		{
		}

		inline SETRECT(float a, float b, float c, float d) :
			SETPOINT(a, b),
			m_x2(c),
			m_y2(d)
		{
		}
	};
}

#endif