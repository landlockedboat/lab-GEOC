#ifndef _GEOC_POINT_H
#define _GEOC_POINT_H

#include <geoc/geoc.h>
#include <geoc/scene/Entity.h>
#include <geoc/math/BoundingBox.h>
#include <geoc/math/Vector.h>
#include <string>
#include <iosfwd>

namespace geoc {

class Graphics;

/** \ingroup Scene */
//! A point entity.
class DECLDIR Point : public Entity
{
    Vector3			pos;
    BoundingBox3	box;
    std::string		label;
    
public:
    
    Colour3	colour;
    
public:
    
    //! Default constructor.
    /*!
     * Position is set to the origin.
     * The bounding box has zero volume and is centered at the origin.
     * Colour is set to black.
     * Empty label.
     */
    Point() {}
    
    //! Builds a point from a point vector and a colour.
    Point(const Vector3& position, const Colour3& colour = zero3);
    
    //! Builds a point given its coordinates and colour components.
    Point(num x, num y, num z = 0, num r = 0, num g = 0, num b = 0);
    
    //! Gets one of the point's coordinates.
    const num& operator[](int coord) const;
    
    //! Tests two points for equality.
    /*!
     * \return True if both points share the same position, false otherwise.
     * Colour is not taken into account.
     */
    bool operator==(const Point& p) const { return pos == p.pos; }
    
    //! Gets the point's position.
    const Vector3& position() const { return pos; }
    
    //! Draws the point.
    /**
     * \sa Graphics
     */
    void draw(Graphics& gfx) const;
    
    //! Draws the point's label.
    /**
     * \sa Font
     */
    void drawLabel(const Font& font) const;
    
    //! Sets the point's label.
    void setLabel(const std::string& label);
    
    //! Gets the point's bounding box.
    /**
     * \sa BoundingBox
     */
    BoundingBox3 bb() const { return box; }
    
    //! Gets the header for points.
    static const char* header() { return "p"; }
    
    //! Gets the point's header.
    const char* getHeader() const { return Point::header(); }
    
    //! Reads the point from the given input stream.
    static void read(std::istream& is, Point& p);
    
    //! Writes the point to the given output stream.
    void write(std::ostream& os) const;
    
    //! Writes the point to the given file stream.
    void write(std::fstream& fs) const;
};


} //namespace geoc

#endif //_GEOC_POINT_H
