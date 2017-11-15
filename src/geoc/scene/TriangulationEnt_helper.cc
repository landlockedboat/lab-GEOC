#include <geoc/scene/TriangulationEnt.h>
#include <geoc/geometry/Triangulation.h>


using namespace geoc;


TriangulationEnt* geoc::make_student_triangulation()
{
    return new TriangulationEnt(new Triangulation);
}
