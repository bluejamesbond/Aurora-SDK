
// Aurora-SDK

//------------------------------------------------------------------------------
// INPUT STRUCTURE
//------------------------------------------------------------------------------
struct PX_QUADEXPANSION
{
	float4 position : SV_POSITION;
	float4 colorTex : COLOR;

	// [texture/color/both, opacity, reserved, reserved]
	nointerpolation float4 options : FLOAT4;
};

//------------------------------------------------------------------------------
// OUPUT STRUCTURE
//------------------------------------------------------------------------------
struct VX_QUADEXPANSION
{
	float4 position		: POSITION0;
	float4 options		: POSITION1;    // [text/color/both, opacity, reserved, reserved]      NOTE: contents must be in float. 
	float4 borderWidths : POSITION2;	// [leftWidth, topWidth, rightWidth, bottomWidth]      NOTE: contents must be in float.
	float4 borderRadius : POSITION3;	// [leftRadius, topRadius, rightRadius, bottomRadius]  NOTE: contents must be in float.
	float4 colorTex		: COLOR0;
	uint4 borderColors	: UINT4_0;		// [leftColor, topColor, rightColor, bottomColor]      NOTE: contents must be in uint4.
};

//------------------------------------------------------------------------------
// ADDITIONAL FUNCTIONS
//------------------------------------------------------------------------------
float4 ARGBtoFloat4(uint color)
{
	//#ARGB to (Rf, Gf, Bf, Af)
	return float4(((color >> 24) & 0xFF) / 255.0, ((color >> 16) & 0xFF) / 255.0, ((color >> 8) & 0xFF) / 255.0, (color & 0xFF) / 255.0);
}
