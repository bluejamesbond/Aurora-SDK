
#include "../../../Include/Windows/ExtLibs.h"
#include "../../../Include/Windows/QuadFactory.h"

using namespace A2D;

QuadFactory::QuadFactory(ID3D10Device ** xDevice, const Dims * xWindowDims)
{
	aDevice = xDevice;
	aWindowDims = xWindowDims;
}

QuadFactory::~QuadFactory()
{
	D3DDESTROY(aVertexBuffer);
	D3DDESTROY(aIndexBuffer);
}

STATUS QuadFactory::initialize()
{
	SAFELY(DXUtils::CreateDefaultDynamicVertexBuffer<ColoredTextureVertex>(*aDevice, &aVertexBuffer, 6));
	SAFELY(DXUtils::CreateDefaultIndexBuffer(*aDevice, &aIndexBuffer, 6));

	return STATUS_OK;
}

// Temporarily moved to cpp to make the build process faster
void QuadFactory::updateVertexBuffer(QuadData<QuadExpansionVertex, 1> * x_quadData, A2DCOMPONENTRENDERSTYLESET& x_renderSet, Texture * x_texture)
{
	float winWidth = aWindowDims->m_width;
	float winHeight = aWindowDims->m_height;

	QuadExpansionVertex * vertices = x_quadData->aVertices;

	//------------------------------------------------------------------------------
	// WARNING: No repeat with textureClip
	//------------------------------------------------------------------------------
	if (x_renderSet.m_dirtyRequestRegion || x_renderSet.m_dirtyVisbleRegion)
	{
		#ifdef A2D_DE__			
		SYSOUT_F("[QuadFactory] [ComponentId: 0x%X] Recalculating region.", *x_renderSet.m_id);
		#endif // A2D_DE__

		const Rect& region = *x_renderSet.mR;
		const Rect& subRegion = *x_renderSet.m_subRegion;
		const Rect& visibleRegion = *x_renderSet.m_visibleRegion;

		float rectX = 0.0f;
		float rectY = 0.0f;
		float rectWidth = x_renderSet.m_region->m_width;
		float rectHeight = x_renderSet.m_region->m_height;

		float calcLeft = max__(rectX, 0.0);
		float calcTop = max__(rectY, 0.0);
		float calcRight = x_quadData->m_previousCalcRight = min__(visibleRegion.m_width, rectX > 0 ? rectWidth : rectX + rectWidth);
		float calcBottom = x_quadData->m_previousCalcBottom = min__(visibleRegion.m_height, rectY > 0 ? rectY + rectHeight : rectY + rectHeight);
		float calcHeight = x_quadData->m_previousCalcHeight = calcBottom - calcTop;
		float calcWidth = x_quadData->m_previousCalcWidth = calcRight - calcLeft;
		
		vertices[0].m_position = D3DXVECTOR4(cvtpx2rp__(winWidth, visibleRegion.m_x),
											-cvtpx2rp__(winHeight, visibleRegion.m_y), 
											cvtpx2rd__(winWidth, visibleRegion.m_width),
											cvtpx2rd__(winHeight, visibleRegion.m_height));
		
		vertices[0].m_rect = D3DXVECTOR4(0.0f, 0.0f, rectWidth, rectHeight);
		vertices[0].m_subRegion = D3DXVECTOR4(subRegion.m_x, subRegion.m_y, subRegion.m_width, subRegion.m_height);

		x_renderSet.m_dirtyVisbleRegion = false;
		x_renderSet.m_dirtyRequestRegion = false;				
	}
	
	if (x_renderSet.m_dirtyBackground)
	{
		#ifdef A2D_DE__			
		SYSOUT_F("[QuadFactory] [ComponentId: 0x%X] Recalculating texel.", *x_renderSet.m_id);
		#endif // A2D_DE__

		const Rect& visibleRegion = *x_renderSet.m_visibleRegion;

		float rectX = x_renderSet.m_region->m_x < 0.0f ? abs__(x_renderSet.m_region->m_x) : 0.0f;
		float rectY = x_renderSet.m_region->m_y < 0.0f ? abs__(x_renderSet.m_region->m_y) : 0.0f;
		float rectWidth = x_renderSet.m_region->m_width;
		float rectHeight = x_renderSet.m_region->m_height;

		float calcRight = x_quadData->m_previousCalcRight;
		float calcBottom = x_quadData->m_previousCalcBottom;
		float calcHeight = x_quadData->m_previousCalcHeight;
		float calcWidth = x_quadData->m_previousCalcWidth;

		float textureWidth = x_texture->GetClip()->m_width;
		float textureHeight = x_texture->GetClip()->m_height;

		float 
			texLeft, 
			texTop, 
			texRight, 
			texBottom,
			texelLeft, 
			texelTop, 
			texelRight, 
			texelBottom;

		if (x_renderSet.m_backgroundStyle.m_layout == Style::Background::Layout::COVER)
		{
			float resizeVFactor = 1.0,
				  resizeHFactor = 1.0;

			// Discrete Point of Interest 
			// Proportional Strech Algorithm - @author MK
			//------------------------------------------------------------------------------
			// offset[C] = quadrant_2[R][C] * (pointOfInterest[C] / quadrant_1[R][C]) - pointOfInterest[C] 
			// where C = X or Y
			//       R = Range
			//  Offset = offset inside quadrant_2
			// and   0 <= pointOfInterest[C] <= quadrant_1[R][C]

			// TEMPORARILY FORCED
			//------------------------------------------------------------------------------
			float pointOfInterestX = textureWidth;
			float pointOfInterestY = textureHeight / 2;

			float proportionalConstantX = pointOfInterestX / textureWidth;
			float proportionalConstantY = pointOfInterestY / textureHeight;
			//------------------------------------------------------------------------------

			if ((textureWidth / textureHeight) > (rectWidth / rectHeight))
			{
				textureWidth *= resizeVFactor = rectHeight / textureHeight;

				texLeft = (textureWidth - rectWidth) * proportionalConstantX + rectX;
				texTop = 0.0f;
				texRight = rectWidth + texLeft;
				texBottom = textureHeight;
			}
			else
			{
				textureHeight *= resizeHFactor = rectWidth / textureWidth;

				texLeft = 0.0f;
				texTop = (textureHeight - rectHeight) * proportionalConstantY + rectY;
				texRight = textureWidth;
				texBottom = rectHeight + texTop;
			}

			texelLeft = texLeft / textureWidth;
			texelTop = texTop / textureHeight;
			texelRight = texRight / textureWidth;
			texelBottom = texBottom / textureHeight;

			// Crop out any regions that might extend out
			// of the contraints
			//------------------------------------------------------------------------------
			if (calcWidth < rectWidth)
			{
				texelRight -= (rectWidth - calcWidth) / textureWidth / resizeHFactor;
			}

			if (calcHeight < rectHeight)
			{
				texelBottom -= (rectHeight - calcHeight) / textureHeight / resizeVFactor;
			}
		}
		else
		{
			texLeft = rectX > 0 ? 0.0f : abs__(rectX);
			texTop = rectY > 0 ? 0.0f : abs__(rectY);
			texRight = calcRight < visibleRegion.m_width ? rectWidth : calcWidth;
			texBottom = calcBottom < visibleRegion.m_height ? rectHeight : calcHeight;

			if (x_renderSet.m_backgroundStyle.m_layout == Style::Background::Layout::REPEAT)
			{
				texelLeft = texLeft / textureWidth;
				texelTop = texTop / textureHeight;
				texelRight = (calcWidth + texLeft) / textureWidth;
				texelBottom = (calcHeight + texTop) / textureHeight;
			}
			else /*(xBackgroundSettings == Style::STRETCH_WIDTH_HEIGHT)*/
			{
				texelLeft = texLeft / rectWidth;
				texelTop = texTop / rectHeight;
				texelRight = texRight / rectWidth;
				texelBottom = texBottom / rectHeight;
			}
		}

		vertices[0].aColorTex = D3DXVECTOR4(texelLeft, texelTop, texelRight, texelBottom);

		x_renderSet.m_dirtyBackground = false;
	}

	// Set up vertices
	//------------------------------------------------------------------------------
	if (x_renderSet.m_dirtyOpacityDepth)
	{
		#ifdef A2D_DE__			
		SYSOUT_F("[QuadFactory] [ComponentId: 0x%X] Recalculating opacity/depth.", *x_renderSet.m_id);
		#endif // A2D_DE__

		vertices[0].m_options = D3DXVECTOR4(1.0f, 0.0f, aDepth, x_renderSet.m_opacity);

		x_renderSet.m_dirtyOpacityDepth = false;
	}

	if (x_renderSet.m_dirtyBorderColors)
	{
		#ifdef A2D_DE__			
		SYSOUT_F("[QuadFactory] [ComponentId: 0x%X] Recalculating border colors.", *x_renderSet.m_id);
		#endif // A2D_DE__

		vertices[0].aBorderColors = A2DUINT4(x_renderSet.m_borders.m_leftColor.m_raw,
											 x_renderSet.m_borders.m_topColor.m_raw,
											 x_renderSet.m_borders.m_rightColor.m_raw,
											 x_renderSet.m_borders.m_bottomColor.m_raw);

		x_renderSet.m_dirtyBorderColors = false;
	}
	
	if (x_renderSet.m_dirtyBorderWidths)
	{
		#ifdef A2D_DE__			
		SYSOUT_F("[QuadFactory] [ComponentId: 0x%X] Recalculating border widths.", *x_renderSet.m_id);
		#endif // A2D_DE__          

		vertices[0].aBorderWidths = D3DXVECTOR4(SFLOAT(x_renderSet.m_borders.m_precalculatedBorderWidths.m_left),
												SFLOAT(x_renderSet.m_borders.m_precalculatedBorderWidths.m_top),
												SFLOAT(x_renderSet.m_borders.m_precalculatedBorderWidths.m_right),
												SFLOAT(x_renderSet.m_borders.m_precalculatedBorderWidths.m_bottom));
		
		x_renderSet.m_dirtyBorderWidths = false;
	}

	if (x_renderSet.m_dirtyBorderRadii)
	{
		vertices[0].aBorderRadii = D3DXVECTOR4(SFLOAT(x_renderSet.m_precalculatedBorderRadii.m_left),
											   SFLOAT(x_renderSet.m_precalculatedBorderRadii.m_top),
											   SFLOAT(x_renderSet.m_precalculatedBorderRadii.m_right),
											   SFLOAT(x_renderSet.m_precalculatedBorderRadii.m_bottom));

		x_renderSet.m_dirtyBorderRadii = false;
	}

	if (x_renderSet.m_dirty)
	{
		void * mappedVertices = 0;

		// Lock the vertex buffer.
		//------------------------------------------------------------------------------
		x_quadData->aVertexBuffer->Map(D3D10_MAP_WRITE_DISCARD, 0, static_cast<void**>(&mappedVertices));

		// Copy data using SSE2 accelerated method
		//------------------------------------------------------------------------------
		memcpy(static_cast<QuadExpansionVertex*>(mappedVertices), vertices, sizeof(QuadExpansionVertex));

		// Unlock the vertex buffer.
		//------------------------------------------------------------------------------
		x_quadData->aVertexBuffer->Unmap();

		x_renderSet.m_dirty = false;
	}
}