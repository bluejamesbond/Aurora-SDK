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
#include "../Core/OrderedList.h"

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

		Font			*	aCurrentFont;
		Texture			*	aFontTexture;

		OrderedList<Font *>	aFontList;
		
	public:

		inline void TextFactory::setFont(Fonts * xFont)
		{
			Font * font;
			if (xFont->isUsed)
			{
				// Is the font is already used, then it is in our list.
				font = findFont(xFont);
			}
			else
			{
				// If font is not used, we need to make a new Font object and add to list.
				font = new Font(*xFont, aDevice);
				font->initialize();
				aFontList.push_back(font, NULL); // NULL, because we will never remove it.
			}
			aCurrentFont = font;
		}

		inline Font * TextFactory::findFont(Fonts * xFont)
		{
			OrderedList<Font*>::Node<Font*> * node = aFontList._end();
			while (node)
			{
				if (node->value->aFont == *xFont)
				{
					return node->value;
				}
				node = node->left;
			}
		}

		inline Fonts * TextFactory::getCurrentFont()
		{
			return &aCurrentFont->aFont;
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
			float charX;
			float charY;
			float width;
			float height;
			float offsetX;
			float offsetY;
			float advanceX;

			Rect * clipR = new Rect;
			Rect * inputR = xRect;
			Texture * texture = aCurrentFont->aFontTexture;
			Font * font = aCurrentFont;

			int inputLength = xText->aText.length();

			const char * input = xText->aText.c_str();

			for (int i = 0; i < inputLength; i += 1)
			{

				charX = FLOAT(font->aCharacters[input[i]].aX);
				charY = FLOAT(font->aCharacters[input[i]].aY);
				width = FLOAT(font->aCharacters[input[i]].aWidth);
				height = FLOAT(font->aCharacters[input[i]].aHeight);
				offsetX = FLOAT(font->aCharacters[input[i]].aXOffset);
				offsetY = FLOAT(font->aCharacters[input[i]].aYOffset);
				advanceX = FLOAT(font->aCharacters[input[i]].aXAdvance);

				// Get new clip.
				clipR->aX = charX;
				clipR->aY = charX;
				clipR->aWidth = width;
				clipR->aHeight = height;

				texture->SetClip(clipR);

				// Adjust input rect for each letter.
				//inputR->aX += offsetX;
				//inputR->aY - offsetY;

				// Calculate vertex and render letter.
				if (aQuadFactory->updateVertexBuffer(quadData, inputR, texture, false))
				{
					aTextureShader->setTexture(texture);
					aQuadFactory->renderQuad(quadData->aVertexBuffer, sizeof(TextureVertex));
					aTextureShader->renderShader();
				}

				// Prepare for next letter.
				inputR->aX += advanceX;

			}
		}

	public:
		
		virtual STATUS                 initialize();
	};

}




#endif