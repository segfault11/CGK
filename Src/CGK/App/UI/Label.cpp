//------------------------------------------------------------------------------
#include <cstdlib>
#include <ft2build.h>
#include FT_FREETYPE_H
#include "Label.h"
#include "../Application.h"
#include "../../OpenGL/Program.h"
#include "../../OpenGL/Texture.h"
#include "../../Error/Error.h"
#include "../../Util.h"
#include "../../Math/Vector2.h"
//------------------------------------------------------------------------------
struct CGKUIFont
{
    // INTERNAL REPRESENTATION OF A FONT

    GLuint TexAtlas; // handle to the gl texture atlas
    GLint TexWidth;
    GLint TexHeight;

    // Glyph info
    int BitmapWidths[128];          
    int AtlasOffXs[128];
    CGKVector2i Advances[128];
    CGKVector2i Bearings[128];
};
//------------------------------------------------------------------------------
CGKUIFontRef CGKUIFontCreate(const char* filename, unsigned int size)
{
    // check if we have an OpenGL context
    if (!CGKAppIsInitialized())
    {
        CGK_REPORT("Application was not initialized", CGK_UNKNOWN_ERROR);
        return NULL;
    }

    FT_Library library;

    // load the library
    FT_Error err = FT_Init_FreeType(&library);

    CGK_ASSERT(err == 0)

    FT_Face face;

    // load the font (face)
    err = FT_New_Face(
            library,
            filename,
            0,
            &face 
        );

    if (!(err == 0))
    {
        CGK_REPORT("Could not load font.", CGK_FILE_NOT_FOUND);
        return NULL;
    }

    FT_Set_Pixel_Sizes(face, 0, size);    

    FT_GlyphSlot g = face->glyph;
    int atlasWidth = 0;
    int atlasHeight = 0;

    // compute the dimensions of the atlas
    for (unsigned int i = 32; i < 128; i++) 
    {
        if(FT_Load_Char(face, i, FT_LOAD_RENDER)) 
        {
            CGK_REPORT("Loading character %c failed!", CGK_INVALID_FILE)
            continue;
        }

        atlasWidth += g->bitmap.width;
        atlasHeight = std::max(atlasHeight, g->bitmap.rows);
    }

    unsigned char* atlas = new unsigned char[atlasWidth*atlasHeight];
    
    for (unsigned int i = 0; i < atlasHeight*atlasWidth; i++)
    {
        atlas[i] = 0;
    }

    // create a font struct    
    CGKUIFont* font = new CGKUIFont;

    font->TexWidth = atlasWidth;
    font->TexHeight = atlasHeight;

    int marker = 0;

    // fill the atlas and the [font] with information about each character. 
    for (unsigned int i = 32; i < 128; i++) 
    {
        if(FT_Load_Char(face, i, FT_LOAD_RENDER)) 
        {
            continue;
        }
        
        int w = g->bitmap.width;
        int h = g->bitmap.rows;
        
        unsigned char* buffer = g->bitmap.buffer;
        
        // copy character to atlas
        for (unsigned int v = 0; v < h; v++)
        {
            for (unsigned int u = 0; u < w; u++)
            {
                int y = atlasHeight - 1 - v;
                int x = marker + u;
                atlas[y*atlasWidth + x] = buffer[v*w + u];
            }
        }

        // save character info
        font->BitmapWidths[i] = w;
        font->AtlasOffXs[i] = marker;
        font->Advances[i] = CGKVector2i(g->advance.x >> 6, g->advance.y >> 6);
        font->Bearings[i] = CGKVector2i(g->bitmap_left, g->bitmap_top);

        // increase marker
        marker += w;
    }

    // create and configure the texture atlas
    glGenTextures(1, &font->TexAtlas);
    glBindTexture(GL_TEXTURE_2D, font->TexAtlas);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glPixelStorei(GL_PACK_ALIGNMENT, 4); // for saving the image as bmp.

    glTexImage2D(
        GL_TEXTURE_2D, 0, GL_R8, atlasWidth, atlasHeight, 
        0, GL_RED, GL_UNSIGNED_BYTE, atlas
    );



    CGK_ASSERT(GL_NO_ERROR == glGetError())


    // clean up
    delete[] atlas;
    FT_Done_FreeType(library);

    return font;
}
//------------------------------------------------------------------------------
void CGKUIFontDestroy(CGKUIFontRef *font)
{
    glDeleteTextures(1, &(*font)->TexAtlas);
    CGK_DELETE(*font);
    *font = NULL;
}
//------------------------------------------------------------------------------
#define TO_STRING(x) #x 
static const char* vertexShader = 
    "#version 150\n"
    TO_STRING(
        uniform int ScreenWidth;
        uniform int ScreenHeight;
        uniform int AtlasWidth;
        uniform int AtlasHeight;

        in vec4 GlyphData; // x offset from the [Origin] and width of the glyph 

        out VertexData
        {
            float BitmapWidthNDC;  // Glyph width in NDC
            float BitmapHeightNDC; // Glyph height in NDC
            float TexStart;
            float TexEnd;        
        } 
        VertexOut;

        void main()
        {
            // compute position in NDC
            float posX = GlyphData.x/ScreenWidth;
            float posY = GlyphData.y/ScreenHeight;

            posX = 2.0f*posX - 1.0f;
            posY = 2.0f*posY - 1.0f;

            // compute texture coordinates
            VertexOut.TexStart = float(GlyphData.w)/AtlasWidth;
            VertexOut.TexEnd = float(GlyphData.w + GlyphData.z)/AtlasWidth;

            // compute width and height of the bmp in NDC
            VertexOut.BitmapWidthNDC = 2.0f*float(GlyphData.z)/ScreenWidth;
            VertexOut.BitmapHeightNDC = 2.0f*float(AtlasHeight)/ScreenHeight;

            gl_Position = vec4(posX, posY, 0.0f, 1.0f);
        }
    );
//------------------------------------------------------------------------------
static const char* geometryShader = 
    "#version 150\n"
    TO_STRING(
        in VertexData
        {
            float BitmapWidthNDC;  // Glyph width in NDC
            float BitmapHeightNDC; // Glyph height in NDC
            float TexStart;
            float TexEnd;        
        } 
        VertexIn[];

        out VertexData
        {
            vec2 TexCoord;        
        } 
        VertexOut;    

        layout (points) in;
        layout (triangle_strip, max_vertices = 6) out;

        void main()
        {
            vec4 pos = gl_in[0].gl_Position;
            float w = VertexIn[0].BitmapWidthNDC;
            float h = -VertexIn[0].BitmapHeightNDC;
            float ts = VertexIn[0].TexStart;
            float te = VertexIn[0].TexEnd;


            gl_Position = vec4(pos.x, pos.y, 0.0f, 1.0f);
            VertexOut.TexCoord = vec2(ts, 1.0f);
            EmitVertex(); 

            gl_Position = vec4(pos.x + w, pos.y, 0.0f, 1.0f);
            VertexOut.TexCoord = vec2(te, 1.0f);
            EmitVertex(); 

            gl_Position = vec4(pos.x + w, pos.y + h, 0.0f, 1.0f);
            VertexOut.TexCoord = vec2(te, 0.0f);
            EmitVertex();
            EndPrimitive();  

            gl_Position = vec4(pos.x, pos.y, 0.0f, 1.0f);
            VertexOut.TexCoord = vec2(ts, 1.0f);
            EmitVertex(); 

            gl_Position = vec4(pos.x, pos.y + h, 0.0f, 1.0f);
            VertexOut.TexCoord = vec2(ts, 0.0f);
            EmitVertex();

            gl_Position = vec4(pos.x + w, pos.y + h, 0.0f, 1.0f);
            VertexOut.TexCoord = vec2(te, 0.0f);
            EmitVertex(); 

            EndPrimitive();         
        }
    );
//------------------------------------------------------------------------------
static const char* fragmentShader = 
    "#version 150\n"
    TO_STRING(
        uniform sampler2D Atlas;
        uniform vec3 TextColor;

        in VertexData
        {
            vec2 TexCoord;        
        } 
        VertexIn; 
        
        out vec4 FragOut;

        void main()
        {
            float alpha = texture(Atlas, VertexIn.TexCoord).r;
            vec3 textColor = vec3(
                    alpha*TextColor.x, 
                    alpha*TextColor.y, 
                    alpha*TextColor.z
                );

            FragOut = vec4(alpha, alpha, alpha, alpha);
            //FragOut = vec4(1.0f, 0.0f, 0.0f, 1.0f);
        }
    );
//------------------------------------------------------------------------------
class CGKUILabel::RealLabel
{
public:
    RealLabel(
        const CGKVector2i& pos,
        const std::string& text, 
        CGKUIFontRef font, 
        const CGKVector3f& fontCol, 
        const CGKVector3f& bgCol
    );

    ~RealLabel();

    void Draw();

private:
    void setBuffer(const std::string& text);

    CGKVector2i position;
    std::string text;
    CGKUIFontRef font;

    GLuint buffer;
    GLuint vertexArray;
    GLuint program;
};
//------------------------------------------------------------------------------
CGKUILabel::RealLabel::RealLabel(
    const CGKVector2i& pos,
    const std::string& text, 
    CGKUIFontRef font, 
    const CGKVector3f& fontCol, 
    const CGKVector3f& bgCol
)
: position(pos), text(text), font(font)
{
    // program
    this->program = glCreateProgram();
    CGK_ASSERT(this->program);
    
    CGKOpenGLProgramAttachShaderFromSource(
        this->program, 
        GL_VERTEX_SHADER, 
        vertexShader
    );

    CGKOpenGLProgramAttachShaderFromSource(
        this->program, 
        GL_GEOMETRY_SHADER, 
        geometryShader
    );

    CGKOpenGLProgramAttachShaderFromSource(
        this->program, 
        GL_FRAGMENT_SHADER, 
        fragmentShader
    );

    glBindAttribLocation(this->program, 0, "GlyphData");
    glBindFragDataLocation(this->program, 0, "FragOut");
    CGKOpenGLProgramLink(this->program);
    glUseProgram(this->program);
    CGKOpenGLProgramUniform1i(this->program, "AtlasWidth", font->TexWidth);
    CGKOpenGLProgramUniform1i(this->program, "AtlasHeight", font->TexHeight);
    CGKOpenGLProgramUniform1i(this->program, "Atlas", 0);
    
    // geometry
    glGenBuffers(1, &this->buffer);
    glBindBuffer(GL_ARRAY_BUFFER, this->buffer);

    glBufferData(
        GL_ARRAY_BUFFER, 
        sizeof(int)*4*text.size(), 
        NULL, 
        GL_STATIC_DRAW
    );

    glGenVertexArrays(1, &this->vertexArray);
    glBindVertexArray(this->vertexArray);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, this->buffer);
    glVertexAttribPointer(0, 4, GL_INT, GL_FALSE, 0, 0);

    this->setBuffer(text);
}
//------------------------------------------------------------------------------
CGKUILabel::RealLabel::~RealLabel()
{
    glDeleteProgram(this->program);
}
//------------------------------------------------------------------------------
void CGKUILabel::RealLabel::setBuffer(const std::string& text)
{
    unsigned int length = text.size();
    GLsizei size = sizeof(int)*4*length;
    int* glyphData = new int[4*length];
    int posX = this->position.GetX();
    int posY = this->position.GetY();   

    for (unsigned int i = 0; i < length; i++)
    {
        char c = text.c_str()[i];

        // ignore non ascii chars ...
        if (c >= 128 || c < 0)
        {
            continue;
        }

        glyphData[4*i + 0] = posX + this->font->Bearings[(int)c].GetX();
        glyphData[4*i + 1] = posY + this->font->Bearings[(int)c].GetY();
        glyphData[4*i + 2] = this->font->BitmapWidths[(int)c];
        glyphData[4*i + 3] = this->font->AtlasOffXs[(int)c];
        std::cout << "[" << posX << " " << posY << "]" << std::endl;
        posX += this->font->Advances[(int)c].GetX();
        posY += this->font->Advances[(int)c].GetY();
    } 

    glBindBuffer(GL_ARRAY_BUFFER, this->buffer);

//    if (this->text.size() >= text.size())
//    {
//        glBufferSubData(GL_ARRAY_BUFFER, 0, size, glyphData);
//    }
//    else
    {
        glBufferData(GL_ARRAY_BUFFER, size, glyphData, GL_STATIC_DRAW);
    }
    
    CGK_ASSERT( GL_NO_ERROR == glGetError() )

    delete[] glyphData;
}
//------------------------------------------------------------------------------
void CGKUILabel::RealLabel::Draw()
{
    glUseProgram(this->program);
    
    CGKOpenGLProgramUniform1i(
        this->program, 
        "ScreenWidth", 
        CGKAppGetScreenWidth()
    );
    
    CGKOpenGLProgramUniform1i(
        this->program, 
        "ScreenHeight", 
        CGKAppGetScreenHeight()
    );
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->font->TexAtlas);
    glBindVertexArray(this->vertexArray);
    glDrawArrays(GL_POINTS, 0, this->text.size());
}
//------------------------------------------------------------------------------
CGKUILabel::CGKUILabel(
    const CGKVector2i& pos,
    const std::string& text, 
    CGKUIFontRef font, 
    const CGKVector3f& fontCol, 
    const CGKVector3f& bgCol
)
{
    this->label = new RealLabel(pos, text, font, fontCol, bgCol);
}
//------------------------------------------------------------------------------
CGKUILabel::~CGKUILabel()
{
    if (this->label) 
    {
        delete this->label;
    }    
}
//------------------------------------------------------------------------------
void CGKUILabel::Draw()
{
    if (this->label)
    {
        this->label->Draw();
    }
}
//------------------------------------------------------------------------------
