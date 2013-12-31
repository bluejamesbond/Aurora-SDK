///////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __PANEL_H__
#define __PANEL_H__

//+-----------------------------------------------------------------------------
//
//  Struct:
//      PANEL
//
//  Synopsis:
//      Differentiates which of the two possible arcs could match the given arc
//      parameters.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "Component.h"
#include "ImageProperties.h"

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

	class Panel : public Component
	{
	public:

		// Variables
		float translationX = 0;
		float translationXG1 = 10;
		float translationYG1 = 10;
		float translationY = 0;
		float translationYDirection = 1;
		float translationXDirection = 1;
		float translationXDirectionG1 = 1;
		float translationYDirectionG1 = 1;

	protected:

		// Variables
		ImageProperties	*			aOptBackgroundProps;					// background-size/background-repeat
		LPCWSTR			*				aOptBackgroundSrc = NULL;				// background-image  (CSS)
		int								aOptBackgroundColor = 0xFF000000;       // background-color  (CSS)
		int								aOptBackgroundPosX = 0;					// background-position-x  (CSS)
		int								aOptBackgroundPosY = 0;					// background-position-x  (CSS)

	public:

		// Additional
		virtual void                    paintComponent(RenderData * xRenderData);

	public:

		// Implementation
		// { ABSTRACT }
		virtual LPCWSTR                 GetClass();
		virtual LPCWSTR                 ToString();
	};
}

#endif
