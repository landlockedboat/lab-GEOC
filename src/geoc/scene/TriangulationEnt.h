#ifndef _GEOC_TRIANGULATION_ENT_H
#define _GEOC_TRIANGULATION_ENT_H

#include <geoc/geoc.h>
#include <geoc/scene/Entity.h>
#include <geoc/geometry/TriangulationBase.h>
#include <geoc/scene/LineSegmentEnt.h>
#include <geoc/scene/TriangleEnt.h>
#include <geoc/math/Vector.h>
#include <geoc/math/BoundingBox.h>
#include <vector>

namespace geoc {

/** \ingroup Scene */
enum TRIANGULATION_DRAW_MODE
{
    TRIANGULATION_2D_RAW,
    TRIANGULATION_2D_PRUNED,
    TRIANGULATION_3D_PRUNED_AND_GRAY,
    TRIANGULATION_3D_PRUNED,
    TRIANGULATION_3D_PRUNED_AND_SMOOTH
};

/** \ingroup Scene */
//! Represents a triangulation of a set of points in the plane.
/*!
 * TriangulationEnt does not actually perform any triangulation. That task is left for subclasses to complete.
 * \sa Triangulation
 */
class DECLDIR TriangulationEnt : public Entity
{
    TriangulationBase* triang;
    
    static const int nDrawModes = 5;
    
    std::vector<LineSegmentEnt>	segments;	  //Segments vector, ex4.
    std::vector<TriangleEnt>	triangles;	  //Triangles vector, ex4 / ex5.
    std::vector<TriangleEnt>	triangles_pruned; //Pruned triangulation, ex5.
    
    BoundingBox3     m_bb;
    std::vector<int> geometry;
    Graphics*        gfx;
    
    template <class triang_t> friend TriangulationEnt* make_triangulation_ent();
    
public:
    
    TRIANGULATION_DRAW_MODE	drawMode;
    
    //! Creates a new triangulation.
    TriangulationEnt(TriangulationBase* tb) : triang(tb), geometry(nDrawModes, -1), drawMode(TRIANGULATION_2D_RAW) {}
    
    //! Destroys a triangulation.
    virtual ~TriangulationEnt();
    
    void prepare(Graphics* gfx, bool enable_3d);
    
    //! Draws the triangulation.
    void draw(Graphics& gfx) const;
    
    //! Draws the triangulation's labels.
    void drawLabel(const Font& font) const;
    
    //! Gets the bounding box surrounding this triangulation.
    BoundingBox3 bb() const { return m_bb; }
    
    //! Gets the header for triangulations.
    static const char* header() { return "triangulation"; }
    
    //! Gets the header for triangulations.
    const char* getHeader() const { return TriangulationEnt::header(); }
    
    //! Reads a triangulation from an input stream.
    static void read(std::istream& is, TriangulationEnt& t);
};


// This is what I'd use in reality, but this forces ex4-5 application to
// be recompiled when the student modifies Triangulation.h.
//! Creates a new triangulation.
template <class triang_t>
TriangulationEnt* make_triangulation_ent()
{
    TriangulationEnt* t = new TriangulationEnt(new triang_t);
    return t;
}


// Ugly, but avoids ex4-5 recompilation.
DECLDIR TriangulationEnt* make_student_triangulation();

} //namespace geoc

#endif //_GEOC_TRIANGULATION_ENT_H
