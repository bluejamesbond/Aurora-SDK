////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __MATH_H__
#define __MATH_H__

//+-----------------------------------------------------------------------------
//
//  Abstract Class:
//      MATH
//
//  Synopsis:
//      Differentiates which of the two possible arcs could match the given arc
//      parameters.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "Rect.h"
#include "A2DFLOAT4.h"

namespace A2D {

	// @author Mathew K.
	class Math 
	{

	public:

		// Calculate difference between two Rects
		static inline A2DFLOAT4 subtract(const Rect& x_rect_a, const Rect& x_rect_b)
		{
			float a_x = x_rect_a.aX,
				  a_y = x_rect_a.aY,
				  a_x_ = a_x + x_rect_a.aWidth,
				  a_y_ = a_y + x_rect_a.aHeight;

			float b_x = x_rect_b.aX,
				  b_y = x_rect_b.aY,
				  b_x_ = b_x + x_rect_b.aWidth,
				  b_y_ = b_y + x_rect_b.aHeight;

			return A2DFLOAT4(a_x - b_x, a_y - b_y, a_y_ - b_y_, a_y_ - b_y_);
		}

		// Calculate difference between two Rects for effects
		// Requirement: x_rect_from MUST CONTAIN x_rect_by
		static inline A2DFLOAT4 subtract_contains(const Rect& x_rect_from, const Rect& x_rect_by)
		{
			float f_x = x_rect_from.aX,
				  f_y = x_rect_from.aY,
			      f_x_ = f_x + x_rect_from.aWidth,
				  f_y_ = f_y + x_rect_from.aHeight;

			float b_x = x_rect_by.aX,
				  b_y = x_rect_by.aY,
				  b_x_ = b_x + x_rect_by.aWidth,
				  b_y_ = b_y + x_rect_by.aHeight;

			return A2DFLOAT4(b_x - f_x, b_y - f_y, f_y_ - b_y_, f_y_ - b_y_);
		}

		// Rectangle Intersection
		static inline Rect intersect(const Rect& x_rect_a, const Rect& x_rect_b)
		{
			float a_x = x_rect_a.aX,
				  a_y = x_rect_a.aY,
				  a_x_ = a_x + x_rect_a.aWidth,
				  a_y_ = a_y + x_rect_a.aHeight;

			float b_x = x_rect_b.aX,
				  b_y = x_rect_b.aY,
				  b_x_ = b_x + x_rect_b.aWidth,
				  b_y_ = b_y + x_rect_b.aHeight;

			if (a_x > b_x_  ||  a_y > b_y_ || a_x_ < b_x || a_y_ < b_y)
			{
				// NOTE This is for Aurora internal use
				// so the return coordinates are actually set
				// to a_x, a_y
				return Rect(a_x, a_y, 0.0f, 0.0f);
			}
			
			float c_x = max__(a_x, b_x),
				  c_y = max__(a_y, b_y),
				  c_x_ = min__(a_x_, b_x_),
				  c_y_ = min__(a_y_, b_y_);

			return Rect(c_x, c_y, c_x_ - c_x, c_y_ - c_y);
		}

	};

}

#endif