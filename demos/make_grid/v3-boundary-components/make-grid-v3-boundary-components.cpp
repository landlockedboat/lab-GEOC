#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Projection_traits_xy_3.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Alpha_shape_2.h> 

#include <fstream>
#include <vector>
#include <map> //
#include <set> //

#include <boost/foreach.hpp>
#define foreach BOOST_FOREACH 

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Projection_traits_xy_3<K>  Gt;

typedef CGAL::Alpha_shape_vertex_base_2<Gt> Vb; 
typedef CGAL::Alpha_shape_face_base_2<Gt>  Fb; 
typedef CGAL::Triangulation_data_structure_2<Vb,Fb> Tds; 
typedef CGAL::Delaunay_triangulation_2<Gt,Tds> Delaunay; 

typedef CGAL::Alpha_shape_2<Delaunay>  Alpha_shape_2; 
typedef Alpha_shape_2::Alpha_shape_edges_iterator Alpha_shape_edges_iterator; 

typedef K::Point_3   Point;
typedef K::Segment_3  Segment; 

typedef std::vector<Segment> SegmentContainer; // 
typedef std::set<Point> PointContainer; //
typedef std::map<Point, PointContainer> NeighborMap; //
typedef std::vector<Point> Boundary; //
typedef std::vector<Boundary> BoundaryContainer; //

/**
 *  Version 3: compute 
 *    - Delone triangulation
 *    - Alpha shapes
 *    - Boundaries
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

void remove_vertex(NeighborMap& nm, const Point& p)
{
    foreach(const Point& q, nm[p]) {
        nm[q].erase(p);
    }
    nm.erase(p);
}

void make_boundaries(const SegmentContainer& segments, BoundaryContainer& bc)
{
    // we use heavily here that boundaries don't intersect for the magic alpha

    NeighborMap nm;
    foreach(const Segment& s, segments) {
        nm[s[0]].insert(s[1]);
        nm[s[1]].insert(s[0]);
    }
    // Invariant: nm[i].size()>0 for all i

    while (!nm.empty()) {
        const NeighborMap::iterator mit = nm.begin();
        Point v(mit->first); 
        const Point start(v);
        Boundary b;
        b.push_back(v);
        v = *(mit->second.begin());
        nm[v].erase(start); // first time round, erase only the back-pointing edge to start, so that the node "start" can still be found
        while(v != start) {
            b.push_back(v);
            const Point p(v);
            v = *(nm[v].begin());
            remove_vertex(nm, p);
        }
        nm.erase(start);
        bc.push_back(b);
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
    
    Alpha_shape_2 A(pts.begin(), pts.end(),
                    magic_alpha,
                    Alpha_shape_2::GENERAL);
    SegmentContainer segments;
    alpha_edges( A, std::back_inserter(segments));

    std::cout << "Found " << segments.size() << " boundary segments, distributed into" << std::endl;
//     foreach(const Segment& s, segments) {
//         std::cout << s[0] << "\n" << s[1] << std::endl;
//     }

    BoundaryContainer bc;
    make_boundaries(segments, bc);
    std::cout << bc.size() << " boundary components of size ";
    foreach(const Boundary& b, bc) {
        std::cout << b.size() << " ";
    }
    std::cout << std::endl;

    return 0;
}
