#ifndef _GEOC_ENTITY_H
#define _GEOC_ENTITY_H

#include <geoc/geoc.h>
#include <iosfwd>

namespace geoc {

class Graphics;
class Font;

template <int N> class BoundingBox;
typedef BoundingBox<3> BoundingBox3;

/** \ingroup Scene */
//! Base class for drawable entities in the scene.
/*!
 * An entity must provide:
 * · A method with which to draw itself.
 * · A method to retrieve its bounding box.
 * 
 * Optionally, an entity may provide:
 * · A method with which to write itself to a file.
 * · A method to draw a label over itself.
 */
class DECLDIR Entity
{
    friend std::ostream& operator<<(std::ostream& os, const Entity& e);
    friend std::fstream& operator<<(std::fstream& f, const Entity& e);
    
public:
    
    virtual ~Entity() {}
    
    //! Draws the entity.
    virtual void draw(Graphics& gfx) const = 0;
    
    //! Draws the entity's label.
    virtual void drawLabel(const Font&) const {}
    
    //! Gets the the entity's bounding box.
    virtual BoundingBox3 bb() const = 0;
    
    //! Gets the entity's header.
    /*!
     * The header is the string preceeding this particular entity's data in a file, such
     * as "p" for points, "s" for segments etc.
     */
    virtual const char* getHeader() const { return ""; }
    
    //! Writes the entity to the given output stream.
    virtual void write(std::ostream&) const {}
    
    //! Writes the entity to the given file stream.
    virtual void write(std::fstream&) const {}
};


inline std::ostream& operator<<(std::ostream& os, const Entity& e)
{
    e.write(os);
    return os;
}


inline std::fstream& operator<<(std::fstream& f, const Entity& e)
{
    e.write(f);
    return f;
}

} //namespace geoc

#endif //_GEOC_ENTITY_H
