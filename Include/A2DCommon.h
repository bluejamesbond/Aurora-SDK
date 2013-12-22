#ifndef __A2DCOMMON_H__
#define __A2DCOMMON_H__

//+-----------------------------------------------------------------------------
//
//  Class:
//      A2DCOMMON
//
//  Synopsis:
//      Differentiates which of the two possible arcs could match the given arc
//      parameters.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// DEFINE
////////////////////////////////////////////////////////////////////////////////

#define A2D_PIPELINE_PREPROCESS_START                         0x2510
#define A2D_PIPELINE_PREPROCESS_CREATE                        0x2511
#define A2D_PIPELINE_PREPROCESS_FINISH                        0x2512

#define A2D_GRAPHICS_ACTIVE_BUFFER_PRIMARY   		          0x3511
#define A2D_GRAPHICS_ACTIVE_BUFFER_SECONDARY		          0x3512
#define A2D_GRAPHICS_ACTIVE_BUFFER_TERTIARY					  0x3513

#define A2D_WINDOW_BOX_SHADOW_SAFETY_RATIO					 2
#define A2D_WINDOW_RESIZE_EDGE_DISTANCE                      10
#define A2D_WINDOW_RESIZE_DEFAULT_DISTANCE					 3

#define A2D_GRAPHICSTOOLKIT_BASIC_TEXTURE_SHADER			  0x4000
#define A2D_GRAPHICSTOOLKIT_VERTICAL_BLUR_TEXTURE_SHADER      0x4001
#define A2D_GRAPHICSTOOLKIT_HORIZONTAL_BLUR_TEXTURE_SHADER    0x4002

#define	A2D_OPT_BACKGROUND_REPEAT_REPEAT_X					  0x3001
#define	A2D_OPT_BACKGROUND_REPEAT_REPEAT_Y					  0x3010
#define	A2D_OPT_BACKGROUND_REPEAT_NO_REPEAT					  0x3003

#define	A2D_OPT_BACKGROUND_POSITION_CENTER					  0x3004
#define	A2D_OPT_BACKGROUND_POSITION_TOP						  0x3005
#define	A2D_OPT_BACKGROUND_POSITION_RIGHT					  0x3006
#define	A2D_OPT_BACKGROUND_POSITION_BOTTOM					  0x3007
#define	A2D_OPT_BACKGROUND_POSITION_LEFT					  0x3008

#define	A2D_OPT_BACKGROUND_SIZE_COVER						  0x3009
#define	A2D_OPT_BACKGROUND_SIZE_STRETCH						  0x300A

// Debugging

#define SYSOUT_FLT(x)										  _RPT1( 0, "%f\n", x )
#define SYSOUT_INT(x)										  _RPT1( 0, "%d\n", x )
#define SYSOUT_HEX(x)										  _RPT1( 0, "0x%X\n", x )
#define SYSOUT_STR(x)										  _RPT1( 0, "%s\n", x )

#endif
