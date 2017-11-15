#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Projection_traits_xy_3.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Alpha_shape_2.h> //!

#include <fstream>
#include <vector>

#include <boost/foreach.hpp> //
#define foreach BOOST_FOREACH //

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Projection_traits_xy_3<K>  Gt;

typedef CGAL::Alpha_shape_vertex_base_2<Gt> Vb; //
typedef CGAL::Alpha_shape_face_base_2<Gt>  Fb; //
typedef CGAL::Triangulation_data_structure_2<Vb,Fb> Tds; //
typedef CGAL::Delaunay_triangulation_2<Gt,Tds> Delaunay; //

typedef CGAL::Alpha_shape_2<Delaunay>  Alpha_shape_2; //
typedef Alpha_shape_2::Alpha_shape_edges_iterator Alpha_shape_edges_iterator; //

typedef K::Point_3   Point;
typedef K::Segment_3  Segment; //

/**
 *  Version 2: compute 
 *    - Delone triangulation
 *    - Alpha shapes
 */


template <class OutputIterator>
void alpha_edges(const Alpha_shape_2& A, OutputIterator out)
{
  for(Alpha_shape_edges_iterator it =  A.alpha_shape_edges_begin();
      it != A.alpha_shape_edges_end();
      ++it){
    *out++ = A.segment(*it);
  }
}

int main(int argc, char *argv[])
{
    if (argc!=2) {
        std::cerr << "Usage: " << argv[0] << " <input data file>" 
                  << std::endl;
        return 1;
    }
    const char* filename (argv[1]);
    const K::FT magic_alpha(2.5e5);

    std::ifstream in(filename);
    char buf[500];
    in.getline(buf, 500); // kill the first line in the file
    std::istream_iterator<Point> pts_begin(in);
    std::istream_iterator<Point> pts_end;
    std::vector<Point> pts(pts_begin, pts_end);
    
    Alpha_shape_2 A(pts.begin(), pts.end(), magic_alpha, Alpha_shape_2::GENERAL);
    std::vector<Segment> segments;
    alpha_edges( A, std::back_inserter(segments));
    
    std::cerr << "Alpha Shape computed" << std::endl;
    std::cerr << segments.size() << " alpha shape edges" << std::endl;

    std::cout << "s\n";
    foreach(const Segment& s, segments)
        std::cout << s.min() << "\n" << s.max() << std::endl;

    return 0;
}
