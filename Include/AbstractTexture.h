////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __ABSTRACTTEXTURE_H__
#define __ABSTRACTTEXTURE_H__

//+-----------------------------------------------------------------------------
//
//  Class:  
//      ABSTRACTTEXTURE
//
//  Synopsis:
//      Texture container class.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "Rect.h"
#include "Abstract.h"

namespace A2D {

	////////////////////////////////////////////////////////////////////////////////
	// FORWARD DECLARATIONS
	////////////////////////////////////////////////////////////////////////////////

	class Abstract;
	class AbstractTexture;

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

	class AbstractTexture : public Abstract
	{

	protected:

		// Variables
		Dims							aDims;
		Rect							aClip;

	public:

		// Accessors
		Dims			*		GetSize();
		Rect			*		GetClip(int xIndex = 0);

		// Mutators
		void					SetClip(Rect * xClip, int xIndex = 0);

		// Virtual
		virtual void			*		getPlatformCompatibleResource() = 0;
		virtual	bool					hasAlpha() = 0;

	public:

		// Implementation
		// { ABSTRACT }
		virtual HRESULT                 initialize() = 0;
		virtual LPCWSTR                 getClass() = 0;
		virtual LPCWSTR                 toString() = 0;

	};

}

#endif
