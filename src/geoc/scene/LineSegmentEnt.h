#ifndef _GEOC_LINE_SEGMENT_ENT_H
#define _GEOC_LINE_SEGMENT_ENT_H

#include <geoc/geoc.h>
#include <geoc/geometry/LineSegment.h>
#include <geoc/scene/Entity.h>
#include <geoc/math/BoundingBox.h>
#include <geoc/math/Vector.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

namespace geoc {

class Graphics;

/** \ingroup Scene */
//! A line segment entity.
class DECLDIR LineSegmentEnt : public LineSegment, public Entity
{
    BoundingBox3	box;
    std::string		label;
    
    template <class iter_t> friend LineSegmentEnt linesegment_ent(iter_t);
    
public:
    
    Colour3			colour;
    
public:
    
    //! Default constructor.
    /*!
     * Points are set to the origin.
     * The bounding box has zero volume and is centered at the origin.
     * Colour is set to black.
     * Empty label.
     */
    LineSegmentEnt() {}
    
    //! Builds a LineSegmentEnt from two points and a colour.
    LineSegmentEnt(const Vector3& p1, const Vector3& p2, const Colour3& colour = Colour3(0,0,0));
    
    //! Builds a LineSegmentEnt from a LineSegment.
    LineSegmentEnt(const LineSegment& s);
    
    //! Draws the line segment.
    /**
     * \sa Graphics
     */
    void draw(Graphics& gfx) const;
    
    //! Draws the line segment's label.
    /**
     * \sa Font
     */
    void drawLabel(const Font& font) const;
    
    //! Sets the line segment's label.
    void setLabel(const std::string& label);
    
    //! Gets the line segment's bounding box.
    /**
     * \sa BoundingBox
     */
    BoundingBox3 bb() const { return box; }
    
    //! Gets the header for line segments.
    static const char* header() { return "s"; }
    
    //! Gets the line segment's header.
    const char* getHeader() const { return LineSegmentEnt::header(); }
    
    //! Reads the line segment from the given input stream.
    static void read(std::istream& is, LineSegmentEnt& s);
    
    //! Writes the line segment to the given output stream.
    void write(std::ostream& os) const;
    
    //! Writes the line segment to the given file stream.
    void write(std::fstream& fs) const;
};


//! Builds a LineSegmentEnt from two points, provided an iterator.
/*!
 * The given iterator must be an iterator over Vector3.
 * The given iterator must point to a sequence of at least two points.
 */
template <class iter_t>
LineSegmentEnt linesegment_ent(iter_t it)
{
    LineSegmentEnt s;
    (LineSegment&)s = linesegment(it);
    s.box.add(s[0]);
    s.box.add(s[1]);
    return s;
}


} //namespace geoc


#endif //_GEOC_LINE_SEGMENT_ENT_H
