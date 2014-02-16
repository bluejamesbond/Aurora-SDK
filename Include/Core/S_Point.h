////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __SPOINT_H__
#define __SPOINT_H__

//+-----------------------------------------------------------------------------
//
//  Class:  
//      POINT
//
//  Synopsis:
//      Texture container class.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// DECLARATION
////////////////////////////////////////////////////////////////////////////////

namespace A2D {

	struct SPoint
	{
		float			m_x1, m_y1;

		inline SPoint() :
			m_x1(0.0f),
			m_y1(0.0f)
		{
		}

		inline SPoint(float x_x, float x_y) :
			m_x1(x_x),
			m_y1(x_y)
		{
		}
	};
}

#endif