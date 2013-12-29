////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __RENDERABLE_H__
#define __RENDERABLE_H__

//+-----------------------------------------------------------------------------
//
//  Class:
//      RENDERABLE
//
//  Synopsis:
//      Differentiates which of the two possible arcs could match the given arc
//      parameters.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "Abstract.h"

namespace A2D {

	////////////////////////////////////////////////////////////////////////////////
	// FORWARD DECLARATIONS
	////////////////////////////////////////////////////////////////////////////////

	class Abstract;
	class Renderable;
	class AbstractComponent;
	class Camera;
	struct CameraProperties;
	struct RenderData;
	class BackBuffer;
	class MatrixFactory;
	class ModelFactory;
	class RootPane;
	class Window;
	
	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

	class Renderable : public Abstract
	{

	public:

		// Pure Virtual
		virtual void                    Update(RenderData * xRenderData) = 0;

	public:

		// Implementation
		// { ABSTRACT }
		virtual HRESULT                 Initialize() = 0;
		virtual void                    Deinitialize() = 0;
		virtual LPCWSTR                 GetClass() = 0;
		virtual LPCWSTR                 ToString() = 0;
		virtual bool                    operator==(Abstract * xAbstract) = 0;

	};
}
#endif
