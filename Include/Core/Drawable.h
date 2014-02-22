////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __DRAWABLE_H__
#define __DRAWABLE_H__

//+-----------------------------------------------------------------------------
//
//  Class:  
//      DRAWABLE
//
//  Synopsis:
//      Texture container class.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "Rect.h"
#include "Pipelineable.h"
#include "OrderedList.h"
#include "ChangeListener.h"

namespace A2D {

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

	class Drawable : Pipelineable
	{
		friend class Graphics;
		friend class QuadExpansionShader;

	public:

		Drawable();
		Drawable(wchar_t * x_src);

		virtual ~Drawable()
		{
			// Graphics::unbindTexture();
		}
		
	private:

		OrderedList<ChangeListener*>	m_changeListeners;

		wchar_t*						m_src;
		bool							m_ready;
		bool							m_requestUpdate;
		float							m_opacity;
		Rect							m_rect;
		void*							m_activeTexture;
		void*							m_inActiveTexture;
		byte*							m_data;
		unsigned int					m_bytes;

	public:
		
		inline void setSource(wchar_t * x_src)
		{
			m_src = x_src;

			m_requestUpdate = true;
		}

		inline void fireChangeListeners()
		{
			OrderedList<ChangeListener*>::Node<ChangeListener*>* node = m_changeListeners._head();

			while (node->value)
			{
				node->value->update(this, 0);

				node = node->right;
			}
		}

		inline void addChangeListener(ChangeListener* x_linkable)
		{
			m_changeListeners.push_back(x_linkable, &x_linkable->m_ticket);
		}

		inline void removeChangeListener(ChangeListener* x_linkable)
		{
			m_changeListeners.remove_request(&x_linkable->m_ticket);
		}

		inline wchar_t* getSource()
		{
			return m_src;
		}		

		inline const Dims& getSize()
		{
			return static_cast<Dims&>(m_rect);
		}


	};
}

#endif
