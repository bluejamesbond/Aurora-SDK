
#include "../../../Include/Windows/ExtLibs.h"
#include "../../../Include/Windows/QuadExpansionShader.h"

using namespace A2D;

QuadExpansionShader* QuadExpansionShader::m_singelton = NULL;

QuadExpansionShader::QuadExpansionShader(ID3D10Device ** xDevice) : 
	AbstractShader(xDevice),
	aQuadEffect(NULL),
	aTexturePtr(NULL),
	m_positionMatrixPtr(NULL)
{
	EXECUTE_ONCE(QuadExpansionShader*, 0x000000, m_singelton = this);
}
QuadExpansionShader::~QuadExpansionShader()
{
	AbstractShader::~AbstractShader();

	DESTROY(aTexturePtr);
}

void QuadExpansionShader::updatePositionMatrix(D3DXMATRIX * x_position_matrix)
{
	m_positionMatrixPtr->SetMatrix((float*)(x_position_matrix));
}

void QuadExpansionShader::update(void * x_param, int x_id)
{
	Drawable * drawable = static_cast<Drawable*>(x_param);

	if (drawable)
	{
		Texture * texture = static_cast<Texture*>(drawable->m_activeTexture);

		if (texture)
		{
			SYSOUT_STR("[QuadExpansionShader] Setting new texture.");

			setTexture(texture);
		}
	}
}

ID3D10Effect ** QuadExpansionShader::getEffect()
{
	return &aQuadEffect;
}

LPCWSTR QuadExpansionShader::getEffectName()
{
	return L"../../../Aurora-SDK/Lib/Assets/Shaders/quad.fx";
}

STATUS QuadExpansionShader::getUsableVariablePointers(ID3D10Effect * xEffect)
{
	// Get pointers to the three matrices inside the 
	// shader so we can update them from this class.

	if (!aTexturePtr)
	{
		aTexturePtr = xEffect->GetVariableByName("shaderTexture")->AsShaderResource();
	}

	if (!m_positionMatrixPtr)
	{
		m_positionMatrixPtr = xEffect->GetVariableByName("position_matrix")->AsMatrix();
	}

	return STATUS_OK;
}

STATUS	QuadExpansionShader::createPolygonLayout(D3D10_INPUT_ELEMENT_DESC ** xPolygonLayout)
{	
	*xPolygonLayout = QuadExpansionVertex::aPolygonLayout;

	return STATUS_OK;
}

unsigned int QuadExpansionShader::getPolygonLayoutElementCount()
{
	return 9;
}

LPCSTR QuadExpansionShader::getTechniqueName()
{
	return "ColorTechnique";
}