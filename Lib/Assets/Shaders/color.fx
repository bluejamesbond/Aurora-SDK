//+-----------------------------------------------------------------------------
//
//  Shader:  
//      COLOR.fx
//
//  Synopsis:
//      Texture container class.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// GLOBAL
//------------------------------------------------------------------------------
matrix worldMatrix; // unused
matrix viewMatrix;  // unused
matrix projectionMatrix; // unused

//------------------------------------------------------------------------------
// STRUCTS
//------------------------------------------------------------------------------
struct ColorVertex
{
    float4 position : POSITION;
    float4 color : COLOR;
};

struct ColorPixel
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
};

// UNUSED
struct QuadFillVertex
{
	float4 position : POSITION0;       // [left, top, right, bottom]
	float4 options : POSITION1;        // [reserved, reserved, z, opacity]
	uint4  colors : UINT4_0;		   // [leftColor, topColor, rightColor, bottomColor]
};

//------------------------------------------------------------------------------
// FUNCTIONS
//------------------------------------------------------------------------------

//#ARGB to (Rf, Gf, Bf, Af)
float4 ARGBtoFloat4(uint color)
{
	return float4(((color >> 24) & 0xFF) / 255, ((color >> 16) & 0xFF) / 255, ((color >> 8) & 0xFF) / 255, 1.0);
}

//------------------------------------------------------------------------------
// VS
//------------------------------------------------------------------------------
ColorPixel ColorVertexShader(ColorVertex input)
{
	ColorPixel output;
        
	// Force w-buffer to be 1.0
	input.position.w = 1.0f;

	// Calculate z-buffer manually
	input.position.z = (10000000 - input.position.z) / 10000000;

	// Calculate the position of the vertex 
	// against the world, view, and projection matrices.
    output.position = input.position; 

	// Store the input color for the 
	// pixel shader to use.
    output.color = input.color;
    
	return output;
}

//------------------------------------------------------------------------------
// PS
//------------------------------------------------------------------------------
float4 ColorPixelShader(ColorPixel input) : SV_Target
{
    return input.color;
}

//------------------------------------------------------------------------------
// TECHNIQUE
//------------------------------------------------------------------------------
technique10 ColorTechnique
{
    pass pass0
    {
        SetVertexShader(CompileShader(vs_4_0, ColorVertexShader()));
        SetPixelShader(CompileShader(ps_4_0, ColorPixelShader()));
        SetGeometryShader(NULL);
    }
}