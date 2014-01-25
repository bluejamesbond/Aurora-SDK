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
#include "../Core/OrderedList.h"
#include "../Core/Font.h"
#include "../Structure/Graphics.h"

#include "ExtLibs.h"
#include "DXUtils.h"
#include "Texture.h"
#include "Text.h"
#include "VertexTypes.h"

namespace A2D {

	////////////////////////////////////////////////////////////////////////////////
	// FORWARD DECLARATIONS
	////////////////////////////////////////////////////////////////////////////////

	class Abstract;
	class DXShapeUtils;
	class Font;

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

	class TextFactory
	{
		friend class Graphics;
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
			aCurrentFont = font; // If null, error.
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
			return NULL;
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

		inline void TextFactory::renderText(Text * xText, unsigned int xStride)
		{
			ID3D10Device  *	device = *aDevice;
			unsigned int offset = 0;

			// Set the vertex buffer to active in the input 
			// assembler so it can be rendered.
			device->IASetVertexBuffers(0, 1, &xText->aVertexBuffer, &xStride, &offset);

			// Set the index buffer to active in the input
			// assembler so it can be rendered.
			device->IASetIndexBuffer(xText->aIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
		}

		inline bool TextFactory::updateVertexBuffer(Text * xText, Rect * xRect)
		{
			
			Rect * clipR = new Rect;
			Rect * inputR = xRect;
			Texture * texture = aCurrentFont->aFontTexture;
			Font * font = aCurrentFont;
			const char * input = xText->aText.c_str();

			float currentWidth = 0;
			float boxWidth = inputR->aWidth;
			int inputLength = xText->aText.length();
			int indexV = 0;
			int indexI = 0;

			float rectX = xRect->aX;
			float rectY = xRect->aY;
			float rectWidth = xRect->aWidth;
			float rectHeight = xRect->aHeight;
			float depth = aDepth;

			float topTx, bottomTx, leftTx, rightTx,
				top, bottom, left, right;

			float charX, charY, width, height, offsetX, offsetY,
				advanceX, baseWidth, baseHeight;

			TextureVertex * vertices = new TextureVertex[xText->aNumVertices];
			unsigned long * indices = new unsigned long[xText->aNumIndices];
			void * mappedVertices = 0;
			void * mappedIndices = 0;

			for (int i = 0; i < inputLength; i += 1)
			{

				charX = FLOAT(font->aCharacters[input[i]].aX);
				charY = FLOAT(font->aCharacters[input[i]].aY);
				width = FLOAT(font->aCharacters[input[i]].aWidth);
				height = FLOAT(font->aCharacters[input[i]].aHeight);
				offsetX = FLOAT(font->aCharacters[input[i]].aXOffset);
				offsetY = FLOAT(font->aCharacters[input[i]].aYOffset);
				advanceX = FLOAT(font->aCharacters[input[i]].aXAdvance);
				baseWidth = FLOAT(font->aWidth);
				baseHeight = FLOAT(font->aHeight);

				if (currentWidth + width + offsetX > boxWidth)
				{
					// Clip current quad/letter.
					width = boxWidth - currentWidth - offsetX;
				}

				// Calculations.
				left = rectX + offsetX;
				top = rectY - offsetY;
				right = left + width;
				bottom = top - height;

				leftTx = charX / baseWidth;
				rightTx = (charX + width) / baseWidth;
				topTx = charY / baseHeight;
				bottomTx = (charY + height) / baseHeight;

				// Load vertex data.
				vertices[indexV].position = D3DXVECTOR3(left, top, depth);
				vertices[indexV++].texture = D3DXVECTOR2(leftTx, topTx);

				vertices[indexV].position = D3DXVECTOR3(left, bottom, depth);
				vertices[indexV++].texture = D3DXVECTOR2(leftTx, bottomTx);

				vertices[indexV].position = D3DXVECTOR3(right, top, depth);
				vertices[indexV++].texture = D3DXVECTOR2(rightTx, topTx);

				vertices[indexV].position = D3DXVECTOR3(right, bottom, depth);
				vertices[indexV++].texture = D3DXVECTOR2(rightTx, bottomTx);
				
				// Load index data.
				indices[indexI++] = indexV - 1;
				indices[indexI++] = indexV - 2;
				indices[indexI++] = indexV - 3;
				indices[indexI++] = indexV - 2;
				indices[indexI++] = indexV - 1;
				indices[indexI++] = indexV;
				
				// Prepare for next letter.
				inputR->aX += advanceX;

				// Add measurements.
				currentWidth += width + advanceX;

			}

			// Map vertex and index buffers.
			xText->aVertexBuffer->Map(D3D10_MAP_WRITE_DISCARD, 0, static_cast<void**>(&mappedVertices));
			memcpy(mappedVertices, (void*)vertices, sizeof(TextureVertex)* xText->aNumVertices);
			xText->aVertexBuffer->Unmap();

			xText->aIndexBuffer->Map(D3D10_MAP_WRITE_DISCARD, 0, static_cast<void**>(&mappedVertices));
			memcpy(mappedIndices, (void*)indices, sizeof(unsigned long)* xText->aNumIndices);
			xText->aIndexBuffer->Unmap();

			return STATUS_OK;
		}

	public:
		
		virtual STATUS                 initialize();
	};

}




#endif