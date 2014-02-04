////////////////////////////////////////////////////////////////////////////////

#ifndef __A2DINTERPOLATORFLOAT1_H__
#define __A2DINTERPOLATORFLOAT1_H__

//+-----------------------------------------------------------------------------
//
//  Struct:
//      A2DINTERPOLATORFLOAT1
//
//  Synopsis:
//      Differentiates which of the two possible arcs could match the given arc
//      parameters.
//
//------------------------------------------------------------------------------

#include "A2DCOMPONENTFUNCTIONPTR.h"
#include "Easing.h"

namespace A2D {

	struct A2DINTERPOLATORFLOAT1
	{
		TWEEN * m_tween;
		A2DANIMMUTATORFLOAT1* m_interpolatable;
		A2DCALLBACKVOID1* m_callback;

		int m_startTime;

		float m_period;
		float m_range;
		float m_start;

		void * m_arg;
		void * m_removeTicket;

		A2DINTERPOLATORFLOAT1() :
			m_range(0.0f),
			m_start(0.0f),
			m_period(0),
			m_startTime(0),
			m_callback(NULL),
			m_removeTicket(NULL)
		{
		}
	};
}

#endif