#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Projection_traits_xy_3.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Segment_2.h>

#include <fstream>


typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Projection_traits_xy_3<K>  Gt;
typedef CGAL::Delaunay_triangulation_2<Gt> Delaunay;

typedef K::Segment_3 Segment;
typedef K::Point_3   Point;

/**
 *  Version 1: Only compute Delone triangulation
 */

int main(int argc, char *argv[])
{
    if (argc!=2) {
        std::cerr << "Usage: " << argv[0] << " <input data file>" 
                  << std::endl;
        return 1;
    }
    const char* filename (argv[1]);

    std::ifstream in(filename);
    char buf[500];
    in.getline(buf, 500); // kill the first line in the file
    std::istream_iterator<Point> begin(in);
    std::istream_iterator<Point> end;
    
    Delaunay dt;
    dt.insert(begin, end);
    std::cerr << "Triangulated " << dt.number_of_vertices() << " vertices" << std::endl;

    std::cout << "s\n";
    for(Delaunay::Finite_edges_iterator eit = dt.finite_edges_begin(); eit!=dt.finite_edges_end(); ++eit) {
        const Segment seg(dt.segment(eit));
        const Point p0(seg.min()), p1(seg.max());
        if (p0 != Point(0,0,0))
            std::cout << p0 << "\n" << p1 << std::endl;
    } 

   return 0;
}
