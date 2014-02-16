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
static const float BORDER_Z_OFFSET = 0.5f / 1000000.0f;

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
	float4 rect : POSITION2;		 // [width, height, reserved, reserved]				  NOTE: contents must be in float. 
	float4 crop_dist : POSITION3;		 // [width, height, reserved, reserved]				  NOTE: contents must be in float. 
	float4 border_widths : POSITION4; // [leftWidth, topWidth, rightWidth, bottomWidth]      NOTE: contents must be in float.
	float4 border_radii : POSITION5;  // [leftRadius, topRadius, rightRadius, bottomRadius]  NOTE: contents must be in float.
	float4 color_tex : COLOR0;
	uint4  border_colors : UINT4_0;    // [leftColor, topColor, rightColor, bottomColor]      NOTE: contents must be in uint4.
};

struct QuadPixel
{
	float4 position : SV_POSITION;
	float4 color_tex : COLOR;
	nointerpolation float4 options : FLOAT4_0; // [texture/color/both/left/top/bottom/right, opacity, radius, border_width]
	nointerpolation float4 border_radii : FLOAT4_1; // [leftTop, rightTop, leftBottom, rightBottom ]
	nointerpolation float2 raw_dims : FLOAT2_0; // [width, height]
	nointerpolation float4 border_widths : FLOAT4_2;
	nointerpolation float4 crop_dist : FLOAT4_3;
	float2 raw_px : FLOAT2_1;
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
		if (euclideanDist < (radius + ANTIALIAS_DISTANCE))
		{
			color.a *= 1.0f - smoothstep(radius - ANTIALIAS_DISTANCE, radius + ANTIALIAS_DISTANCE, euclideanDist);
		}
		else
		{
			color.a = 0.0f;
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
	///////////////////////////////////////////////////////////////////////////
	//
	//  NOTE THAT THIS REGION IS NOT OPTIMIZED AT ALL
	//
	///////////////////////////////////////////////////////////////////////////

	QuadPixel main, border;

	float left, top, right, bottom;

	float width = input[0].position[2],
	      height = input[0].position[3],
		  width_px = input[0].rect[2],
		  height_px = input[0].rect[3],
		  opacity = input[0].options[3],
		  _left =  left = input[0].position[0],
		  _top = top = input[0].position[1],
		  _right = right = left + width,
		  _bottom = bottom = top - height;

	float4 rel_border_widths = mul(input[0].border_widths, borderCalculationMatrix);

	float border_left_width = rel_border_widths[0],
	      border_top_width = rel_border_widths[1],
		  border_right_width = rel_border_widths[2],
		  border_bottom_width = rel_border_widths[3];
		
	bool has_left_border = border_left_width > 0.0f,
	     has_top_border = border_top_width > 0.0f,
		 has_right_border = border_right_width > 0.0f,
		 has_bottom_border = border_bottom_width > 0.0f;
		
	float4 border_radii = input[0].border_radii,
		   border_radiiSet1 = float4(border_radii[0], border_radii[0], border_radii[1], border_radii[1]), //TopLeft TopRight
		   border_radiiSet2 = float4(border_radii[2], border_radii[2], border_radii[3], border_radii[3]), //BottomLeft BottomRight
		   rel_border_radii_s1 = mul(border_radiiSet1, borderCalculationMatrix),
		   rel_border_radii_s2 = mul(border_radiiSet2, borderCalculationMatrix),
		   crop_dist = input[0].crop_dist,
		   rel_crop_dist = mul(crop_dist, borderCalculationMatrix);
		
	float4 border_left_color = argb_to_float4(input[0].border_colors[0]),
	       border_top_color = argb_to_float4(input[0].border_colors[1]),
	       border_right_color = argb_to_float4(input[0].border_colors[2]),
		   border_bottom_color = argb_to_float4(input[0].border_colors[3]);

	border_left_color.a *= opacity;
	border_top_color.a *= opacity;
	border_right_color.a *= opacity;
	border_bottom_color.a *= opacity;

	left += rel_crop_dist[0];
	top += rel_crop_dist[1];
	right += rel_crop_dist[2];
	bottom += rel_crop_dist[3];

	// Borders
	//------------------------------------------------------
	float z = input[0].options[2];
	border.options = float4(0.0, opacity, 0, 0);
	border.raw_px = float2(0, 0);
	border.crop_dist = crop_dist;
	border.border_radii = border_radii;
	border.raw_dims = float2(width_px, height_px);
	border.border_widths = input[0].border_widths;

	// Left
	//------------------------------------------------------
	if (has_left_border && border_left_color.a)
	{
		border.color_tex = border_left_color;
		border.options[0] = 0.0f;
		border.options[2] = input[0].border_widths[0];
		
		//bottom left
		border.position = float4(left - border_left_width, (has_bottom_border ? bottom - border_bottom_width : bottom), z, 1);
		border.raw_px = float2(0, height_px + input[0].border_widths[1] + input[0].border_widths[3]);
		quadStream.Append(border);

		//top left
		border.position = float4(left - border_left_width, (has_top_border ? top + border_top_width : top), z, 1);
		border.raw_px = float2(0, 0); // minor fix
		quadStream.Append(border);

		//bottom right
		border.position = float4(left + rel_border_radii_s2[0], bottom + rel_border_radii_s2[1], z, 1);
		border.raw_px = float2(input[0].border_widths[0] + border_radiiSet2[0], height_px + input[0].border_widths[1] - border_radiiSet2[1]);
		quadStream.Append(border);

		//top right
		border.position = float4(left + rel_border_radii_s1[0], (has_top_border ? top : top) - rel_border_radii_s1[1], z, 1); // Look at the previous code, to create the slope correctly!
		border.raw_px = float2(input[0].border_widths[0] + border_radiiSet1[0],  input[0].border_widths[1] + border_radiiSet1[1]);
		quadStream.Append(border);
		
		// Reset
		quadStream.RestartStrip();
	}


	// Top
	//------------------------------------------------------
	if (has_top_border && border_top_color.a)
	{
		border.color_tex = border_top_color;
		border.options[0] = -1.0f;
		border.options[2] = input[0].border_widths[1];

		//bottom left
		border.position = float4((has_left_border ? left : left) + rel_border_radii_s1[0], top - rel_border_radii_s1[1], z, 1);
		border.raw_px = float2(input[0].border_widths[0] + border_radiiSet1[0], input[0].border_widths[1] + border_radiiSet1[1]);
		quadStream.Append(border);

		//top left
		border.position = float4((has_left_border ? left - border_left_width : left), top + border_top_width, z, 1);
		border.raw_px = float2(0, 0); // Minor fix here
		quadStream.Append(border);

		//bottom right
		border.position = float4(right - rel_border_radii_s1[2], top - rel_border_radii_s1[3], z, 1);
		border.raw_px = float2(width_px + input[0].border_widths[0] - border_radiiSet1[2], input[0].border_widths[1] + border_radiiSet1[3]);
		quadStream.Append(border);

		//top right
		border.position = float4((has_right_border ? right + border_right_width : right), top + border_top_width, z, 1);
		border.raw_px = float2(width_px + input[0].border_widths[0] + input[0].border_widths[2], 0);
		quadStream.Append(border);

		// Reset
		quadStream.RestartStrip();
	}

	// Right
	//------------------------------------------------------
	if (has_right_border && border_right_color.a)
	{
		border.color_tex = border_right_color;
		border.options[0] = -2.0f;
		border.options[2] = input[0].border_widths[2];

		//bottom left
		border.position = float4(right - rel_border_radii_s2[2], bottom + rel_border_radii_s2[3], z, 1);
		border.raw_px = float2(width_px + input[0].border_widths[0] - border_radiiSet2[2], height_px + input[0].border_widths[1] - border_radiiSet2[3]);
		quadStream.Append(border);

		//top left
		border.position = float4(right - rel_border_radii_s1[2], top - rel_border_radii_s1[3], z, 1);
		border.raw_px = float2(width_px + input[0].border_widths[0] - border_radiiSet1[2], input[0].border_widths[1] + border_radiiSet1[3]);
		quadStream.Append(border);

		//bottom right
		border.position = float4(right + border_right_width, (has_bottom_border ? bottom - border_bottom_width : bottom), z, 1);
		border.raw_px = float2(input[0].border_widths[0] + input[0].border_widths[2] + width_px, input[0].border_widths[1] + input[0].border_widths[3] + height_px);
		quadStream.Append(border);

		//top right
		border.position = float4(right + border_right_width, (has_top_border ? top + border_top_width : top), z, 1);
		border.raw_px = float2(input[0].border_widths[0] + input[0].border_widths[2] + width_px, 0);
		quadStream.Append(border);

		// Reset
		quadStream.RestartStrip();
	}

	// Bottom
	//------------------------------------------------------
	if (has_bottom_border && border_bottom_color.a)
	{
		border.color_tex = border_bottom_color;
		border.options[0] = -3.0f;
		border.options[2] = input[0].border_widths[3];

		//bottom left
		border.position = float4((has_left_border ? left - border_left_width : left), bottom - border_bottom_width, z, 1);
		border.raw_px = float2(0, height_px + input[0].border_widths[3] + input[0].border_widths[1]);
		quadStream.Append(border);

		//top left
		border.position = float4(left + rel_border_radii_s2[0], bottom + rel_border_radii_s2[1], z, 1);
		border.raw_px = float2(input[0].border_widths[0] + border_radiiSet2[0], input[0].border_widths[1] + height_px - border_radiiSet2[1]);
		quadStream.Append(border);

		//bottom right
		border.position = float4((has_right_border ? right + border_right_width : right) , bottom - border_bottom_width, z, 1);
		border.raw_px = float2(width_px + input[0].border_widths[2] + input[0].border_widths[0], height_px + input[0].border_widths[3] + input[0].border_widths[1]);
		quadStream.Append(border);

		//top right
		border.position = float4(right - rel_border_radii_s2[2], bottom + rel_border_radii_s2[3], z, 1);
		border.raw_px = float2(width_px + input[0].border_widths[0] - border_radiiSet2[2], input[0].border_widths[1] + height_px - border_radiiSet2[3]);
		quadStream.Append(border);

		// Reset
		quadStream.RestartStrip();
	}


	// Main
	//------------------------------------------------------
	float4 mainTexels = input[0].color_tex;
	z = input[0].options[2] + BORDER_Z_OFFSET;

	main.options = float4(1.0f, opacity, input[0].options[3], 0.0);
	main.border_radii = border_radii;
	main.crop_dist = float4(0, 0, 0, 0);
	main.raw_dims = float2(width_px, height_px);
	main.border_widths = float4(0, 0, 0, 0);
	// main.color_tex = float4(input[0].color_tex.rgb, input[0].color_tex.a * opacity);

	//bottom left
	main.position = float4(_left, _bottom, z, 1);
	main.color_tex = float4(mainTexels[0], mainTexels[3], 0, 0);
	main.raw_px = float2(crop_dist[0], crop_dist[3]) + float2(0, height_px);
	quadStream.Append(main);

	//top left
	main.position = float4(_left, _top, z, 1);
	main.color_tex = float4(mainTexels[0], mainTexels[1], 0, 0);
	main.raw_px = float2(crop_dist[0], crop_dist[1]) + float2(0, 0);
	quadStream.Append(main);

	//bottom right
	main.position = float4(_right, _bottom, z, 1);
	main.color_tex = float4(mainTexels[2], mainTexels[3], 0, 0);
	main.raw_px = float2(crop_dist[2], crop_dist[3]) + float2(width_px, height_px);
	quadStream.Append(main);

	//top right
	main.position = float4(_right, _top, z, 1);
	main.color_tex = float4(mainTexels[2], mainTexels[1], 0, 0);
	main.raw_px = float2(crop_dist[2], crop_dist[1]) + float2(width_px, 0);
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
		float4 color = float4(input.color_tex.rgb, input.color_tex.a * opacity);

		float x_px = input.raw_px[0],
		      y_px = input.raw_px[1],
			  border_width = input.options[2],
			  width = input.raw_dims[0],
			  height = input.raw_dims[1],
			  border_left_width = input.border_widths[0],
		      border_top_width = input.border_widths[1],
			  border_right_width = input.border_widths[2],
			  border_bottom_width = input.border_widths[3];
		
		if (y_px <= (input.crop_dist[1]))
		{
			color.a = 0.0f;
			return color;
		}

		if (isColorTex == 0.0f)
		{
			float radius_1, radius_2;	 float calcSet1, calcSet2;
			radius_1 = input.border_radii[0] + border_left_width;
			radius_2 = input.border_radii[2] + border_left_width;
			
			if ((x_px < (calcSet1 = radius_1)) && (y_px < (calcSet2 = (radius_1 + (border_top_width - border_left_width)))))
			{
				return get_euclidean_dist_color(color, radius_1, float2(calcSet1 - x_px, calcSet2 - y_px), border_left_width);
			}
			else if ((x_px < (calcSet1 = radius_2)) && (y_px >(calcSet2 = (height + (border_top_width + border_left_width) - radius_2))))
			{		
				return get_euclidean_dist_color(color, radius_2, float2(calcSet1 - x_px, y_px - calcSet2), border_left_width);
			}
		}
		else if (isColorTex == -1.0f)
		{
			float radius_1, radius_2; float calcSet1, calcSet2;
			radius_1 = input.border_radii[0] + border_top_width;
			radius_2 = input.border_radii[1] + border_top_width;

			if ((x_px < (calcSet1 = (radius_1 - border_top_width + border_left_width))) && (y_px < (calcSet2 = radius_1)))
			{
				return get_euclidean_dist_color(color, radius_1, float2(calcSet1 - x_px, calcSet2 - y_px), border_top_width);
			}
			else if ((x_px >(calcSet1 = (width + border_left_width + border_top_width - radius_2))) && (y_px < (calcSet2 = radius_2)))
			{
				return get_euclidean_dist_color(color, radius_2, float2(calcSet1 - x_px, calcSet2 - y_px), border_top_width);
			}
		}
		else if (isColorTex == -3.0f)
		{
			float radius_1, radius_2; float calcSet1, calcSet2;
			radius_1 = input.border_radii[2] + border_bottom_width;
			radius_2 = input.border_radii[3] + border_bottom_width;
			
			if ((x_px < (calcSet1 = (radius_1 + (border_left_width - border_bottom_width)))) && y_px >(calcSet2 = (height + (border_top_width + border_bottom_width) - radius_1))) // top + bottom
			{
				return get_euclidean_dist_color(color, radius_1, float2(calcSet1 - x_px, y_px - calcSet2), border_bottom_width);
			}
			else if ((x_px > (calcSet1 = (width + border_left_width + border_bottom_width - radius_2))) && (y_px > (calcSet2 = (height + border_top_width + border_bottom_width - radius_2))))
			{
				return get_euclidean_dist_color(color, radius_2, float2(x_px - calcSet1, y_px - calcSet2), border_bottom_width);
			}
		}
		else if (isColorTex == -2.0f)
		{
			float radius_1, radius_2; float calcSet1, calcSet2;
			radius_1 = input.border_radii[1] + border_right_width;
			radius_2 = input.border_radii[3] + border_right_width;
			
			if ((x_px > (calcSet1 = (width + border_left_width + border_right_width - radius_1))) && (y_px < (calcSet2 = (radius_1 + (border_top_width - border_right_width)))))
			{
				return get_euclidean_dist_color(color, radius_1, float2(x_px - calcSet1, calcSet2 - y_px), border_right_width);
			}
			else if ((x_px >(calcSet1 = (width + border_left_width + border_right_width - radius_2))) && (y_px > (calcSet2 = (height + border_top_width - radius_2 + border_right_width))))
			{
				return get_euclidean_dist_color(color, radius_2, float2(x_px - calcSet1, y_px - calcSet2), border_right_width);
			}
		}

		return color;
	}
	else if (isColorTex == 1.0) // Texture only
	{
		float4 color = shaderTexture.Sample(SampleType, float2(input.color_tex[0], input.color_tex[1]));

		// Adjust opacity
		color.a *= opacity;

		float x_px = input.raw_px[0];
		float y_px = input.raw_px[1];
		float width = input.raw_dims[0];
		float height = input.raw_dims[1];
		float antialiasDist = 2;
		float radius;

		//-------------------------------------------------------------------------------------------
		// Top left

		radius = input.border_radii[0];
		
		if ((x_px < radius) && (y_px < radius))
		{
			return get_euclidean_dist_color(color, radius, float2(radius - x_px, radius - y_px), 0);
		}

		//-------------------------------------------------------------------------------------------
		// Top right

		radius = input.border_radii[1];

		if ((x_px > (width - radius)) && (y_px < radius))
		{
			return get_euclidean_dist_color(color, radius, float2(x_px - (width - radius), radius - y_px), 0);
		}
		
		//-------------------------------------------------------------------------------------------
		// Bottom left
		
		radius = input.border_radii[2];
		
		if ((x_px < radius) && (y_px > (height - radius)))
		{
			return get_euclidean_dist_color(color, radius, float2(radius - x_px, (height - radius) - y_px), 0);
		}

		//-------------------------------------------------------------------------------------------
		// Bottom right
		
		radius = input.border_radii[3];

		if ((x_px > (width - radius)) && (y_px > (height - radius)))
		{
			return get_euclidean_dist_color(color, radius, float2(x_px - (width - radius), y_px - (height - radius)), 0);
		}

		return float4(color.rgb, color.a * opacity);
	}
	else // Texture and color
	{
		return input.color_tex;
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
