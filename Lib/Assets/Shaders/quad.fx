////////////////////////////////////////////////////////////////////////////////
// Filename: quad.fx
////////////////////////////////////////////////////////////////////////////////

Texture2D shaderTexture;

//////////////////
// BLEND STATE  //
//////////////////
//BlendState SrcAlphaBlendingAdd
//{
//	BlendEnable[0] = TRUE;
//	SrcBlend = SRC_ALPHA;
//	DestBlend = INV_SRC_ALPHA;
//	BlendOp = ADD;
//	SrcBlendAlpha = ZERO;
//	DestBlendAlpha = ZERO;
//	BlendOpAlpha = ADD;
//	RenderTargetWriteMask[0] = 0x0F;
//};

///////////////////
// SAMPLE STATES //
///////////////////
SamplerState SampleType
{
	Filter = MIN_MAG_MIP_LINEAR;
	AddressU = Wrap;
	AddressV = Wrap;
};

//////////////
// TYPEDEFS //
//////////////
struct QuadVertex
{
	float4 position : POSITION0;
	float4 options : POSITION1;      // [texture/color/both, textureSlice, z, opacity]
	float4 borderWidths : POSITION2; // [leftWidth, topWidth, rightWidth, bottomWidth]
	float4 borderRadius : POSITION3; // [leftRadius, topRadius, rightRadius, bottomRadius]
	float4 colorTex : COLOR0;
	uint4 borderColors : UINT4_0;      // [leftColor, topColor, rightColor, bottomColor]
};

struct QuadPixel
{
	float4 position : SV_POSITION;
	float4 colorTex : COLOR;
	nointerpolation float4 options : FLOAT4; // [texture/color/both, opacity, reserved, reserved]
};

////////////////////////////////////////////////////////////////////////////////
// Vertex Shader
////////////////////////////////////////////////////////////////////////////////
QuadVertex QuadCollapsedShader(QuadVertex input)
{
	return input;
}

//#ARGB to (Rf, Gf, Bf, Af)
float4 ARGBtoFloat4(uint color)
{
	return float4(((color >> 24) & 0xFF) / 255, ((color >> 16) & 0xFF) / 255, ((color >> 8) & 0xFF) / 255, 1.0);
}

////////////////////////////////////////////////////////////////////////////////
// Geometry Shader
////////////////////////////////////////////////////////////////////////////////
[maxvertexcount(24)]
void QuadExpansionShader(point QuadVertex input[1], inout TriangleStream<QuadPixel> quadStream)
{
	QuadPixel main, border;

	float left, top, right, z,
		bottom, width, height,
		borderLeftWidth, borderTopWidth,
		borderRightWidth, borderBottomWidth,
		opacity;

	float4 borderLeftColor, borderTopColor, borderRightColor, borderBottomColor;

	width = input[0].position[2];
	height = input[0].position[3];

	left = input[0].position[0];
	top = input[0].position[1];
	right = left + width;
	bottom = top - height;

	borderLeftWidth = input[0].borderWidths[0];
	borderTopWidth = input[0].borderWidths[1];
	borderRightWidth = input[0].borderWidths[2];
	borderBottomWidth = input[0].borderWidths[3];

	borderLeftColor = ARGBtoFloat4(input[0].borderColors[0]);
	borderTopColor = ARGBtoFloat4(input[0].borderColors[1]);
	borderRightColor = ARGBtoFloat4(input[0].borderColors[2]);
	borderBottomColor = ARGBtoFloat4(input[0].borderColors[3]);

	z = input[0].options[2];
	opacity = input[0].options[3];

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
	z -= 0.000001f;
	// 0.0 indicates color coordinates
	// 1.0 indicates texture coordinates
	// 2.0 indicates texture on backgroundColor
	border.options = float4(0.0f, opacity, 0, 0);

	//*******************************
	// Left
	//*******************************
	border.colorTex = borderLeftColor;

	//bottom left
	border.position = float4(left, bottom, z, 1);
	quadStream.Append(border);
	//top left
	border.position = float4(left, top, z, 1);
	quadStream.Append(border);
	//bottom right
	border.position = float4(left + borderLeftWidth, bottom + borderLeftWidth, z, 1);
	quadStream.Append(border);
	//top right
	border.position = float4(left + borderLeftWidth, top - borderLeftWidth, z, 1);
	quadStream.Append(border);

	// Reset
	quadStream.RestartStrip();

	//*******************************
	// Top
	//*******************************
	border.colorTex = borderTopColor;

	//bottom left
	border.position = float4(left + borderTopWidth, top - borderTopWidth, z, 1);
	quadStream.Append(border);
	//top left
	border.position = float4(left, top, z, 1);
	quadStream.Append(border);
	//bottom right
	border.position = float4(right - borderTopWidth, top - borderTopWidth, z, 1);
	quadStream.Append(border);
	//top right
	border.position = float4(right, top, z, 1);
	quadStream.Append(border);

	// Reset
	quadStream.RestartStrip();

	//*******************************
	// Right
	//*******************************
	border.colorTex = borderRightColor;

	//bottom left
	border.position = float4(right - borderRightWidth, bottom + borderRightWidth, z, 1);
	quadStream.Append(border);
	//top left
	border.position = float4(right - borderRightWidth, top - borderRightWidth, z, 1);
	quadStream.Append(border);
	//bottom right
	border.position = float4(right, bottom, z, 1);
	quadStream.Append(border);
	//top right
	border.position = float4(right, top, z, 1);
	quadStream.Append(border);

	// Reset
	quadStream.RestartStrip();

	//*******************************
	// Bottom
	//*******************************
	border.colorTex = borderBottomColor;

	//bottom left
	border.position = float4(left, bottom, z, 1);
	quadStream.Append(border);
	//top left
	border.position = float4(left + borderRightWidth, bottom + borderRightWidth, z, 1);
	quadStream.Append(border);
	//bottom right
	border.position = float4(right, bottom, z, 1);
	quadStream.Append(border);
	//top right
	border.position = float4(right - borderRightWidth, bottom + borderRightWidth, z, 1);

	// Reset
	quadStream.Append(border);

}

////////////////////////////////////////////////////////////////////////////////
// Pixel Shader
////////////////////////////////////////////////////////////////////////////////
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

////////////////////////////////////////////////////////////////////////////////
// Technique
////////////////////////////////////////////////////////////////////////////////
technique10 ColorTechnique
{
	pass pass0
	{
		SetVertexShader(CompileShader(vs_4_0, QuadCollapsedShader()));
		SetGeometryShader(CompileShader(gs_4_0, QuadExpansionShader()));
		SetPixelShader(CompileShader(ps_4_0, QuadExpandedShader()));
		//SetBlendState(SrcAlphaBlendingAdd, float4(0.0f, 0.0f, 0.0f, 0.0f), 0xFFFFFFFF);
	}
}