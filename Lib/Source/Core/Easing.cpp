
#include "../../../include/Core/ExtLibs.h"
#include "../../../include/Core/Easing.h"

using namespace A2D;

TWEEN Easing::IN_QUAD = &Easing::inQuad;
TWEEN Easing::OUT_QUAD = &Easing::outQuad;
TWEEN Easing::IN_OUT_QUAD = &Easing::inOutQuad;
TWEEN Easing::IN_CUBIC = &Easing::inOutBounce;
TWEEN Easing::OUT_CUBIC = &Easing::inOutBounce;
TWEEN Easing::IN_OUT_CUBIC = &Easing::inOutBounce;
TWEEN Easing::IN_QUART = &Easing::inOutBounce;
TWEEN Easing::OUT_QUART = &Easing::outQuart;
TWEEN Easing::IN_OUT_QUART = &Easing::inOutQuart;
TWEEN Easing::INT_QUINT = &Easing::inOutBounce;
TWEEN Easing::OUT_QUINT = &Easing::inOutBounce;
TWEEN Easing::IN_OUT_QUINT = &Easing::inOutBounce;
TWEEN Easing::IN_SINE = &Easing::inOutBounce;
TWEEN Easing::OUT_SINE = &Easing::inOutBounce;
TWEEN Easing::IN_OUT_SINE = &Easing::inOutBounce;
TWEEN Easing::IN_EXPO = &Easing::inOutBounce;
TWEEN Easing::OUT_EXPO = &Easing::inOutBounce;
TWEEN Easing::IN_OUT_EXPO = &Easing::inOutBounce;
TWEEN Easing::IN_CIRC = &Easing::inOutBounce;
TWEEN Easing::OUT_CIRC = &Easing::outCirc;
TWEEN Easing::IN_OUT_CIRC = &Easing::inOutCirc;
TWEEN Easing::IN_ELASTIC = &Easing::inElastic;
TWEEN Easing::OUT_ELASTIC = &Easing::outElastic;
TWEEN Easing::IN_OUT_ELASTIC = &Easing::inOutElastic;
TWEEN Easing::IN_BACK = &Easing::inOutBounce;
TWEEN Easing::OUT_BACK = &Easing::outBack;
TWEEN Easing::IN_OUT_BACK = &Easing::inOutBounce;
TWEEN Easing::IN_BOUNCE = &Easing::inBounce;
TWEEN Easing::OUT_BOUNCE = &Easing::outBounce;
TWEEN Easing::IN_OUT_BOUNCE = &Easing::inOutBounce;
TWEEN Easing::OUT_BACK_CIRC = &Easing::outBackCirc;