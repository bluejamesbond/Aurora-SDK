////////////////////////////////////////////////////////////////////////////////

#ifndef __A2DINTERPOLATORFLOAT_H__
#define __A2DINTERPOLATORFLOAT_H__

//+-----------------------------------------------------------------------------
//
//  Struct:
//      A2DINTERPOLATORFLOAT
//
//  Synopsis:
//      Differentiates which of the two possible arcs could match the given arc
//      parameters.
//
//------------------------------------------------------------------------------

#include "A2DCOMPONENTFUNCTIONPTR.h"
#include "Easing.h"

namespace A2D {

	struct A2DINTERPOLATORFLOAT
	{
		enum Mode
		{
			ONE_PARAMETER,
			TWO_PARAMETERS,
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

		float m_period; // To reduce conversions during animations

		float m_range_a, m_range_b, m_range_c, m_range_d;
		float m_start_a, m_start_b, m_start_c, m_start_d;
		
		void * m_arg;
		void * m_removeTicket;

		Mode m_mode;

		inline A2DINTERPOLATORFLOAT() :
			m_callback(NULL),
			m_removeTicket(NULL)
		{
		}

		inline A2DINTERPOLATORFLOAT(A2DANIMMUTATORFLOAT1 * x_interpolatable,
							  TWEEN * x_tween, 
							  int x_startTime, 
							  float x_start_a, 
							  float x_range_a, 
							  float x_period, 
							  A2DCALLBACKVOID1 * x_callback, 
							  void * x_arg) :
		m_interpolatable(x_interpolatable),
		m_tween(x_tween),
		m_startTime(x_startTime),
		m_start_a(x_start_a),
		m_range_a(x_range_a),
		m_period(x_period),
		m_callback(x_callback),
		m_arg(x_arg),
		m_mode(A2DINTERPOLATORFLOAT::Mode::ONE_PARAMETER)
		{
		}

		inline A2DINTERPOLATORFLOAT(A2DANIMMUTATORFLOAT2 * x_interpolatable,
							  TWEEN * x_tween,
							  int x_startTime,
							  float x_start_a,
							  float x_range_a,
							  float x_start_b,
							  float x_range_b,
							  float x_period,
							  A2DCALLBACKVOID1 * x_callback,
							  void * x_arg) :
		m_interpolatable_b(x_interpolatable),
		m_tween(x_tween),
		m_startTime(x_startTime),
		m_start_a(x_start_a),
		m_range_a(x_range_a),
		m_start_b(x_start_b),
		m_range_b(x_range_b),
		m_period(x_period),
		m_callback(x_callback),
		m_arg(x_arg),
		m_mode(A2DINTERPOLATORFLOAT::Mode::TWO_PARAMETERS)
		{
		}

		inline A2DINTERPOLATORFLOAT(A2DANIMMUTATORFLOAT3 * x_interpolatable,
							  TWEEN * x_tween,
							  int x_startTime,
							  float x_start_a,
							  float x_range_a,
							  float x_start_b,
							  float x_range_b,
							  float x_start_c,
							  float x_range_c,
							  float x_period,
							  A2DCALLBACKVOID1 * x_callback,
							  void * x_arg) :
		m_interpolatable_c(x_interpolatable),
		m_tween(x_tween),
		m_startTime(x_startTime),
		m_start_a(x_start_a),
		m_range_a(x_range_a),
		m_start_b(x_start_b),
		m_range_b(x_range_b),
		m_start_c(x_start_c),
		m_range_c(x_range_c),
		m_period(x_period),
		m_callback(x_callback),
		m_arg(x_arg),
		m_mode(A2DINTERPOLATORFLOAT::Mode::THREE_PARAMETERS)
		{
		}


		inline A2DINTERPOLATORFLOAT(A2DANIMMUTATORFLOAT4 * x_interpolatable,
							  TWEEN * x_tween,
							  int x_startTime,
							  float x_start_a,
							  float x_range_a,
							  float x_start_b,
							  float x_range_b,
							  float x_start_c,
							  float x_range_c,
							  float x_start_d,
							  float x_range_d,
							  float x_period,
							  A2DCALLBACKVOID1 * x_callback,
							  void * x_arg) :
		m_interpolatable_d(x_interpolatable),
		m_tween(x_tween),
		m_startTime(x_startTime),
		m_start_a(x_start_a),
		m_range_a(x_range_a),
		m_start_b(x_start_b),
		m_range_b(x_range_b),
		m_start_c(x_start_c),
		m_range_c(x_range_c),
		m_start_d(x_start_d),
		m_range_d(x_range_d),
		m_period(x_period),
		m_callback(x_callback),
		m_arg(x_arg),
		m_mode(A2DINTERPOLATORFLOAT::Mode::FOUR_PARAMETERS)
		{
		}
	};
}

#endif