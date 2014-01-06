
#include "../../include/ExtLibs.h"
#include "../../include/RootPane.h"

using namespace A2D;

void  ImageProperties::memcpySSE2(ImageProperties * xDest, const ImageProperties * xSrc)
{
	// Memcpy built just for Rect and is optimized for
	// 64 bit architecture with use of 128 bit registers.
	// Use this for memcpy

	__asm
	{
		mov esi, xSrc;
		mov edi, xDest;

		movdqu xmm1, [esi];
		movdqu[edi], xmm1;
	}
}
