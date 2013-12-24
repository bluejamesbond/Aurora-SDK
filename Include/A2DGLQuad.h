////////////////////////////////////////////////////////////////////////////////
// GUARDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __A2DGLXQUAD_H__
#define __A2DGLXQUAD_H__

//+-----------------------------------------------------------------------------
//
//  Class: 
//      A2DGLXQUAD
//
//  Synopsis:
//      Open GL 4.0 + Linux Implementation of Quad class to be rendered.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "A2DExtLibs.h"
#include "A2DAbstractShape.h"
#include "A2DTexture.h"
#include "A2DRect.h"

////////////////////////////////////////////////////////////////////////////////
// FORWARD DECLARATIONS
////////////////////////////////////////////////////////////////////////////////

class A2D;
class A2DAbstract;
class A2DAbstractShape;
class A2DTexture;

////////////////////////////////////////////////////////////////////////////////
// DEFINE
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// DECLARATION
////////////////////////////////////////////////////////////////////////////////

class A2DGLXQuad : public A2DQuad
{
public:

        A2DQuad(A2DBackBuffer * xBackBuffer, A2DRect * xRect);
        ~A2DQuad();

        ///////////////////////////////////////////////////////////

        A2DTexture                        *                        aTexture;
        A2DDims                                *                        aWindowDims;
        
        ///////////////////////////////////////////////////////////

        A2DRect                                *                        aRect;
        A2DRect                                *                        aConstraints;
        A2DVertexData                *                        aVertices; // DONT FORGET TO RELEASE THIS AFTER

        float                                                        aQuadWidth;
        float                                                        aQuadHeight;

        float                                                        aPrevPosX;
        float                                                        aPrevPosY;

        float                                                        aLeft;
        float                                                        aRight;
        float                                                        aTop;
        float                                                        aBottom;
        float                                                        aLeftTex;
        float                                                        aRightTex;
        float                                                        aTopTex;
        float                                                        aBottomTex;

        int                                                                aIndex = 0;

        bool                                                        aCONSTRAINT_CHANGED;

        ///////////////////////////////////////////////////////////

        virtual void                                        Update(void* xArgs[]);
        virtual HRESULT                                        Map();

        ////////////////////////////////////////////////////////////

public:

        virtual void                                        SetConstraints(A2DRect * xRect);

        ////////////////////////////////////////////////////////////

protected:

        virtual void                                        CalculateCoords(A2DRect * xTexRect);
        virtual HRESULT                                        MapCoords();

        ////////////////////////////////////////////////////////////

        virtual void                                        DestroyResources();

public:

        //////////////////////////////////////////////////////////
        // A2DABSTRACT IMPLEMENTATION
        //////////////////////////////////////////////////////////

        virtual HRESULT                 Initialize();
        virtual void                    Deinitialize();
        virtual LPCWSTR                 GetClass();
        virtual LPCWSTR                 ToString();
        virtual bool                    operator==(A2DAbstract * xAbstract); // Don't campare against quad but against any Object
};



#endif