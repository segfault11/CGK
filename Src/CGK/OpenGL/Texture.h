/*!
** Declaration of various GL helper functions.
**    
** @since 2013-09-10
*/
/**
    TODOS:
        Texture2DCreateFromFile:
        - allow user to specify internal format and other params of the tex

        Texture2DSaveAsBMP:
        - complete the check to figure out the channels of the texture
*/
#ifndef TEXTURE_H__
#define TEXTURE_H__

#ifdef __APPLE__ 
    #include <GL/GLEW.h>
#elif __linux
    #include <GL/glew.h>
#endif

/// Creates an OpenGL 2D texture from an image file. The caller is 
/// responsible to release the texture. The texture is default configured to
/// have a liner minifying and magnification function as well as well as 
/// clamped wrapping.
/// 
/// NOTE: this function binds the newly created texture to the OpenGL context.
/// 
///
/// @param filename Filename of the image to be loaded.
/// @return Handle to the texture if succeeded. Otherwise 0.
GLuint CGKOpenGLTexture2DCreateFromFile(const char* filename);

/// Saves the texture's image data as an bmp file. Fails if [filename]
/// does not end with ".bmp". 
///
/// NOTE: this function binds the newly created texture to the OpenGL context.
void CGKOpenGLTexture2DSaveAsBMP(const char* filename, GLuint handle);
 
#endif /* end of include guard: TEXTURE_H__ */
