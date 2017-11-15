#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Projection_traits_xy_3.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Alpha_shape_2.h> 
#include <CGAL/Polygon_2.h> //
#include <CGAL/Boolean_set_operations_2.h> //
#include <CGAL/Bbox_3.h> //
#include <CGAL/Kernel/solve.h>

#include <fstream>
#include <vector>
#include <map> 
#include <set> 
#include <string>

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
typedef Delaunay::Face_handle Face_handle;

typedef K::Point_3   Point;
typedef K::Point_2   Point_2;
typedef K::Segment_3  Segment; 

typedef std::vector<Segment> SegmentContainer; 
typedef std::set<Point> PointContainer; 
typedef std::map<Point, PointContainer> NeighborMap; 
typedef std::vector<Point_2> Point_2Container;

typedef CGAL::Polygon_2<K> Polygon;
typedef Polygon Boundary; 
typedef std::vector<Boundary> BoundaryContainer; 
typedef std::vector<Polygon> PolygonContainer;
typedef CGAL::Polygon_with_holes_2<K> Polygon_with_holes;
typedef std::vector<Polygon_with_holes> PwhContainer;
typedef CGAL::Bbox_2 Bbox;


/**
 *  Version 4: compute 
 *    - Delone triangulation
 *    - Alpha shapes
 *    - Boundaries
 *    - Grid
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

    // make a directed graph out of the segments, by doubling the underlying undirected graph
    NeighborMap nm;
    foreach(const Segment& s, segments) {
        nm[s[0]].insert(s[1]);
        nm[s[1]].insert(s[0]);
    }

    // begin at a vertex "start", and iteratively eat outgoing edges until you get back to it
    while (!nm.empty()) {
        const NeighborMap::iterator mit = nm.begin();
        Point v(mit->first); 
        const Point start(v);
        Boundary b;
        b.push_back(Point_2(v[0], v[1]));
        v = *(mit->second.begin());
        nm[v].erase(start); // first time round, erase only the back-pointing edge to start, so that the node "start" can still be found
        while(v != start) {
            b.push_back(Point_2(v[0], v[1]));
            const Point p(v);
            v = *(nm[v].begin());
            remove_vertex(nm, p);
        }
        nm.erase(start);

        // take care of orientation of each cycle, for later use in intersecting with a line
        if (!b.is_counterclockwise_oriented())
            b.reverse_orientation();
        bc.push_back(b);
    }
}

void barycentric_coordinates(K::FT a1, K::FT a2, K::FT b1, K::FT b2, K::FT c1, K::FT c2, K::FT x, K::FT y, K::FT& lam1, K::FT& lam2, K::FT& lam3) 
{
    CGAL::solve(a1, a2, 1.0, b1, b2, 1.0, c1, c2, 1.0, x, y, 1.0, lam1, lam2, lam3);
}

template<class DT>
Point interpolate_point(K::FT x, K::FT y, const DT& dt, K::FT height_distortion)
{
    Face_handle fh = dt.locate(Point(x,y,0));
    K::FT lam1(0), lam2(0), lam3(0);
    const Point 
        p1(fh->vertex(0)->point()),
        p2(fh->vertex(1)->point()),
        p3(fh->vertex(2)->point());
    barycentric_coordinates(p1[0], p1[1], p2[0], p2[1], p3[0], p3[1], x, y, lam1, lam2, lam3);
    return Point(lam1*p1[0] + lam2*p2[0] + lam3*p3[0],
                 lam1*p1[1] + lam2*p2[1] + lam3*p3[1],
                 height_distortion*(lam1*p1[2] + lam2*p2[2] + lam3*p3[2]));
}

template<class OutputIterator, class DT>
void make_gridpoints(K::FT local_ymin,  K::FT local_ymax, 
                     K::FT global_ymin, 
                     K::FT x, K::FT deltay, 
                     bool offset_points, bool hexagonal,
                     const DT& dt, K::FT height_distortion, OutputIterator out)
{
    const int 
        k1 = ceil ( (local_ymin  - global_ymin) / deltay);
    // this comes from global_ymin + k1 . deltay >= local_ymin
    int k2 = floor( (local_ymax - global_ymin) / deltay);
    // this comes from global_ymin + k2 . deltay <= local_ymax
    
    *out++ = interpolate_point(x, local_ymin, dt, height_distortion);
    K::FT y = global_ymin + k1*deltay;
    
    if (offset_points) {
        --k2;
        y += .5 * deltay;
    }
    
    for (int k=k1; k<=k2; ++k) {
        if (!hexagonal || k%3 != (int)offset_points)
            *out++ = interpolate_point(x, y, dt, height_distortion);
        y += deltay;
    }
    
    *out++ = interpolate_point(x, local_ymax, dt, height_distortion);                    
}

template<class OutputIterator, class DT>
void make_grid_on_line(K::FT x, const Bbox& bb, const BoundaryContainer& bc, 
                       K::FT deltay, bool offset_points, bool hexagonal,
                       const DT& dt, K::FT height_distortion, OutputIterator out)
{
    Polygon seg;
    seg.push_back(Point_2(x, bb.ymin()));
    seg.push_back(Point_2(x+0.1, bb.ymin()));
    seg.push_back(Point_2(x+0.1, bb.ymax()));
    seg.push_back(Point_2(x, bb.ymax()));
    foreach (const Polygon& island, bc) {
        PwhContainer intersectc;
        CGAL::intersection(seg, island, std::back_inserter(intersectc));
        if (!intersectc.empty()) {
            foreach (const Polygon_with_holes& pwh, intersectc) {
                const Bbox local_bb (pwh.outer_boundary().bbox());
                make_gridpoints(local_bb.ymin(), local_bb.ymax(), bb.ymin(), 
                                x, deltay, offset_points, hexagonal, dt, height_distortion, out);
            }
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc<4 || argc>7) {
        std::cerr << "Usage: " << argv[0] 
                  << " [-v for verbose] <input data file> "
            "<t|s|h for triangular, square or hexagonal grid> "
            "<number of gridpoints in each direction> "
            "[height distortion = 1] [magic alpha = 2.5e5]" 
                  << std::endl;
        return 1;
    }
    int argstart(1), real_argc(argc);
    const bool verbose(argc>=5 && !strcmp(argv[1], "-v"));
    if (verbose) {
        ++argstart;
        --real_argc;
    }

    const char* filename (argv[argstart]);
    const K::FT height_distortion ((real_argc>=5) ? atof(argv[argstart+3]) : 1.0);
    const K::FT magic_alpha((real_argc>=6) ? atof(argv[argstart+4]) : 2.5e5);
    const char tesselation_type(*argv[argstart+1]);
    const int n_gridpoints (atoi(argv[argstart+2]));

    std::ifstream in(filename);
    char buf[500];
    in.getline(buf, 500); // kill the first line in the file
    std::istream_iterator<Point> pts_begin(in);
    std::istream_iterator<Point> pts_end;
    std::vector<Point> pts(pts_begin, pts_end);
    
    // make alpha shape
    Alpha_shape_2 A(pts.begin(), pts.end(), magic_alpha, Alpha_shape_2::GENERAL);
    SegmentContainer sc;
    alpha_edges( A, std::back_inserter(sc));
    if (verbose)
        std::cout << "Found " << sc.size() << " boundary segments, distributed into" << std::endl;

    // distribute boundary edges into connected components
    BoundaryContainer bc;
    make_boundaries(sc, bc);
    if (verbose) {
        std::cout << bc.size() << " boundary components of size ";
        foreach(const Boundary& b, bc) {
            std::cout << b.size() << " ";
        }
        std::cout << std::endl;
    }

    // calculate the bounding box of the boundary
    const Segment s0 = *(sc.begin());
    const Point p0 = s0.min(), p1 = s0.max();
    Bbox bb (p0[0],p0[1],p1[0],p1[1]);
    foreach(const Segment& s, sc) {
        const Point p2 = s.min(), p3 = s.max();
        bb = bb + Bbox(p2[0],p2[1],p3[0],p3[1]);
    }

    // calculate grid points
    K::FT deltax = (bb.xmax() - bb.xmin()) / K::FT(n_gridpoints),
        deltay = (bb.ymax() - bb.ymin()) / K::FT(n_gridpoints);
    deltax = std::min(deltax, deltay);
    deltay = deltax;
    if (tesselation_type=='h') {
        deltay *= K::FT(1.15470053838); // 2/sqrt(3)
    }
    if (verbose) 
        std::cout << "deltax: " << deltax << std::endl
                  << "deltay: " << deltay << std::endl;
    std::vector<Point> pc;
    bool odd = false;
    for (K::FT x = bb.xmin(); x<=bb.xmax(); x+=deltax, odd = !odd) {
        make_grid_on_line(x, bb, bc, deltay, 
                          (tesselation_type=='t' || tesselation_type=='h') && odd, 
                          tesselation_type=='h', A, height_distortion, std::back_inserter(pc));
    }

    std::cerr << "Sampled " << pc.size() << " points." << std::endl;

    std::cout << "triangulation\n";
    foreach(const Point& p, pc)
        std::cout << p << std::endl;
    return 0;
}
