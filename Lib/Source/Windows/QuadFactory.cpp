
#include "../../../Include/Windows/ExtLibs.h"
#include "../../../Include/Windows/QuadFactory.h"

using namespace A2D;

QuadFactory::QuadFactory(ID3D10Device ** xDevice, Dims * xWindowDims)
{
	aDevice = xDevice;
	aWindowDims = xWindowDims;
}

QuadFactory::~QuadFactory()
{
	D3DDESTROY(aVertexBuffer);
	D3DDESTROY(aIndexBuffer);
}

STATUS QuadFactory::initialize()
{
	SAFELY(DXUtils::CreateDefaultDynamicVertexBuffer<ColoredTextureVertex>(*aDevice, &aVertexBuffer, 6));
	SAFELY(DXUtils::CreateDefaultIndexBuffer(*aDevice, &aIndexBuffer, 6));

	return STATUS_OK;
}

// Temporarily moved to cpp to make the build process faster
void QuadFactory::updateVertexBuffer(QuadData<QuadExpansionVertex, 1> * xQuadData, Rect * xRect, Texture * xTexture, BorderSet * xBorderSet, Paint * xPaint, Styles::Background xBackgroundSettings)
{
	Rect& constraints = aConstraints;
	Rect * textureClip = xTexture->GetClip();
	
	//-------------------------------------
	// WARNING: No repeat with textureClip
	//-------------------------------------

	float rectX = xRect->aX;
	float rectY = xRect->aY;
	float rectWidth = xRect->aWidth;
	float rectHeight = xRect->aHeight;

	float winWidth = aWindowDims->aWidth;
	float winHeight = aWindowDims->aHeight;

	float calcLeft, calcTop, calcRight, calcBottom, calcHeight, calcWidth,
		left, width, top, height, texLeft, texTop, texRight, texBottom, texelLeft, texelTop,
		texelRight, texelBottom,
		textureWidth = textureClip->aWidth,
		textureHeight = textureClip->aHeight,
		depth = aDepth;

	QuadExpansionVertex * vertices = xQuadData->aVertices;
	void * mappedVertices = 0;

	calcLeft = max__(rectX, 0.0);
	calcTop = max__(rectY, 0.0);
	calcRight = min__(constraints.aWidth, rectX > 0 ? rectWidth : rectX + rectWidth);
	calcBottom = min__(constraints.aHeight, rectY > 0 ? rectY + rectHeight : rectY + rectHeight);

	calcHeight = calcBottom - calcTop;
	calcWidth = calcRight - calcLeft;
		
	if (xBackgroundSettings.m_layout == Styles::Background::Layout::COVER)
	{
		float usableWidth = rectWidth, 
			  usableHeight = rectHeight,
			  resizeVFactor = 1.0,
			  resizeHFactor = 1.0;

		// Discrete Point of Interest 
		// Proportional Strech Algorithm - @author MK
		// ------------------------------------------
		// offset[C] = quadrant_2[R][C] * (pointOfInterest[C] / quadrant_1[R][C]) - pointOfInterest[C] 
		// where C = X or Y
		//       R = Range
		//  Offset = offset inside quadrant_2
		// and   0 <= pointOfInterest[C] <= quadrant_1[R][C]

		//-----------------------------------------------
		// TEMPORARILY FORCED
		//-----------------------------------------------
		float pointOfInterestX = textureWidth;
		float pointOfInterestY = textureHeight / 2;

		float proportionalConstantX = pointOfInterestX / textureWidth;
		float proportionalConstantY = pointOfInterestY / textureHeight;
		//-----------------------------------------------

		if ((textureWidth / textureHeight) > (usableWidth / usableHeight))
		{
			textureWidth *= resizeVFactor = usableHeight / textureHeight;

			texLeft = (textureWidth - rectWidth) * proportionalConstantX;
			texTop = 0.0;
			texRight = rectWidth + texLeft;
			texBottom = textureHeight;
		}
		else
		{
			textureHeight *= resizeHFactor = usableWidth / textureWidth;

			texLeft = 0.0;
			texTop = (textureHeight - rectHeight) * proportionalConstantY;
			texRight = textureWidth;
			texBottom = rectHeight + texTop;
		}

		texelLeft = texLeft / textureWidth;
		texelTop = texTop / textureHeight;
		texelRight = texRight / textureWidth;
		texelBottom = texBottom / textureHeight;

		// Crop out any regions that might extend out
		// of the contraints
		if (calcWidth < rectWidth)
		{
			texelRight -= (rectWidth - calcWidth) / textureWidth / resizeHFactor;
		}

		if (calcHeight < rectHeight)
		{
			texelBottom -= (rectHeight - calcHeight) / textureHeight / resizeVFactor;
		}

		goto _createAndUpdateVertex;
	}

	texLeft = rectX > 0 ? 0.0f : abs__(rectX);
	texTop = rectY > 0 ? 0.0f : abs__(rectY);
	texRight = calcRight < constraints.aWidth ? rectWidth : calcWidth;
	texBottom = calcBottom < constraints.aHeight ? rectHeight : calcHeight;

	if (xBackgroundSettings.m_layout == Styles::Background::Layout::REPEAT)
	{
		texelLeft = texLeft / textureWidth;
		texelTop = texTop / textureHeight;
		texelRight = (calcWidth + texLeft) / textureWidth;
		texelBottom = (calcHeight + texTop) / textureHeight;
	}
	else /*(xBackgroundSettings == Styles::STRETCH_WIDTH_HEIGHT)*/
	{
		texelLeft = texLeft / rectWidth;
		texelTop = texTop / rectHeight;
		texelRight = texRight / rectWidth;
		texelBottom = texBottom / rectHeight;
	}	

_createAndUpdateVertex:

	left = cvtpx2rp__(winWidth, constraints.aX + calcLeft);
	top = -cvtpx2rp__(winHeight, constraints.aY + calcTop);
	width = cvtpx2rd__(winWidth, calcWidth);
	height = cvtpx2rd__(winHeight, calcHeight);

	// Set up vertices
	vertices[0].aPosition = D3DXVECTOR4(left, top, width, height);
	vertices[0].aColorTex = D3DXVECTOR4(texelLeft, texelTop, texelRight, texelBottom);
	vertices[0].aOptions = D3DXVECTOR4(1.0f, 0.0f, aDepth, 1.0f);
	vertices[0].aBorderColors = A2DUINT4(xBorderSet->m_left.m_color.m_raw,
										 xBorderSet->m_top.m_color.m_raw,
										 xBorderSet->m_right.m_color.m_raw,
									     xBorderSet->m_bottom.m_color.m_raw);
	vertices[0].aBorderWidths = D3DXVECTOR4(cvtpx2rd__(winWidth, xBorderSet->m_left.m_width),
											cvtpx2rd__(winHeight, xBorderSet->m_top.m_width),
											cvtpx2rd__(winWidth, xBorderSet->m_right.m_width),
											cvtpx2rd__(winHeight, xBorderSet->m_bottom.m_width));

	// Lock the vertex buffer.
	xQuadData->aVertexBuffer->Map(D3D10_MAP_WRITE_DISCARD, 0, static_cast<void**>(&mappedVertices));

	// Copy data using SSE2 accelerated method
	memcpy(static_cast<QuadExpansionVertex*>(mappedVertices), vertices, sizeof(QuadExpansionVertex));

	// Unlock the vertex buffer.
	xQuadData->aVertexBuffer->Unmap();
}