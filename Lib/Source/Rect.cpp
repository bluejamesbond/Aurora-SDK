
#include "../../include/ExtLibs.h"
#include "../../include/Rect.h"

using namespace A2D;

void  Rect::memcpySSE2(Rect * xDest, const Rect * xSrc)
{
	// Memcpy built just for Rect and is optimized for
	// 64 bit architecture with use of 128 bit registers.

	__asm
	{
		mov esi, xSrc;
		mov edi, xDest;

		movdqu xmm1, [ESI];
		movdqu [EDI], xmm1;
	}
}