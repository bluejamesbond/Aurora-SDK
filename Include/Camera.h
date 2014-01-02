////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __CAMERA_H__
#define __CAMERA_H__

//+-----------------------------------------------------------------------------
//
//  Class:
//      CAMERA
//
//  Synopsis:
//      Differentiates which of the two possible arcs could match the given arc
//      parameters.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "CameraProperties.h"
#include "Abstract.h"

namespace A2D {

	////////////////////////////////////////////////////////////////////////////////
	// FORWARD DECLARATIONS
	////////////////////////////////////////////////////////////////////////////////

	class Abstract;
	class Renderable;
	class Container;
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

	class Camera : public Abstract
	{

	public:

		// Constructor
		Camera();
		Camera(CameraProperties * xCameraProps);

		// Deconstructor
		~Camera();

	private:

		// Variables
		CameraProperties       *     aCameraProps;
		D3DXMATRIX                *     aViewMatrix;

	public:

		// Accesors
		D3DXMATRIX                *     GetViewMatrix();
		CameraProperties       *     GetProperties();          // returns the camera properties by pointer

	private:

		// Builders
		// { NONE }

		// Factory
		// { NONE }

	public:
		// Additional
		void						   CreateResources();

		// Pure Virtual
		// { NONE }

		// Virtual
		// { NONE }

	public:

		// Implementation
		// { ABSTRACT }
		virtual HRESULT                 initialize();
		virtual void                    Deinitialize();
		virtual LPCWSTR                 getClass();
		virtual LPCWSTR                 toString();
		virtual bool                    operator==(Abstract * xAbstract);

	};
}
#endif
