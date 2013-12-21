#ifndef BUFFER_H
#define BUFFER_H

#ifdef __APPLE__ 
    #include <GL/GLEW.h>
#elif __linux
    #include <GL/glew.h>
#endif

#include "../Math/Vector2.h"

GLuint CGKOpenGLBufferCreateAsMeshWithHeightField(
	const CGKVector2f& start,
	const CGKVector2f& end,
	float dx,
	float (*f)(const CGKVector2f&)
);

#endif /* end of include guard: BUFFER_H */
