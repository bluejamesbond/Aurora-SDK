////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __PIPELINE_H__
#define __PIPELINE_H__

//+-----------------------------------------------------------------------------
//
//  Class:
//      PIPELINE
//
//  Synopsis:
//      Differentiates which of the two possible arcs could match the given arc
//      parameters.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "../_A2DCommon.h"
#include "Pipelineable.h"

namespace A2D {

	////////////////////////////////////////////////////////////////////////////////
	// FORWARD DECLARATIONS
	////////////////////////////////////////////////////////////////////////////////

	class Abstract;
	class Pipelineable;

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

	class Pipeline
	{
		friend class Graphics;

	public:

		Pipeline();
		~Pipeline();

	private:

		Pipelineable		  *			aPipelineComps[8];
		int							    aLength = 0;
		int								aLifeCycle = 0;
		static int						aGlobalLifeCycle;

	public:

		static void						nextLifeCycle();
		virtual STATUS					initialize();

	};
}

#endif
