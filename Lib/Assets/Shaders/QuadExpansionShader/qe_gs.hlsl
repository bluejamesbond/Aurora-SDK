
// Aurora-SDK

#include "qe_hd.hlsli"

//------------------------------------------------------------------------------
// CBUFFER
//------------------------------------------------------------------------------
cbuffer GS_CONSTANT_BUFFER : register(b0)
{
	//------------------------------------------------------------------------------
	matrix borderCalculationMatrix;
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
};

//------------------------------------------------------------------------------
// ENTRY POINT
//------------------------------------------------------------------------------
[maxvertexcount(24)]
void main(point VX_QUADEXPANSION input[1], inout TriangleStream<PX_QUADEXPANSION> quadStream)
{
	PX_QUADEXPANSION main, border;

	bool insetBorder = false;

	float width = input[0].position[2];
	float height = input[0].position[3];

	float left = input[0].position[0];
	float top = input[0].position[1];
	float right = left + width;
	float bottom = top - height;

	input[0].borderWidths = mul(input[0].borderWidths, borderCalculationMatrix);

	float borderLeftWidth = input[0].borderWidths[0];
	float borderTopWidth = input[0].borderWidths[1];
	float borderRightWidth = input[0].borderWidths[2];
	float borderBottomWidth = input[0].borderWidths[3];

	float4 borderLeftColor = ARGBtoFloat4(input[0].borderColors[0]);
	float4 borderTopColor = ARGBtoFloat4(input[0].borderColors[1]);
	float4 borderRightColor = ARGBtoFloat4(input[0].borderColors[2]);
	float4 borderBottomColor = ARGBtoFloat4(input[0].borderColors[3]);

	bool hasLeftBorder = borderLeftWidth > 0.0f;
	bool hasTopBorder = borderTopWidth > 0.0f;
	bool hasRightBorder = borderRightWidth > 0.0f;
	bool hasBottomBorder = borderBottomWidth > 0.0f;

	float z = (10000000.0f - input[0].options[2]) / 10000000.0f;
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
	z = (10000000.0f - (input[0].options[2] + 0.5f)) / 10000000.0f;
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