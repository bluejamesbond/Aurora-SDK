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

#include "Renderable.h"
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

	class AbstractComponent : public Renderable
	{
	public:

		// Constructor
		AbstractComponent();

		// Deconstructor
		~AbstractComponent();

	protected:

		// Variables
		Graphics			   **       aGraphics;  // cached for later use; i.e. repaint
		AbstractComponent      **		aChildrenComps;
		AbstractComponent	  *			aParentComp;

		int                             aChildrenCompsLength = 0;
		int                             aChildrenCompsIndex = 0;

		Rect							aOptRegion;
		Rect							aOptBackgroundRegion;
		Rect							aCalculatedRegion;

	public:
		// Accessors
		AbstractComponent      *		getParent();

	public:

		// Accessors
		Rect							getBounds();

	private:

		bool							aValidatedContents;

	protected:

		Rect				  *			_getBounds(); //ptr so it can be switched
		void							validated();
		void							validate();

	public:

		void							invalidate();
		void							revalidate();

	private:

		// Builders
		AbstractComponent      **		CreateAmmoritizedComponentArray();

		// Factory
		// { NONE }

	public:

		// Additional
		void                            add(AbstractComponent * xAbstractComponent);

	protected:

		// Additional
		void							setParent(AbstractComponent * xComponent);

	private:

		// Additional
		void                            removeComponent(AbstractComponent * xAbstractComponent);
		void                            addComponent(AbstractComponent * xAbstractComponent);

	public:

		// Pure Virtual
		virtual void                    paintComponent(RenderData& xRenderData) = 0;
		virtual void                    paintComponentBorder(RenderData& xRenderData) = 0;

	public:

		// Virtual
		virtual void					setBounds(Rect& xRect);
		virtual void					setBounds(float xX, float xY, float xWidth, float xHeight);

	protected:

		// Virtual
		virtual void                    paintChildren(RenderData& xRenderData);
		virtual void                    DeinitializeChildren() final;

	public:

		virtual void                    paint(RenderData& xRenderData);

	public:

		// Virtual
		// { RENDERABLE }
		virtual void                    update(RenderData& xRenderData) final;

	public:

		// Implementation
		// { ABSTRACT }
		virtual HRESULT                 Initialize();
		virtual void                    Deinitialize();
		virtual LPCWSTR                 GetClass();
		virtual LPCWSTR                 ToString();
		virtual bool                    operator==(Abstract * xAbstract);

	};
}

#endif
