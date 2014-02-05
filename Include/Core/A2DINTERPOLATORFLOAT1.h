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
		enum Mode
		{
			ONE_PARAMATER,
			TWO_PARAMATERS,
			THREE_PARAMETERS,
			FOUR_PARAMETERS
		};

		TWEEN * m_tween;
		
		A2DANIMMUTATORFLOAT1 * m_interpolatable;
		A2DANIMMUTATORFLOAT2 * m_interpolatable_b;
		A2DANIMMUTATORFLOAT3 * m_interpolatable_c;
		A2DANIMMUTATORFLOAT4 * m_interpolatable_d;
		
		A2DCALLBACKVOID1 * m_callback;
		
		int m_startTime;

		float m_period;

		float m_range_a, m_range_b, m_range_c, m_range_d;
		float m_start_a, m_start_b, m_start_c, m_start_d;
		
		void * m_arg;
		void * m_removeTicket;

		Mode m_mode;

		A2DINTERPOLATORFLOAT1() :
			m_callback(NULL),
			m_removeTicket(NULL)
		{
		}
	};
}

#endif