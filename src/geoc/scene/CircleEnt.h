#ifndef _GEOC_CIRCLE_ENT_H
#define _GEOC_CIRCLE_ENT_H

#include <geoc/geoc.h>
#include <geoc/geometry/Circle.h>
#include <geoc/scene/Entity.h>
#include <geoc/math/BoundingBox.h>
#include <string>
#include <iosfwd>

namespace geoc {

class Graphics;
class Point;

/** \ingroup Scene */
//! A circle entity.
class DECLDIR CircleEnt : public Circle, public Entity
{
    BoundingBox3	box;
    std::string		label;
    
    template <class iter_t> friend CircleEnt circle_ent(iter_t);
    
public:
    
    Colour3	colour;
    
public:
    
    //! Default constructor.
    /*!
     * Points are set to the origin.
     * The bounding box has zero volume and is centered at the origin.
     * Colour is set to black.
     * Empty label.
     */
    CircleEnt() {}
    
    //! Builds a CircleEnt from three points and a colour.
    CircleEnt(const Vector3& v1, const Vector3& v2, const Vector3& v3, const Colour3& colour = zero3);
    
    //! Builds a CircleEnt from a Circle.
    CircleEnt(const Circle& c);
    
    //! Draws the circle.
    /**
     * \sa Graphics
     */
    void draw(Graphics& gfx) const;
    
    //! Draws the circle's label.
    /**
     * \sa Font
     */
    void drawLabel(const Font& font) const;
    
    //! Sets the cirle's label.
    void setLabel(const std::string& label);
    
    //! Gets the bounding box surrounding the circle.
    /**
     * \sa BoundingBox
     */
    BoundingBox3 bb() const { return box; }
    
    //! Gets the header for circles.
    static const char* header() { return "c"; }
    
    //! Gets the circle's header.
    const char* getHeader() const { return CircleEnt::header(); }
    
    //! Reads the circle from the given input stream.
    static void read(std::istream& is, CircleEnt& c);
    
    //! Writes the circle to the given output stream.
    void write(std::ostream& os) const;
    
    //! Writes the circle to the given file stream.
    void write(std::fstream& fs) const;
};


//! Builds a CircleEnt from three points, provided an iterator.
/*!
 * The given iterator must be an iterator over Vector3.
 * The given iterator must point to a sequence of at least three points.
*/
template <class iter_t>
CircleEnt circle_ent(iter_t it)
{
    CircleEnt c;
    (Circle&)c = circle(it);
    c.box.add(c[0]);
    c.box.add(c[1]);
    c.box.add(c[2]);
    return c;
}


} //namespace geoc

#endif //_GEOC_CIRCLE_ENT_H
