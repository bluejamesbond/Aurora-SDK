
#include "../../include/ExtLibs.h"
#include "../../include/ColoredTextureShader.h"

using namespace A2D;

ColoredTextureShader::ColoredTextureShader(ID3D10Device ** xDXDevice) :
AbstractTextureShader(xDXDevice){}

HRESULT	ColoredTextureShader::createPolygonLayout(D3D10_INPUT_ELEMENT_DESC * xPolygonLayout)
{
	xPolygonLayout[0].SemanticName = "POSITION";
	xPolygonLayout[0].SemanticIndex = 0;
	xPolygonLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	xPolygonLayout[0].InputSlot = 0;
	xPolygonLayout[0].AlignedByteOffset = 0;
	xPolygonLayout[0].InputSlotClass = D3D10_INPUT_PER_VERTEX_DATA;
	xPolygonLayout[0].InstanceDataStepRate = 0;

	xPolygonLayout[1].SemanticName = "TEXCOORD";
	xPolygonLayout[1].SemanticIndex = 0;
	xPolygonLayout[1].Format = DXGI_FORMAT_R32G32_FLOAT;
	xPolygonLayout[1].InputSlot = 0;
	xPolygonLayout[1].AlignedByteOffset = D3D10_APPEND_ALIGNED_ELEMENT;
	xPolygonLayout[1].InputSlotClass = D3D10_INPUT_PER_VERTEX_DATA;
	xPolygonLayout[1].InstanceDataStepRate = 0;

	xPolygonLayout[2].SemanticName = "COLOR";
	xPolygonLayout[2].SemanticIndex = 0;
	xPolygonLayout[2].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	xPolygonLayout[2].InputSlot = 0;
	xPolygonLayout[2].AlignedByteOffset = D3D10_APPEND_ALIGNED_ELEMENT;
	xPolygonLayout[2].InputSlotClass = D3D10_INPUT_PER_VERTEX_DATA;
	xPolygonLayout[2].InstanceDataStepRate = 0;

	return S_OK;
}

unsigned int ColoredTextureShader::getPolygonLayoutElementCount()
{
	return 3;
}

LPCSTR ColoredTextureShader::getTechniqueName()
{
	return "ColoredTextureTechnique";
}