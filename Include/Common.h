#ifndef __COMMON_H__
#define __COMMON_H__

//+-----------------------------------------------------------------------------
//
//  Class:
//      COMMON
//
//  Synopsis:
//      Differentiates which of the two possible arcs could match the given arc
//      parameters.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// DEFINE
////////////////////////////////////////////////////////////////////////////////

#define FLT_ZERO                                              0.0f
#define FLT_ONE                                               1.0f

#define _PIPELINE_PREPROCESS_START                         0x2510
#define _PIPELINE_PREPROCESS_CREATE                        0x2511
#define _PIPELINE_PREPROCESS_FINISH                        0x2512

#define _GRAPHICS_ACTIVE_BUFFER_PRIMARY   		          0x3511
#define _GRAPHICS_ACTIVE_BUFFER_SECONDARY		          0x3512
#define _GRAPHICS_ACTIVE_BUFFER_TERTIARY					  0x3513

#define _WINDOW_BOX_SHADOW_SAFELYTY_RATIO					  2
#define _WINDOW_RESIZE_EDGE_DISTANCE                       5
#define _WINDOW_RESIZE_DEFAULT_DISTANCE					  3
#define _WINDOW_MOVE_BAR_DISTANCE							25
#define _WINDOW_MOVE_DEFAULT_DISTANCE						10

#define _GRAPHICSTOOLKIT_BASIC_TEXTURE_SHADER			  0x4000
#define _GRAPHICSTOOLKIT_VERTICAL_BLUR_TEXTURE_SHADER      0x4001
#define _GRAPHICSTOOLKIT_HORIZONTAL_BLUR_TEXTURE_SHADER    0x4002

#define	_OPT_BACKGROUND_REPEAT_REPEAT_X					  0x3001
#define	_OPT_BACKGROUND_REPEAT_REPEAT_Y					  0x3010
#define	_OPT_BACKGROUND_REPEAT_NO_REPEAT					  0x3003

#define	_OPT_BACKGROUND_POSITION_CENTER					  0x3004
#define	_OPT_BACKGROUND_POSITION_TOP						  0x3005
#define	_OPT_BACKGROUND_POSITION_RIGHT					  0x3006
#define	_OPT_BACKGROUND_POSITION_BOTTOM					  0x3007
#define	_OPT_BACKGROUND_POSITION_LEFT					  0x3008

#define	_OPT_BACKGROUND_SIZE_COVER						  0x3009
#define	_OPT_BACKGROUND_SIZE_STRETCH						  0x300A

// Debugging

#define SYSOUT_FLT(x)										  _RPT1( 0, "[Aurora -SDK] %f\n", x )
#define SYSOUT_INT(x)										  _RPT1( 0, "[Aurora -SDK] %d\n", x )
#define SYSOUT_HEX(x)										  _RPT1( 0, "[Aurora -SDK] 0x%X\n", x )
#define SYSOUT_STR(x)										  _RPT1( 0, "[Aurora -SDK] %s\n", x )
#define SYSOUT_F(f, ...)									  _RPT1( 0, "[Aurora -SDK] " f "\n", __VA_ARGS__ )

#define FLT_255			255.0f

#define G_SAFELY(hr)    if(hr != 0) { SYSOUT_STR("Failure detected");	return; }
#define SAFELY(hr)		if(hr != 0){ SYSOUT_STR("Failure detected");return E_FAIL; }
#define NULLCHECK(hr)	if(!hr){ SYSOUT_STR("Failure detected"); return E_FAIL; }
#define	DESTROY(x)		if(x) { delete x; x = 0; }
#define D3DDESTROY(x)   if(x) { x->Release(); x = 0; }
#define THREAD_DESTROY(x)  if(x) { x->stop(); delete x; x = 0; }

#endif
