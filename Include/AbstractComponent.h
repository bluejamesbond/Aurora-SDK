////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __ABSTRACTCOMPONENT_H__
#define __ABSTRACTCOMPONENT_H__

//+-----------------------------------------------------------------------------
//
//  Abstract Class:
//      ABSTRACTCOMPONENT
//
//  Synopsis:
//      Differentiates which of the two possible arcs could match the given arc
//      parameters.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "QuickList.h"
#include "Rect.h"

namespace A2D {

    ////////////////////////////////////////////////////////////////////////////////
    // FORWARD DECLARATIONS
    ////////////////////////////////////////////////////////////////////////////////

    class Abstract;
    class Renderable;
    struct RenderData;
    class Graphics;

    ////////////////////////////////////////////////////////////////////////////////
    // DECLARATION
    ////////////////////////////////////////////////////////////////////////////////

    class AbstractComponent
    {

    protected:

        Graphics               **       aGraphics;  // cached for later use; i.e. repaint
        AbstractComponent      **       aChildrenComps;
        AbstractComponent       *       aParentComp;
        
        Rect                            aOptRegion;
        Rect                            aOptBackgroundRegion;
        Rect                            aCalculatedRegion;
        QuickList<AbstractComponent*>   aChildren;

        bool                            aValidatedContents;

    protected:

        Rect                  *         _getBounds(); //ptr so it can be switched
        void                            validated();
        void                            setParent(AbstractComponent * xComponent); // used internally

        virtual void                    validate();
        virtual void                    paintComponent(Graphics& xGraphics) = 0;
        virtual void                    paintComponentBorder(Graphics& xGraphics) = 0;

    public:

        void                            invalidate();
        void                            revalidate();
        AbstractComponent&              getParent();
        Rect                            getBounds();
        void                            setBounds(Rect& xRect);
        void                            update(Graphics& graphics);
        void                            updateChildren(Graphics& xGraphics);
        void                            add(AbstractComponent& xAbstractComponent);
        void                            remove(AbstractComponent& xAbstractComponent);
        void                            setBounds(float xX, float xY, float xWidth, float xHeight);
    public:

        virtual HRESULT                 Initialize() = 0;
        virtual LPCWSTR                 GetClass();
        virtual LPCWSTR                 ToString();
        virtual bool                    operator==(Abstract * xAbstract);

    };
}

#endif
