
#include "../../include/ExtLibs.h"
#include "../../include/Rect.h"

using namespace A2D;

void  Rect::memcpySSE2(Rect * xDest, const Rect * xSrc)
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

byte Rect::memeqlSSE4(Rect * xComp1, Rect * xComp2)
{
	// Memcpy built just for Rect and is optimized for
	// 64 bit architecture with use of 128 bit registers.
	// DO NOT USE THIS!

	byte result = 0;

	__asm
	{
		mov esi, xComp1;
		mov edx, xComp2;
		xor cl, cl;

		movdqu xmm0, [ESI];
		movdqu xmm1, [EDX];

		pxor   xmm1, xmm0;
		ptest  xmm1, xmm1;

		jz equal;

		add cl, 1;
	equal:
		mov result, cl;
	};

	return result;
}


// TEST

//A2D::Rect a1;
//a1.aX = 10.0f;
//a1.aY = 0.0f;
//a1.aWidth = 10.f;
//a1.aHeight = 0.0f;
//
//A2D::Rect a2;
//a2.aX = 10.0f;
//a2.aY = 0.0f;
//a2.aWidth = 11.f;
//a2.aHeight = 0.0f;
//
//clock_t tStart = clock();
//
//for (int y = 0; y < 100000000; y++)
//{
//	A2D::Rect::memcpySSE2(&a1, &a2);
//}
//
//SYSOUT_F("FPS %.5f\n", ((double)(clock() - tStart) / CLOCKS_PER_SEC));
//
//tStart = clock();
//
//for (int y = 0; y < 100000000; y++)
//{
//	memcpy(&a1, &a2, sizeof(A2D::Rect));
//}
//
//SYSOUT_F("FPS %.5f\n", ((double)(clock() - tStart) / CLOCKS_PER_SEC));
//
//
//for (int y = 0; y < 100000000; y++)
//{
//	A2D::Rect::memeqlSSE4(&a1, &a2);
//}
//
//SYSOUT_F("FPS %.5f\n", ((double)(clock() - tStart) / CLOCKS_PER_SEC));
//
//tStart = clock();
//
//for (int y = 0; y < 100000000; y++)
//{
//	memcmp(&a1, &a2, sizeof(A2D::Rect));
//}
//
//SYSOUT_F("FPS %.5f\n", ((double)(clock() - tStart) / CLOCKS_PER_SEC));