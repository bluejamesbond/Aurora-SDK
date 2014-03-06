////////////////////////////////////////////////////////////////////////////////
// Filename: horizontalblur.fx
////////////////////////////////////////////////////////////////////////////////


/////////////
// GLOBALS //
/////////////
matrix worldMatrix;
matrix viewMatrix;
matrix projectionMatrix;
Texture2D shaderTexture;
float texelSize = 0.0f;


///////////////////
// SAMPLE STATES //
///////////////////
SamplerState SampleType
{
	Filter = MIN_MAG_MIP_LINEAR;
	AddressU = Clamp;
	AddressV = Clamp;
};

// MK Gaussian kernel creator - Javascript
//
//function getGaussianKernel(xRadius)
//{
//	if (xRadius < 1)
//	{
//		return NULL;
//	}
//
//	var dataLength = xRadius * 2 + 1;
//
//	var data = new Array();
//
//	var sigma = xRadius / 3.0;
//	var twoSigmaSquare = 2.0 * sigma * sigma;
//	var sigmaRoot = parseFloat(Math.sqrt(twoSigmaSquare * 3.14159));
//	var total = 0.0;
//
//	for (var i = -xRadius; i <= xRadius; i++)
//	{
//		var distance = parseFloat(i * i);
//		var index = i + xRadius;
//		data[index] = parseFloat(Math.exp(-distance / twoSigmaSquare) / sigmaRoot);
//		total += data[index];
//	}
//
//	for (var i = 0; i < dataLength; i++)
//	{
//		data[i] /= total;
//	}
//
//	return data;
//}
//
//function getPixelKernel(radius)
//{
//	var data = new Array();
//	for (var i = -radius; i < radius + 1; i++)
//		data.push(i);
//	return data;
//}
//
//function getGaussian(radius) {
//	var pKernel = getPixelKernel(radius);
//	var data = "static const float kernel[" + (radius * 2 + 1) + "] = { " + pKernel + " };";
//	var gKernel = getGaussianKernel(radius);
//
//	console.log((data += "\nstatic const float weights[" + (radius * 2 + 1) + "] = { " + gKernel + " };"));
//}


static const float kernel[23] = { -11, -10, -9, -8, -7, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
static const float weights[23] = { 0.00121068926685057, 0.0026437056149144406, 0.005359084430219722, 0.01008475169812478, 0.017617201626268997, 0.028569704244896306, 0.043010220492970465, 0.0601083349811317, 0.07798208303686283, 0.0939186994791525, 0.10500413777949748, 0.10898277469822033, 0.10500413777949748, 0.0939186994791525, 0.07798208303686283, 0.0601083349811317, 0.043010220492970465, 0.028569704244896306, 0.017617201626268997, 0.01008475169812478, 0.005359084430219722, 0.0026437056149144406, 0.00121068926685057 };
//////////////
// TYPEDEFS //
//////////////
struct VertexInputType
{
    float4 position : POSITION;
    float2 tex : TEXCOORD0;
};

struct PixelInputType
{
    float4 position : SV_POSITION;
    float2 tex : TEXCOORD0;
};


////////////////////////////////////////////////////////////////////////////////
// Vertex Shader
////////////////////////////////////////////////////////////////////////////////
PixelInputType HorizontalBlurVertexShader(VertexInputType input)
{
    PixelInputType output;

	// Force w-buffer to be 1.0
	output.position.w = 1.0f;

	// Calculate z-buffer manually
	output.position.z = (10000000 - input.position.z) / 10000000;

	// Calculate the position of the vertex 
	// against the world, view, and projection matrices.
	output.position = input.position;

	// Store the texture coordinates for the pixel shader.
    output.tex = input.tex;
	
	return output;
}


////////////////////////////////////////////////////////////////////////////////
// Pixel Shader
////////////////////////////////////////////////////////////////////////////////
float4 HorizontalBlurPixelShader(PixelInputType input) : SV_Target
{
	// Determine the floating point size of a texel for a screen with this specific width.
	float4 color = float4(0.0f, 0.0f, 0.0f, 0.0f);

	for (int i = 0; i < 23; i++)
	{
		color += shaderTexture.Sample(SampleType, input.tex + float2(texelSize * kernel[i], 0.0f)) * weights[i];
	}

	color.a = 1;

	return color;
}


////////////////////////////////////////////////////////////////////////////////
// Technique
////////////////////////////////////////////////////////////////////////////////
technique10 MainTechnique
{
    pass pass0
    {
        SetVertexShader(CompileShader(vs_4_0, HorizontalBlurVertexShader()));
        SetPixelShader(CompileShader(ps_4_0, HorizontalBlurPixelShader()));
        SetGeometryShader(NULL);
    }
}