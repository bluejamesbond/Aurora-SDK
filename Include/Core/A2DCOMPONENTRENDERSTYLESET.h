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

#include "A2DBORDERSET4.h"
#include "A2DDISTANCESET2.h"
#include "A2DDISTANCESET4.h"
#include "A2DPIXELDISTANCESETUINT2.h"
#include "A2DPIXELDISTANCESETINT4.h"
#include "A2DFLOAT4.h"

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

	struct A2DCOMPONENTRENDERSTYLESET
	{
		bool                        m_visible;

		float						m_opacity;
		float	                    m_depth;

		float						m_scrollTop;
		float						m_scrollLeft;

		const Rect*                 m_region;
		const A2DFLOAT4*			m_subRegion;
		const A2DFLOAT4*			m_subBordersRegion;
		const Rect*                 m_visibleRegion;

		Style::Background           m_backgroundStyle;
		Style::Display              m_display;
		Style::Position             m_position;

		A2DBORDERSET4				m_borders;

		A2DDISTANCESET2				m_size;
		A2DDISTANCESET4				m_margins;
		A2DDISTANCESET4				m_positioning;
		A2DDISTANCESET4				m_padding;
		A2DDISTANCESET4				m_borderRadii;

		A2DPIXELDISTANCESETUINT2	m_precalculatedSize;
		A2DPIXELDISTANCESETINT4     m_precalculatedMargins;
		A2DPIXELDISTANCESETINT4     m_precalculatedPositioning;
		A2DPIXELDISTANCESETINT4     m_precalculatedPadding;
		A2DPIXELDISTANCESETUINT4	m_precalculatedBorderRadii;


		int*						m_id;

		wchar_t*                    m_backgroundSrc;
		Paint                       m_backgroundPaint;

		bool						m_dirty;
		bool						m_dirtyRequestRegion;
		bool						m_dirtyVisbleRegion;
		bool						m_dirtyBackground;
		bool						m_dirtyBorderColors;
		bool						m_dirtyBorderWidths;
		bool						m_dirtyOpacityDepth;
		bool						m_dirtyBorderRadii;
		
		A2DCOMPONENTRENDERSTYLESET() :
			m_depth(INT_MIN),
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
			m_dirtyOpacityDepth(false),
			m_dirtyBorderRadii(false),
			m_scrollTop(0),
			m_scrollLeft(0)
		{
		}

		inline void					markRequestRegionAsDirty()		{ m_dirty = m_dirtyRequestRegion = true; }
		inline void					markVisibleRegionAsDirty()		{ m_dirty = m_dirtyVisbleRegion = true; }
		inline void					markBackgroundAsDirty()			{ m_dirty = m_dirtyBackground = true; }
		inline void					markBorderWidthsAsDirty()		{ m_dirty = m_dirtyBorderWidths = true; }
		inline void					markBorderColorsAsDirty()		{ m_dirty = m_dirtyBorderColors = true; }
		inline void					markOpacityAsDirty()			{ m_dirty = m_dirtyOpacityDepth = true; }
		inline void					markDepthAsDirty()				{ m_dirty = m_dirtyOpacityDepth = true; }
		inline void					markBorderRadiiAsDirty()		{ m_dirty = m_dirtyBorderRadii = true; }

		inline bool					isDirty()						{ return m_dirty; };
	};
}

#endif