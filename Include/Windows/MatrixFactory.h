////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __MATRIXFACTORY_H__
#define __MATRIXFACTORY_H__

//+-----------------------------------------------------------------------------
//
//  Class:
//      MATRIXFACTORY
//
//  Synopsis:
//      Differentiates which of the two possible arcs could match the given arc
//      parameters.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "../Core/Dims.h"
#include "../Core/GXSettings.h"
#include "../Core/CameraProperties.h"

namespace A2D {

	////////////////////////////////////////////////////////////////////////////////
	// FORWARD DECLARATIONS
	////////////////////////////////////////////////////////////////////////////////

	class Abstract;
	class Container;
	struct CameraProperties;
	class BackBuffer;
	class MatrixFactory;
	class RootPane;
	class Window;

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

	class MatrixFactory
	{

	public:

		static HRESULT				    createDefaultWorldMatrix(D3DXMATRIX ** xWorldMatrix);
		static HRESULT					createDefaultProjectionMatrix(D3DXMATRIX ** xProjectionMatrix, Dims* xWindowSize, GXSettings*  xSettings);
		static HRESULT				    createDefaultOrthogonalMatrix(D3DXMATRIX ** xProjectionMatrix, Dims* xWindowSize, GXSettings* xSettings);
		static HRESULT					createViewMatrix(D3DXMATRIX ** xViewMatrix, CameraProperties& xCameraProperties);

	};
}

#endif
