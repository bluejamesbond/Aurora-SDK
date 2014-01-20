////////////////////////////////////////////////////////////////////////////////
// GUARDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __TEXTFACTORY_H__
#define __TEXTFACTORY_H__

//+-----------------------------------------------------------------------------
//
//  Class: 
//      TEXTFACTORY
//
//  Synopsis:
//      Text maker that takes in text data.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////


#include "../Core/Rect.h"
#include "../Core/Font.h"

#include "ExtLibs.h"
#include "DXUtils.h"
#include "Texture.h"
#include "Text.h"

namespace A2D {

	////////////////////////////////////////////////////////////////////////////////
	// FORWARD DECLARATIONS
	////////////////////////////////////////////////////////////////////////////////

	class Abstract;
	class DXShapeUtils;

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

	class TextFactory
	{
	public:
		
		TextFactory(ID3D10Device ** xDevice, Dims * xWindowDims);
		~TextFactory();

		//ID3D10Buffer	*	aIndexBuffer; // not needed atm
		//ID3D10Buffer	*	aVertexBuffer; // not needed atm
		
		float				aDepth = 0.0f;

		///////////////////////////////////////////////////////////

		Rect				aConstraints;
		Dims			*	aWindowDims;
		ID3D10Device	**	aDevice;

		///////////////////////////////////////////////////////////

	private:

		Font			*	aFont;
		Texture			*	aFontTexture;
		
	public:

		inline void TextFactory::setFont(Font * xFont)
		{
			
		}

		inline string * TextFactory::getCurrentFont()
		{
			return &aFont->aFontName;
		}

		inline void TextFactory::setDepth(float xZ)
		{
			aDepth = xZ;
		}

		inline bool TextFactory::setConstraints(Rect * xContraints, float xZ)
		{
			aDepth = xZ;

			Rect::memcpySSE2(&aConstraints, xContraints);

			// WHy store constraints into every QuadData
			//	if (memcmp(&xQuadData->aPreviousContraints, xContraints, sizeof(Rect)) != 0)
			//	{
			//		x_aligned_memcpy_sse2(&xQuadData->aPreviousContraints, xContraints, sizeof(Rect));
			//		return aContraintsChanged = true;
			//	}
			//	else
			//	{
			//		return aContraintsChanged = false;
			//	}

			return true;
		}

		inline void TextFactory::renderText(ID3D10Buffer * xVertexBuffer, unsigned int xStride)
		{
			//ID3D10Device  *	device = *aDevice;
			//unsigned int offset = 0;

			//// Set the vertex buffer to active in the input 
			//// assembler so it can be rendered.
			//device->IASetVertexBuffers(0, 1, &xVertexBuffer, &xStride, &offset);

			//// Set the index buffer to active in the input
			//// assembler so it can be rendered.
			//device->IASetIndexBuffer(aIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
		}

		inline bool TextFactory::updateVertexBuffer(Text * xText, Rect * xRect)
		{
			
		}

	public:
		
		virtual STATUS                 initialize();
	};

}




#endif