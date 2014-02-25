/////////////
// GLOBALS //
/////////////
matrix worldMatrix;
matrix viewMatrix;
matrix projectionMatrix;
Texture2D shaderTexture;
float4 fontColor;
float4 shadowColor;


///////////////////
// SAMPLE STATES //
///////////////////
SamplerState SampleType
{
	Filter = MIN_MAG_MIP_LINEAR;
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

struct FontPixel
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
	float4 color : COLOR;
};

struct FontColor
{
	float4 color: COLOR;
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
FontPixel TextureVertexShader(TextureVertex input)
{
	FontPixel output;

	// Force w-buffer to be 1.0
	input.position.w = 1.0f;

	// Calculate z-buffer manually
	input.position.z = (10000000 - input.position.z) / 10000000;

	// Calculate the position of the vertex 
	// against the world, view, and projection matrices.
	output.position = input.position;

	output.tex = input.tex;
	output.color = float4(0.9, 0.1, 1.0, 1.0);; // Use black as default


	return output;
}


////////////////////////////////////////////////////////////////////////////////
// Pixel Shader
////////////////////////////////////////////////////////////////////////////////
float4 TexturePixelShader(TexturePixel input) : SV_Target
{
	float4 textureColor;
	float dist;
	
	// Sample the pixel color from the texture using the sampler at this texture coordinate location.
	textureColor = shaderTexture.Sample(SampleType, input.tex);

	return textureColor; 

	dist = textureColor.a;
	textureColor = saturate(textureColor);
	const float smoothing = 2.0 / 16.0;


	if (textureColor.a > 0.5)
	{
		//if (textureColor.a < 0.)
		//{
		//	textureColor.x = 0.2;
		//	textureColor.y = 0.1;
		//	textureColor.z = 1.0;
		//	textureColor.a = 1.0;
		//	
		//}
		//else
		//{
		//	textureColor.x = 0.8;
		//	textureColor.y = 0.5;
		//	textureColor.z = 0.2;
		//	textureColor.a = 1.0;
		//	textureColor.a *= smoothstep(.5 - smoothing, .5 + smoothing, dist);
		//}
		textureColor.a = 1.0;	
	}
	else
	{
		textureColor.a = 0.0;
	}





	float EFFECT_CENTER = .2;
	float BASE_CENTER = .5;

	float EFFECT_OFFSET = 0.01;
	float EFFECT_MIND = 0.01;
	float EFFECT_MAXD = 0.01;
	float4 EFFECT_COLOR = float4(0.0,0.0,0.0,1.0);

	//const float smoothing = 1.0 / 16.0;
	// 2048x2048 tex -> min .5, max .6
	// 1024x1024 tex -> min .45, max .75

	//textureColor.a *= smoothstep(BASE_CENTER - smoothing, BASE_CENTER + smoothing, dist);
	
	textureColor.a *= smoothstep(.52, .58, dist);

	//float4 effectTexel = shaderTexture.Sample(SampleType, input.tex.xy + EFFECT_OFFSET);
	//float distEffect = effectTexel.a;
	//float4 effectC = EFFECT_COLOR * smoothstep(EFFECT_MIND - smoothing, EFFECT_MAXD + smoothing, effectTexel.a);

	//effectC.a *= smoothstep(EFFECT_MIND - smoothing, EFFECT_MAXD + smoothing, distEffect);

	textureColor.x = 0.2;
	textureColor.y = 0.1;
	textureColor.z = 1.0;

	// textureColor = lerp(effectC, textureColor, dist);

	return textureColor;

	//textureColor.a = 0.0;

	//if (textureColor.a >= 0.5)
	//{
	//	textureColor.a = 1.0;
	//	return textureColor;
	//}

	//textureColor.a = 0.0;

}

float4 TextureShadowedPixelShader(FontPixel input) : SV_TARGET
{
	// Process distance field texture for base font.
	float4 base, baseColor;
	float alphaBaseDistance;
	const float baseCenter = 0.5;
	const float smoothing = 1.0 / 16.0;

	base = shaderTexture.Sample(SampleType, input.tex);
	alphaBaseDistance = base.a;
	//baseColor = float4(0.2, 0.1, 1.0, 1.0); // base color should be blue, for testing purposes
	baseColor = fontColor;

	// Threshold.
	if (base.a > 0.5)
	{
		base.a = 1.0;
	}
	else
	{
		base.a = 0.0;
	}

	base.a *= smoothstep(baseCenter - smoothing, baseCenter + smoothing, alphaBaseDistance);


	base.x = baseColor.x; // Is there a more efficient way to do this?
	base.y = baseColor.y;
	base.z = baseColor.z;

	// Process distance field  texture for shadow.
	float4 shadow, shadowTexel;
	//float4 shadowColor;
	float SHADOW_OFFSET = 0.004;
	float alphaShadowMaskDistance;
	float2 s_f = input.tex.xy;
	s_f.x -= SHADOW_OFFSET;
	s_f.y += SHADOW_OFFSET;

	//shadowTexel = shaderTexture.Sample(SampleType, input.tex.xy - SHADOW_OFFSET);
	shadowTexel = shaderTexture.Sample(SampleType, s_f);
	alphaShadowMaskDistance = shadow.a;
	//shadowColor = float4(0.0, 0.0, 0.0, 1.0); // black shadow color

	shadow = shadowColor * smoothstep(0.1, 0.6, shadowTexel.a);
	//shadow = smoothstep(0.5, 0.6, alphaShadowMaskDistance);

	//shadow.x = shadowColor.x;
	//shadow.y = shadowColor.y;
	//shadow.z = shadowColor.z;

	//shadow.a *= smoothstep(0.1, 1.0, shadow.a); // bigger gap on min and max to get blur effect.


	//shadow.a *= 0.67; // set opacity


	base = lerp(shadow, base, base.a);
	
	return base;

	return base + shadow; // How do we combine these two?


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
		SetPixelShader(CompileShader(ps_4_0, TextureShadowedPixelShader()));
		SetGeometryShader(NULL);
	}

}



