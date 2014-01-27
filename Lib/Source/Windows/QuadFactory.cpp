
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
	float winWidth = aWindowDims->aWidth;
	float winHeight = aWindowDims->aHeight;

	QuadExpansionVertex * vertices = x_quadData->aVertices;


	//------------------------------------------------------------------------------
	// WARNING: No repeat with textureClip
	//------------------------------------------------------------------------------
	if (x_renderSet.m_dirtyRequestRegion || x_renderSet.m_dirtyVisbleRegion)
	{
		#ifdef A2D_DE__			
		SYSOUT_F("[QuadFactory] [ComponentId: 0x%X] Recalculating region.", *x_renderSet.m_id);
		#endif // A2D_DE__

		const Rect& constraints = *x_renderSet.m_visibleRegion;

		float rectX = 0.0f;
		float rectY = 0.0f;
		float rectWidth = x_renderSet.m_region->aWidth;
		float rectHeight = x_renderSet.m_region->aHeight;

		float calcLeft = max__(rectX, 0.0);
		float calcTop = max__(rectY, 0.0);
		float calcRight = x_quadData->m_previousCalcRight = min__(constraints.aWidth, rectX > 0 ? rectWidth : rectX + rectWidth);
		float calcBottom = x_quadData->m_previousCalcBottom = min__(constraints.aHeight, rectY > 0 ? rectY + rectHeight : rectY + rectHeight);
		float calcHeight = x_quadData->m_previousCalcHeight = calcBottom - calcTop;
		float calcWidth = x_quadData->m_previousCalcWidth = calcRight - calcLeft;
		
		vertices[0].aPosition = D3DXVECTOR4(cvtpx2rp__(winWidth, constraints.aX + calcLeft),
											-cvtpx2rp__(winHeight, constraints.aY + calcTop), 
											cvtpx2rd__(winWidth, calcWidth),
											cvtpx2rd__(winHeight, calcHeight));

		vertices[0].aOptionsSet2 = D3DXVECTOR4(rectWidth, rectHeight, 0.0f, 0.0f);

		x_renderSet.m_dirtyVisbleRegion = false;
		x_renderSet.m_dirtyRequestRegion = false;				
	}
	
	if (x_renderSet.m_dirtyBackground)
	{
		#ifdef A2D_DE__			
		SYSOUT_F("[QuadFactory] [ComponentId: 0x%X] Recalculating texel.", *x_renderSet.m_id);
		#endif // A2D_DE__

		const Rect& constraints = *x_renderSet.m_visibleRegion;

		float rectX = 0.0f;
		float rectY = 0.0f;
		float rectWidth = x_renderSet.m_region->aWidth;
		float rectHeight = x_renderSet.m_region->aHeight;

		float calcRight = x_quadData->m_previousCalcRight;
		float calcBottom = x_quadData->m_previousCalcBottom;
		float calcHeight = x_quadData->m_previousCalcHeight;
		float calcWidth = x_quadData->m_previousCalcWidth;

		float textureWidth = x_texture->GetClip()->aWidth;
		float textureHeight = x_texture->GetClip()->aHeight;

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

				texLeft = (textureWidth - rectWidth) * proportionalConstantX;
				texTop = 0.0;
				texRight = rectWidth + texLeft;
				texBottom = textureHeight;
			}
			else
			{
				textureHeight *= resizeHFactor = rectWidth / textureWidth;

				texLeft = 0.0;
				texTop = (textureHeight - rectHeight) * proportionalConstantY;
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
			texRight = calcRight < constraints.aWidth ? rectWidth : calcWidth;
			texBottom = calcBottom < constraints.aHeight ? rectHeight : calcHeight;

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

		vertices[0].aOptions = D3DXVECTOR4(x_renderSet.m_opacity, 0.0f, aDepth, 1.0f);

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

		/*  vertices[0].aBorderWidths = D3DXVECTOR4(cvtpx2rd__(winWidth, x_renderSet.m_borders.m_precalculatedBorderWidths.m_left),
                                                  cvtpx2rd__(winHeight, x_renderSet.m_borders.m_precalculatedBorderWidths.m_top),
                                                  cvtpx2rd__(winWidth, x_renderSet.m_borders.m_precalculatedBorderWidths.m_right),
                                                  cvtpx2rd__(winHeight, x_renderSet.m_borders.m_precalculatedBorderWidths.m_bottom));*/
          

		vertices[0].aBorderWidths = D3DXVECTOR4(x_renderSet.m_borders.m_precalculatedBorderWidths.m_left,
												x_renderSet.m_borders.m_precalculatedBorderWidths.m_top,
												x_renderSet.m_borders.m_precalculatedBorderWidths.m_right,
												x_renderSet.m_borders.m_precalculatedBorderWidths.m_bottom);
		x_renderSet.m_dirtyBorderWidths = false;
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