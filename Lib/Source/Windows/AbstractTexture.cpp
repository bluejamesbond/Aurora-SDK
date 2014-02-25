
#include "../../../Include/Windows/ExtLibs.h"
#include "../../../Include/Windows/AbstractTexture.h"

using namespace A2D;

bool AbstractTexture::hasAlpha()
{
	// Force to be true
	return true;
}

Dims* AbstractTexture::GetSize()
{
	return &aDims;
}

const Rect* AbstractTexture::GetClip(int xIndex)
{
	return &aClip;
}

void AbstractTexture::SetClip(Rect * xClip, int xIndex)
{
	if (!xClip)
	{
		aClip.m_x = 0.0f;
		aClip.m_y = 0.0f;
		aClip.m_width = aDims.m_width;
		aClip.m_height = aDims.m_height;

		return;
	}

	// All values greater than zero but less than height/width
	aClip.m_x = min__(max__(xClip->m_x, 0.0f), aDims.m_width);
	aClip.m_y = min__(max__(xClip->m_y, 0.0f), aDims.m_height);
	aClip.m_width = min__(max__(xClip->m_width, 0.0f), aDims.m_width);
	aClip.m_height = min__(max__(xClip->m_height, 0.0f), aDims.m_height);
}

/////////////////////////////////////////////////////////////////////////////
// REQUIRED BY _ABSTRACT
////////////////////////////////////////////////////////////////////////////

STATUS AbstractTexture::initialize()
{
	SetClip(NULL);

	return STATUS_OK;
}
