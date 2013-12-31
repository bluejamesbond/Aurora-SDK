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
		AbstractComponent      *		GetParent();

	public:

		// Accessors
		Rect					  *		GetBounds();

		// Mutators
		// { NONE }


	private:

		bool							aValidatedContents;

	protected:

		void							validated();

	public:

		void							invalidate();
		void							revalidate();

	private:

		// Builders
		AbstractComponent      **		CreateAmmoritizedComponentArray();
		Graphics               *		CreateGraphics();

		// Factory
		// { NONE }

	public:

		// Additional
		void                            Add(AbstractComponent * xAbstractComponent);

	protected:

		// Additional
		void							SetParent(AbstractComponent * xComponent);

	private:

		// Additional
		void                            RemoveComponent(AbstractComponent * xAbstractComponent);
		void                            AddComponent(AbstractComponent * xAbstractComponent);

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
		virtual void					validate();

	public:

		virtual void                    Render(RenderData& xRenderData);

	public:

		// Virtual
		// { RENDERABLE }
		virtual void                    Update(RenderData& xRenderData) final;

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
