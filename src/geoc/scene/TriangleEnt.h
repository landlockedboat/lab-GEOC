#ifndef _GEOC_TRIANGLE_ENT_H
#define _GEOC_TRIANGLE_ENT_H

#include <geoc/geoc.h>
#include <geoc/geometry/Triangle.h>
#include <geoc/scene/Entity.h>
#include <geoc/math/BoundingBox.h>
#include <geoc/math/Vector.h>
#include <string>
#include <iosfwd>

namespace geoc {

class Graphics;
class Point;

/** \ingroup Scene */
//! A triangle entity.
/*!
 * This class inherits from the basic Triangle class and adds functionality to make
 * itself an Entity.
 */
class DECLDIR TriangleEnt : public Triangle, public Entity
{
    std::string label;
    
    template <class iter_t> friend TriangleEnt triangle_ent(iter_t);
    
public:
    
    Colour3 colour;
    
public:
    
    //! Default constructor.
    /*!
     * Points are set to the origin.
     * The bounding box has zero volume as is centerd at the origin.
     * Colour is set to black.
     * Empty label.
     */
    TriangleEnt() {}
    
    //! Builds a TriangleEnt from the given points.
    /*!
     * Colour is set to black.
     * Empty label.
     */
    TriangleEnt(const Vector3& p1, const Vector3& p2, const Vector3& p3) : Triangle(p1, p2, p3) {}
    
    //! Builds a TriangleEnt from a Triangle.
    /**
     * Colour is set to black.
     * Empty label.
     */
    TriangleEnt(const Triangle& t) : Triangle(t) {}
    
    //! Builds a TriangleEnt from a Triangle and a color.
    /**
     * Empty label.
     */
    TriangleEnt(const Triangle& t, const Colour3& c) : Triangle(t), colour(c) {}
    
    //! Tests two triangles for equality.
    /*!
     * \return True if both triangles share the same vertices and these are in the same order, false otherwise.
     */
    bool operator==(const TriangleEnt& t) const;
    
    //! Sets a colour uniformly for all of the triangle's vertices.
    void setColour(const Colour3& colour) { this->colour = colour; }
    
    //! Draws the triangle.
    /**
     * \sa Graphics
     */
    void draw(Graphics& gfx) const;
    
    //! Draws the triangle's label.
    /**
     * \sa Font
     */
    void drawLabel(const Font& font) const;
    
    //! Sets the triangle's label.
    void setLabel(const std::string& label);
    
    //! Gets the triangle's bounding box.
    /**
     * \sa BoundingBox
     */
    BoundingBox3 bb() const { return BoundingBox3(&(*this)[0], &(*this)[0] + 3); }
    
    //! Gets the header for triangles.
    static const char* header() { return "t"; }
    
    //! Gets the triangle's header.
    const char* getHeader() const { return TriangleEnt::header(); }
    
    //! Reads the triangle from the given input stream.
    static void read(std::istream& is, TriangleEnt& t);
    
    //! Writes the triangle to the given output stream.
    void write(std::ostream& os) const;
    
    //! Writes the triangle to the given file stream.
    void write(std::fstream& fs) const;
};


//! Builds a TriangleEnt from three points, provided an iterator.
/*!
 * The given iterator must be an iterator over Vector3.
 * The given iterator must point to a sequence of at least three points.
 */
template <class iter_t>
TriangleEnt triangle_ent(iter_t it)
{
    TriangleEnt t;
    (Triangle&)t = triangle(it);
    return t;
}


} //namespace geoc

#endif //_GEOC_TRIANGLE_ENT_H
