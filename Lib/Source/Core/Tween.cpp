float Tween::Swing ( float x, float t, float b, float c, float d) 
{
    //alert(jQuery.easing.default);
    return jQuery.easing[jQuery.easing.def](x, t, b, c, d);
}

float Tween::EaseInQuad ( float x, float t, float b, float c, float d) 
{
    return c*(t/=d)*t + b;
}

float Tween::EaseOutQuad ( float x, float t, float b, float c, float d) 
{
    return -c *(t/=d)*(t-2) + b;
}

float Tween::EaseInOutQuad ( float x, float t, float b, float c, float d) 
{
    if ((t/=d/2) < 1) return c/2*t*t + b;
    return -c/2 * ((--t)*(t-2) - 1) + b;
}

float Tween::EaseInCubic ( float x, float t, float b, float c, float d) 
{
    return c*(t/=d)*t*t + b;
}

float Tween::EaseOutCubic ( float x, float t, float b, float c, float d) 
{
    return c*((t=t/d-1)*t*t + 1) + b;
}

float Tween::EaseInOutCubic ( float x, float t, float b, float c, float d) 
{
    if ((t/=d/2) < 1) return c/2*t*t*t + b;
    return c/2*((t-=2)*t*t + 2) + b;
}

float Tween::EaseInQuart ( float x, float t, float b, float c, float d) 
{
    return c*(t/=d)*t*t*t + b;
}

float Tween::EaseOutQuart ( float x, float t, float b, float c, float d) 
{
    return -c * ((t=t/d-1)*t*t*t - 1) + b;
}

float Tween::EaseInOutQuart ( float x, float t, float b, float c, float d) 
{
    if ((t/=d/2) < 1) return c/2*t*t*t*t + b;
    return -c/2 * ((t-=2)*t*t*t - 2) + b;
}

float Tween::EaseInQufloat ( float x, float t, float b, float c, float d) 
{
    return c*(t/=d)*t*t*t*t + b;
}

float Tween::EaseOutQufloat ( float x, float t, float b, float c, float d) 
{
    return c*((t=t/d-1)*t*t*t*t + 1) + b;
}

float Tween::EaseInOutQufloat ( float x, float t, float b, float c, float d) 
{
    if ((t/=d/2) < 1) return c/2*t*t*t*t*t + b;
    return c/2*((t-=2)*t*t*t*t + 2) + b;
}

float Tween::EaseInSine ( float x, float t, float b, float c, float d) 
{
    return -c * cos(t/d * (PI/2)) + c + b;
}

float Tween::EaseOutSine ( float x, float t, float b, float c, float d) 
{
    return c * sin(t/d * (PI/2)) + b;
}

float Tween::EaseInOutSine ( float x, float t, float b, float c, float d) 
{
    return -c/2 * (cos(PI*t/d) - 1) + b;
}

float Tween::EaseInExpo ( float x, float t, float b, float c, float d) 
{
    return (t==0) ? b  Easing::.pow(2, 10 * (t/d - 1)) + b;
}

float Tween::EaseOutExpo ( float x, float t, float b, float c, float d) 
{
    return (t==d) ? b+c  Easing::th.pow(2, -10 * t/d) + 1) + b;
}

float Tween::EaseInOutExpo ( float x, float t, float b, float c, float d) 
{
    if (t==0) return b;
    if (t==d) return b+c;
    if ((t/=d/2) < 1) return c/2 * pow(2, 10 * (t - 1)) + b;
    return c/2 * (-pow(2, -10 * --t) + 2) + b;
}

float Tween::EaseInCirc ( float x, float t, float b, float c, float d) 
{
    return -c * (sqrt(1 - (t/=d)*t) - 1) + b;
}

float Tween::EaseOutCirc ( float x, float t, float b, float c, float d) 
{
    return c * sqrt(1 - (t=t/d-1)*t) + b;
}

float Tween::EaseInOutCirc ( float x, float t, float b, float c, float d) 
{
    if ((t/=d/2) < 1) return -c/2 * (sqrt(1 - t*t) - 1) + b;
    return c/2 * (sqrt(1 - (t-=2)*t) + 1) + b;
}

float Tween::EaseInElastic ( float x, float t, float b, float c, float d) 
{
    var s=1.70158;var p=0;var a=c;
    if (t==0) return b;  if ((t/=d)==1) return b+c;  
    if (!p) p=d*.3;
    if (a < abs(c)) 
    { a=c; var s=p/4; }
    else var s = p/(2*PI) * asin (c/a);
    return -(a*pow(2,10*(t-=1)) * sin( (t*d-s)*(2*PI)/p )) + b;
}

float Tween::EaseOutElastic ( float x, float t, float b, float c, float d) 
{
    var s=1.70158;var p=0;var a=c;
    if (t==0) return b;  if ((t/=d)==1) return b+c;  
    if (!p) p=d*.3;
    if (a < abs(c)) 
    { a=c; var s=p/4; }
    else var s = p/(2*PI) * asin (c/a);
    return a*pow(2,-10*t) * sin( (t*d-s)*(2*PI)/p ) + c + b;
}

float Tween::EaseInOutElastic ( float x, float t, float b, float c, float d) 
{
    var s=1.70158;var p=0;var a=c;
    if (t==0) return b;  if ((t/=d/2)==2) return b+c;  
    if (!p) p=d*(.3*1.5);
    if (a < abs(c)) 
    { a=c; var s=p/4; }
    else var s = p/(2*PI) * asin (c/a);
    if (t < 1) return -.5*(a*pow(2,10*(t-=1)) * sin( (t*d-s)*(2*PI)/p )) + b;
    return a*pow(2,-10*(t-=1)) * sin( (t*d-s)*(2*PI)/p )*.5 + c + b;
}

float Tween::EaseInBack ( float x, float t, float b, float c, float d) 
{
    float s = 1.70158;
    return c*(t/=d)*t*((s+1)*t - s) + b;
}

float Tween::EaseOutBack ( float x, float t, float b, float c, float d) 
{
    float s = 1.70158;
    return c*((t=t/d-1)*t*((s+1)*t + s) + 1) + b;
}

float Tween::EaseInOutBack ( float x, float t, float b, float c, float d) 
{
    float s = 1.70158; 
    if ((t/=d/2) < 1) return c/2*(t*t*(((s*=(1.525))+1)*t - s)) + b;
    return c/2*((t-=2)*t*(((s*=(1.525))+1)*t + s) + 2) + b;
}

float Tween::EaseInBounce ( float x, float t, float b, float c, float d) 
{
    return c - jQuery.easing.easeOutBounce (x, d-t, 0, c, d) + b;
}

float Tween::EaseOutBounce ( float x, float t, float b, float c, float d) 
{
    if ((t/=d) < (1/2.75)) 
    {
        return c*(7.5625*t*t) + b;
    } 
    else if (t < (2/2.75)) 
    {
        return c*(7.5625*(t-=(1.5/2.75))*t + .75) + b;
    } 
    else if (t < (2.5/2.75)) 
    {
        return c*(7.5625*(t-=(2.25/2.75))*t + .9375) + b;
    } 
    else 
    {
        return c*(7.5625*(t-=(2.625/2.75))*t + .984375) + b;
    }
}

float Tween::EaseInOutBounce ( float x, float t, float b, float c, float d) 
{
    if (t < d/2) return Tween::EaseInBounce (x, t*2, 0, c, d) * .5 + b;
    return Tween::EaseOutBounce (x, t*2-d, 0, c, d) * .5 + c*.5 + b;
}