////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __IMS_H__
#define __IMS_H__

//+-----------------------------------------------------------------------------
//
//  Class:  
//      IMS
//
//  Synopsis:
//      Texture container class.
//
//------------------------------------------------------------------------------

namespace A2D {
	
	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

	struct Dims
	{
		float			aWidth;
		float			aHeight;

		inline Dims() :
			aWidth(0.0f),
			aHeight(0.0f)
		{
		}


		inline Dims(float x_width, float x_height) :
			aWidth(x_width),
			aHeight(x_height)
		{
		}

		static inline void memcpySSE2(Dims * xDest, const Dims * xSrc)
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
	};
}

#endif