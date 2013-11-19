#ifndef SDLAPPLICATION_H__
#define SDLAPPLICATION_H__

#include "IEventHandler.h"
#include "IDrawable.h"
#include "Camera.h"
#include <list>


/// Initialize the application. Creates a window and an OpenGL 3.2 context.
/// 
/// @param name Name of the applications (title of the window).
/// @param x x position of the window.
/// @param y y position of the window.
/// @param width width of the window.
/// @param height height of the window.
///
/// @since 2013-08-15 
void CGKAppInit(
    const char* name, 
    unsigned int x, 
    unsigned int y, 
    unsigned int width, 
    unsigned int height
);
void CGKAppDestroy();
/// Enters the main loop of the application.
///  
/// @since 2013-08-15
void CGKAppRun();
void CGKAppSetCamera(const CGKCamera& camera);
CGKCamera& CGKAppGetCamera();
void CGKAppRegisterDrawable(CGKAppIDrawable& drawable);
void CGKAppRegisterEventHandler(CGKAppIEventHandler& eventHandler);
unsigned int CGKAppGetScreenWidth();
unsigned int CGKAppGetScreenHeight();
bool CGKAppIsInitialized();
float CGKAppGetDeltaTime();

#endif /* end of include guard: SDLAPPLICATION_H__ */