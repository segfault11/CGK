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
    
    /// Sets the text of the label.
    /// \param text Text of the label.
    void SetText(const std::string& text);

    /// Sets the color of the label.
    /// \param color Color of the label.
    void SetFontColor(const CGKVector3f& color);

    /// Draws the label to the current framebuffer.
    void Draw();

private:
    class RealLabel;
    RealLabel* label;
};
 
#endif /* end of include guard: LABEL_H__ */
