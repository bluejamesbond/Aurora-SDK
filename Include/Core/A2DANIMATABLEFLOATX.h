////////////////////////////////////////////////////////////////////////////////

#ifndef __A2DANIMATABLEFLOATX_H__
#define __A2DANIMATABLEFLOATX_H__

//+-----------------------------------------------------------------------------
//
//  Struct:
//      A2DANIMATABLEFLOATX
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

		A2DANIMACCESSORFLOAT1 m_accessor_a;

		float m_max;
		float m_min;

		A2DANIMATABLEFLOAT1() :
			m_max(0.0f),
			m_min(0.0f)
		{
		}

		A2DANIMATABLEFLOAT1(A2DANIMACCESSORFLOAT1 x_accessor_a, 
							A2DANIMMUTATORFLOAT1 x_mutator, 
							float x_min, float x_max) :
			m_mutator(x_mutator),
			m_accessor_a(x_accessor_a),
			m_min(x_min),
			m_max(x_max)
		{
		}
	};

	struct A2DANIMATABLEFLOAT2
	{
		A2DANIMMUTATORFLOAT2 m_mutator;

		A2DANIMACCESSORFLOAT1 m_accessor_a;
		A2DANIMACCESSORFLOAT1 m_accessor_b;

		float m_max_a;
		float m_min_a;

		float m_max_b;
		float m_min_b;

		A2DANIMATABLEFLOAT2() :
			m_max_a(0.0f),
			m_min_a(0.0f),
			m_max_b(0.0f),
			m_min_b(0.0f)
		{
		}

		A2DANIMATABLEFLOAT2(A2DANIMACCESSORFLOAT1 x_accessor_a, 
							A2DANIMACCESSORFLOAT1 x_accessor_b, 
							A2DANIMMUTATORFLOAT2 x_mutator, 
							float x_min_a, float x_max_a, 
							float x_min_b, float x_max_b) :
			m_mutator(x_mutator),
			m_accessor_a(x_accessor_a),
			m_accessor_b(x_accessor_b),
			m_min_a(x_min_a),
			m_max_a(x_max_a),
			m_min_b(x_min_b),
			m_max_b(x_max_b)
		{
		}
	};

	struct A2DANIMATABLEFLOAT3
		{
			A2DANIMMUTATORFLOAT3 m_mutator;

			A2DANIMACCESSORFLOAT1 m_accessor_a;
			A2DANIMACCESSORFLOAT1 m_accessor_b;
			A2DANIMACCESSORFLOAT1 m_accessor_c;

			float m_max_a;
			float m_min_a;

			float m_max_b;
			float m_min_b;

			float m_max_c;
			float m_min_c;

			A2DANIMATABLEFLOAT3() :
				m_max_a(0.0f),
				m_min_a(0.0f),
				m_max_b(0.0f),
				m_min_b(0.0f),
				m_max_c(0.0f),
				m_min_c(0.0f)
			{
			}

			A2DANIMATABLEFLOAT3(A2DANIMACCESSORFLOAT1 x_accessor_a, 
								A2DANIMACCESSORFLOAT1 x_accessor_b, 
								A2DANIMACCESSORFLOAT1 x_accessor_c, 
								A2DANIMMUTATORFLOAT3 x_mutator, 
								float x_min_a, float x_max_a, 
								float x_min_b, float x_max_b,
								float x_min_c, float x_max_c) :
				m_mutator(x_mutator),
				m_accessor_a(x_accessor_a),
				m_accessor_b(x_accessor_b),
				m_min_a(x_min_a),
				m_max_a(x_max_a),
				m_min_b(x_min_b),
				m_max_b(x_max_b),
				m_min_c(x_min_c),
				m_max_c(x_max_c)
			{
			}
	};



	struct A2DANIMATABLEFLOAT4
	{
		A2DANIMMUTATORFLOAT4 m_mutator;

		A2DANIMACCESSORFLOAT1 m_accessor_a;
		A2DANIMACCESSORFLOAT1 m_accessor_b;
		A2DANIMACCESSORFLOAT1 m_accessor_c;
		A2DANIMACCESSORFLOAT1 m_accessor_d;

		float m_max_a;
		float m_min_a;

		float m_max_b;
		float m_min_b;

		float m_max_c;
		float m_min_c;

		float m_max_d;
		float m_min_d;

		A2DANIMATABLEFLOAT4() :
			m_max_a(0.0f),
			m_min_a(0.0f),
			m_max_b(0.0f),
			m_min_b(0.0f),
			m_max_c(0.0f),
			m_min_c(0.0f),
			m_max_d(0.0f),
			m_min_d(0.0f)
		{
		}

		A2DANIMATABLEFLOAT4(A2DANIMACCESSORFLOAT1 x_accessor_a,
							A2DANIMACCESSORFLOAT1 x_accessor_b,
							A2DANIMACCESSORFLOAT1 x_accessor_c,
							A2DANIMACCESSORFLOAT1 x_accessor_d,
							A2DANIMMUTATORFLOAT4 x_mutator,
							float x_min_a, float x_max_a,
							float x_min_b, float x_max_b,
							float x_min_c, float x_max_c,
							float x_min_d, float x_max_d) :
			m_mutator(x_mutator),
			m_accessor_a(x_accessor_a),
			m_accessor_b(x_accessor_b),
			m_min_a(x_min_a),
			m_max_a(x_max_a),
			m_min_b(x_min_b),
			m_max_b(x_max_b),
			m_min_c(x_min_c),
			m_max_c(x_max_c),
			m_min_d(x_min_d),
			m_max_d(x_max_d)
		{
		}
	};
}

#endif