////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __A2DGXSETTINGS_H__
#define __A2DGXSETTINGS_H__

//+-----------------------------------------------------------------------------
//
//  Class:
//      A2DGX3DSETTINGS
//
//  Synopsis:
//      Differentiates which of the two possible arcs could match the given arc
//      parameters.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// DECLARATION
////////////////////////////////////////////////////////////////////////////////

struct A2DGXSettings
{
	float							aScreenNear = 0.1f;
	float							aScreenDepth = 1000.0f;
	bool                            aVsync = true;
	bool                            aFullScreen = false;

};

#endif
