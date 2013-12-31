////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __ABSTRACTFRAME_H__
#define __ABSTRACTFRAME_H__

//+-----------------------------------------------------------------------------
//
//  Class:
//      ABSTRACTFRAME
//
//  Synopsis:
//      Differentiates which of the two possible arcs could match the given arc
//      parameters.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "Abstract.h"
#include "Graphics.h"
#include "Renderable.h"
#include "AbstractComponent.h"
#include "Pipelineable.h"
#include "AbstractTexture.h"
#include "Component.h"
#include "Panel.h"
#include "Camera.h"
#include "CameraProperties.h"
#include "RenderData.h"
#include "BackBuffer.h"
#include "MatrixFactory.h"
#include "RootPane.h"
#include "AbstractWindow.h"
#include "GXSettings.h"
#include "Rect.h"

namespace A2D {
	
	////////////////////////////////////////////////////////////////////////////////
	// FORWARD DECLARATIONS
	////////////////////////////////////////////////////////////////////////////////

	class	Abstract;
	class	Renderable;
	class	AbstractComponent;
	class	Camera;
	struct	CameraProperties;
	struct	RenderData;
	class	MatrixFactory;
	class	BackBuffer;
	struct	BufferData;
	class	MatrixFactory;
	class	RootPane;
	
	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

	class AbstractFrame : public Abstract, public Runnable
	{

	private:

		RootPane               *     aRootPane;
		BackBuffer             *     aBackBuffer;
		TextureBuffer          *     aTextureBuffer;
		TextureBuffer          *     aBlurBuffer;
		Camera                 *     aCamera;
		GXSettings			  		aGXSettings;
		AbstractWindow	  	  * 	aWindow;
		AbstractEventQueue	  *		aEventQueue = NULL;
		Graphics				  *		aGraphics;

		int								aId;
		static int						aClassInstances;

		bool							aValidatedContents;
	public:

		RootPane               *     GetRootPane();
		HRESULT                         CreateResources();
		void                            Update();
		void							dispose();
		void							invalidate();
		// void							revalidate(); --- Unsafe for AbstractFrame!!!

	protected:
		void							validated();
		void							validate();

	public:
		int								id();
		void							setBackground(byte xRed, byte xGreen, byte xBlue);
		void							setBorder(byte xAlpha, byte xRed, byte xGreen, byte xBlue, float xWidth);
		void							setShadow(byte xAlpha, byte xRed, byte xGreen, byte xBlue, float xRadius);
		void							SetVisible(bool xVisibility);
		void							SetName(LPCWSTR  xName);
		void							setBounds(Rect * xRect);
		void							setBounds(float xLeft, float xTop, float xWidth, float xHeight);
		void							SetSize(float xWidth, float xHeight);
		void							SetSize(Dims * xDims);
		void							SetUndecorated(bool xDecorated);
		void							SetLocationRelativeTo(AbstractFrame * xFrame);
		void							SetVsync(bool xVsync);
		void							SetDefaultCloseOperation(int xOperation);
		AbstractWindow		  *		getWindow();
		void							run(int xThreadId);

		////////////////////////////////////////////////////////////////////////////////
		// PLATFORM COMPATIBLE IMPLEMENTATION
		////////////////////////////////////////////////////////////////////////////////

	protected:

		virtual AbstractWindow *		createPlatformCompatibleWindow() = 0;
		virtual AbstractEventQueue*	createPlatformCompatibleEventQueue() = 0;

		////////////////////////////////////////////////////////////////////////////////
		// ABSTRACT
		////////////////////////////////////////////////////////////////////////////////

	public:

		virtual HRESULT                 Initialize();
		virtual void                    Deinitialize();
		virtual LPCWSTR                 GetClass();
		virtual LPCWSTR                 ToString();
		virtual bool                    operator==(Abstract * xAbstract);

	};
}

#endif
