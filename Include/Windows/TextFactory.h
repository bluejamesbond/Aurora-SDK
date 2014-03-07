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
#include "FontVertex.h"
#include "QuadFactory.h"

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
				font = new Font(xFont, aDevice);
				font->initialize();
				aFontList.push_back(font, NULL); // NULL, because we will never remove it.
				
				// Set as used, so we don't have to process it again.
				xFont->isUsed = true;
			}
			aCurrentFont = font; // If null, error.
		}

		inline Font * TextFactory::findFont(Fonts * xFont)
		{
			OrderedList<Font*>::Node<Font*> * node = aFontList._end();
			while (node)
			{
				if (node->value->aFont == xFont)
				{
					return node->value;
				}
				node = node->left;
			}
			return 0;
		}

		inline Fonts * TextFactory::getCurrentFont()
		{
			return aCurrentFont->aFont;
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

		inline bool TextFactory::updateVertexBuffer(Text * xText, Rect * xRect, float xPixelSize)
		{
			
			Rect * clipR = new Rect;
			Texture * texture = aCurrentFont->aFontTexture;
			Font * font = aCurrentFont;
			const char * input = xText->aText.c_str();


			float currentWidth = 0;
			int inputLength = xText->aText.length();
			int indexV = 0;
			int indexI = 0;

			Rect& constraints = aConstraints;
			float rectX = min(xRect->aX, constraints.aWidth);
			float rectY = min(xRect->aY, constraints.aHeight);
			float rectWidth = min(xRect->aWidth, constraints.aWidth);
			float rectHeight = min(xRect->aHeight, constraints.aHeight);

			float boxWidth = rectWidth;
			float boxHeight = rectHeight;

			float depth = aDepth;

			float topTexel, bottomTexel, leftTexel, rightTexel ,
				top, bottom, left, right;

			float charX, charY, texWidth, texHeight, offsetX, offsetY,
				advanceX, scaledWidth, scaledHeight;

			float baseWidth = aCurrentFont->aFontTexture->GetSize()->aWidth;
			float baseHeight = aCurrentFont->aFontTexture->GetSize()->aHeight;

			float shadowOffset = 1;
			float pixelSize = xPixelSize;

			FontVertex * vertices = new FontVertex[xText->aNumVertices];
			unsigned long * indices = new unsigned long[xText->aNumIndices];
			//FontVertex * vertices = new FontVertex[4];
			//unsigned long * indices = new unsigned long[6];
			void * mappedVertices = 0;
			void * mappedIndices = 0;

			for (int i = 0; i < inputLength; i += 1)
			{

				charX = FLOAT(font->aCharacters[input[i]].aX);
				charY = FLOAT(font->aCharacters[input[i]].aY);
				texWidth = FLOAT(font->aCharacters[input[i]].aWidth);
				texHeight = FLOAT(font->aCharacters[input[i]].aHeight);
				offsetX = FLOAT(font->aCharacters[input[i]].aXOffset) * pixelSize;
				offsetY = FLOAT(font->aCharacters[input[i]].aYOffset) * pixelSize;
				advanceX = FLOAT(font->aCharacters[input[i]].aXAdvance) * pixelSize;

				scaledWidth = texWidth * pixelSize;
				scaledHeight = texHeight * pixelSize;

				//advanceX *= pixelSize;

				// Check if over the textbox width/height.
				//scaledWidth = currentWidth + scaledWidth + offsetX > boxWidth ? boxWidth - currentWidth - offsetX : scaledWidth;

				if (currentWidth + scaledWidth + offsetX > boxWidth)
				{ 
					float calcWidth = boxWidth - currentWidth;
					float oldS = scaledWidth;
					float oldT = texWidth;
					////texWidth -= (scaledWidth - boxWidth) / (scaledWidth)* texWidth;
					////scaledWidth = boxWidth - currentWidth - offsetX;
					//scaledWidth = 300;

					scaledWidth = scaledWidth - (scaledWidth - calcWidth);

					texWidth = (scaledWidth * oldT) / oldS;

					i = inputLength; // stop rendering letters after this one. CHANGE THE SIZE OF MAPPING ACCORDING TO THIS INDEX
				}

				//if (scaledHeight > boxHeight)
				//{
				//	float old = texHeight;
				//	float good = (scaledHeight - boxHeight) / scaledHeight * texHeight;
				//	texHeight -= (scaledHeight - boxHeight) / (scaledHeight)* texHeight;
				//	//charY += texHeight;
				//	float offset = old - texHeight;
				//	charY += offset;
				//	rectY = scaledHeight - boxHeight;
				//	scaledHeight = boxHeight;

				//}
				//else
				//{
				//	rectY = xRect->aY;
				//}


				if (rectY < scaledHeight)
				{
					float old = texHeight;
					offsetY -= scaledHeight - rectY;
					texHeight -= (scaledHeight - rectY) / scaledHeight * texHeight;

					//texHeight += 0;
					charY += old - texHeight;
					
					scaledHeight -= scaledHeight - rectY;


				}

				// Calculations.
				left = rectX + offsetX;
				top = rectY - offsetY;
				top -= pixelSize * 2;
				//top += constraints.aHeight - pixelSize * 2;
				
				//if (rectY > top)
				//{
				//	//float offset = rectY - top;
				//	//float texOffset = offset * texHeight / scaledHeight;
				//	////texHeight = texOffset;
				//	////charX += texOffset;
				//	////scaledHeight -= offset;
				//	//top += offset;

				//	scaledHeight -= rectY - top - 10;
				//}


				right = left + scaledWidth;
				bottom = top + scaledHeight;

				left = pixelsToRelativePoint(aWindowDims->aWidth, constraints.aX + left);
				top = -pixelsToRelativePoint(aWindowDims->aHeight, constraints.aY + top);
				right = pixelsToRelativePoint(aWindowDims->aWidth, constraints.aX + right);
				bottom = -pixelsToRelativePoint(aWindowDims->aHeight, constraints.aY + bottom);
				
				//float modCharX = charX + 1.0f; // put the modified version here later
				//float modCharY = charY - 1.0f; // aka shadow offsets
				float modCharX = charX;
				float modCharY = charY;

				leftTexel = modCharX / baseWidth;
				rightTexel = (modCharX + texWidth) / baseWidth;
				topTexel = modCharY / baseHeight;
				bottomTexel = (modCharY + texHeight) / baseHeight;

				// Load vertex data.
				vertices[indexV].position = D3DXVECTOR3(left, top, depth);
				vertices[indexV++].texture = D3DXVECTOR2(leftTexel, topTexel);

				vertices[indexV].position = D3DXVECTOR3(left, bottom, depth);
				vertices[indexV++].texture = D3DXVECTOR2(leftTexel, bottomTexel);

				vertices[indexV].position = D3DXVECTOR3(right, top, depth);
				vertices[indexV++].texture = D3DXVECTOR2(rightTexel, topTexel);

				vertices[indexV].position = D3DXVECTOR3(right, bottom, depth);
				vertices[indexV++].texture = D3DXVECTOR2(rightTexel, bottomTexel);

				// Load index data. Counter-clockwise triangles.
				indices[indexI++] = indexV - 2;
				indices[indexI++] = indexV - 3;
				indices[indexI++] = indexV - 4;
				indices[indexI++] = indexV - 3;
				indices[indexI++] = indexV - 2;
				indices[indexI++] = indexV - 1;

				// Prepare for next letter.
				rectX += advanceX;

				// Add measurements.
				currentWidth += advanceX;
			
			}

			// Map vertex and index buffers.
			xText->aVertexBuffer->Map(D3D10_MAP_WRITE_DISCARD, 0, static_cast<void**>(&mappedVertices));
			memcpy(mappedVertices, (void*)vertices, sizeof(FontVertex)* xText->aNumVertices);
			//memcpy(mappedVertices, (void*)vertices, sizeof(FontVertex)* 4);
			//QuadFactory::memcpySSE2QuadVertex(static_cast<TextureVertex*>(mappedVertices), vertices);
			xText->aVertexBuffer->Unmap();

			xText->aIndexBuffer->Map(D3D10_MAP_WRITE_DISCARD, 0, static_cast<void**>(&mappedIndices));
			memcpy(mappedIndices, (void*)indices, sizeof(unsigned long)* xText->aNumIndices);
			//memcpy(mappedIndices, (void*)indices, sizeof(unsigned long)* 6);
			xText->aIndexBuffer->Unmap();

			return true;

		}

	public:
		
		virtual STATUS                 initialize();
	};

}




#endif