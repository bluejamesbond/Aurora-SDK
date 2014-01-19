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

#include "../_A2DCommon.h"

#include "../Core/Rect.h"
#include "../Core/Pipelineable.h"

namespace A2D {

    ////////////////////////////////////////////////////////////////////////////////
    // FORWARD DECLARATIONS
    ////////////////////////////////////////////////////////////////////////////////

    class AbstractTexture;

    ////////////////////////////////////////////////////////////////////////////////
    // DECLARATION
    ////////////////////////////////////////////////////////////////////////////////

    class AbstractTexture : public Pipelineable
    {
    public:

        virtual ~AbstractTexture() {};

    protected:

        // Variables
        Dims                            aDims;
        Rect                            aClip;

    public:

        // Accessors
        Dims                    *       GetSize();
        Rect                    *       GetClip(int xIndex = 0);

        // Mutators
        void                            SetClip(Rect * xClip, int xIndex = 0);

        // Virtual
        virtual void            *       getPlatformCompatibleResource() IMPLEMENT;
        virtual bool                    hasAlpha() IMPLEMENT;

    public:

        virtual STATUS                 initialize() IMPLEMENT;

    };

}

#endif
