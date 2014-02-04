////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __A2DCACHEDANIMATION_H__
#define __A2DCACHEDANIMATION_H__

//+-----------------------------------------------------------------------------
//
//  Class:  
//      A2DCACHEDANIMATION
//
//  Synopsis:
//      Contains Component styles
//
//------------------------------------------------------------------------------

#include "A2DANIMATABLEFLOAT1.h"
#include "A2DINTERPOLATORFLOAT1.h"

namespace A2D{

	// Cached animations
	struct A2DCACHEDANIMATION
	{
		A2DANIMATABLEFLOAT1 * m_animatable;
		A2DCALLBACKVOID1 * m_callback;
		TWEEN * m_tween;

		float m_to;
		int m_period;

		void * m_arg;

		inline A2DCACHEDANIMATION() :
			m_to(0.0f),
			m_period(0),
			m_arg(NULL)
		{
		}

		inline A2DCACHEDANIMATION(A2DANIMATABLEFLOAT1& x_animatable, TWEEN& x_tween, float x_to, int x_period, A2DCALLBACKVOID1 * x_callback, void * x_arg) :
			m_animatable(&x_animatable),
			m_tween(&x_tween),
			m_callback(x_callback),
			m_to(x_to),
			m_period(x_period),
			m_arg(x_arg)
		{
		}
	};
}

#endif


