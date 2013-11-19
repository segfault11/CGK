//------------------------------------------------------------------------------
#include "IEventHandler.h"
#include <iostream>
//------------------------------------------------------------------------------
void CGKAppIEventHandler::OnEvent(const SDL_Event& event)
{
    switch(event.type) 
    {
        case SDL_KEYDOWN: 

            if (event.key.repeat == 1)
            {
                return;
            }

            OnKeyDown(event.key.keysym.sym);
            break;
        
        case SDL_KEYUP: 
            OnKeyUp(event.key.keysym.sym);
            break;
    }   
}
//------------------------------------------------------------------------------
void CGKAppIEventHandler::OnKeyDown(SDL_Keycode key)
{

}
//------------------------------------------------------------------------------
void CGKAppIEventHandler::OnKeyUp(SDL_Keycode key)
{

}
//------------------------------------------------------------------------------