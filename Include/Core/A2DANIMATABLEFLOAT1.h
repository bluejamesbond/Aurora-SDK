////////////////////////////////////////////////////////////////////////////////

#ifndef __A2DANIMATABLEFLOAT1_H__
#define __A2DANIMATABLEFLOAT1_H__

//+-----------------------------------------------------------------------------
//
//  Struct:
//      A2DANIMATABLEFLOAT1
//
//  Synopsis:
//      Differentiates which of the two possible arcs could match the given arc
//      parameters.
//
//------------------------------------------------------------------------------

#include "A2DCOMPONENTFUNCTIONPTR.h"

namespace A2D {

	struct A2DANIMATABLEFLOAT1
	{
		A2DANIMMUTATORFLOAT1 m_mutator;
		A2DANIMACCESSORFLOAT1 m_accessor;

		float m_max;
		float m_min;

		A2DANIMATABLEFLOAT1() :
			m_max(0.0f),
			m_min(0.0f)
		{
		}

		A2DANIMATABLEFLOAT1(A2DANIMACCESSORFLOAT1 x_accessor, A2DANIMMUTATORFLOAT1 x_mutator, float x_min, float x_max) :
			m_mutator(x_mutator),
			m_accessor(x_accessor),
			m_min(x_min),
			m_max(x_max)
		{
		}
	};
}

#endif