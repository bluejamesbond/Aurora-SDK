//#include "../../Include/ExtLibs.h"
#include "../../Include/GLXExtLibs.h"
#include "../../Include/AbstractFrame.h"
//#include "../../Include/TextureBuffer.h"

using namespace A2D;

AbstractFrame::AbstractFrame(){}

AbstractFrame::~AbstractFrame()
{

}

HRESULT AbstractFrame::createResources()
{	
    createPlatformCompatibleWindow(&aWindow);
		
	return S_OK;
}
