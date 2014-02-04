////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __ANIMATOR_H__
#define __ANIMATOR_H__

//+-----------------------------------------------------------------------------
//
//  Class:  
//      ANIMATOR
//
//  Synopsis:
//      Contains Component styles
//
//------------------------------------------------------------------------------

#include "A2DANIMATABLEFLOAT1.h"
#include "A2DINTERPOLATORFLOAT1.h"

namespace A2D{

	class Component;

	// Typedef animation
	typedef void** Animation;

	// Typedef animation
	typedef void** HANIMATION;
	
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

	class Animator
	{

	public:	
		
		static A2DANIMATABLEFLOAT1				COMPONENT_OPACITY;
		static A2DANIMATABLEFLOAT1				COMPONENT_WIDTH;
		static A2DANIMATABLEFLOAT1				COMPONENT_HEIGHT;
		static A2DANIMATABLEFLOAT1				COMPONENT_BORDER_RADII_TOP_LEFT;
		static A2DANIMATABLEFLOAT1				COMPONENT_BORDER_RADII_UNIFIED;
		static A2DANIMATABLEFLOAT1				COMPONENT_BOUNDS_X;
		static A2DANIMATABLEFLOAT1				COMPONENT_BOUNDS_Y;

		static HANIMATION _fastcall				animate(Component& x_component, A2DCACHEDANIMATION& x_cachedAnimation);
		static void	_fastcall					stop(Component& x_component, Animation x_animation, bool x_callback);
		static void	_fastcall					stop(Component& x_component, HANIMATION x_animation);
	};
}

#endif