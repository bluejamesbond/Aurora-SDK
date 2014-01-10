
#include "../../../Include/Windows/ExtLibs.h"
#include "../../../Include/Windows/VertexTypes.h"

using namespace A2D;

D3D10_INPUT_ELEMENT_DESC QuadExpansionVertex::aPolygonLayout[] =
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D10_APPEND_ALIGNED_ELEMENT, D3D10_INPUT_PER_VERTEX_DATA, 0 },
	{ "POSITION", 1, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D10_APPEND_ALIGNED_ELEMENT, D3D10_INPUT_PER_VERTEX_DATA, 0 },
	{ "POSITION", 2, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D10_APPEND_ALIGNED_ELEMENT, D3D10_INPUT_PER_VERTEX_DATA, 0 },
	{ "POSITION", 3, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D10_APPEND_ALIGNED_ELEMENT, D3D10_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D10_APPEND_ALIGNED_ELEMENT, D3D10_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR", 1, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D10_APPEND_ALIGNED_ELEMENT, D3D10_INPUT_PER_VERTEX_DATA, 0 }
};

D3D10_INPUT_ELEMENT_DESC ColoredTextureVertex::aPolygonLayout[] =
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D10_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D10_APPEND_ALIGNED_ELEMENT, D3D10_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D10_APPEND_ALIGNED_ELEMENT, D3D10_INPUT_PER_VERTEX_DATA, 0 }
};


D3D10_INPUT_ELEMENT_DESC ColorVertex::aPolygonLayout[] =
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D10_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D10_APPEND_ALIGNED_ELEMENT, D3D10_INPUT_PER_VERTEX_DATA, 0 }
};

D3D10_INPUT_ELEMENT_DESC TextureVertex::aPolygonLayout[] =
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D10_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D10_APPEND_ALIGNED_ELEMENT, D3D10_INPUT_PER_VERTEX_DATA, 0 }
};

void  TextureVertex::memcpySSE2(TextureVertex * xDest, const TextureVertex * xSrc)
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