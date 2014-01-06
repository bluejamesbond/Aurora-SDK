////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __GXSETTINGS_H__
#define __GXSETTINGS_H__

//+-----------------------------------------------------------------------------
//
//  Class:
//      GX3DSETTINGS
//
//  Synopsis:
//      Differentiates which of the two possible arcs could match the given arc
//      parameters.
//
//------------------------------------------------------------------------------

namespace A2D {

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

	struct GXSettings
	{
		float							aScreenNear = 0.1f;
		float							aScreenDepth = 1000.0f;
		bool                            aVsync = true;
		bool                            aFullScreen = false;

	};
}
#endif
