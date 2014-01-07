
#include "../../../include/Core/ExtLibs.h"
#include "../../../include/Core/Dims.h"

using namespace A2D;

void  Dims::memcpySSE2(Dims * xDest, const Dims * xSrc)
{
	// Memcpy built just for Rect and is optimized for
	// 64 bit architecture with use of 128 bit registers.
	// Use this for memcpy

	__asm
	{
		mov esi, xSrc;
		mov edi, xDest;

		movlpd xmm0, 0[ESI]; // 64 bits
		movlpd[edi], xmm1;   // 64 bits
	}
}
