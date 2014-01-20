//+-----------------------------------------------------------------------------
//
//  Shader:  
//      QUAD.fx
//
//  Synopsis:
//      Texture container class.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// GLOBAL
//------------------------------------------------------------------------------

Texture2D shaderTexture : register(ps_4_0, t[0]) ;

//------------------------------------------------------------------------------
// SAMPLER
//------------------------------------------------------------------------------

SamplerState SampleType
{
	Filter = MIN_MAG_MIP_LINEAR;
	AddressU = Wrap;
	AddressV = Wrap;
};

//------------------------------------------------------------------------------
// STRUCTS
//------------------------------------------------------------------------------
struct QuadVertex
{
	float4 position : POSITION0;
	float4 options : POSITION1;      // [text/color/both, opacity, reserved, reserved]      NOTE: contents must be in float. 
	float4 borderWidths : POSITION2; // [leftWidth, topWidth, rightWidth, bottomWidth]      NOTE: contents must be in float.
	float4 borderRadius : POSITION3; // [leftRadius, topRadius, rightRadius, bottomRadius]  NOTE: contents must be in float.
	float4 colorTex : COLOR0;
	uint4 borderColors : UINT4_0;    // [leftColor, topColor, rightColor, bottomColor]      NOTE: contents must be in uint4.
};

// >>>>>>> Proposed for future
// >>>>>>> [complexOptions, opacity, reserved, reserved]
//
// ------------------------- ComplexOptions - BitLayout ------------------------
//
//  Values are 32 bit values laid out as follows:
//
//   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
//  +-+-+-+-+-+---------------------+-------------------------------+
//  |r|r|r|C|I|   TextureSlice      |            Z-Index            |
//  +-+-+-+-+-+---------------------+-------------------------------+
//
//  where
//
//      C - Contents - indicates whether the contents in float4: colorTex
//                     are representing texture or color                 
//
//          0 - true (Texture)
//          1 - false (Color) 
//
//      B - InsetBorder - indicates whether the borders are inset or
//                        outset
//
//      r - reserved for future use
//
//------------------------------------------------------------------------------

struct QuadPixel
{
	float4 position : SV_POSITION;
	float4 colorTex : COLOR;
	nointerpolation float4 options : FLOAT4; // [texture/color/both, opacity, reserved, reserved]
};

//------------------------------------------------------------------------------
// FUNCTIONS
//------------------------------------------------------------------------------

//#ARGB to (Rf, Gf, Bf, Af)
float4 ARGBtoFloat4(uint color)
{
	return float4(((color >> 24) & 0xFF) / 255.0, ((color >> 16) & 0xFF) / 255.0, ((color >> 8) & 0xFF) / 255.0, (color & 0xFF) / 255.0);
}

//------------------------------------------------------------------------------
// VS
//------------------------------------------------------------------------------

QuadVertex QuadCollapsedShader(QuadVertex input)
{
	return input;
}

//------------------------------------------------------------------------------
// GS
//------------------------------------------------------------------------------

[maxvertexcount(24)]
void QuadExpansionShader(point QuadVertex input[1], inout TriangleStream<QuadPixel> quadStream)
{
	QuadPixel main, border;
	
	bool insetBorder = false;

	float width = input[0].position[2];
	float height = input[0].position[3];

	float left = input[0].position[0];
	float top = input[0].position[1];
	float right = left + width;
	float bottom = top - height;

	float borderLeftWidth = input[0].borderWidths[0];
	float borderTopWidth = input[0].borderWidths[1];
	float borderRightWidth = input[0].borderWidths[2];
	float borderBottomWidth = input[0].borderWidths[3];

	float4 borderLeftColor = ARGBtoFloat4(input[0].borderColors[0]);
	float4 borderTopColor = ARGBtoFloat4(input[0].borderColors[1]);
	float4 borderRightColor = ARGBtoFloat4(input[0].borderColors[2]);
	float4 borderBottomColor = ARGBtoFloat4(input[0].borderColors[3]);

	bool hasLeftBorder = borderLeftWidth > 0;
	bool hasTopBorder = borderTopWidth > 0;
	bool hasRightBorder = borderRightWidth > 0;
	bool hasBottomBorder = borderBottomWidth > 0;

	float z = (10000000 - input[0].options[2]) / 10000000;
	float opacity = input[0].options[3];

	//**********************************************************************
	// Main
	//**********************************************************************
	float4 mainTexels = input[0].colorTex;

	main.options = float4(1.0f, opacity, 0, 0);
	// main.colorTex = float4(input[0].colorTex.rgb, input[0].colorTex.a * opacity);
	
	//bottom left
	main.position = float4(left, bottom, z, 1);
	main.colorTex = float4(mainTexels[0], mainTexels[3], 0, 0);
	quadStream.Append(main);
	//top left
	main.position = float4(left, top, z, 1);
	main.colorTex = float4(mainTexels[0], mainTexels[1], 0, 0);
	quadStream.Append(main);
	//bottom right
	main.position = float4(right, bottom, z, 1);
	main.colorTex = float4(mainTexels[2], mainTexels[3], 0, 0);
	quadStream.Append(main);
	//top right
	main.position = float4(right, top, z, 1);
	main.colorTex = float4(mainTexels[2], mainTexels[1], 0, 0);
	quadStream.Append(main);

	// Reset
	quadStream.RestartStrip();
	
	//**********************************************************************
	// Borders
	//**********************************************************************
	z = (10000000 - (input[0].options[2] + 0.5)) / 10000000;
	// 0.0 indicates color coordinates
	// 1.0 indicates texture coordinates
	// 2.0 indicates texture on backgroundColor
	border.options = float4(0.0f, opacity, 0, 0);

	//*******************************
	// Left
	//*******************************
	if (hasLeftBorder && borderLeftColor.a)
	{
		border.colorTex = borderLeftColor;

		if (insetBorder)
		{
			//bottom left
			border.position = float4(left, bottom, z, 1);
			quadStream.Append(border);
			//top left
			border.position = float4(left, top, z, 1);
			quadStream.Append(border);
			//bottom right
			border.position = float4(left + borderLeftWidth, (hasBottomBorder ? bottom + borderBottomWidth : bottom), z, 1);
			quadStream.Append(border);
			//top right
			border.position = float4(left + borderLeftWidth, (hasTopBorder ? top - borderTopWidth : top), z, 1);
			quadStream.Append(border);
		}
		else
		{
			//bottom left
			border.position = float4(left - borderLeftWidth, (hasBottomBorder ? bottom - borderBottomWidth : bottom), z, 1);
			quadStream.Append(border);
			//top left
			border.position = float4(left - borderLeftWidth, (hasTopBorder ? top + borderTopWidth : top), z, 1);
			quadStream.Append(border);
			//bottom right
			border.position = float4(left, bottom, z, 1);
			quadStream.Append(border);
			//top right
			border.position = float4(left, top, z, 1);
			quadStream.Append(border);
		}

		// Reset
		quadStream.RestartStrip();
	}


	//*******************************
	// Top
	//*******************************
	if (hasTopBorder && borderTopColor.a)
	{
		border.colorTex = borderTopColor;

		if (insetBorder)
		{
			//bottom left
			border.position = float4((hasLeftBorder ? left + borderLeftWidth : left), top - borderTopWidth, z, 1);
			quadStream.Append(border);
			//top left
			border.position = float4(left, top, z, 1);
			quadStream.Append(border);
			//bottom right
			border.position = float4((hasRightBorder ? right - borderRightWidth : right), top - borderTopWidth, z, 1);
			quadStream.Append(border);
			//top right
			border.position = float4(right, top, z, 1);
			quadStream.Append(border);

			// Reset
			quadStream.RestartStrip();
		}
		else
		{
			//bottom left
			border.position = float4(left, top, z, 1);
			quadStream.Append(border);
			//top left
			border.position = float4((hasLeftBorder ? left - borderLeftWidth : left), top + borderTopWidth, z, 1);
			quadStream.Append(border);
			//bottom right
			border.position = float4(right, top, z, 1);
			quadStream.Append(border);
			//top right
			border.position = float4((hasRightBorder ? right + borderRightWidth : right), top + borderTopWidth, z, 1);
			quadStream.Append(border);

			// Reset
			quadStream.RestartStrip();

		}
	}

	//*******************************
	// Right
	//*******************************
	if (hasRightBorder && borderRightColor.a)
	{
		border.colorTex = borderRightColor;

		if (insetBorder)
		{
			//bottom left
			border.position = float4(right - borderRightWidth, (hasBottomBorder ? bottom + borderBottomWidth : bottom), z, 1);
			quadStream.Append(border);
			//top left
			border.position = float4(right - borderRightWidth, (hasTopBorder ? top - borderTopWidth : top), z, 1);
			quadStream.Append(border);
			//bottom right
			border.position = float4(right, bottom, z, 1);
			quadStream.Append(border);
			//top right
			border.position = float4(right, top, z, 1);
			quadStream.Append(border);

			// Reset
			quadStream.RestartStrip();
		}
		else
		{
			//bottom left
			border.position = float4(right, bottom, z, 1);
			quadStream.Append(border);
			//top left
			border.position = float4(right, top, z, 1);
			quadStream.Append(border);
			//bottom right
			border.position = float4(right + borderRightWidth, (hasBottomBorder ? bottom - borderBottomWidth : bottom), z, 1);
			quadStream.Append(border);
			//top right
			border.position = float4(right + borderRightWidth, (hasTopBorder ? top + borderTopWidth : top), z, 1);
			quadStream.Append(border);

			// Reset
			quadStream.RestartStrip();
		}
	}
	//*******************************
	// Bottom
	//*******************************
	if (hasBottomBorder && borderBottomColor.a)
	{
		border.colorTex = borderBottomColor;

		if (insetBorder)
		{
			//bottom left
			border.position = float4(left, bottom, z, 1);
			quadStream.Append(border);
			//top left
			border.position = float4((hasLeftBorder ? left + borderLeftWidth : left), bottom + borderBottomWidth, z, 1);
			quadStream.Append(border);
			//bottom right
			border.position = float4(right, bottom, z, 1);
			quadStream.Append(border);
			//top right
			border.position = float4((hasRightBorder ? right - borderRightWidth : right), bottom + borderBottomWidth, z, 1);

			// Reset
			quadStream.Append(border);
		}
		else
		{
			//bottom left
			border.position = float4((hasLeftBorder ? left - borderLeftWidth : left), bottom - borderBottomWidth, z, 1);
			quadStream.Append(border);
			//top left
			border.position = float4(left, bottom, z, 1);
			quadStream.Append(border);
			//bottom right
			border.position = float4((hasRightBorder ? right + borderRightWidth : right), bottom - borderBottomWidth, z, 1);
			quadStream.Append(border);
			//top right
			border.position = float4(right, bottom, z, 1);

			// Reset
			quadStream.Append(border);
		}
	}
}

//------------------------------------------------------------------------------
// PS
//------------------------------------------------------------------------------
float4 QuadExpandedShader(QuadPixel input) : SV_Target
{
	float isColorTex = input.options[0];
	float opacity = input.options[1];

	if (isColorTex == 0.0) // Color only
	{
		return float4(input.colorTex.rgb, input.colorTex.a * opacity);
	}
	else if (isColorTex == 1.0) // Texture only
	{
		float4 color = shaderTexture.Sample(SampleType, float2(input.colorTex[0], input.colorTex[1]));

		return float4(color.rgb, color.a * opacity);
	}
	else // Texture and color
	{
		return input.colorTex;
	}
}

//------------------------------------------------------------------------------
// TECHNIQUE
//------------------------------------------------------------------------------

technique10 ColorTechnique
{
	pass pass0
	{
		SetVertexShader(CompileShader(vs_4_0, QuadCollapsedShader()));
		SetGeometryShader(CompileShader(gs_4_0, QuadExpansionShader()));
		SetPixelShader(CompileShader(ps_4_0, QuadExpandedShader()));
	}
}
