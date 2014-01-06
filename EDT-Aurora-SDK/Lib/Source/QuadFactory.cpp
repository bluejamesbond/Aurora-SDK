
#include "../../Include/GLXExtLibs.h"
#include "../../Include/QuadFactory.h"

using namespace A2D;

QuadFactory::QuadFactory(Dims * xWindowDims)
{
//	aDXDevice = xDXDevice;
//	aWindowDims = xWindowDims;
}

QuadFactory::~QuadFactory()
{
//	D3DDESTROY(aVertexBuffer);
//	D3DDESTROY(aIndexBuffer);
}

/*void QuadFactory::setDepth(float xZ)
{
	aDepth = xZ;
}


HRESULT QuadFactory::updateVertexBuffer(QuadData<ColoredTextureVertex> * xQuadData, Rect * xRect, Texture * xTexture, Paint * xPaint, bool xRepeat)
{
	Rect& constraints = aConstraints;
	Rect * textureClip = xTexture->GetClip();
	
	int textureDimsChange = 0;
	int textureClipChange = 0;
	int rectChange = 0;
	int imagePropertiesChange = 0;

	float rectX = xRect->aX;
	float rectY = xRect->aY;
	float rectWidth = xRect->aWidth;
	float rectHeight = xRect->aHeight;

	if (rectX >= constraints.aWidth || rectY >= constraints.aHeight)	return S_OK;

	float calcLeft, calcTop, calcRight, calcBottom, calcHeight, calcWidth,
		left, right, top, bottom, texLeft, texTop, texRight, texBottom, texelLeft, texelTop,
		texelRight, texelBottom,
		textureWidth = textureClip->aWidth,
		textureHeight = textureClip->aHeight,
		depth = aDepth;

	ColoredTextureVertex * vertices = xQuadData->aVertices;
	void * mappedVertices = 0;

	calcLeft = max(rectX, 0);
	calcTop = max(rectY, 0);
	calcRight = min(constraints.aWidth, rectX > 0 ? rectWidth : rectX + rectWidth);
	calcBottom = min(constraints.aHeight, rectY > 0 ? rectHeight : rectY + rectHeight);

	calcHeight = calcBottom - calcTop;
	calcWidth = calcRight - calcLeft;

	left = -aWindowDims->aWidth / 2 + (constraints.aX + calcLeft);
	right = left + calcWidth;
	top = aWindowDims->aHeight / 2 - (constraints.aY + calcTop);
	bottom = top - calcHeight;

	texLeft = rectX > 0 ? 0.0f : abs(rectX);
	texTop = rectY > 0 ? 0.0f : abs(rectY);
	texRight = calcRight < constraints.aWidth ? rectWidth : calcWidth;
	texBottom = calcBottom < constraints.aHeight ? rectHeight : calcHeight;

	texelLeft = xRepeat ? texLeft / textureWidth : texLeft / rectWidth;
	texelTop = xRepeat ? texTop / textureHeight : texTop / rectHeight;
	texelRight = xRepeat ? (calcWidth + texLeft) / textureWidth : texRight / rectWidth;
	texelBottom = xRepeat ? (calcHeight + texTop) / textureHeight : texBottom / rectHeight;
	
	Color3D& topLeftColor = xPaint->aStart;
	Color3D& topRightColor = xPaint->aStart;
	Color3D& bottomLeftColor = xPaint->aEnd;
	Color3D& bottomRightColor = xPaint->aEnd;

	// Set up vertices
	vertices[0].position = D3DXVECTOR3(left, top, depth);  // Top left.
	vertices[0].texture = D3DXVECTOR2(texelLeft, texelTop);
	vertices[0].color = D3DXVECTOR4(topLeftColor.aRed, topLeftColor.aGreen, topLeftColor.aBlue, topLeftColor.aAlpha);

	vertices[1].position = D3DXVECTOR3(right, bottom, depth);  // Bottom right.
	vertices[1].texture = D3DXVECTOR2(texelRight, texelBottom);
	vertices[1].color = D3DXVECTOR4(bottomRightColor.aRed, bottomRightColor.aGreen, bottomRightColor.aBlue, bottomRightColor.aAlpha);

	vertices[2].position = D3DXVECTOR3(left, bottom, depth);  // Bottom left.
	vertices[2].texture = D3DXVECTOR2(texelLeft, texelBottom);
	vertices[2].color = D3DXVECTOR4(bottomLeftColor.aRed, bottomLeftColor.aGreen, bottomLeftColor.aBlue, bottomLeftColor.aAlpha);

	vertices[3].position = D3DXVECTOR3(left, top, depth);  // Top left.
	vertices[3].texture = D3DXVECTOR2(texelLeft, texelTop);
	vertices[3].color = D3DXVECTOR4(topLeftColor.aRed, topLeftColor.aGreen, topLeftColor.aBlue, topLeftColor.aAlpha);

	vertices[4].position = D3DXVECTOR3(right, top, depth);  // Top right.
	vertices[4].texture = D3DXVECTOR2(texelRight, texelTop);
	vertices[4].color = D3DXVECTOR4(topRightColor.aRed, topRightColor.aGreen, topRightColor.aBlue, topRightColor.aAlpha);

	vertices[5].position = D3DXVECTOR3(right, bottom, depth);  // Bottom right.
	vertices[5].texture = D3DXVECTOR2(texelRight, texelBottom);
	vertices[5].color = D3DXVECTOR4(bottomRightColor.aRed, bottomRightColor.aGreen, bottomRightColor.aBlue, bottomRightColor.aAlpha);

	// Lock the vertex buffer.
	SAFELY(xQuadData->aVertexBuffer->Map(D3D10_MAP_WRITE_DISCARD, 0, static_cast<void**>(&mappedVertices)));

	// Copy data using SSE2 accelerated method
	QuadFactory::memcpySSE2QuadVertex(static_cast<ColoredTextureVertex*>(mappedVertices), vertices);

	// Unlock the vertex buffer.
	xQuadData->aVertexBuffer->Unmap();

	return S_OK;

}

HRESULT QuadFactory::updateVertexBuffer(QuadData<TextureVertex> * xQuadData, Rect * xRect, Texture * xTexture, bool xRepeat)
{
	Rect& constraints = aConstraints;
	Rect * textureClip = xTexture->GetClip();

	int textureDimsChange = 0;
	int textureClipChange = 0;
	int rectChange = 0;
	int imagePropertiesChange = 0;

	float rectX = xRect->aX;
	float rectY = xRect->aY;
	float rectWidth = xRect->aWidth;
	float rectHeight = xRect->aHeight;

	if (rectX >= constraints.aWidth || rectY >= constraints.aHeight)	return S_OK;


	// Compare using built in accelerated-function
	rectChange = memcmp(&xQuadData->aPreviousRect, xRect, sizeof(Rect));
	imagePropertiesChange = memcmp(&xQuadData->aPreviousImageProperties, xImageProperties, sizeof(ImageProperties));
	imagePropertiesChange = memcmp(&xQuadData->aPreviousImageProperties, xImageProperties, sizeof(ImageProperties));

	if (!(rectChange | imagePropertiesChange) && !aContraintsChanged)	return hr;

	// Transfer all previous constraints over using accelerated functions
	x_aligned_memcpy_sse2(&xQuadData->aPreviousRect, xRect, sizeof(Rect));
	x_aligned_memcpy_sse2(&xQuadData->aPreviousImageProperties, xImageProperties, sizeof(Rect));
	x_aligned_memcpy_sse2(&xQuadData->aPreviousImageProperties, xImageProperties, sizeof(Rect));


	float calcLeft, calcTop, calcRight, calcBottom, calcHeight, calcWidth,
		left, right, top, bottom, texLeft, texTop, texRight, texBottom, texelLeft, texelTop,
		texelRight, texelBottom,
		textureWidth = textureClip->aWidth,
		textureHeight = textureClip->aHeight,
		depth = aDepth;

	TextureVertex * vertices = xQuadData->aVertices;
	void * mappedVertices = 0;

	calcLeft = max(rectX, 0);
	calcTop = max(rectY, 0);
	calcRight = min(constraints.aWidth, rectX > 0 ? rectWidth : rectX + rectWidth);
	calcBottom = min(constraints.aHeight, rectY > 0 ? rectHeight : rectY + rectHeight);

	calcHeight = calcBottom - calcTop;
	calcWidth = calcRight - calcLeft;

	left = -aWindowDims->aWidth / 2 + (constraints.aX + calcLeft);
	right = left + calcWidth;
	top = aWindowDims->aHeight / 2 - (constraints.aY + calcTop);
	bottom = top - calcHeight;

	texLeft = rectX > 0 ? 0.0f : abs(rectX);
	texTop = rectY > 0 ? 0.0f : abs(rectY);
	texRight = calcRight < constraints.aWidth ? rectWidth : calcWidth;
	texBottom = calcBottom < constraints.aHeight ? rectHeight : calcHeight;

	texelLeft = xRepeat ? texLeft / textureWidth : texLeft / rectWidth;
	texelTop = xRepeat ? texTop / textureHeight : texTop / rectHeight;
	texelRight = xRepeat ? (calcWidth + texLeft) / textureWidth : texRight / rectWidth;
	texelBottom = xRepeat ? (calcHeight + texTop) / textureHeight : texBottom / rectHeight;

	// Set up vertices
	vertices[0].position = D3DXVECTOR3(left, top, depth);  // Top left.
	vertices[0].texture = D3DXVECTOR2(texelLeft, texelTop);

	vertices[1].position = D3DXVECTOR3(right, bottom, depth);  // Bottom right.
	vertices[1].texture = D3DXVECTOR2(texelRight, texelBottom);

	vertices[2].position = D3DXVECTOR3(left, bottom, depth);  // Bottom left.
	vertices[2].texture = D3DXVECTOR2(texelLeft, texelBottom);

	vertices[3].position = D3DXVECTOR3(left, top, depth);  // Top left.
	vertices[3].texture = D3DXVECTOR2(texelLeft, texelTop);

	vertices[4].position = D3DXVECTOR3(right, top, depth);  // Top right.
	vertices[4].texture = D3DXVECTOR2(texelRight, texelTop);

	vertices[5].position = D3DXVECTOR3(right, bottom, depth);  // Bottom right.
	vertices[5].texture = D3DXVECTOR2(texelRight, texelBottom);

	// Lock the vertex buffer.
	SAFELY(xQuadData->aVertexBuffer->Map(D3D10_MAP_WRITE_DISCARD, 0, static_cast<void**>(&mappedVertices)));

	// Copy data using SSE2 accelerated method
	QuadFactory::memcpySSE2QuadVertex(static_cast<TextureVertex*>(mappedVertices), vertices);

	// Unlock the vertex buffer.
	xQuadData->aVertexBuffer->Unmap();

	return S_OK;

}

HRESULT QuadFactory::updateVertexBuffer(QuadData<ColorVertex> * xQuadData, Rect * xRect, Paint * xPaint)
{
	Rect& constraints = aConstraints;

	int textureDimsChange = 0;
	int textureClipChange = 0;
	int rectChange = 0;
	int imagePropertiesChange = 0;

	float rectX = xRect->aX;
	float rectY = xRect->aY;
	float rectWidth = xRect->aWidth;
	float rectHeight = xRect->aHeight;

	if (rectX >= constraints.aWidth || rectY >= constraints.aHeight)	return S_OK;
	
	float calcLeft, calcTop, calcRight, calcBottom, calcHeight, calcWidth,
		left, right, top, bottom, depth = aDepth;

	ColorVertex * vertices = xQuadData->aVertices;
	void * mappedVertices = 0;

	calcLeft = max(rectX, 0);
	calcTop = max(rectY, 0);
	calcRight = min(constraints.aWidth, rectX > 0 ? rectWidth : rectX + rectWidth);
	calcBottom = min(constraints.aHeight, rectY > 0 ? rectHeight : rectY + rectHeight);

	calcHeight = calcBottom - calcTop;
	calcWidth = calcRight - calcLeft;

	left = -aWindowDims->aWidth / 2 + (constraints.aX + calcLeft);
	right = left + calcWidth;
	top = aWindowDims->aHeight / 2 - (constraints.aY + calcTop);
	bottom = top - calcHeight;
	
	Color3D& topLeftColor = xPaint->aStart;
	Color3D& topRightColor = xPaint->aStart;
	Color3D& bottomLeftColor = xPaint->aEnd;
	Color3D& bottomRightColor = xPaint->aEnd;

	// Set up vertices
	vertices[0].position = D3DXVECTOR3(left, top, depth);  // Top left.
	vertices[0].color = D3DXVECTOR4(topLeftColor.aRed, topLeftColor.aGreen, topLeftColor.aBlue, topLeftColor.aAlpha);

	vertices[1].position = D3DXVECTOR3(right, bottom, depth);  // Bottom right.
	vertices[1].color = D3DXVECTOR4(bottomRightColor.aRed, bottomRightColor.aGreen, bottomRightColor.aBlue, bottomRightColor.aAlpha);

	vertices[2].position = D3DXVECTOR3(left, bottom, depth);  // Bottom left.
	vertices[2].color = D3DXVECTOR4(bottomLeftColor.aRed, bottomLeftColor.aGreen, bottomLeftColor.aBlue, bottomLeftColor.aAlpha);

	vertices[3].position = D3DXVECTOR3(left, top, depth);  // Top left.
	vertices[3].color = D3DXVECTOR4(topLeftColor.aRed, topLeftColor.aGreen, topLeftColor.aBlue, topLeftColor.aAlpha);

	vertices[4].position = D3DXVECTOR3(right, top, depth);  // Top right.
	vertices[4].color = D3DXVECTOR4(topRightColor.aRed, topRightColor.aGreen, topRightColor.aBlue, topRightColor.aAlpha);

	vertices[5].position = D3DXVECTOR3(right, bottom, depth);  // Bottom right
	vertices[5].color = D3DXVECTOR4(bottomRightColor.aRed, bottomRightColor.aGreen, bottomRightColor.aBlue, bottomRightColor.aAlpha);

	// Lock the vertex buffer.
	SAFELY(xQuadData->aVertexBuffer->Map(D3D10_MAP_WRITE_DISCARD, 0, static_cast<void**>(&mappedVertices)));

	// Copy data using SSE2 accelerated method
	QuadFactory::memcpySSE2QuadVertex(static_cast<ColorVertex*>(mappedVertices), vertices);

	// Unlock the vertex buffer.
	xQuadData->aVertexBuffer->Unmap();

	return S_OK;

}

void  QuadFactory::memcpySSE2QuadVertex(TextureVertex * xDest, const TextureVertex * xSrc)
{
	// Memcopy built specifically for TextureVertex (120 bytes)
	// Unaligned D3DData
	// @author MK - Based on William Chan and Google

	__asm
	{
		// Store
		mov esi, xSrc;
		mov edi, xDest;

		// No need to prefetch since the 
		// offset is really low

		// Move into Xmms - 128 bit
		movdqu xmm0, 0[ESI];
		movdqu xmm1, 16[ESI];
		movdqu xmm2, 32[ESI];
		movdqu xmm3, 48[ESI];
		movdqu xmm4, 64[ESI];
		movdqu xmm5, 80[ESI];
		movdqu xmm6, 96[ESI];

		movlpd xmm7, 112[ESI];

		movdqu 0[EDI], xmm0;
		movdqu 16[EDI], xmm1;
		movdqu 32[EDI], xmm2;
		movdqu 48[EDI], xmm3;
		movdqu 64[EDI], xmm4;
		movdqu 80[EDI], xmm5;
		movdqu 96[EDI], xmm6;

		movlpd 112[EDI], xmm7;

	}
}

void  QuadFactory::memcpySSE2QuadVertex(ColoredTextureVertex * xDest, const ColoredTextureVertex * xSrc)
{
	// Memcopy built specifically for TextureVertex (216 bytes)
	// Unaligned D3DData
	// @author MK - Based on William Chan and Google

	__asm
	{
		// Store
		mov esi, xSrc;
		mov edi, xDest;

		prefetchnta 128[ESI]; //SSE2 prefetch
		prefetchnta 160[ESI];
		prefetchnta 192[ESI];

		// Move into Xmms - 128 bit
		movdqu xmm0, 0[ESI];
		movdqu xmm1, 16[ESI];
		movdqu xmm2, 32[ESI];
		movdqu xmm3, 48[ESI];
		movdqu xmm4, 64[ESI];
		movdqu xmm5, 80[ESI];
		movdqu xmm6, 96[ESI];
		movdqu xmm7, 112[ESI];

		movdqu 0[EDI], xmm0;
		movdqu 16[EDI], xmm1;
		movdqu 32[EDI], xmm2;
		movdqu 48[EDI], xmm3;
		movdqu 64[EDI], xmm4;
		movdqu 80[EDI], xmm5;
		movdqu 96[EDI], xmm6;
		movdqu 112[EDI], xmm7;

		add esi, 128;
		add edi, 128;				// 128 bytes moved (88 left)

		movdqu xmm0, 0[ESI];
		movdqu xmm1, 16[ESI];
		movdqu xmm2, 32[ESI];
		movdqu xmm3, 48[ESI];
		movdqu xmm4, 64[ESI];
		movlpd xmm5, 80[ESI];

		movdqu 0[EDI], xmm0;
		movdqu 16[EDI], xmm1;
		movdqu 32[EDI], xmm2;
		movdqu 48[EDI], xmm3;
		movdqu 64[EDI], xmm4;
		movlpd 80[EDI], xmm5;
	}
}

void  QuadFactory::memcpySSE2QuadVertex(ColorVertex * xDest, const ColorVertex * xSrc)
{
	// Memcopy built specifically for TextureVertex (216 bytes)
	// Unaligned D3DData
	// @author MK - Based on William Chan and Google

	__asm
	{
		// Store
		mov esi, xSrc;
		mov edi, xDest;

		prefetchnta 128[ESI]; //SSE2 prefetch
		prefetchnta 160[ESI];
		prefetchnta 192[ESI];

		// Move into Xmms - 128 bit
		movdqu xmm0, 0[ESI];
		movdqu xmm1, 16[ESI];
		movdqu xmm2, 32[ESI];
		movdqu xmm3, 48[ESI];
		movdqu xmm4, 64[ESI];
		movdqu xmm5, 80[ESI];
		movdqu xmm6, 96[ESI];
		movdqu xmm7, 112[ESI];

		movdqu 0[EDI], xmm0;
		movdqu 16[EDI], xmm1;
		movdqu 32[EDI], xmm2;
		movdqu 48[EDI], xmm3;
		movdqu 64[EDI], xmm4;
		movdqu 80[EDI], xmm5;
		movdqu 96[EDI], xmm6;
		movdqu 112[EDI], xmm7;

		add esi, 128;
		add edi, 128;				// 128 bytes moved (88 left)

		movdqu xmm0, 0[ESI];
		movdqu xmm1, 16[ESI];
		movdqu xmm2, 32[ESI];
		movdqu xmm3, 48[ESI];
		movdqu xmm4, 64[ESI];
		movlpd xmm5, 80[ESI];

		movdqu 0[EDI], xmm0;
		movdqu 16[EDI], xmm1;
		movdqu 32[EDI], xmm2;
		movdqu 48[EDI], xmm3;
		movdqu 64[EDI], xmm4;
		movlpd 80[EDI], xmm5;
	}
}

void QuadFactory::renderQuad(ID3D10Buffer * xVertexBuffer, unsigned int xStride)
{
	ID3D10Device  *	device = *aDXDevice;
	unsigned int offset = 0;

	// Set the vertex buffer to active in the input 
	// assembler so it can be rendered.
	device->IASetVertexBuffers(0, 1, &xVertexBuffer, &xStride, &offset);

	// Set the index buffer to active in the input
	// assembler so it can be rendered.
	device->IASetIndexBuffer(aIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
}

bool QuadFactory::setConstraints(Rect * xContraints, float xZ)
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
*/
HRESULT QuadFactory::initialize()
{
//	SAFELY(DXShapeUtils::CreateDefaultDynamicVertexBuffer<ColoredTextureVertex>(*aDXDevice, &aVertexBuffer, 6));
//	SAFELY(DXShapeUtils::CreateDefaultIndexBuffer(*aDXDevice, &aIndexBuffer, 6));

	return S_OK;
}

LPCWSTR QuadFactory::getClass()
{
    return "QuadFactory";
}

LPCWSTR QuadFactory::toString()
{
    return "QuadFactory";
}
