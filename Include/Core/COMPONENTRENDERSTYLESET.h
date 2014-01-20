///////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __COMPONENTRENDERSTYLESET_H__
#define __COMPONENTRENDERSTYLESET_H__

//+-----------------------------------------------------------------------------
//
//  Struct:
//      COMPONENTRENDERSTYLESET
//
//  Synopsis:
//      Differentiates which of the two possible arcs could match the given arc
//      parameters.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "../_A2DLinkers.h"

#include "ExtLibs.h"
#include "Rect.h"
#include "Paint.h"
#include "Style.h"

namespace A2D {

	////////////////////////////////////////////////////////////////////////////////
	// FORWARD DECLARATIONS
	////////////////////////////////////////////////////////////////////////////////

	class AbstractFrame;
	class Abstract;
	class Graphics;
	class Component;
	struct ImageProperties;
	class ComponentManager;

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

	struct COMPONENTRENDERSTYLESET
	{
		bool                        m_visible;

		float						m_opacity;
		float                       m_depth;

		Rect*                       m_region;
		Rect*                       m_visibleRegion;

		Style::Background           m_backgroundStyle;
		Style::Display              m_display;
		Style::Position             m_position;

		Style::BORDERSET4           m_borders;

		Style::DISTANCESET2         m_size;
		Style::DISTANCESET4         m_margins;
		Style::DISTANCESET4         m_positioning;
		Style::DISTANCESET4         m_padding;

		Style::PIXELDISTANCESETUINT2	m_precalculatedSize;
		Style::PIXELDISTANCESETINT4     m_precalculatedMargins;
		Style::PIXELDISTANCESETINT4     m_precalculatedPositioning;
		Style::PIXELDISTANCESETINT4     m_precalculatedPadding;

		wchar_t*                    m_backgroundSrc;
		Paint                       m_backgroundPaint;

		bool						m_dirty;
		bool						m_dirtyRequestRegion;
		bool						m_dirtyVisbleRegion;
		bool						m_dirtyBackground;
		bool						m_dirtyBorderColors;
		bool						m_dirtyBorderWidths;
		bool						m_dirtyOpacityDepth;


		COMPONENTRENDERSTYLESET() :
			m_depth(0.0f),
			m_opacity(1.0f),
			m_visible(true),
			m_display(Style::Display::BLOCK),
			m_position(Style::Position::RELATIVE_),
			m_backgroundSrc(NULL),
			m_dirty(false),
			m_dirtyRequestRegion(false),
			m_dirtyVisbleRegion(false),
			m_dirtyBackground(false),
			m_dirtyBorderColors(false),
			m_dirtyOpacityDepth(false)
		{
		}

		inline void markRequestRegionAsDirty()		{ m_dirty = m_dirtyRequestRegion = true; }
		inline void markVisibleRegionAsDirty()		{ m_dirty = m_dirtyVisbleRegion = true; }
		inline void markBackgroundAsDirty()			{ m_dirty = m_dirtyBackground = true; }
		inline void markBorderWidthsAsDirty()		{ m_dirty = m_dirtyBorderWidths = true; }
		inline void markBorderColorsAsDirty()		{ m_dirty = m_dirtyBorderColors = true; }
		inline void markOpacityDepthAsDirty()		{ m_dirty = m_dirtyOpacityDepth = true; }

		inline bool isDirty()						{ return m_dirty; };
	};
}

#endif