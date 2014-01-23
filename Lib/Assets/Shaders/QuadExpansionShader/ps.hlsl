
// Aurora-SDK

#include "hd.hlsli"

//------------------------------------------------------------------------------
// PER-FRAME RESOURCES
//------------------------------------------------------------------------------
Texture2D shaderTexture;
SamplerState sampleType;

//------------------------------------------------------------------------------
// ENTRY POINT
//------------------------------------------------------------------------------
float4 main(PX_QUADEXPANSION input) : SV_Target
{
	float isColorTex = input.options[0];
	float opacity = input.options[1];

	if (isColorTex == 0.0) // Color only
	{
		return float4(input.colorTex.rgb, input.colorTex.a * opacity);
	}
	else if (isColorTex == 1.0) // Texture only
	{
		float4 color = shaderTexture.Sample(sampleType, float2(input.colorTex[0], input.colorTex[1]));

		return float4(color.rgb, color.a * opacity);
	}
	else // Texture and color
	{
		return input.colorTex;
	}
}