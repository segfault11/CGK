#ifndef LABEL_H__
#define LABEL_H__

#include <string>
#include "../IDrawable.h"
#include "../../Math/Vector3.h"
#include "../../Math/Vector2.h"

/// Defines a pointer to a font.
struct CGKUIFont;
typedef const CGKUIFont* CGKUIFontRef;
    
/// Creates a font. Takes the filename and the size of the font as
/// arguments. 
/// \return A pointer to the font if succeeded, otherwise NULL.
CGKUIFontRef CGKUIFontCreate(const char* name, unsigned int size);

/// Destroys a font.
void CGKUIFontDestroy(CGKUIFontRef* font);



// DELETE ME, I AM JUST FOR DEBUGGING
#include <GL/GLEW.h>
class AtlasDrawer
{
public:
    AtlasDrawer(CGKUIFontRef font);
    ~AtlasDrawer();

    void Draw();

private:
    CGKUIFontRef font;
    GLuint program;
    GLuint vertexArray;
    GLuint buffer;
    GLuint tcBuffer;
    GLuint tex;
};





class CGKUILabel : public CGKAppIDrawable
{
public:
            
    CGKUILabel(
        const CGKVector2i& pos,
        const std::string& text, 
        CGKUIFontRef font, 
        const CGKVector3f& fontCol, 
        const CGKVector3f& bgCol
    );
    ~CGKUILabel();

    void Draw();

private:
    class RealLabel;
    RealLabel* label;

    AtlasDrawer* drawer;
};
 
#endif /* end of include guard: LABEL_H__ */
