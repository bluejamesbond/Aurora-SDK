
#include "../../include/ExtLibs.h"
#include "../../include/QuadFactory.h"

using namespace A2D;

QuadFactory::QuadFactory(ID3D10Device ** xDXDevice, Dims * xWindowDims) : aDXDevice(xDXDevice), aWindowDims(xWindowDims){}

QuadFactory::~QuadFactory()
{
	D3DDESTROY(aVertexBuffer);
	D3DDESTROY(aIndexBuffer);
}

bool QuadFactory::setConstraints(QuadData * aQuadData, Rect * xContraints)
{

	Rect::memcpySSE2(&aConstraints, xContraints);

	// WHy store constraints into every QuadData
//	if (memcmp(&aQuadData->aPreviousContraints, xContraints, sizeof(Rect)) != 0)
//	{
//		x_aligned_memcpy_sse2(&aQuadData->aPreviousContraints, xContraints, sizeof(Rect));
//		return aContraintsChanged = true;
//	}
//	else
//	{
//		return aContraintsChanged = false;
//	}

	return true;
}

HRESULT QuadFactory::updateVertexBuffer(QuadData * aQuadData, Rect * xRect, Rect * xTextureClip,
					Dims * xTextureDims, ImageProperties * xImageProperties)
{
	HRESULT hr = S_OK;

	Rect& constraints = aConstraints;

	int textureDimsChange = 0;
	int textureClipChange = 0;
	int rectChange = 0;
	int imagePropertiesChange = 0;

	float rectX = xRect->aX;
	float rectY = xRect->aY;
	float rectWidth = xRect->aWidth;
	float rectHeight = xRect->aHeight;
		
	if (rectX >= constraints.aWidth || rectY >= constraints.aHeight)	return hr;
	
	/*
	// Compare using built in accelerated-function
	rectChange = memcmp(&aQuadData->aPreviousRect, xRect, sizeof(Rect));
	imagePropertiesChange = memcmp(&aQuadData->aPreviousImageProperties, xImageProperties, sizeof(ImageProperties));
	imagePropertiesChange = memcmp(&aQuadData->aPreviousImageProperties, xImageProperties, sizeof(ImageProperties));

	if (!(rectChange | imagePropertiesChange) && !aContraintsChanged)	return hr;

	// Transfer all previous constraints over using accelerated functions
	x_aligned_memcpy_sse2(&aQuadData->aPreviousRect, xRect, sizeof(Rect));
	x_aligned_memcpy_sse2(&aQuadData->aPreviousImageProperties, xImageProperties, sizeof(Rect));
	x_aligned_memcpy_sse2(&aQuadData->aPreviousImageProperties, xImageProperties, sizeof(Rect));
		*/

	bool repeat;

	float calcLeft, calcTop, calcRight, calcBottom, calcHeight, calcWidth,
		left, right, top, bottom, texLeft, texTop, texRight, texBottom, texelLeft, texelTop,
		texelRight, texelBottom, 
		textureWidth = xTextureClip->aWidth,
		textureHeight = xTextureClip->aHeight,
		aOrigWidth = rectWidth,
		aOrigHeight = rectHeight;

	ColoredTextureVertex * vertices = aQuadData->aVertices;
	void * mappedVertices = 0;
	
	// Add as static method to Image properties
	repeat = (xImageProperties->aOptRepeat >= _OPT_BACKGROUND_REPEAT_REPEAT_X) && 
			  (xImageProperties->aOptRepeat <= (_OPT_BACKGROUND_REPEAT_REPEAT_X | _OPT_BACKGROUND_REPEAT_REPEAT_Y));
	
	repeat = true;
	
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
	texRight = calcRight < constraints.aWidth ? aOrigWidth : calcWidth;
	texBottom = calcBottom < constraints.aHeight ? aOrigHeight : calcHeight;

	texelLeft = repeat ? texLeft / textureWidth : texLeft / aOrigWidth;
	texelTop = repeat ? texTop / textureHeight : texTop / aOrigHeight;
	texelRight = repeat ? (calcWidth + texLeft) / textureWidth : texRight / aOrigWidth;
	texelBottom = repeat ? (calcHeight + texTop) / textureHeight : texBottom / aOrigHeight;
	
	// Set up vertices
	vertices[0].position = D3DXVECTOR3(left, top, 0.0f);  // Top left.
	vertices[0].texture = D3DXVECTOR2(texelLeft, texelTop);
	vertices[0].color = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f);

	vertices[1].position = D3DXVECTOR3(right, bottom, 0.0f);  // Bottom right.
	vertices[1].texture = D3DXVECTOR2(texelRight, texelBottom);
	vertices[1].color = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f);

	vertices[2].position = D3DXVECTOR3(left, bottom, 0.0f);  // Bottom left.
	vertices[2].texture = D3DXVECTOR2(texelLeft, texelBottom);
	vertices[2].color = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f);

	vertices[3].position = D3DXVECTOR3(left, top, 0.0f);  // Top left.
	vertices[3].texture = D3DXVECTOR2(texelLeft, texelTop);
	vertices[3].color = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f);

	vertices[4].position = D3DXVECTOR3(right, top, 0.0f);  // Top right.
	vertices[4].texture = D3DXVECTOR2(texelRight, texelTop);
	vertices[4].color = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f);

	vertices[5].position = D3DXVECTOR3(right, bottom, 0.0f);  // Bottom right.
	vertices[5].texture = D3DXVECTOR2(texelRight, texelBottom);
	vertices[5].color = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f);
	
	// Lock the vertex buffer.
	hr = aQuadData->aVertexBuffer->Map(D3D10_MAP_WRITE_DISCARD, 0, static_cast<void**>(&mappedVertices));
	if (FAILED(hr))	return hr;
	
	// Copy data using SSE2 accelerated method
	QuadFactory::memcpySSE2QuadColoredTextureVertex(static_cast<ColoredTextureVertex*>(mappedVertices), vertices);

	// Unlock the vertex buffer.
	aQuadData->aVertexBuffer->Unmap();

	return hr;

}

unsigned int QuadFactory::aStride = sizeof(ColoredTextureVertex);
unsigned int QuadFactory::aOffset = 0;

void QuadFactory::RenderQuad(QuadData * aQuadData)
{
	ID3D10Device  *	device = *aDXDevice;

	// Set the vertex buffer to active in the input 
	// assembler so it can be rendered.
	device->IASetVertexBuffers(0, 1, &aQuadData->aVertexBuffer, &aStride, &aOffset);

	// Set the index buffer to active in the input
	// assembler so it can be rendered.
	device->IASetIndexBuffer(aIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

	// Set the type of primitive that should be 
	// rendered from this vertex buffer, in this case triangles.
	device->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return;
}

void  QuadFactory::memcpySSE2QuadTextureVertex(TextureVertex * xDest, const TextureVertex * xSrc)
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

void  QuadFactory::memcpySSE2QuadColoredTextureVertex(ColoredTextureVertex * xDest, const ColoredTextureVertex * xSrc)
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

HRESULT QuadFactory::initialize()
{
	SAFELY(DXShapeUtils::CreateDefaultDynamicVertexBuffer<ColoredTextureVertex>(*aDXDevice, &aVertexBuffer, 6));
	SAFELY(DXShapeUtils::CreateDefaultIndexBuffer(*aDXDevice, &aIndexBuffer, 6));

	return S_OK;
}

LPCWSTR QuadFactory::getClass()
{
	return L"QuadFactory";
}

LPCWSTR QuadFactory::toString()
{
	return L"QuadFactory";
}