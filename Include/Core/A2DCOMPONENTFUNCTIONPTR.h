////////////////////////////////////////////////////////////////////////////////

#ifndef __A2DCOMPONENTFUNCTIONPTR_H__
#define __A2DCOMPONENTFUNCTIONPTR_H__

//+-----------------------------------------------------------------------------
//
//  Struct:
//      A2DCOMPONENTFUNCTIONPTR
//
//  Synopsis:
//      Differentiates which of the two possible arcs could match the given arc
//      parameters.
//
//------------------------------------------------------------------------------

namespace A2D {

	class Component;

	// Typedef interpolatables
	typedef void (Component::*A2DANIMMUTATORFLOAT1)(float);
	typedef void (Component::*A2DANIMMUTATORFLOAT2)(float, float);
	typedef void (Component::*A2DANIMMUTATORFLOAT3)(float, float, float);
	typedef void (Component::*A2DANIMMUTATORFLOAT4)(float, float, float, float);

	typedef float (Component::*A2DANIMACCESSORFLOAT1)(void);

	typedef void(*A2DCALLBACKVOID1)(void*);
	typedef void(*A2DCALLBACKVOID1INT1)(void*, int);
}

#endif