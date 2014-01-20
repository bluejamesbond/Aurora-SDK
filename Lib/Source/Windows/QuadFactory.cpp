
#include "../../../Include/Windows/ExtLibs.h"
#include "../../../Include/Windows/TextFactory.h"

using namespace A2D;

TextFactory::TextFactory(ID3D10Device ** xDevice, Dims * xWindowDims) :
aDevice(xDevice), aWindowDims(xWindowDims)
{}

TextFactory::~TextFactory()
{}

STATUS TextFactory::initialize()
{

	return STATUS_OK;
}