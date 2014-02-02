#include "../../../include/Core/ExtLibs.h"
#include "../../../include/Core/FadeListener.h"

using namespace A2D;

FadeListener::FadeListener(){}

FadeListener::~FadeListener(){}


void FadeListener::mouseExited(MouseEvent * xEvent)
{
	Component * source = (Component*)xEvent->getSource();
	source->animate(Component::INTERPOLATE_OPACITY, Easing::OUT_QUAD, 1.0f, 0, 1000);
	xEvent->setConsumed(true);
}

void FadeListener::mouseEntered(MouseEvent * xEvent)
{

	Component * source = (Component*)xEvent->getSource();
	source->animate(Component::INTERPOLATE_OPACITY, Easing::IN_QUAD, 0, 1.0f, 1000);
	xEvent->setConsumed(true);
}
