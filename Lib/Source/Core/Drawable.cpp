
#include "../../../include/Core/ExtLibs.h"
#include "../../../include/Core/Drawable.h"

using namespace A2D;

Drawable::Drawable() :
	m_src(NULL),
	m_ready(false), 
	m_requestUpdate(false),
	m_opacity(0.0f),
	m_activeTexture(NULL),
	m_inActiveTexture(NULL)
{
}


Drawable::Drawable(wchar_t * x_src) :
	m_src(x_src),
	m_ready(false), 
	m_requestUpdate(true),
	m_opacity(0.0f),
	m_activeTexture(NULL),
	m_inActiveTexture(NULL)
{
}