
#ifndef _Demo_SampleGameState_H_
#define _Demo_SampleGameState_H_

#include "OgrePrerequisites.h"
#include "TutorialGameState.hpp"

namespace Demo
{
    class SampleGameState : public TutorialGameState
    {
    public:
        SampleGameState( const Ogre::String &helpDescription );

        virtual void createScene01(void);

        virtual void keyReleased(const SDL_KeyboardEvent &arg);
    };
}

#endif
