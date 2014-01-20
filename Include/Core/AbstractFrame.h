
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


#include "Panel.h"
#include "CameraProperties.h"
#include "AbstractBackBuffer.h"
#include "AbstractWindow.h"
#include "GXSettings.h"
#include "ComponentManager.h"
#include "Rect.h"
#include "EventSource.h"

namespace A2D {
    
    ////////////////////////////////////////////////////////////////////////////////
    // FORWARD DECLARATIONS
    ////////////////////////////////////////////////////////////////////////////////

    class   Abstract;
    class   BackBuffer;
    class   RootPane;
    class   Graphics;
    
    ////////////////////////////////////////////////////////////////////////////////
    // DECLARATION
    ////////////////////////////////////////////////////////////////////////////////

    class AbstractFrame : public Runnable, public EventSource
    {

    public:

        AbstractFrame();
        ~AbstractFrame();

    private:

        AbstractBackBuffer     *        aBackBuffer;
        AbstractWindow         *        aWindow;
        AbstractEventQueue     *        aEventQueue = NULL;
        void                   *        aGraphics;
        ComponentManager       *        aComponentManager;
        Panel                           aRootPane;
        GXSettings                      aGXSettings;

        int                             aId;
        static int                      aClassInstances;

        bool                            aValidatedContents;

    public:

        Panel&                          getRootPane();
        STATUS                          createResources();
        void                            update();
        void                            dispose();
        void                            invalidate();
        // void                         revalidate(); --- Unsafe for AbstractFrame!!!

    protected:
        void                            validated();
        void                            validate();
        STATUS                          addListener(AbstractListener * xListener);
        STATUS                          removeListener(AbstractListener * xListener);
        Rect *                          getEventRegion();

    public:
        int                             id();
        void                            setBackground(byte xRed, byte xGreen, byte xBlue);
        void                            setBorder(byte xAlpha, byte xRed, byte xGreen, byte xBlue, float xWidth);
        void                            setShadow(byte xAlpha, byte xRed, byte xGreen, byte xBlue, float xRadius);
        void                            setVisible(bool xVisibility);
        void                            setName(wchar_t *  xName);
        void                            setBounds(Rect * xRect);
        void                            setBounds(float xLeft, float xTop, float xWidth, float xHeight);
        void                            setSize(float xWidth, float xHeight);
        void                            setSize(Dims * xDims);
        void                            setUndecorated(bool xDecorated);
        void                            setLocationRelativeTo(AbstractFrame * xFrame);
        void                            setVsync(bool xVsync);
        void                            setDefaultCloseOperation(int xOperation);
		void                            run(int xThreadId);
		AbstractWindow*					getWindow();
        ComponentManager*				getComponentManager();


    protected:

        virtual STATUS                  createPlatformCompatibleEventQueue(AbstractEventQueue ** xEventQueue) IMPLEMENT;
        virtual STATUS                  createPlatformCompatibleWindow(AbstractWindow ** xWindow) IMPLEMENT;
        virtual STATUS                  createPlatformCompatibleBackBuffer(AbstractBackBuffer ** xBackBuffer, AbstractWindow * xWindow, GXSettings * xSettings) IMPLEMENT;
        virtual STATUS                  createAndInitPlatformCompatibleGraphics(void ** xGraphics, AbstractBackBuffer * xBackbuffer) IMPLEMENT;
        
    public:

        virtual STATUS                 initialize();

    };
}

#endif
