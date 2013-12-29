////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __IMAGEPROPERTIES_H__
#define __IMAGEPROPERTIES_H__

//+-----------------------------------------------------------------------------
//
//  Abstract Class:
//      IMAGEPROPERTIES
//
//  Synopsis:
//      Differentiates which of the two possible arcs could match the given arc
//      parameters.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "ExtLibs.h"
#include "Abstract.h"
#include "FileInfo.h"
#include "Common.h"

namespace A2D {

	////////////////////////////////////////////////////////////////////////////////
	// FORWARD DECLARATIONS
	////////////////////////////////////////////////////////////////////////////////

	class Abstract;
	class Renderable;
	class Camera;
	struct CameraProperties;
	struct RenderData;
	class Graphics;
	class BackBuffer;
	class MatrixFactory;
	class ModelFactory;
	class RootPane;
	class Window;

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////


	struct ImageProperties : public Abstract
	{
		ImageProperties(){};
		~ImageProperties(){};
		ImageProperties(ImageProperties * xImageProps);

		int								aOptRepeat = _OPT_BACKGROUND_REPEAT_REPEAT_X | _OPT_BACKGROUND_REPEAT_REPEAT_Y;      // background-repeat (CSS)
		int								aOptSizeX = _OPT_BACKGROUND_SIZE_COVER;       // background-size-x  (CSS)
		int								aOptSizeY = _OPT_BACKGROUND_SIZE_COVER;       // background-size-x  (CSS)

	public:

		////////////////////////////////////////////////////////////////////////////////
		// ABSTRACT
		////////////////////////////////////////////////////////////////////////////////

		virtual HRESULT                 Initialize();
		virtual void                    Deinitialize();
		virtual LPCWSTR                 GetClass();
		virtual LPCWSTR                 ToString();
		virtual bool                    operator==(Abstract * xAbstract);
	};
}

#endif