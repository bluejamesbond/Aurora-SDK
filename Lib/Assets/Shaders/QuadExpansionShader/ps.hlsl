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
// PER-FRAME RESOURCES
//------------------------------------------------------------------------------
Texture2D shaderTexture;
SamplerState sampleType;

//------------------------------------------------------------------------------
// INPUT STRUCTURE
//------------------------------------------------------------------------------
struct QuadPixel
{
	float4 position : SV_POSITION;
	float4 colorTex : COLOR;

	// [texture/color/both, opacity, reserved, reserved]
	nointerpolation float4 options : FLOAT4; 
};

//------------------------------------------------------------------------------
// ENTRY POINT
//------------------------------------------------------------------------------
float4 main(QuadPixel input) : SV_Target
{
	float isColorTex = input.options[0];
	float opacity = input.options[1];

	if (isColorTex == 0.0) // Color only
	{
		return float4(input.colorTex.rgb, input.colorTex.a * opacity);
	}
	else if (isColorTex == 1.0) // Texture only
	{
		float4 color = shaderTexture.Sample(sampleType, float2(input.colorTex[0], input.colorTex[1]));

		return float4(color.rgb, color.a * opacity);
	}
	else // Texture and color
	{
		return input.colorTex;
	}
}

//------------------------------------------------------------------------------
// ADDITIONAL FUNCTIONS
//------------------------------------------------------------------------------
float4 ARGBtoFloat4(uint color)
{
	//#ARGB to (Rf, Gf, Bf, Af)
	return float4(((color >> 24) & 0xFF) / 255.0, ((color >> 16) & 0xFF) / 255.0, ((color >> 8) & 0xFF) / 255.0, (color & 0xFF) / 255.0);
}
