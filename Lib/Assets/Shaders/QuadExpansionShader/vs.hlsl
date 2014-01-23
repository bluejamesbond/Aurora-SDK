
// Aurora-SDK

#include "hd.hlsli"
 
PX_QUADEXPANSION main(VX_QUADEXPANSION quadVertex)
{
	PX_QUADEXPANSION quadPixel;

	quadPixel.position = quadVertex.position;
	quadPixel.colorTex = quadVertex.colorTex;
	quadPixel.options = float4(0.0f, 0.0f, 0.0f, 0.0f);

	return quadPixel;
}