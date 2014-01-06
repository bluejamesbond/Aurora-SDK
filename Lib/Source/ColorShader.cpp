
#include "../../include/ExtLibs.h"
#include "../../include/ColorShader.h"

using namespace A2D;

//******************* STATIC _ VARIABLES *****************//
// These are the variables held as static for every effect file.
// Filename: color.fx
//
// Why?
// ----
// All chidlren will automatically get these. Updating these,
// will update the children as well.
ID3D10Effect * ColorShader::aColorEffect = NULL;
float ** ColorShader::aProjectionMatrix = NULL;
ID3D10EffectMatrixVariable * ColorShader::aWorldMatrixPtr = NULL;
ID3D10EffectMatrixVariable * ColorShader::aViewMatrixPtr = NULL;
ID3D10EffectMatrixVariable * ColorShader::aProjectionMatrixPtr = NULL;
/***********************************************************/

ColorShader::ColorShader(ID3D10Device ** xDevice) : AbstractShader(xDevice) {}

ColorShader::~ColorShader()
{
	AbstractShader::~AbstractShader();

	DESTROY(aWorldMatrixPtr);
	DESTROY(aViewMatrixPtr);
	DESTROY(aProjectionMatrixPtr);
}

ID3D10Effect ** ColorShader::getEffect()
{
	return &aColorEffect;
}

LPCWSTR ColorShader::getEffectName()
{
	return L"../../../Aurora-SDK/Lib/Assets/Shaders/color.fx";
}

HRESULT ColorShader::getUsableVariablePointers(ID3D10Effect * xEffect)
{
	// Get pointers to the three matrices inside the 
	// shader so we can update them from this class.

	if (!aWorldMatrixPtr)
	{
		aWorldMatrixPtr = xEffect->GetVariableByName("worldMatrix")->AsMatrix();
	}

	if (!aViewMatrixPtr)
	{
		aViewMatrixPtr = xEffect->GetVariableByName("viewMatrix")->AsMatrix();
	}

	if (!aProjectionMatrixPtr)
	{
		aProjectionMatrixPtr = xEffect->GetVariableByName("projectionMatrix")->AsMatrix();
	}

	return S_OK;
}

void ColorShader::setWorldMatrix(float ** xMatrix)
{
	// Set the world matrix variable 
	// inside the shader.
	aWorldMatrixPtr->SetMatrix(*xMatrix);

}

void ColorShader::setViewMatrix(float ** xMatrix)
{

	// Set the view matrix variable 
	// minside the shader.
	aViewMatrixPtr->SetMatrix(*xMatrix);
}

void ColorShader::setProjectionMatrix(float ** xMatrix)
{

	// Set the projection matrix variable 
	// inside the shader.
	aProjectionMatrixPtr->SetMatrix(*(aProjectionMatrix = xMatrix));
}

void ColorShader::reloadProjectionMatrix()
{

	// Set the projection matrix variable 
	// inside the shader.
	aProjectionMatrixPtr->SetMatrix(*aProjectionMatrix);
}

HRESULT	ColorShader::createPolygonLayout(D3D10_INPUT_ELEMENT_DESC * xPolygonLayout)
{
	xPolygonLayout[0].SemanticName = "POSITION";
	xPolygonLayout[0].SemanticIndex = 0;
	xPolygonLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	xPolygonLayout[0].InputSlot = 0;
	xPolygonLayout[0].AlignedByteOffset = 0;
	xPolygonLayout[0].InputSlotClass = D3D10_INPUT_PER_VERTEX_DATA;
	xPolygonLayout[0].InstanceDataStepRate = 0;

	xPolygonLayout[1].SemanticName = "COLOR";
	xPolygonLayout[1].SemanticIndex = 0;
	xPolygonLayout[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	xPolygonLayout[1].InputSlot = 0;
	xPolygonLayout[1].AlignedByteOffset = D3D10_APPEND_ALIGNED_ELEMENT;
	xPolygonLayout[1].InputSlotClass = D3D10_INPUT_PER_VERTEX_DATA;
	xPolygonLayout[1].InstanceDataStepRate = 0;

	return S_OK;
}

unsigned int ColorShader::getPolygonLayoutElementCount()
{
	return 2;
}

LPCSTR ColorShader::getTechniqueName()
{
	return "ColorTechnique";
}

LPCWSTR ColorShader::toString()
{
	return L"ColorShader";
}

LPCWSTR ColorShader::getClass()
{
	return L"ColorShader";
}