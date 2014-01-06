int Tween::Swing ( int x, int t, int b, int c, int d) 
{
    //alert(jQuery.easing.default);
    return jQuery.easing[jQuery.easing.def](x, t, b, c, d);
}

int Tween::EaseInQuad ( int x, int t, int b, int c, int d) 
{
    return c*(t/=d)*t + b;
}

int Tween::EaseOutQuad ( int x, int t, int b, int c, int d) 
{
    return -c *(t/=d)*(t-2) + b;
}

int Tween::EaseInOutQuad ( int x, int t, int b, int c, int d) 
{
    if ((t/=d/2) < 1) return c/2*t*t + b;
    return -c/2 * ((--t)*(t-2) - 1) + b;
}

int Tween::EaseInCubic ( int x, int t, int b, int c, int d) 
{
    return c*(t/=d)*t*t + b;
}

int Tween::EaseOutCubic ( int x, int t, int b, int c, int d) 
{
    return c*((t=t/d-1)*t*t + 1) + b;
}

int Tween::EaseInOutCubic ( int x, int t, int b, int c, int d) 
{
    if ((t/=d/2) < 1) return c/2*t*t*t + b;
    return c/2*((t-=2)*t*t + 2) + b;
}

int Tween::EaseInQuart ( int x, int t, int b, int c, int d) 
{
    return c*(t/=d)*t*t*t + b;
}

int Tween::EaseOutQuart ( int x, int t, int b, int c, int d) 
{
    return -c * ((t=t/d-1)*t*t*t - 1) + b;
}

int Tween::EaseInOutQuart ( int x, int t, int b, int c, int d) 
{
    if ((t/=d/2) < 1) return c/2*t*t*t*t + b;
    return -c/2 * ((t-=2)*t*t*t - 2) + b;
}

int Tween::EaseInQuint ( int x, int t, int b, int c, int d) 
{
    return c*(t/=d)*t*t*t*t + b;
}

int Tween::EaseOutQuint ( int x, int t, int b, int c, int d) 
{
    return c*((t=t/d-1)*t*t*t*t + 1) + b;
}

int Tween::EaseInOutQuint ( int x, int t, int b, int c, int d) 
{
    if ((t/=d/2) < 1) return c/2*t*t*t*t*t + b;
    return c/2*((t-=2)*t*t*t*t + 2) + b;
}

int Tween::EaseInSine ( int x, int t, int b, int c, int d) 
{
    return -c * cos(t/d * (PI/2)) + c + b;
}

int Tween::EaseOutSine ( int x, int t, int b, int c, int d) 
{
    return c * sin(t/d * (PI/2)) + b;
}

int Tween::EaseInOutSine ( int x, int t, int b, int c, int d) 
{
    return -c/2 * (cos(PI*t/d) - 1) + b;
}

int Tween::EaseInExpo ( int x, int t, int b, int c, int d) 
{
    return (t==0) ? b  Easing::.pow(2, 10 * (t/d - 1)) + b;
}

int Tween::EaseOutExpo ( int x, int t, int b, int c, int d) 
{
    return (t==d) ? b+c  Easing::th.pow(2, -10 * t/d) + 1) + b;
}

int Tween::EaseInOutExpo ( int x, int t, int b, int c, int d) 
{
    if (t==0) return b;
    if (t==d) return b+c;
    if ((t/=d/2) < 1) return c/2 * pow(2, 10 * (t - 1)) + b;
    return c/2 * (-pow(2, -10 * --t) + 2) + b;
}

int Tween::EaseInCirc ( int x, int t, int b, int c, int d) 
{
    return -c * (sqrt(1 - (t/=d)*t) - 1) + b;
}

int Tween::EaseOutCirc ( int x, int t, int b, int c, int d) 
{
    return c * sqrt(1 - (t=t/d-1)*t) + b;
}

int Tween::EaseInOutCirc ( int x, int t, int b, int c, int d) 
{
    if ((t/=d/2) < 1) return -c/2 * (sqrt(1 - t*t) - 1) + b;
    return c/2 * (sqrt(1 - (t-=2)*t) + 1) + b;
}

int Tween::EaseInElastic ( int x, int t, int b, int c, int d) 
{
    var s=1.70158;var p=0;var a=c;
    if (t==0) return b;  if ((t/=d)==1) return b+c;  
    if (!p) p=d*.3;
    if (a < abs(c)) 
    { a=c; var s=p/4; }
    else var s = p/(2*PI) * asin (c/a);
    return -(a*pow(2,10*(t-=1)) * sin( (t*d-s)*(2*PI)/p )) + b;
}

int Tween::EaseOutElastic ( int x, int t, int b, int c, int d) 
{
    var s=1.70158;var p=0;var a=c;
    if (t==0) return b;  if ((t/=d)==1) return b+c;  
    if (!p) p=d*.3;
    if (a < abs(c)) 
    { a=c; var s=p/4; }
    else var s = p/(2*PI) * asin (c/a);
    return a*pow(2,-10*t) * sin( (t*d-s)*(2*PI)/p ) + c + b;
}

int Tween::EaseInOutElastic ( int x, int t, int b, int c, int d) 
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

int Tween::EaseInBack ( int x, int t, int b, int c, int d) 
{
    int s = 1.70158;
    return c*(t/=d)*t*((s+1)*t - s) + b;
}

int Tween::EaseOutBack ( int x, int t, int b, int c, int d) 
{
    int s = 1.70158;
    return c*((t=t/d-1)*t*((s+1)*t + s) + 1) + b;
}

int Tween::EaseInOutBack ( int x, int t, int b, int c, int d) 
{
    int s = 1.70158; 
    if ((t/=d/2) < 1) return c/2*(t*t*(((s*=(1.525))+1)*t - s)) + b;
    return c/2*((t-=2)*t*(((s*=(1.525))+1)*t + s) + 2) + b;
}

int Tween::EaseInBounce ( int x, int t, int b, int c, int d) 
{
    return c - jQuery.easing.easeOutBounce (x, d-t, 0, c, d) + b;
}

int Tween::EaseOutBounce ( int x, int t, int b, int c, int d) 
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

int Tween::EaseInOutBounce ( int x, int t, int b, int c, int d) 
{
    if (t < d/2) return Tween::EaseInBounce (x, t*2, 0, c, d) * .5 + b;
    return Tween::EaseOutBounce (x, t*2-d, 0, c, d) * .5 + c*.5 + b;
}