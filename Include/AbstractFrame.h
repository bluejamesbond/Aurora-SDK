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
#include "AbstractTexture.h"
#include "RootPane.h"
#include "CameraProperties.h"
#include "RenderData.h"
#include "BackBuffer.h"
#include "MatrixFactory.h"
#include "AbstractWindow.h"
#include "GXSettings.h"
#include "RepaintManager.h"
#include "Rect.h"

namespace A2D {
	
	////////////////////////////////////////////////////////////////////////////////
	// FORWARD DECLARATIONS
	////////////////////////////////////////////////////////////////////////////////

	class	Abstract;
	class	Renderable;
	class	Container;
	class	Camera;
	struct	CameraProperties;
	struct	RenderData;
	class	MatrixFactory;
	class	BackBuffer;
	struct	BufferData;
	class	MatrixFactory;
	class	RootPane;
	class	EventSource;

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

	class AbstractFrame : public Runnable, public EventSource
	{

	public:

		AbstractFrame();
		~AbstractFrame();

	private:

		RepaintManager		   *		aRepaintManager;
		RootPane                		aRootPane;
		GXSettings			  			aGXSettings;
		BackBuffer			   *		aBackBuffer;
		AbstractWindow	  	   *		aWindow;
		AbstractEventQueue	   *		aEventQueue = NULL;
		Graphics			   * 		aGraphics;

		int								aId;
		static int						aClassInstances;

		bool							aValidatedContents;

	public:

		RootPane&               		getRootPane();
		HRESULT                         createResources();
		void                            update();
		void							dispose();
		void							invalidate();
		// void							revalidate(); --- Unsafe for AbstractFrame!!!
		void							addMouseListener(MouseListener * xListener);
		void							addMouseMotionListener(MouseMotionListener * xListener);

	protected:
		void							validated();
		void							validate();

	public:
		int								id();
		void							setBackground(byte xRed, byte xGreen, byte xBlue);
		void							setBorder(byte xAlpha, byte xRed, byte xGreen, byte xBlue, float xWidth);
		void							setShadow(byte xAlpha, byte xRed, byte xGreen, byte xBlue, float xRadius);
		void							setVisible(bool xVisibility);
		void							setName(LPCWSTR  xName);
		void							setBounds(Rect * xRect);
		void							setBounds(float xLeft, float xTop, float xWidth, float xHeight);
		void							setSize(float xWidth, float xHeight);
		void							setSize(Dims * xDims);
		void							setUndecorated(bool xDecorated);
		void							setLocationRelativeTo(AbstractFrame * xFrame);
		void							setVsync(bool xVsync);
		void							setDefaultCloseOperation(int xOperation);
		AbstractWindow			*		getWindow();
		void							run(int xThreadId);
		RepaintManager*					getRepaintManager();


	protected:

		virtual AbstractWindow *		createPlatformCompatibleWindow() = 0;
		virtual AbstractEventQueue*		createPlatformCompatibleEventQueue() = 0;
		
	public:

		virtual HRESULT                 initialize();
		virtual LPCWSTR                 getClass();
		virtual LPCWSTR                 toString();

	};
}

#endif
