////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __EASING_H__
#define __EASING_H__

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

#include "../_A2DCommon.h"

#include "ExtLibs.h"

namespace A2D {

	class Easing
	{
	public:

		template<class T>
		inline static T easeInQuad(T x, T t, T b, T c, T d) {
			return c*(t /= d)*t + b;
		}

		template<class T>
		inline static T easeOutQuad(T x, T t, T b, T c, T d) {
			return -c *(t /= d)*(t - 2) + b;
		}

		template<class T>
		inline static T easeInOutQuad(T x, T t, T b, T c, T d) {
			if ((t /= d / 2) < 1) return c / 2 * t*t + b;
			return -c / 2 * ((--t)*(t - 2) - 1) + b;
		}

		template<class T>
		inline static T easeInCubic(T x, T t, T b, T c, T d) {
			return c*(t /= d)*t*t + b;
		}

		template<class T>
		inline static T easeOutCubic(T x, T t, T b, T c, T d) {
			return c*((t = t / d - 1)*t*t + 1) + b;
		}

		template<class T>
		inline static T easeInOutCubic(T x, T t, T b, T c, T d) {
			if ((t /= d / 2) < 1) return c / 2 * t*t*t + b;
			return c / 2 * ((t -= 2)*t*t + 2) + b;
		}

		template<class T>
		inline static T easeInQuart(T x, T t, T b, T c, T d) {
			return c*(t /= d)*t*t*t + b;
		}

		template<class T>
		inline static T easeOutQuart(T x, T t, T b, T c, T d) {
			return -c * ((t = t / d - 1)*t*t*t - 1) + b;
		}

		template<class T>
		inline static T easeInOutQuart(T x, T t, T b, T c, T d) {
			if ((t /= d / 2) < 1) return c / 2 * t*t*t*t + b;
			return -c / 2 * ((t -= 2)*t*t*t - 2) + b;
		}

		template<class T>
		inline static T easeInQuint(T x, T t, T b, T c, T d) {
			return c*(t /= d)*t*t*t*t + b;
		}

		template<class T>
		inline static T easeOutQuint(T x, T t, T b, T c, T d) {
			return c*((t = t / d - 1)*t*t*t*t + 1) + b;
		}

		template<class T>
		inline static T easeInOutQuint(T x, T t, T b, T c, T d) {
			if ((t /= d / 2) < 1) return c / 2 * t*t*t*t*t + b;
			return c / 2 * ((t -= 2)*t*t*t*t + 2) + b;
		}

		template<class T>
		inline static T easeInSine(T x, T t, T b, T c, T d) {
			return -c * cos(t / d * (M_PI / 2)) + c + b;
		}

		template<class T>
		inline static T easeOutSine(T x, T t, T b, T c, T d) {
			return c * sin(t / d * (M_PI / 2)) + b;
		}

		template<class T>
		inline static T easeInOutSine(T x, T t, T b, T c, T d) {
			return -c / 2 * (cos(M_PI*t / d) - 1) + b;
		}

		template<class T>
		inline static T easeInExpo(T x, T t, T b, T c, T d) {
			return (t == 0) ? b : c * pow(2, 10 * (t / d - 1)) + b;
		}

		template<class T>
		inline static T easeOutExpo(T x, T t, T b, T c, T d) {
			return (t == d) ? b + c : c * (-pow(2, -10 * t / d) + 1) + b;
		}

		template<class T>
		inline static T easeInOutExpo(T x, T t, T b, T c, T d) {
			if (t == 0) return b;
			if (t == d) return b + c;
			if ((t /= d / 2) < 1) return c / 2 * pow(2, 10 * (t - 1)) + b;
			return c / 2 * (-pow(2, -10 * --t) + 2) + b;
		}

		template<class T>
		inline static T easeInCirc(T x, T t, T b, T c, T d) {
			return -c * (sqrt(1 - (t /= d)*t) - 1) + b;
		}

		template<class T>
		inline static T easeOutCirc(T x, T t, T b, T c, T d) {
			return c * sqrt(1 - (t = t / d - 1)*t) + b;
		}

		template<class T>
		inline static T easeInOutCirc(T x, T t, T b, T c, T d) {
			if ((t /= d / 2) < 1) return -c / 2 * (sqrt(1 - t*t) - 1) + b;
			return c / 2 * (sqrt(1 - (t -= 2)*t) + 1) + b;
		}

		template<class T>
		inline static T easeInElastic(T x, T t, T b, T c, T d) {
			float s = 1.70158f; T p = 0; T a = c;
			if (t == 0) return b;  if ((t /= d) == 1) return b + c;  if (!p) p = d*.3;
			if (a < abs(c)) { a = c; T s = p / 4; }
			else T s = p / (2 * M_PI) * asin(c / a);
			return -(a*pow(2, 10 * (t -= 1)) * sin((t*d - s)*(2 * M_PI) / p)) + b;
		}

		template<class T>
		inline static T easeOutElastic(T x, T t, T b, T c, T d) {
			float s = 1.70158f; T p = 0; T a = c;
			if (t == 0) return b;  if ((t /= d) == 1) return b + c;  if (!p) p = d*.3;
			if (a < abs(c)) { a = c; T s = p / 4; }
			else T s = p / (2 * M_PI) * asin(c / a);
			return a*pow(2, -10 * t) * sin((t*d - s)*(2 * M_PI) / p) + c + b;
		}

		template<class T>
		inline static T  easeInOutElastic(T x, T t, T b, T c, T d) {
			float s = 1.70158f; T p = 0; T a = c;
			if (t == 0) return b;  if ((t /= d / 2) == 2) return b + c;  if (!p) p = d*(.3*1.5);
			if (a < abs(c)) { a = c; T s = p / 4; }
			else T s = p / (2 * M_PI) * asin(c / a);
			if (t < 1) return -.5*(a*pow(2, 10 * (t -= 1)) * sin((t*d - s)*(2 * M_PI) / p)) + b;
			return a*pow(2, -10 * (t -= 1)) * sin((t*d - s)*(2 * M_PI) / p)*.5 + c + b;
		}

		template<class T>
		inline static T easeInBack(T x, T t, T b, T c, T d, T s) {
			if (s == NULL) s = 1.70158f;
			return c*(t /= d)*t*((s + 1)*t - s) + b;
		}

		template<class T>
		inline static T easeOutBack(T x, T t, T b, T c, T d, T s) {
			if (s == NULL) s = 1.70158f;
			return c*((t = t / d - 1)*t*((s + 1)*t + s) + 1) + b;
		}

		template<class T>
		inline static T easeInOutBack(T x, T t, T b, T c, T d, T s) {
			if (s == NULL) s = 1.70158f;
			if ((t /= d / 2) < 1) return c / 2 * (t*t*(((s *= (1.525)) + 1)*t - s)) + b;
			return c / 2 * ((t -= 2)*t*(((s *= (1.525)) + 1)*t + s) + 2) + b;
		}

		template<class T>
		inline static T easeInBounce(T x, T t, T b, T c, T d) {
			return c - easeOutBounce<T>(x, d - t, 0, c, d) + b;
		}

		template<class T>
		inline static T easeOutBounce(T x, T t, T b, T c, T d) {
			if ((t /= d) < (1 / 2.75)) {
				return c*(7.5625*t*t) + b;
			}
			else if (t < (2 / 2.75)) {
				return c*(7.5625*(t -= (1.5 / 2.75))*t + .75) + b;
			}
			else if (t < (2.5 / 2.75)) {
				return c*(7.5625*(t -= (2.25 / 2.75))*t + .9375) + b;
			}
			else {
				return c*(7.5625*(t -= (2.625 / 2.75))*t + .984375) + b;
			}
		}

		template<class T>
		inline static T easeInOutBounce(T x, T t, T b, T c, T d) {
			if (t < d / 2) return easeInBounce<T>(x, t * 2, 0, c, d) * .5 + b;
			return easeOutBounce<T>(x, t * 2 - d, 0, c, d) * .5 + c*.5 + b;
		}
	};
}

#endif