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

Texture2D shaderTexture;
matrix borderCalculationMatrix : register( b0);


// -------------------------- borderCalculationMatrix --------------------------
//
//  Matrix:
//
//  [  {  width / 2  }   {      0      }   {      0      }   {      0      }  ]
//  [  {      0      }   {  height / 2 }   {      0      }   {      0      }  ]
//  [  {      0      }   {      0      }   {  width / 2  }   {      0      }  ]
//  [  {      0      }   {      0      }   {      0      }   {  height / 2 }  ]
//
//  Input:
//  
//  [  {  leftWidth  }  ] 
//  [  {  topWidth   }  ] 
//  [  { rightWIdth  }  ] 
//  [  { bottomWidth }  ]
//
//
//  Output: mul(input, matrix)
//

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
	float4 options : POSITION1;      // [text/color/both, opacity, zIndex, reserved]      NOTE: contents must be in float. 
	float4 optionsSet2 : POSITION2;      // [width, height, reserved, reserved]				  NOTE: contents must be in float. 
	float4 borderWidths : POSITION3; // [leftWidth, topWidth, rightWidth, bottomWidth]      NOTE: contents must be in float.
	float4 borderRadius : POSITION4; // [leftRadius, topRadius, rightRadius, bottomRadius]  NOTE: contents must be in float.
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
	nointerpolation float4 options : FLOAT4_0; // [texture/color/both/left/top/bottom/right, opacity, radius, borderWidth]
	nointerpolation float4 borderRadii : FLOAT4_1; // [leftTop, rightTop, leftBottom, rightBottom ]
	nointerpolation float2 rawDimensions : FLOAT2_0; // [width, height]
	float2 rawPixel : FLOAT2_1;
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

	float widthPixel = input[0].optionsSet2[0];
	float heightPixel = input[0].optionsSet2[1];

	float left = input[0].position[0];
	float top = input[0].position[1];
	float right = left + width;
	float bottom = top - height;

	input[0].borderWidths[1] = 10;

	float4 relativeBorderWidths = mul(input[0].borderWidths, borderCalculationMatrix);

	float borderLeftWidth = relativeBorderWidths[0];
	float borderTopWidth = relativeBorderWidths[1];
	float borderRightWidth = relativeBorderWidths[2];
	float borderBottomWidth = relativeBorderWidths[3];

	float4 borderLeftColor = ARGBtoFloat4(input[0].borderColors[0]);
	float4 borderTopColor = ARGBtoFloat4(input[0].borderColors[1]);
	float4 borderRightColor = ARGBtoFloat4(input[0].borderColors[2]);
	float4 borderBottomColor = ARGBtoFloat4(input[0].borderColors[3]);

	bool hasLeftBorder = borderLeftWidth > 0.0f;
	bool hasTopBorder = borderTopWidth > 0.0f;
	bool hasRightBorder = borderRightWidth > 0.0f;
	bool hasBottomBorder = borderBottomWidth > 0.0f;

	float opacity = input[0].options[3];

	float radius = 50;
	float4 radius4 = float4(radius, radius, radius + 1, radius + 1);
	radius4 = mul(radius4, borderCalculationMatrix);
		
	//**********************************************************************
	// Borders
	//**********************************************************************
	float z = (1000000.0f - (input[0].options[2] - 0.5f)) / 1000000.0f;
	// 0.0 indicates color coordinates
	// 1.0 indicates texture coordinates
	// 2.0 indicates texture on backgroundColor
	border.options = float4(0.0, opacity, 0, radius);
	border.rawPixel = float2(0, 0);
	border.borderRadii = float4(0,0,0,0);
	border.rawDimensions = float2(widthPixel, heightPixel);

	//*******************************
	// Left
	//*******************************
	if (hasLeftBorder && borderLeftColor.a)
	{
		border.colorTex = borderLeftColor;
		border.options[0] = 0.0f;
		border.options[2] = input[0].borderWidths[0];

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
			border.rawPixel = float2(0, heightPixel + input[0].borderWidths[0] * 2);
			quadStream.Append(border);
			//top left
			border.position = float4(left - borderLeftWidth, (hasTopBorder ? top + borderTopWidth : top), z, 1);
			border.rawPixel = float2(0, 0);
			quadStream.Append(border);
			//bottom right
			border.position = float4(left, bottom, z, 1);
			border.rawPixel = float2(input[0].borderWidths[0], heightPixel + input[0].borderWidths[1]);
			quadStream.Append(border);
			//top right
			border.position = float4(left + borderLeftWidth + radius4[0], (hasTopBorder ? top - borderTopWidth : top) - radius4[1], z, 1);
			border.rawPixel = float2(input[0].borderWidths[0] * 2 + radius, input[0].borderWidths[0] * 2 + radius);
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
		border.options[0] = -1.0f;
		border.options[2] = input[0].borderWidths[1];

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
			border.position = float4((hasLeftBorder ? left + borderLeftWidth : left) + radius4[0], top - borderTopWidth - radius4[1], z, 1);
			border.rawPixel = float2(input[0].borderWidths[0] * 2 + radius, input[0].borderWidths[1] * 2 + radius);
			quadStream.Append(border);
			//top left
			border.position = float4((hasLeftBorder ? left - borderLeftWidth : left), top + borderTopWidth, z, 1);
			border.rawPixel = float2(0, 0);
			quadStream.Append(border);
			//bottom right
			border.position = float4(right, top, z, 1);
			border.rawPixel = float2(widthPixel + input[0].borderWidths[1], input[0].borderWidths[1]);
			quadStream.Append(border);
			//top right
			border.position = float4((hasRightBorder ? right + borderRightWidth : right), top + borderTopWidth, z, 1);
			border.rawPixel = float2(widthPixel + input[0].borderWidths[1] * 2, 0);
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


	//**********************************************************************
	// Main
	//**********************************************************************
	float4 mainTexels = input[0].colorTex;
	z = (1000000.0f - input[0].options[2]) / 1000000.0f;
	main.options = float4(1.0f, opacity, input[0].options[3], radius);
	main.borderRadii = float4(50.0, 35.0, 20.0, 25.0);
	main.rawDimensions = float2(widthPixel, heightPixel);
	// main.colorTex = float4(input[0].colorTex.rgb, input[0].colorTex.a * opacity);

	//bottom left
	main.position = float4(left, bottom, z, 1);
	main.colorTex = float4(mainTexels[0], mainTexels[3], 0, 0);
	main.rawPixel = float2(0, input[0].optionsSet2[1]);
	quadStream.Append(main);
	//top left
	main.position = float4(left, top, z, 1);
	main.colorTex = float4(mainTexels[0], mainTexels[1], 0, 0);
	main.rawPixel = float2(0, 0);
	quadStream.Append(main);
	//bottom right
	main.position = float4(right, bottom, z, 1);
	main.colorTex = float4(mainTexels[2], mainTexels[3], 0, 0);
	main.rawPixel = float2(input[0].optionsSet2[0], input[0].optionsSet2[1]);
	quadStream.Append(main);
	//top right
	main.position = float4(right, top, z, 1);
	main.colorTex = float4(mainTexels[2], mainTexels[1], 0, 0);
	main.rawPixel = float2(input[0].optionsSet2[0], 0);
	quadStream.Append(main);

	// Reset
	quadStream.RestartStrip();
}

//------------------------------------------------------------------------------
// PS
//------------------------------------------------------------------------------
float4 QuadExpandedShader(QuadPixel input) : SV_Target
{
	float isColorTex = input.options[0];
	float opacity = input.options[1];

	if (isColorTex < 1.0) // Color only
	{
		float4 color = float4(input.colorTex.rgb, input.colorTex.a * opacity);

		float rawPixelX = input.rawPixel[0];
		float rawPixelY = input.rawPixel[1];
		float radius = 50;
		float borderWidth = input.options[2];
		float radiusPow = pow(radius, 2);
		float radiusPowLowerLimit = pow(radius - borderWidth, 2); // 5 is border width

		if (isColorTex == 0.0f)
		{
			if ((rawPixelX < radius) && (rawPixelY < radius))
			{
				if ((pow(radius - rawPixelX, 2) + pow(radius - rawPixelY, 2) > radiusPow) ||
					(pow(radius - rawPixelX, 2) + pow(radius - rawPixelY, 2) < radiusPowLowerLimit))
				{
					color.a = 0.0f;
				}
			}
			else if (rawPixelX > borderWidth)
			{
				color.a = 0.0f;
			}
		}
		else if (isColorTex == -1.0f)
		{
			if ((rawPixelX < radius) && (rawPixelY < radius))
			{
				if ((pow(radius - rawPixelX, 2) + pow(radius - rawPixelY, 2) > radiusPow) ||
					(pow(radius - rawPixelX, 2) + pow(radius - rawPixelY, 2) < radiusPowLowerLimit))
				{
					color.a = 0.0f;
				}
			}
			else if (rawPixelY > borderWidth)
			{
				color.a = 0.0f;
			}
		}

		return color;
	}
	else if (isColorTex == 1.0) // Texture only
	{
		float4 color = shaderTexture.Sample(SampleType, float2(input.colorTex[0], input.colorTex[1]));

		float rawPixelX = input.rawPixel[0];
		float rawPixelY = input.rawPixel[1];
		float width = input.rawDimensions[0];
		float height = input.rawDimensions[1];

		float radius, radiusPow;

		//-------------------------------------------------------------------------------------------
		// Top left

		radius = input.borderRadii[0];
		radiusPow = radiusPow = pow(radius, 2);

		if ((rawPixelX < radius) && (rawPixelY < radius))
		{
			if (pow(radius - rawPixelX, 2) + pow(radius - rawPixelY, 2) > radiusPow)
			{
				color.a = 0.0f;

				return color;
			}
		}

		//-------------------------------------------------------------------------------------------
		// Top right

		radius = input.borderRadii[1];
		radiusPow = radiusPow = pow(radius, 2);

		if ((rawPixelX > (width - radius)) && (rawPixelY < radius))
		{
			if (pow(rawPixelX - (width - radius), 2) + pow(radius - rawPixelY, 2) > radiusPow)
			{
				color.a = 0.0f;

				return color;
			}
		}
		
		//-------------------------------------------------------------------------------------------
		// Bottom left
		
		radius = input.borderRadii[2];
		radiusPow = radiusPow = pow(radius, 2);
		
		if ((rawPixelX < radius) && (rawPixelY > (height - radius)))
		{
			if (pow(radius - rawPixelX, 2) + pow(rawPixelY - (height - radius), 2) > radiusPow)
			{
				color.a = 0.0f;

				return color;
			}
		}

		//-------------------------------------------------------------------------------------------
		// Bottom right
		
		radius = input.borderRadii[3];
		radiusPow = radiusPow = pow(radius, 2);

		if ((rawPixelX > (width - radius)) && (rawPixelY > (height - radius)))
		{
			if (pow(rawPixelX - (width - radius), 2) + pow(rawPixelY - (height - radius), 2) > radiusPow)
			{
				color.a = 0.0f;

				return color;
			}
		}

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
