
#include "../../../include/Core/ExtLibs.h"
#include "../../../include/Core/AbstractBackBuffer.h"

using namespace A2D;

AbstractBackBuffer::AbstractBackBuffer(AbstractWindow * xWindow, GXSettings * xGXSettings)
{
	memcpy(&aSettings, xGXSettings, sizeof(GXSettings));
	aWindow = xWindow;
}

Dims * AbstractBackBuffer::getSizeAsPtr()
{
	return &aDims;
}

Dims AbstractBackBuffer::getSize()
{
	return aDims;
}

GXSettings * AbstractBackBuffer::getSettings()
{
	return &aSettings;
}

AbstractBackBuffer::~AbstractBackBuffer()
{

}