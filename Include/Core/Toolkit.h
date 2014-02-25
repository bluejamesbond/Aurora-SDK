////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __TOOLKIT_H__
#define __TOOLKIT_H__

//+-----------------------------------------------------------------------------
//
//  Class:  
//      TOOLKIT
//
//  Synopsis:
//      Texture container class.
//
//------------------------------------------------------------------------------

namespace A2D {

	////////////////////////////////////////////////////////////////////////////////
	// FORWARD DECLARATIONS
	////////////////////////////////////////////////////////////////////////////////

	class AbstractEventQueue;

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATIONS
	////////////////////////////////////////////////////////////////////////////////

	class Toolkit
	{
	public:

		static double					SYSTEM_NANOTIME;
		static int					  waitForBackgroundThreads();
		static AbstractEventQueue* getSystemEventQueue(int xFrameInstanceIndex);
		static void					  addSystemEventQueue(AbstractEventQueue * xEventQueue);

	private:

		static AbstractEventQueue* aEventQueues[20];
		static int					  aEventQueuesLength;
		static int					  aEventQueuesIndex;
	};
}
#endif