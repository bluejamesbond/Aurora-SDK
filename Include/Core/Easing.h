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
		// Cheat sheet
		// -------------------
		// t - 0 < t < d
		// b - start value
		// c - total_change
		// d - duration

	public:		

		template<class T>
		inline static T inQuad(T t, T b, T c, T d) {
			return c*(t /= d)*t + b;
		}

		template<class T>
		inline static T outQuad(T t, T b, T c, T d) {
			return -c *(t /= d)*(t - 2) + b;
		}

		template<class T>
		inline static T inOutQuad(T t, T b, T c, T d) {
			if ((t /= d / 2) < 1) return c / 2 * t*t + b;
			return -c / 2 * ((--t)*(t - 2) - 1) + b;
		}

		template<class T>
		inline static T inCubic(T t, T b, T c, T d) {
			return c*(t /= d)*t*t + b;
		}

		template<class T>
		inline static T outCubic(T t, T b, T c, T d) {
			return c*((t = t / d - 1)*t*t + 1) + b;
		}

		template<class T>
		inline static T inOutCubic(T t, T b, T c, T d) {
			if ((t /= d / 2) < 1) return c / 2 * t*t*t + b;
			return c / 2 * ((t -= 2)*t*t + 2) + b;
		}

		template<class T>
		inline static T inQuart(T t, T b, T c, T d) {
			return c*(t /= d)*t*t*t + b;
		}

		template<class T>
		inline static T outQuart(T t, T b, T c, T d) {
			return -c * ((t = t / d - 1)*t*t*t - 1) + b;
		}

		template<class T>
		inline static T inOutQuart(T t, T b, T c, T d) {
			if ((t /= d / 2) < 1) return c / 2 * t*t*t*t + b;
			return -c / 2 * ((t -= 2)*t*t*t - 2) + b;
		}

		template<class T>
		inline static T inQuint(T t, T b, T c, T d) {
			return c*(t /= d)*t*t*t*t + b;
		}

		template<class T>
		inline static T outQuint(T t, T b, T c, T d) {
			return c*((t = t / d - 1)*t*t*t*t + 1) + b;
		}

		template<class T>
		inline static T inOutQuint(T t, T b, T c, T d) {
			if ((t /= d / 2) < 1) return c / 2 * t*t*t*t*t + b;
			return c / 2 * ((t -= 2)*t*t*t*t + 2) + b;
		}

		template<class T>
		inline static T inSine(T t, T b, T c, T d) {
			return -c * cos(t / d * (M_PI / 2)) + c + b;
		}

		template<class T>
		inline static T outSine(T t, T b, T c, T d) {
			return c * sin(t / d * (M_PI / 2)) + b;
		}

		template<class T>
		inline static T inOutSine(T t, T b, T c, T d) {
			return -c / 2 * (cos(M_PI*t / d) - 1) + b;
		}

		template<class T>
		inline static T inExpo(T t, T b, T c, T d) {
			return (t == 0) ? b : c * pow(2, 10 * (t / d - 1)) + b;
		}

		template<class T>
		inline static T outExpo(T t, T b, T c, T d) {
			return (t == d) ? b + c : c * (-pow(2, -10 * t / d) + 1) + b;
		}

		template<class T>
		inline static T inOutExpo(T t, T b, T c, T d) {
			if (t == 0) return b;
			if (t == d) return b + c;
			if ((t /= d / 2) < 1) return c / 2 * pow(2, 10 * (t - 1)) + b;
			return c / 2 * (-pow(2, -10 * --t) + 2) + b;
		}

		template<class T>
		inline static T inCirc(T t, T b, T c, T d) {
			return -c * (sqrt(1 - (t /= d)*t) - 1) + b;
		}

		template<class T>
		inline static T outCirc(T t, T b, T c, T d) {
			return c * sqrt(1 - (t = t / d - 1)*t) + b;
		}

		template<class T>
		inline static T inOutCirc(T t, T b, T c, T d) {
			if ((t /= d / 2) < 1) return -c / 2 * (sqrt(1 - t*t) - 1) + b;
			return c / 2 * (sqrt(1 - (t -= 2)*t) + 1) + b;
		}

		template<class T>
		inline static T inElastic(T t, T b, T c, T d) {
			float s = 1.70158f; T p = 0; T a = c;
			if (t == 0) return b;  if ((t /= d) == 1) return b + c;  if (!p) p = d*.3;
			if (a < abs(c)) { a = c; T s = p / 4; }
			else T s = p / (2 * M_PI) * asin(c / a);
			return -(a*pow(2, 10 * (t -= 1)) * sin((t*d - s)*(2 * M_PI) / p)) + b;
		}

		template<class T>
		inline static T outElastic(T t, T b, T c, T d) {
			float s = 1.70158f; T p = 0; T a = c;
			if (t == 0) return b;  if ((t /= d) == 1) return b + c;  if (!p) p = d*.3;
			if (a < abs(c)) { a = c; T s = p / 4; }
			else T s = p / (2 * M_PI) * asin(c / a);
			return a*pow(2, -10 * t) * sin((t*d - s)*(2 * M_PI) / p) + c + b;
		}

		template<class T>
		inline static T  inOutElastic(T t, T b, T c, T d) {
			float s = 1.70158f; T p = 0; T a = c;
			if (t == 0) return b;  if ((t /= d / 2) == 2) return b + c;  if (!p) p = d*(.3*1.5);
			if (a < abs(c)) { a = c; T s = p / 4; }
			else T s = p / (2 * M_PI) * asin(c / a);
			if (t < 1) return -.5*(a*pow(2, 10 * (t -= 1)) * sin((t*d - s)*(2 * M_PI) / p)) + b;
			return a*pow(2, -10 * (t -= 1)) * sin((t*d - s)*(2 * M_PI) / p)*.5 + c + b;
		}

		template<class T>
		inline static T inBack(T t, T b, T c, T d) {
			float s = 1.70158f;
			return c*(t /= d)*t*((s + 1)*t - s) + b;
		}

		template<class T>
		inline static T outBack(T t, T b, T c, T d) {
			float s = 1.70158f;
			return c*((t = t / d - 1)*t*((s + 1)*t + s) + 1) + b;
		}

		template<class T>
		inline static T inOutBack(T t, T b, T c, T d) {
			float s = 1.70158f;
			if ((t /= d / 2) < 1) return c / 2 * (t*t*(((s *= (1.525)) + 1)*t - s)) + b;
			return c / 2 * ((t -= 2)*t*(((s *= (1.525)) + 1)*t + s) + 2) + b;
		}

		template<class T>
		inline static T inBounce(T t, T b, T c, T d) {
			return c - outBounce<T>(d - t, 0, c, d) + b;
		}

		template<class T>
		inline static T outBounce(T t, T b, T c, T d) {
			if ((t /= d) < (1.0f / 2.75f)) {
				return c*(7.5625f*t*t) + b;
			}
			else if (t < (2.0f / 2.75f)) {
				return c*(7.5625f*(t -= (1.5f / 2.75f))*t + 0.75f) + b;
			}
			else if (t < (2.5f / 2.75f)) {
				return c*(7.5625f*(t -= (2.25f / 2.75f))*t + 0.9375f) + b;
			}
			else {
				return c*(7.5625f*(t -= (2.625f / 2.75f))*t + 0.984375f) + b;
			}
		}

		template<class T>
		inline static T inOutBounce(T t, T b, T c, T d) {
			if (t < d / 2) return inBounce<T>(t * 2, 0, c, d) * 0.5f + b;
			return outBounce<T>(t * 2 - d, 0, c, d) * 0.5f + c* 0.5f + b;
		}
	};
}

#endif