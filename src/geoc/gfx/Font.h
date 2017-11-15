#ifndef _GEOC_FONT_H
#define _GEOC_FONT_H

#include <geoc/geoc.h>
#include <geoc/math/Vector_fwd_decl.h>
#include <string>

class QGLWidget;
class QFont;

namespace geoc {

/** \ingroup Gfx */
//! A font for drawing 2D and 3D text.
class Font
{
    struct Font_impl;
    Font_impl* impl;
    
public:
    
    enum draw_style
    {
        centered,   /*!< Text is centered around the given point. */
        top_left,   /*!< The given point corresponds to the top left corner of the rendered text. */
        bottom_left /*!< The given point corresponds to the bottom left corner of the rendered text. */
    };
    
    enum render_mode
    {
        render_2d, /*!< Enable 2D rendering. */
        render_3d  /*!< Enable 3D rendering. */
    };
    
public:
    
    //! Builds a Font.
    /*!
     * pre: OpenGL context exists.
     */
    Font(num size = 16.0);
    
    //! Default destructor.
    ~Font();
    
    //! Prepares the font for text rendering.
    /**
     * \param mode The mode to render text in.
     * \sa render_mode
     */
    void startRender(render_mode mode = render_3d) const;
    
    //! Flushes out render commands.
    void endRender() const;
    
    //! Sets the font's size.
    void setSize(float size);
    
    //! Renders text directly on the viewport.
    /**
     * \param pos The position where the text should be rendered.
     * \param text The actual text to render.
     * \param style The style to render the given text with.
     * \sa draw_style
     */
    void draw2D(const Vector2& pos, const std::string& text, draw_style style = centered) const;
    
    //! Renders text directly on the viewport.
    /**
     * \param x The x coordinate of the position where the text should be rendered.
     * \param y The y coordinate of the position where the text should be rendered.
     * \param text The actual text to render.
     * \param style The style to render the given text with.
     * \sa draw_style
     */
    void draw2D(int x, int y, const std::string& text, draw_style style = centered) const;
    
    //! Renders text on a quad in 3D space.
    /**
     * \param pos The position where the text should be rendered.
     * \param text The actual text to render.
     * \param style The style to render the given text with.
     * \sa draw_style
     */
    void draw3D(const Vector3& pos, const std::string& text, draw_style style = centered) const;
    
    //! Renders text on a quad in 3D space.
    /**
     * \param x The x coordinate of the position where the text should be rendered.
     * \param y The y coordinate of the position where the text should be rendered.
     * \param z The z coordinate of the position where the text should be rendered.
     * \param text The actual text to render.
     * \param style The style to render the given text with.
     * \sa draw_style
     */
    void draw3D(int x, int y, int z, const std::string& text, draw_style style = centered) const;
};


} //geoc namespace end


#endif //_GEOC_FONT_H
