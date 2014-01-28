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
static const float ANTIALIAS_DISTANCE = 2;


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
	float4 borderRadii : POSITION4; // [leftRadius, topRadius, rightRadius, bottomRadius]  NOTE: contents must be in float.
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
	nointerpolation float4 borderWidths : FLOAT4_2;
	float2 rawPixel : FLOAT2_1;
};

//------------------------------------------------------------------------------
// FUNCTIONS
//------------------------------------------------------------------------------

//#ARGB to (Rf, Gf, Bf, Af)
inline float4 argb_to_float4(uint color)
{
	return float4(((color >> 24) & 0xFF) / 255.0, ((color >> 16) & 0xFF) / 255.0, ((color >> 8) & 0xFF) / 255.0, (color & 0xFF) / 255.0);
}

inline float4 get_euclidean_dist_color(float4 color, float radius, float2 coordinates, float minRadius)
{
	if (radius == minRadius)
	{
		return color;
	}

	float euclideanDist = sqrt(dot(coordinates, coordinates));

	if (euclideanDist > radius)
	{
		color.a = 0.0f;

		if (euclideanDist < (radius + ANTIALIAS_DISTANCE))
		{
			color.a = 1 - smoothstep(radius - ANTIALIAS_DISTANCE, radius + ANTIALIAS_DISTANCE, euclideanDist);
		}

		return color;
	}

	return color;
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

	float width = input[0].position[2];
	float height = input[0].position[3];

	float widthPixel = input[0].optionsSet2[0];
	float heightPixel = input[0].optionsSet2[1];

	float left = input[0].position[0];
	float top = input[0].position[1];
	float right = left + width;
	float bottom = top - height;	

	float4 relativeBorderWidths = mul(input[0].borderWidths, borderCalculationMatrix);

	float borderLeftWidth = relativeBorderWidths[0];
	float borderTopWidth = relativeBorderWidths[1];
	float borderRightWidth = relativeBorderWidths[2];
	float borderBottomWidth = relativeBorderWidths[3];

	float4 borderLeftColor = argb_to_float4(input[0].borderColors[0]);
	float4 borderTopColor = argb_to_float4(input[0].borderColors[1]);
	float4 borderRightColor = argb_to_float4(input[0].borderColors[2]);
	float4 borderBottomColor = argb_to_float4(input[0].borderColors[3]);

	bool hasLeftBorder = borderLeftWidth > 0.0f;
	bool hasTopBorder = borderTopWidth > 0.0f;
	bool hasRightBorder = borderRightWidth > 0.0f;
	bool hasBottomBorder = borderBottomWidth > 0.0f;

	float opacity = input[0].options[3];
	
	float4 borderRadii = input[0].borderRadii;

	float4 borderRadiiSet1 = float4(borderRadii[0], borderRadii[0], borderRadii[1], borderRadii[1]); //TopLeft TopRight
	float4 borderRadiiSet2 = float4(borderRadii[2], borderRadii[2], borderRadii[3], borderRadii[3]); //BottomLeft BottomRight
	
	float4 relativeBorderRadii_S1 = mul(borderRadiiSet1, borderCalculationMatrix);
	float4 relativeBorderRadii_S2 = mul(borderRadiiSet2, borderCalculationMatrix);
		
	//**********************************************************************
	// Borders
	//**********************************************************************
	float z = (1000000.0f - (input[0].options[2] - 0.5f)) / 1000000.0f;
	// 0.0 indicates color coordinates
	// 1.0 indicates texture coordinates
	// 2.0 indicates texture on backgroundColor
	border.options = float4(0.0, opacity, 0, 0);
	border.rawPixel = float2(0, 0);
	border.borderRadii = borderRadii;
	border.rawDimensions = float2(widthPixel, heightPixel);
	border.borderWidths = input[0].borderWidths;

	///////////////////////////////////////////////////////////////////////////
	//
	//  NOTE THAT THIS REGION IS NOT OPTIMIZED AT ALL
	//
	///////////////////////////////////////////////////////////////////////////

	//*******************************
	// Left
	//*******************************
	if (hasLeftBorder && borderLeftColor.a)
	{
		border.colorTex = borderLeftColor;
		border.options[0] = 0.0f;
		border.options[2] = input[0].borderWidths[0];
		
		//bottom left
		border.position = float4(left - borderLeftWidth, (hasBottomBorder ? bottom - borderBottomWidth : bottom), z, 1);
		border.rawPixel = float2(0, heightPixel + input[0].borderWidths[1] + input[0].borderWidths[3]);
		quadStream.Append(border);
		//top left
		border.position = float4(left - borderLeftWidth, (hasTopBorder ? top + borderTopWidth : top), z, 1);
		border.rawPixel = float2(0, 0); // minor fix
		quadStream.Append(border);
		//bottom right
		border.position = float4(left + relativeBorderRadii_S2[0], bottom + relativeBorderRadii_S2[1], z, 1);
		border.rawPixel = float2(input[0].borderWidths[0] + borderRadiiSet2[0], heightPixel + input[0].borderWidths[1] - borderRadiiSet2[1]);
		quadStream.Append(border);
		//top right
		border.position = float4(left + relativeBorderRadii_S1[0], (hasTopBorder ? top : top) - relativeBorderRadii_S1[1], z, 1); // Look at the previous code, to create the slope correctly!
		border.rawPixel = float2(input[0].borderWidths[0] + borderRadiiSet1[0], input[0].borderWidths[1] + borderRadiiSet1[1]);
		quadStream.Append(border);
		
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

		//bottom left
		border.position = float4((hasLeftBorder ? left : left) + relativeBorderRadii_S1[0], top - relativeBorderRadii_S1[1], z, 1);
		border.rawPixel = float2(input[0].borderWidths[0] + borderRadiiSet1[0], input[0].borderWidths[1] + borderRadiiSet1[1]);
		quadStream.Append(border);
		//top left
		border.position = float4((hasLeftBorder ? left - borderLeftWidth : left), top + borderTopWidth, z, 1);
		border.rawPixel = float2(0, 0); // Minor fix here
		quadStream.Append(border);
		//bottom right
		border.position = float4(right - relativeBorderRadii_S1[2], top - relativeBorderRadii_S1[3], z, 1);
		border.rawPixel = float2(widthPixel + input[0].borderWidths[0] - borderRadiiSet1[2], input[0].borderWidths[1] + borderRadiiSet1[3]);
		quadStream.Append(border);
		//top right
		border.position = float4((hasRightBorder ? right + borderRightWidth : right), top + borderTopWidth, z, 1);
		border.rawPixel = float2(widthPixel + input[0].borderWidths[0] + input[0].borderWidths[2], 0);
		quadStream.Append(border);

		// Reset
		quadStream.RestartStrip();
	}

	//*******************************
	// Right
	//*******************************
	if (hasRightBorder && borderRightColor.a)
	{
		border.colorTex = borderRightColor;
		border.options[0] = -2.0f;
		border.options[2] = input[0].borderWidths[2];

		//bottom left
		border.position = float4(right - relativeBorderRadii_S2[2], bottom + relativeBorderRadii_S2[3], z, 1);
		border.rawPixel = float2(widthPixel + input[0].borderWidths[0] - borderRadiiSet2[2], heightPixel + input[0].borderWidths[1] - borderRadiiSet2[3]);
		quadStream.Append(border);
		//top left
		border.position = float4(right - relativeBorderRadii_S1[2], top - relativeBorderRadii_S1[3], z, 1);
		border.rawPixel = float2(widthPixel + input[0].borderWidths[0] - borderRadiiSet1[2], input[0].borderWidths[1] + borderRadiiSet1[3]);
		quadStream.Append(border);
		//bottom right
		border.position = float4(right + borderRightWidth, (hasBottomBorder ? bottom - borderBottomWidth : bottom), z, 1);
		border.rawPixel = float2(input[0].borderWidths[0] + input[0].borderWidths[2] + widthPixel, input[0].borderWidths[1] + input[0].borderWidths[3] + heightPixel);
		quadStream.Append(border);
		//top right
		border.position = float4(right + borderRightWidth, (hasTopBorder ? top + borderTopWidth : top), z, 1);
		border.rawPixel = float2(input[0].borderWidths[0] + input[0].borderWidths[2] + widthPixel, 0);
		quadStream.Append(border);

		// Reset
		quadStream.RestartStrip();
	}
	//*******************************
	// Bottom
	//*******************************
	if (hasBottomBorder && borderBottomColor.a)
	{
		border.colorTex = borderBottomColor;
		border.options[0] = -3.0f;
		border.options[2] = input[0].borderWidths[3];

		//bottom left
		border.position = float4((hasLeftBorder ? left - borderLeftWidth : left), bottom - borderBottomWidth, z, 1);
		border.rawPixel = float2(0, heightPixel + input[0].borderWidths[3] + input[0].borderWidths[1]);
		quadStream.Append(border);
		//top left
		border.position = float4(left + relativeBorderRadii_S2[0], bottom + relativeBorderRadii_S2[1], z, 1);
		border.rawPixel = float2(input[0].borderWidths[0] + borderRadiiSet2[0], input[0].borderWidths[1] + heightPixel - borderRadiiSet2[1]);
		quadStream.Append(border);
		//bottom right
		border.position = float4((hasRightBorder ? right + borderRightWidth : right) , bottom - borderBottomWidth, z, 1);
		border.rawPixel = float2(widthPixel + input[0].borderWidths[2] + input[0].borderWidths[0], heightPixel + input[0].borderWidths[3] + input[0].borderWidths[1]);
		quadStream.Append(border);
		//top right
		border.position = float4(right - relativeBorderRadii_S2[2], bottom + relativeBorderRadii_S2[3], z, 1);
		border.rawPixel = float2(widthPixel + input[0].borderWidths[0] - borderRadiiSet2[2], input[0].borderWidths[1] + heightPixel - borderRadiiSet2[3]);
		quadStream.Append(border);

		// Reset
		quadStream.RestartStrip();
	}


	//**********************************************************************
	// Main
	//**********************************************************************
	float4 mainTexels = input[0].colorTex;
	z = (1000000.0f - input[0].options[2]) / 1000000.0f;

	main.options = float4(1.0f, opacity, input[0].options[3], 0.0);
	main.borderRadii = borderRadii;
	main.rawDimensions = float2(widthPixel, heightPixel);
	main.borderWidths = float4(0, 0, 0, 0);
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
	///////////////////////////////////////////////////////////////////////////
	//
	//  NOTE THAT THIS REGION IS NOT OPTIMIZED AT ALL
	//
	///////////////////////////////////////////////////////////////////////////

	float isColorTex = input.options[0];
	float opacity = input.options[1];

	if (isColorTex < 1.0) // Color only
	{
		float4 color = float4(input.colorTex.rgb, input.colorTex.a * opacity);

		float rawPixelX = input.rawPixel[0];
		float rawPixelY = input.rawPixel[1];
		float borderWidth = input.options[2];
		float width = input.rawDimensions[0];
		float height = input.rawDimensions[1];

		float borderLeftWidth = input.borderWidths[0];
		float borderTopWidth = input.borderWidths[1];
		float borderRightWidth = input.borderWidths[2];
		float borderBottomWidth = input.borderWidths[3];

		if (isColorTex == 0.0f)
		{
			float radius_1, radius_2;	 float calcSet1, calcSet2;
			radius_1 = input.borderRadii[0] + borderLeftWidth;
			radius_2 = input.borderRadii[2] + borderLeftWidth;
			
			if ((rawPixelX < (calcSet1 = radius_1)) && (rawPixelY < (calcSet2 = (radius_1 + (borderTopWidth - borderLeftWidth)))))
			{
				return get_euclidean_dist_color(color, radius_1, float2(calcSet1 - rawPixelX, calcSet2 - rawPixelY), borderLeftWidth);
			}
			else if ((rawPixelX < (calcSet1 = radius_2)) && (rawPixelY >(calcSet2 = (height + (borderTopWidth + borderLeftWidth) - radius_2))))
			{		
				return get_euclidean_dist_color(color, radius_2, float2(calcSet1 - rawPixelX, rawPixelY - calcSet2), borderLeftWidth);
			}
		}
		else if (isColorTex == -1.0f)
		{
			float radius_1, radius_2; float calcSet1, calcSet2;
			radius_1 = input.borderRadii[0] + borderTopWidth;
			radius_2 = input.borderRadii[1] + borderTopWidth;

			if ((rawPixelX < (calcSet1 = (radius_1 - borderTopWidth + borderLeftWidth))) && (rawPixelY < (calcSet2 = radius_1)))
			{
				return get_euclidean_dist_color(color, radius_1, float2(calcSet1 - rawPixelX, calcSet2 - rawPixelY), borderTopWidth);
			}
			else if ((rawPixelX >(calcSet1 = (width + borderLeftWidth + borderTopWidth - radius_2))) && (rawPixelY < (calcSet2 = radius_2)))
			{
				return get_euclidean_dist_color(color, radius_2, float2(calcSet1 - rawPixelX, calcSet2 - rawPixelY), borderTopWidth);
			}
		}
		else if (isColorTex == -3.0f)
		{
			float radius_1, radius_2; float calcSet1, calcSet2;
			radius_1 = input.borderRadii[2] + borderBottomWidth;
			radius_2 = input.borderRadii[3] + borderBottomWidth;
			
			if ((rawPixelX < (calcSet1 = (radius_1 + (borderLeftWidth - borderBottomWidth)))) && rawPixelY >(calcSet2 = (height + (borderTopWidth + borderBottomWidth) - radius_1))) // top + bottom
			{
				return get_euclidean_dist_color(color, radius_1, float2(calcSet1 - rawPixelX, rawPixelY - calcSet2), borderBottomWidth);
			}
			else if ((rawPixelX > (calcSet1 = (width + borderLeftWidth + borderBottomWidth - radius_2))) && (rawPixelY > (calcSet2 = (height + borderTopWidth + borderBottomWidth - radius_2))))
			{
				return get_euclidean_dist_color(color, radius_2, float2(rawPixelX - calcSet1, rawPixelY - calcSet2), borderBottomWidth);
			}
		}
		else if (isColorTex == -2.0f)
		{
			float radius_1, radius_2; float calcSet1, calcSet2;
			radius_1 = input.borderRadii[1] + borderRightWidth;
			radius_2 = input.borderRadii[3] + borderRightWidth;
			
			if ((rawPixelX > (calcSet1 = (width + borderLeftWidth + borderRightWidth - radius_1))) && (rawPixelY < (calcSet2 = (radius_1 + (borderTopWidth - borderRightWidth)))))
			{
				return get_euclidean_dist_color(color, radius_1, float2(rawPixelX - calcSet1, calcSet2 - rawPixelY), borderRightWidth);
			}
			else if ((rawPixelX >(calcSet1 = (width + borderLeftWidth + borderRightWidth - radius_2))) && (rawPixelY > (calcSet2 = (height + borderTopWidth - radius_2 + borderRightWidth))))
			{
				return get_euclidean_dist_color(color, radius_2, float2(rawPixelX - calcSet1, rawPixelY - calcSet2), borderRightWidth);
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
		float antialiasDist = 2;
		float radius;

		//-------------------------------------------------------------------------------------------
		// Top left

		radius = input.borderRadii[0];
		
		if ((rawPixelX < radius) && (rawPixelY < radius))
		{
			return get_euclidean_dist_color(color, radius, float2(radius - rawPixelX, radius - rawPixelY), 0);
		}

		//-------------------------------------------------------------------------------------------
		// Top right

		radius = input.borderRadii[1];

		if ((rawPixelX > (width - radius)) && (rawPixelY < radius))
		{
			return get_euclidean_dist_color(color, radius, float2(rawPixelX - (width - radius), radius - rawPixelY), 0);
		}
		
		//-------------------------------------------------------------------------------------------
		// Bottom left
		
		radius = input.borderRadii[2];
		
		if ((rawPixelX < radius) && (rawPixelY > (height - radius)))
		{
			return get_euclidean_dist_color(color, radius, float2(radius - rawPixelX, (height - radius) - rawPixelY), 0);
		}

		//-------------------------------------------------------------------------------------------
		// Bottom right
		
		radius = input.borderRadii[3];

		if ((rawPixelX > (width - radius)) && (rawPixelY > (height - radius)))
		{
			return get_euclidean_dist_color(color, radius, float2(rawPixelX - (width - radius), rawPixelY - (height - radius)), 0);
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
