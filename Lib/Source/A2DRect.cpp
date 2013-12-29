
#include "../../include/A2DExtLibs.h"
#include "../../include/A2DRect.h"

void  A2DRect::memcpySSE2(A2DRect * xDest, const A2DRect * xSrc)
{
	// Memcpy built just for A2DRect and is optimized for
	// 64 bit architecture with use of 128 bit registers.

	__asm
	{
		mov esi, xSrc;
		mov edi, xDest;

		movdqu xmm1, [ESI];
		movdqu [EDI], xmm1;
	}
}