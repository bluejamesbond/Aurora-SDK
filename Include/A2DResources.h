#ifndef __RESOURCES_H__
#define __RESOURCES_H__

//+-----------------------------------------------------------------------------
//
//  Class:
//      COMMON
//
//  Synopsis:
//      Contains basic utility functions used by the core as well as the 
//      platform dependent implementations.
//
//------------------------------------------------------------------------------

#define LoadImageResource(x, y)			G_SAFELY(Toolkit::preload(x, y))

#define A2D_XL_RESOURCES(y)				static struct R{  y };				
#define A2D_XL_FRAMES(y)				static struct frames{ y };	
#define A2D_XL_DEFINE_FRAME(x, y)		static struct $##x##{ y };
#define A2D_XL_DRAWABLES(y)				static struct drawables { y };
#define A2D_XL_DEFINE_DRAWABLE(x)		static Drawable x;

typedef void* Drawable;

#endif