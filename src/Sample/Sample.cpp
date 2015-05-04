
//---------------------------------------------------------------------------------------
// This tutorial shows nothing fancy. Only how to setup Ogre to render to
// a window, rolling your own game loop, single threaded.
//
// You only need the basics from the Common framework. Just derive from GameState to
// perform your own scene and update it accordingly.
// Scene setup is divided in two stages (createScene01 & createScene02) because it
// is prepared for multithreading; although it is not strictly necessary in this case.
// See the multithreading tutorial for a better explanation
//---------------------------------------------------------------------------------------

#include "GraphicsSystem.hpp"
#include "SampleGameState.hpp"
#include "SdlInputHandler.hpp"

#include "OgreRenderWindow.h"
#include "OgreTimer.h"

#include "Threading/OgreThreads.h"

//Declares WinMain / main
#include "MainEntryPointHelper.hpp"

using namespace Demo;

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
INT WINAPI WinMainApp( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#else
int mainApp()
#endif
{
    SampleGameState sampleGameState(
        "This is template project\n" );
    GraphicsSystem graphicsSystem( &sampleGameState );

    sampleGameState._notifyGraphicsSystem( &graphicsSystem );

    graphicsSystem.initialize( "Sample" );

    if( graphicsSystem.getQuit() )
    {
        graphicsSystem.deinitialize();
        return 0; //User cancelled config
    }

    Ogre::RenderWindow *renderWindow = graphicsSystem.getRenderWindow();

    graphicsSystem.createScene01();
    graphicsSystem.createScene02();

    //Do this after creating the scene for easier the debugging (the mouse doesn't hide itself)
    SdlInputHandler *inputHandler = graphicsSystem.getInputHandler();
    inputHandler->setGrabMousePointer( true );
    inputHandler->setMouseVisible( false );

    Ogre::Timer timer;
    unsigned long startTime = timer.getMicroseconds();

    double timeSinceLast = 1.0 / 60.0;

    while( !graphicsSystem.getQuit() )
    {
        graphicsSystem.beginFrameParallel();
        graphicsSystem.update( static_cast<float>( timeSinceLast ) );
        graphicsSystem.finishFrameParallel();
        graphicsSystem.finishFrame();

        if( !renderWindow->isVisible() )
        {
            //Don't burn CPU cycles unnecessary when we're minimized.
            Ogre::Threads::Sleep( 500 );
        }

        unsigned long endTime = timer.getMicroseconds();
        timeSinceLast = (endTime - startTime) / 1000000.0;
        timeSinceLast = std::min( 1.0, timeSinceLast ); //Prevent from going haywire.
        startTime = endTime;
    }

    graphicsSystem.destroyScene();
    graphicsSystem.deinitialize();

    return 0;
}
