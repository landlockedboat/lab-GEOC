#include "Font.h"
#include <geoc/math/Vector.h>
#include <geoc/gl.h>
#include "alphabet.h"

using namespace geoc;
using namespace std;

// Renders the given text.
// pos corresponds to the bottom left corner of the rendered text.
// size represents the size (width and height) of each letter in object space.
void renderText(const char* text, Vector3 pos, int font_size, num size);

void enter2D();
void leave2D();

void flip_vertically(unsigned char* img_data, int width, int height, int bpp);


struct Font::Font_impl
{
    GLuint      tex;           // Texture id.
    int         letter_stride; // Stride between letters in the texture.
    num         size;          // Font size.
    render_mode mode;          // Current render mode.
};


Font::Font(num size)
{
    impl = new Font_impl();
    
    int w = alphabet_width;
    int h = alphabet_height;
    
    unsigned char* img_data = new unsigned char[w*h*alphabet_bpp];
    memcpy(img_data, alphabet_chunk1, sizeof(alphabet_chunk1) - 1);
    int off = sizeof(alphabet_chunk1) - 1;
    memcpy(img_data + off, alphabet_chunk2, sizeof(alphabet_chunk2) - 1);
    
    flip_vertically(img_data, w, h, alphabet_bpp);
    
    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, img_data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    delete img_data;
    
    impl->tex = tex;
    impl->letter_stride = 8;
    impl->size = size;
}


Font::~Font()
{
    glDeleteTextures(1, &impl->tex);
    delete impl;
}


void Font::startRender(render_mode mode) const
{
    glPushAttrib(GL_LIGHTING_BIT);
    glPushAttrib(GL_POLYGON_BIT);
    glPushAttrib(GL_DEPTH_BUFFER_BIT);
    
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glPolygonMode(GL_FRONT, GL_FILL);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, impl->tex);
    
    if (mode == render_2d)
    {
        impl->mode = render_2d;
        enter2D();
    }
    else impl->mode = render_3d;
}


void Font::endRender() const
{
    if (impl->mode == render_2d)
    {
        leave2D();
    }
    
    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);
    
    glPopAttrib();
    glPopAttrib();
    glPopAttrib();
}


void Font::setSize(float size)
{
    impl->size = size;
}


void Font::draw2D(const Vector2& pos, const std::string& text, draw_style style) const
{
    enter2D();
    draw3D(pos, text, style);
    leave2D();
}


void Font::draw2D(int x, int y, const std::string& text, draw_style style) const
{
    draw2D(Vector2(x, y), text, style);
}


void Font::draw3D(const Vector3& pos, const std::string& text, draw_style style) const
{
    Vector3 pos_;
    
    //Compute the text origin.
    switch (style)
    {
    case centered:
    {
        //Compute average line size and number of lines.
        int sum = 0;
        int line_size = 0;
        int num_lines = 1;
        foreach (char c, text)
        {
            if (c == '\n')
            {
                sum += line_size;
                line_size = 0;
                num_lines++;
            }
            else line_size += 1;
        }
        sum += line_size;
        int avg_size = sum / num_lines;
        
        pos_ = pos - up3 * impl->size * num_lines - right3 * avg_size / 2 * impl->size;
        break;
    }
        
    case top_left:
        pos_ = pos - up3 * impl->size;
        break;
        
    default: break;
    }
    
    renderText(text.c_str(), pos_, impl->letter_stride, impl->size);
}


void Font::draw3D(int x, int y, int z, const std::string& text, draw_style style) const
{
    draw3D(Vector3(x, y, z), text, style);
}


void renderText(const char* text, Vector3 pos, int letter_stride, num size)
{
    num starting_x = pos[X];
    
    float stride = (float)letter_stride / (float)alphabet_width;
    foreach (char c, text)
    {
        if (c == '\n') //eol
        {
            pos[Y] -= size;
            pos[X] = starting_x;
        }
        else
        {
            if (c < 0x20 || c >= 127) c = '?';
            
            float x;
            if (c == 0x20) x = 0;
            else
            {
                x = (c - 0x20) * letter_stride;
                x /= (float)alphabet_width;
            }
            
            // Render quad for this character.
            glTexCoord2f(x, 0.0);
            glVertex3f(pos[X], pos[Y], pos[Z]);
            
            glTexCoord2f(x + stride, 0.0);
            glVertex3f(pos[X] + size, pos[Y], pos[Z]);
            
            glTexCoord2f(x + stride, 1.0);
            glVertex3f(pos[X] + size, pos[Y] + size, pos[Z]);
            
            glTexCoord2f(x, 1.0);
            glVertex3f(pos[X], pos[Y] + size, pos[Z]);
            
            if (c == 0x20) pos[X] += size/2; //make spaces thinner
            else pos[X] += size;
        }
    }
}


void enter2D()
{
    int vPort[4];
    
    glGetIntegerv(GL_VIEWPORT, vPort);
    
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, vPort[2], 0, vPort[3], -1, 1);
    
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
}


void leave2D()
{
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}


void flip_vertically(unsigned char* img_data, int width, int height, int bpp)
{
    int img_size = width * height * bpp;
    int line_size = width * bpp;
    
    unsigned char* top = img_data;
    unsigned char* bot = &img_data[img_size - line_size];
    unsigned char* tmp = new unsigned char[line_size];
    
    while (top < bot)
    {
        memcpy(tmp, top, line_size);
        memcpy(top, bot, line_size);
        memcpy(bot, tmp, line_size);
        
        top += line_size;
        bot -= line_size;
    }
    
    delete tmp;
}
