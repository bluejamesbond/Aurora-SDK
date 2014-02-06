
#include "../../../include/Core/ExtLibs.h"
#include "../../../include/Core/Animator.h"
#include "../../../include/Core/Component.h"
#include "../../../include/Core/AbstractFrame.h"

using namespace A2D;

A2DANIMATABLEFLOAT1 Animator::COMPONENT_OPACITY(&Component::getOpacity, &Component::setOpacity, 0.0f, 1.0f);
A2DANIMATABLEFLOAT1 Animator::COMPONENT_WIDTH(&Component::getWidth, &Component::setWidth, 0.0f, FLT_MAX);
A2DANIMATABLEFLOAT1 Animator::COMPONENT_HEIGHT(&Component::getHeight, &Component::setHeight, 0.0f, FLT_MAX);
A2DANIMATABLEFLOAT1 Animator::COMPONENT_BORDER_RADII_TOP_LEFT(&Component::getBorderRadiiTopLeft, &Component::setBorderRadiiTopLeft, 0.0f, FLT_MAX);
A2DANIMATABLEFLOAT1 Animator::COMPONENT_BORDER_RADII_UNIFIED(&Component::getBorderRadiiUnified, &Component::setBorderRadiiUnified, 0.0f, FLT_MAX);
A2DANIMATABLEFLOAT1 Animator::COMPONENT_BOUNDS_X(&Component::getBoundsX, &Component::setBoundsX, FLT_MIN, FLT_MAX);
A2DANIMATABLEFLOAT1 Animator::COMPONENT_BOUNDS_Y(&Component::getBoundsY, &Component::setBoundsY, FLT_MIN, FLT_MAX);

HANIMATION _fastcall Animator::animate(Component& x_component, A2DCACHEDANIMATION& x_cachedAnimation)
{
	A2DINTERPOLATORFLOAT * interpolator = new A2DINTERPOLATORFLOAT();
		
	interpolator->m_interpolatable = &x_cachedAnimation.m_animatable->m_mutator;
	interpolator->m_tween = x_cachedAnimation.m_tween;
	interpolator->m_startTime = kerneltimelp__; // current time
	interpolator->m_start_a = (x_component.*x_cachedAnimation.m_animatable->m_accessor)();
	interpolator->m_range_a = x_cachedAnimation.m_to - interpolator->m_start_a;
	interpolator->m_period = x_cachedAnimation.m_period;
	interpolator->m_callback = x_cachedAnimation.m_callback;
	interpolator->m_arg = x_cachedAnimation.m_arg;

	x_component.m_interpolators.push_back(interpolator, &interpolator->m_removeTicket);

	x_component.m_activeInterpolations = true;

	x_component.m_eventQueue->startedAnimation();

	#ifdef A2D_DE__			
	SYSOUT_F("[Component] [ComponentId: 0x%X] Adding interpolator.", m_id);
	#endif // A2D_DE__

	return &interpolator->m_removeTicket;
}

HANIMATION _fastcall Animator::animate(Component& x_component, A2DCACHEDANIMATION2& x_cachedAnimation)
{
	float start_a = (x_component.*x_cachedAnimation.m_animatable->m_accessor_a)();
	float start_b = (x_component.*x_cachedAnimation.m_animatable->m_accessor_b)();

	A2DINTERPOLATORFLOAT * interpolator = 
		new A2DINTERPOLATORFLOAT(&x_cachedAnimation.m_animatable->m_mutator,
								  x_cachedAnimation.m_tween,
								  kerneltimelp__, 
								  start_a,
								  x_cachedAnimation.m_to_a - start_a,
								  start_b,
								  x_cachedAnimation.m_to_b - start_b,
								  x_cachedAnimation.m_period,
								  x_cachedAnimation.m_callback,
								  x_cachedAnimation.m_arg);
	
	x_component.m_interpolators.push_back(interpolator, &interpolator->m_removeTicket);

	x_component.m_activeInterpolations = true;

	x_component.m_eventQueue->startedAnimation();

	#ifdef A2D_DE__			
	SYSOUT_F("[Component] [ComponentId: 0x%X] Adding interpolator.", m_id);
	#endif // A2D_DE__

	return &interpolator->m_removeTicket;
}


void _fastcall Animator::stop(Component& x_component, Animation x_animation, bool x_arg)
{
	// BROKEN - FIXME!!!
	// NOTE: This is not really used in dev.

	if (x_arg)
	{
		// Get the data
		A2DINTERPOLATORFLOAT ** interpolator = x_component.m_interpolators.from_ticket(x_animation);

		if (!interpolator)
		{
			return;
		}

		// Execute callback
		if ((*interpolator)->m_callback)
		{
			(*(*interpolator)->m_callback)((*interpolator)->m_arg);
		}
	}

	x_component.m_interpolators.remove_request(x_animation);
}

void _fastcall Animator::stop(Component& x_component, HANIMATION x_animation)
{
	if (x_component.m_interpolators.remove_request(x_animation))
	{
		x_component.m_eventQueue->finishedAnimation();
	}
}