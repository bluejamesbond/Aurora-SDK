
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
bool QuadFactory::updateVertexBuffer(QuadData<QuadExpansionVertex, 1> * xQuadData, Rect * xRect, Texture * xTexture, BorderSet * xBorderSet, Paint * xPaint, Styles::Background xBackgroundSettings)
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

	calcLeft = max(rectX, 0);
	calcTop = max(rectY, 0);
	calcRight = min(constraints.aWidth, rectX > 0 ? rectWidth : rectX + rectWidth);
	calcBottom = min(constraints.aHeight, rectY > 0 ? rectY + rectHeight : rectY + rectHeight);

	calcHeight = calcBottom - calcTop;
	calcWidth = calcRight - calcLeft;
	
	texLeft = rectX > 0 ? 0.0f : abs(rectX);
	texTop = rectY > 0 ? 0.0f : abs(rectY);
	texRight = calcRight < constraints.aWidth ? rectWidth : calcWidth;
	texBottom = calcBottom < constraints.aHeight ? rectHeight : calcHeight;
	
	if (xBackgroundSettings == Styles::COVER_TOP_LEFT)
	{
		float usableWidth = min(calcWidth, rectWidth), 
			  usableHeight = min(calcHeight, rectHeight),
			  resizeFactor = 1.0;

		bool stretch = false;

		if ((textureWidth / textureHeight) > (usableWidth / usableHeight))
		{
			textureWidth *= resizeFactor = usableHeight / textureHeight;
			stretch = true;
		}
		else
		{
			textureHeight *= resizeFactor = usableWidth / textureWidth;
			stretch = false;
		}

		texelLeft = 0.0;
		texelTop = 0.0;
		texelRight = stretch ? texRight / textureWidth : 1.0;
		texelBottom = stretch ? 1.0 : texBottom / textureHeight;
	}
	else if (xBackgroundSettings == Styles::REPEAT_X_Y)
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

	left = pixelsToRelativePoint(winWidth, constraints.aX + calcLeft);
	top = -pixelsToRelativePoint(winHeight, constraints.aY + calcTop);
	width = pixelsToRelativeDistance(winWidth, calcWidth);
	height = pixelsToRelativeDistance(winHeight, calcHeight);

	// Set up vertices
	vertices[0].aPosition = D3DXVECTOR4(left, top, width, height);
	vertices[0].aColorTex = D3DXVECTOR4(texelLeft, texelTop, texelRight, texelBottom);
	vertices[0].aOptions = D3DXVECTOR4(1.0f, 0.0f, aDepth, 1.0f);
	vertices[0].aBorderColors = A2DUINT4(xBorderSet->m_left.m_color.m_raw,
										 xBorderSet->m_top.m_color.m_raw,
										 xBorderSet->m_right.m_color.m_raw,
									     xBorderSet->m_bottom.m_color.m_raw);
	vertices[0].aBorderWidths = D3DXVECTOR4(pixelsToRelativeDistance(winWidth, xBorderSet->m_left.m_width),
											pixelsToRelativeDistance(winHeight, xBorderSet->m_top.m_width),
											pixelsToRelativeDistance(winWidth, xBorderSet->m_right.m_width),
											pixelsToRelativeDistance(winHeight, xBorderSet->m_bottom.m_width));

	// Lock the vertex buffer.
	xQuadData->aVertexBuffer->Map(D3D10_MAP_WRITE_DISCARD, 0, static_cast<void**>(&mappedVertices));

	// Copy data using SSE2 accelerated method
	memcpy(static_cast<QuadExpansionVertex*>(mappedVertices), vertices, sizeof(QuadExpansionVertex));

	// Unlock the vertex buffer.
	xQuadData->aVertexBuffer->Unmap();

	return true;
}