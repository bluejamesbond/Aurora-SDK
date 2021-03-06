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

#include "A2DANIMATABLEFLOATX.h"
#include "A2DINTERPOLATORFLOAT.h"

namespace A2D{

	// Cached animations
	typedef struct A2DCACHEDANIMATION
	{
		A2DANIMATABLEFLOAT1 * m_animatable;
		A2DCALLBACKVOID1 * m_callback;
		TWEEN * m_tween;
		Callable * m_callable;

		float m_to_a;

		float m_period;

		void * m_arg;

		inline A2DCACHEDANIMATION() :
			m_to_a(0.0f),
			m_period(0),
			m_arg(NULL),
			m_callable(NULL)
		{
		}

		inline A2DCACHEDANIMATION(A2DANIMATABLEFLOAT1& x_animatable, TWEEN& x_tween, float x_to, int x_period, Callable * x_callable, A2DCALLBACKVOID1 * x_callback, void * x_arg) :
			m_animatable(&x_animatable),
			m_tween(&x_tween),
			m_callable(x_callable),
			m_callback(x_callback),
			m_to_a(x_to),
			m_period(SFLOAT(x_period)),
			m_arg(x_arg)
		{
		}

		inline void toValue(const float x_to_a)
		{
			m_to_a = x_to_a;
		}

	} VALUEANIMATOR1;

	// Cached animations
	typedef struct A2DCACHEDANIMATION2
	{
		A2DANIMATABLEFLOAT2 * m_animatable;
		A2DCALLBACKVOID1 * m_callback;
		TWEEN * m_tween;
		Callable * m_callable;

		float m_to_a;
		float m_to_b;

		float m_period;

		void * m_arg;

		inline A2DCACHEDANIMATION2() :
			m_to_a(0.0f),
			m_to_b(0.0f),
			m_period(0.0f),
			m_arg(NULL)
		{
		}

		inline A2DCACHEDANIMATION2(A2DANIMATABLEFLOAT2& x_animatable, TWEEN& x_tween,
			float x_to_a, float x_to_b, int x_period, Callable * x_callable,
			A2DCALLBACKVOID1 * x_callback, void * x_arg) :
			m_animatable(&x_animatable),
			m_tween(&x_tween),
			m_callable(x_callable),
			m_callback(x_callback),
			m_to_a(x_to_a),
			m_to_b(x_to_b),
			m_period(SFLOAT(x_period)),
			m_arg(x_arg)
		{
		}

		inline void toValues(const float x_to_a, const float x_to_b)
		{
			m_to_a = x_to_a;
			m_to_b = x_to_b;
		}
	} VALUEANIMATOR2;

	// Cached animations
	typedef struct A2DCACHEDANIMATION3
	{
		A2DANIMATABLEFLOAT3 * m_animatable;
		A2DCALLBACKVOID1 * m_callback;
		TWEEN * m_tween;
		Callable * m_callable;

		float m_to_a;
		float m_to_b;
		float m_to_c;

		float m_period;

		void * m_arg;

		inline A2DCACHEDANIMATION3() :
			m_to_a(0.0f),
			m_to_b(0.0f),
			m_to_c(0.0f),
			m_period(0.0f),
			m_arg(NULL)
		{
		}

		inline A2DCACHEDANIMATION3(A2DANIMATABLEFLOAT3& x_animatable, TWEEN& x_tween,
			float x_to_a, float x_to_b, float x_to_c, int x_period, Callable * x_callable,
			A2DCALLBACKVOID1 * x_callback, void * x_arg) :
			m_animatable(&x_animatable),
			m_tween(&x_tween),
			m_callable(x_callable),
			m_callback(x_callback),
			m_to_a(x_to_a),
			m_to_b(x_to_b),
			m_to_c(x_to_c),
			m_period(SFLOAT(x_period)),
			m_arg(x_arg)
		{
		}

		inline void toValues(const float x_to_a, const float x_to_b, const float x_to_c)
		{
			m_to_a = x_to_a;
			m_to_b = x_to_b;
			m_to_c = x_to_c;
		}

	} VALUEANIMATOR3;

	// Cached animations
	typedef struct A2DCACHEDANIMATION4
	{
		A2DANIMATABLEFLOAT4 * m_animatable;
		A2DCALLBACKVOID1 * m_callback;
		TWEEN * m_tween;
		Callable * m_callable;

		float m_to_a;
		float m_to_b;
		float m_to_c;
		float m_to_d;

		float m_period;

		void * m_arg;

		inline A2DCACHEDANIMATION4() :
			m_to_a(0.0f),
			m_to_b(0.0f),
			m_to_c(0.0f),
			m_to_d(0.0f),
			m_period(0.0f),
			m_arg(NULL)
		{
		}

		inline A2DCACHEDANIMATION4(A2DANIMATABLEFLOAT4& x_animatable, TWEEN& x_tween,
			float x_to_a, float x_to_b, float x_to_c, float x_to_d, int x_period, Callable * x_callable,
			A2DCALLBACKVOID1 * x_callback, void * x_arg) :
			m_animatable(&x_animatable),
			m_tween(&x_tween),
			m_callable(x_callable),
			m_callback(x_callback),
			m_to_a(x_to_a),
			m_to_b(x_to_b),
			m_to_c(x_to_c),
			m_to_d(x_to_d),
			m_period(SFLOAT(x_period)),
			m_arg(x_arg)
		{
		}

		inline void toValues(const float x_to_a, const float x_to_b, const float x_to_c, const float x_to_d)
		{
			m_to_a = x_to_a;
			m_to_b = x_to_b;
			m_to_c = x_to_c;
			m_to_d = x_to_d;
		}

	} VALUEANIMATOR4;
}

#endif


