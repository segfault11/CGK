//------------------------------------------------------------------------------
#include "Application.h"
#include "../Error/Error.h"
#include <stdexcept>
#include <GL/GLEW.h>
#include <iostream>
#include <SDL2/SDL.h>
//------------------------------------------------------------------------------
static bool initialized_ = false;
static SDL_Window* window_ = NULL;
static SDL_GLContext context_ = NULL;
static float elapsed_ = 0.0f;
static std::list<CGKAppIEventHandler*> eventHandlers_;
static std::list<CGKAppIDrawable*> drawables_;
static std::list<CGKAppIDrawable*> guiElements_;
static std::list<CGKAppIObject*> objects_;
static CGKCamera camera_;
//------------------------------------------------------------------------------
static unsigned int screenWidth_;
static unsigned int screenHeight_;
//------------------------------------------------------------------------------
void CGKAppInit(
    const char* name, 
    unsigned int x, 
    unsigned int y, 
    unsigned int width, 
    unsigned int height
)
{
    if (initialized_)
    {
        return;
    }

    // initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        throw std::runtime_error(SDL_GetError());       
    }

    // Set OpenGL context attributes
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 24);
    
    // create a new window  
    window_ = SDL_CreateWindow(
            name,
            0, 0, 
            width, height, 
            SDL_WINDOW_SHOWN
        );

    if (window_ == NULL)
    {
        SDL_Quit();
        throw std::runtime_error(SDL_GetError());
    }

    // create an OpenGL context
    context_ = SDL_GL_CreateContext(window_);
    
    if (context_ == NULL)
    {
        SDL_DestroyWindow(window_);
        SDL_Quit();
        throw std::runtime_error(SDL_GetError());
    }

    // set up GLEW
    glewExperimental = GL_TRUE; 

    CGK_ASSERT(GLEW_OK == glewInit())

    screenWidth_ = width;
    screenHeight_ = height;

    initialized_ = true;

    glGetError();
}
//------------------------------------------------------------------------------
void CGKAppDestroy()
{
    if (!initialized_)
    {
        return;
    }

    SDL_GL_DeleteContext(context_);
    SDL_DestroyWindow(window_);
    SDL_Quit();

    initialized_ = false;
}
//------------------------------------------------------------------------------
void CGKAppRun() 
{
    if (!initialized_)
    {
        throw std::runtime_error("Application not initialized");
    }

    SDL_Event event; 
    bool done = false;

    Uint32 currTime = SDL_GetTicks();

    // event handling
    while (!done) 
    {
        // compute the time
        elapsed_ = static_cast<float>(SDL_GetTicks() - currTime);
        currTime = SDL_GetTicks();
 
        // handle events
        while (SDL_PollEvent(&event))
        {
            // Notify all event listeners
            std::list<CGKAppIEventHandler*>::iterator start = eventHandlers_.begin();
            std::list<CGKAppIEventHandler*>::iterator end = eventHandlers_.end();

            for (; start != end; start++)
            {
                (*start)->OnEvent(event);
            }

            if (event.type == SDL_QUIT || event.type == SDL_QUIT)
            {
                done = true;
            }    
        }


        // update all objects
        {
        
            std::list<CGKAppIObject*>::iterator start = objects_.begin();
            std::list<CGKAppIObject*>::iterator end = objects_.end();

            for (; start != end; start++)
            {
                (*start)->Update();
            }

        }


        //  draw gui renderer
        glEnable(GL_DEPTH_TEST);
        // glDepthMask(GL_TRUE);
        // glDepthFunc(GL_LEQUAL);
        // glDepthRange(0.0f, 1.0f);
        {
            glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
            std::list<CGKAppIDrawable*>::iterator start = drawables_.begin();
            std::list<CGKAppIDrawable*>::iterator end = drawables_.end();

            for (; start != end; start++)
            {
                (*start)->Draw();
            }

        }

        
        //  draw gui renderer
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        {        
            std::list<CGKAppIDrawable*>::iterator start = guiElements_.begin();
            std::list<CGKAppIDrawable*>::iterator end = guiElements_.end();

            for (; start != end; start++)
            {
                (*start)->Draw();
            }

        }
        glDisable(GL_BLEND);


        SDL_GL_SwapWindow(window_);
    }
    
}
//------------------------------------------------------------------------------
void CGKAppRegisterDrawable(CGKAppIDrawable& drawable)
{
    drawables_.push_back(&drawable);
    objects_.push_back(&drawable);
}
//------------------------------------------------------------------------------
void CGKAppRegisterEventHandler(CGKAppIEventHandler& eventHandler)
{
    eventHandlers_.push_back(&eventHandler);
    objects_.push_back(&eventHandler);
}
//------------------------------------------------------------------------------
bool CGKAppIsInitialized()
{
    return initialized_;
}
//------------------------------------------------------------------------------
float CGKAppGetDeltaTime() 
{
    return elapsed_;
}
//------------------------------------------------------------------------------
unsigned int CGKAppGetScreenWidth()
{
    return screenWidth_;
}
//------------------------------------------------------------------------------
unsigned int CGKAppGetScreenHeight()
{
    return screenHeight_;
}
//------------------------------------------------------------------------------
void CGKAppSetCamera(const CGKCamera& camera)
{
    camera_ = camera;
}
//------------------------------------------------------------------------------
CGKCamera& CGKAppGetCamera()
{
    return camera_;
}
//------------------------------------------------------------------------------