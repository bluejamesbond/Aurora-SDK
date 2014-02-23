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

#include "A2DCACHEDANIMATIONX.h"

namespace A2D{

	class Component;

	// Typedef animation
	typedef void** Animation;

	// Typedef animation
	typedef void** HANIMATION;

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
		static A2DANIMATABLEFLOAT1				COMPONENT_SCROLL_TOP;

		static A2DANIMATABLEFLOAT2				COMPONENT_BOUNDS_XY;

		static bool								isAnimating(Component& x_component, HANIMATION x_animation);
		static HANIMATION _fastcall				animate(Component& x_component, A2DCACHEDANIMATION& x_cachedAnimation);
		static HANIMATION _fastcall				animate(Component& x_component, A2DCACHEDANIMATION2& x_cachedAnimation);
		static void	_fastcall					stop(Component& x_component, Animation x_animation, bool x_callback);
		static void	_fastcall					stop(Component& x_component, HANIMATION x_animation);
	};
}

#endif