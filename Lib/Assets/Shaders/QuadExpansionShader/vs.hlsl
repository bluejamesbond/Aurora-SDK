struct QuadVertex
{
	float4 position : POSITION0;
	float4 options : POSITION1;      // [text/color/both, opacity, reserved, reserved]      NOTE: contents must be in float. 
	float4 borderWidths : POSITION2; // [leftWidth, topWidth, rightWidth, bottomWidth]      NOTE: contents must be in float.
	float4 borderRadius : POSITION3; // [leftRadius, topRadius, rightRadius, bottomRadius]  NOTE: contents must be in float.
	float4 colorTex : COLOR0;
	uint4 borderColors : UINT4_0;    // [leftColor, topColor, rightColor, bottomColor]      NOTE: contents must be in uint4.
};
 

float4 main( float4 pos : POSITION ) : SV_POSITION
{
	return pos;
}