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
	Filter = MIN_MAG_MIP_LINEAR;
	AddressU = Wrap;
	AddressV = Wrap;
};


//////////////
// TYPEDEFS //
//////////////
struct VertexInput
{
	float4 position : POSITION;
	float2 tex : TEXCOORD0;
	float4 color : COLOR;
};

struct PixelInput
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
	float4 color : COLOR;
};


////////////////////////////////////////////////////////////////////////////////
// Vertex Shader
////////////////////////////////////////////////////////////////////////////////
PixelInput TextureVertexShader(VertexInput input)
{
	PixelInput output;
	
	// Change the position vector to be 4 units for proper matrix calculations.
	input.position.w = 1.0f;

	// Calculate the position of the vertex against the world, view, and projection matrices.
	output.position = mul(input.position, worldMatrix);
	output.position = mul(output.position, viewMatrix);
	output.position = mul(output.position, projectionMatrix);

	output.tex = input.tex;
	output.color = input.color;

	return output;
}


////////////////////////////////////////////////////////////////////////////////
// Pixel Shader
////////////////////////////////////////////////////////////////////////////////
float4 TexturePixelShader(PixelInput input) : SV_Target
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
// Technique
////////////////////////////////////////////////////////////////////////////////
technique10 MainTechnique
{
	pass pass0
	{
		SetVertexShader(CompileShader(vs_4_0, TextureVertexShader()));
		SetPixelShader(CompileShader(ps_4_0, TexturePixelShader()));
		SetGeometryShader(NULL);
	}
}