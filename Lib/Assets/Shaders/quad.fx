////////////////////////////////////////////////////////////////////////////////
// Filename: quad.fx
////////////////////////////////////////////////////////////////////////////////

Texture2D shaderTexture;

//////////////////
// BLEND STATE  //
//////////////////
BlendState SrcAlphaBlendingAdd
{
	BlendEnable[0] = TRUE;
	SrcBlend = SRC_ALPHA;
	DestBlend = INV_SRC_ALPHA;
	BlendOp = ADD;
	SrcBlendAlpha = ZERO;
	DestBlendAlpha = ZERO;
	BlendOpAlpha = ADD;
	RenderTargetWriteMask[0] = 0x0F;
};

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
	float4 borderLeftColor : COLOR1;
	float4 borderTopColor : COLOR2;
	float4 borderRightColor : COLOR3;
	float4 borderBottomColor : COLOR4;
};

struct QuadPixel
{
	float4 position : SV_POSITION;
	float4 colorTex : COLOR;
	nointerpolation float4 options : FLOAT4; // [texture/color/both, reseved, reserved, reserved]
};

////////////////////////////////////////////////////////////////////////////////
// Vertex Shader
////////////////////////////////////////////////////////////////////////////////
QuadVertex QuadCollapsedShader(QuadVertex input)
{
	return input;
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

	z = input[0].options[2];
	opacity = input[0].options[3];

	//**********************************************************************
	// Borders
	//**********************************************************************
	// 1.0 indicates color
	// 0.0 indicates texture coordinates
	// 2.0 indicates texture on backgroundColor
	border.options = float4(1.0f, 0, 0, 0);

	//*******************************
	// Left
	//*******************************
	border.colorTex = float4(input[0].borderLeftColor.rgb, input[0].borderLeftColor.a * opacity);

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
	border.colorTex = float4(input[0].borderTopColor.rgb, input[0].borderTopColor.a * opacity);

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
	border.colorTex = float4(input[0].borderRightColor.rgb, input[0].borderRightColor.a * opacity);

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
	border.colorTex = float4(input[0].borderBottomColor.rgb, input[0].borderBottomColor.a * opacity);

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

	//**********************************************************************
	// Main
	//**********************************************************************
	main.options = float4(1.0f, 0, 0, 0);
	main.colorTex = float4(input[0].colorTex.rgb, input[0].colorTex.a * opacity);

	//bottom left
	main.position = float4(left, bottom, z, 1);
	quadStream.Append(main);
	//top left
	main.position = float4(left, top, z, 1);
	quadStream.Append(main);
	//bottom right
	main.position = float4(right, bottom, z, 1);
	quadStream.Append(main);
	//top right
	main.position = float4(right, top, z, 1);
	quadStream.Append(main);

	// Reset
	quadStream.RestartStrip();
}

////////////////////////////////////////////////////////////////////////////////
// Pixel Shader
////////////////////////////////////////////////////////////////////////////////
float4 QuadExpandedShader(QuadPixel input) : SV_Target
{
	return input.colorTex;
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
		SetBlendState(SrcAlphaBlendingAdd, float4(0.0f, 0.0f, 0.0f, 0.0f), 0xFFFFFFFF);
	}
}