/////////////
// GLOBALS //
/////////////
matrix worldMatrix;
matrix viewMatrix;
matrix projectionMatrix;
Texture2D shaderTexture;


///////////////////
// SAMPLE STATES //
///////////////////
SamplerState SampleType
{
	Filter = ANISOTROPIC;
	AddressU = Clamp;
	AddressV = Clamp;
};


//////////////
// TYPEDEFS //
//////////////
struct ColoredTextureVertex
{
	float4 position : POSITION;
	float2 tex : TEXCOORD0;
	float4 color : COLOR;
};

struct ColoredTexturePixel
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
	float4 color : COLOR;
};

struct TextureVertex
{
	float4 position : POSITION;
	float2 tex : TEXCOORD0;
};

struct TexturePixel
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
};


////////////////////////////////////////////////////////////////////////////////
// Vertex Shader
////////////////////////////////////////////////////////////////////////////////
ColoredTexturePixel ColoredTextureVertexShader(ColoredTextureVertex input)
{
	ColoredTexturePixel output;

	// Force w-buffer to be 1.0
	input.position.w = 1.0f;

	// Calculate z-buffer manually
	input.position.z = (10000000 - input.position.z) / 10000000;

	// Calculate the position of the vertex 
	// against the world, view, and projection matrices.
	output.position = input.position;

	output.tex = input.tex;
	output.color = input.color;

	return output;
}


////////////////////////////////////////////////////////////////////////////////
// Pixel Shader
////////////////////////////////////////////////////////////////////////////////
float4 ColoredTexturePixelShader(ColoredTexturePixel input) : SV_Target
{
	float4 textureColor;
	float4 alphaComposite;
	float4 inputColor;

	inputColor = input.color;
	textureColor = shaderTexture.Sample(SampleType, input.tex);
	
	// Porter and Duff equations for calculating
	// alpha composite.
	alphaComposite.a = textureColor.a + inputColor.a * (1.0 - textureColor.a);
	alphaComposite.rgb = (textureColor.a * textureColor.rgb + (inputColor.a * inputColor.rgb) * (1.0 - textureColor.a)) / alphaComposite.a;
	
	return alphaComposite;
}

////////////////////////////////////////////////////////////////////////////////
// Vertex Shader
////////////////////////////////////////////////////////////////////////////////
TexturePixel TextureVertexShader(TextureVertex input)
{
	TexturePixel output;

	// Force w-buffer to be 1.0
	input.position.w = 1.0f;

	// Calculate z-buffer manually
	input.position.z = (10000000 - input.position.z) / 10000000;

	// Calculate the position of the vertex 
	// against the world, view, and projection matrices.
	output.position = input.position;

	output.tex = input.tex;

	return output;
}


////////////////////////////////////////////////////////////////////////////////
// Pixel Shader
////////////////////////////////////////////////////////////////////////////////
float4 TexturePixelShader(TexturePixel input) : SV_Target
{
	float4 textureColor;
	
	// Sample the pixel color from the texture using the sampler at this texture coordinate location.
	textureColor = shaderTexture.Sample(SampleType, input.tex);

	textureColor = saturate(textureColor);

	if (textureColor.a >= 0.3)
	{
		textureColor.a = 1.0;
		return textureColor;
	}

	textureColor.a = 0.0;
	
	return textureColor;
}

////////////////////////////////////////////////////////////////////////////////
// Technique
////////////////////////////////////////////////////////////////////////////////
technique10 ColoredTextureTechnique
{
	pass pass0
	{
		SetVertexShader(CompileShader(vs_4_0, ColoredTextureVertexShader()));
		SetPixelShader(CompileShader(ps_4_0, ColoredTexturePixelShader()));
		SetGeometryShader(NULL);
	}
}

////////////////////////////////////////////////////////////////////////////////
// Technique
////////////////////////////////////////////////////////////////////////////////
technique10 TextureTechnique
{
	pass pass0
	{
		SetVertexShader(CompileShader(vs_4_0, TextureVertexShader()));
		SetPixelShader(CompileShader(ps_4_0, TexturePixelShader()));
		SetGeometryShader(NULL);
	}
}



