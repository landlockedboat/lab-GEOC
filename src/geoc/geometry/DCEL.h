#ifndef _DCEL_H
#define _DCEL_H

#include <geoc/geoc.h>
#include <geoc/math/Vector.h>
#include <geoc/math/Math.h>
#include <math.h>
#include <vector>
#include <stack>

namespace geoc {

    class LineSegmentEnt;
    class TriangleEnt;

    /**** FORWARD DECLARATION ****/
    class Vertex;
    class HalfEdge;
    class Face;

    class Vertex {
	private:
	    Vector3 v;
	    HalfEdge *leaving;
	public:
	    Vertex();
	    Vertex(const Vector3& point, HalfEdge *l);
	    ~Vertex();
	    Vector3 getVertex();
	    HalfEdge* getLeaving();
	    void setLeaving(HalfEdge* l);
    };

    class HalfEdge {
	private:
	   Vertex *origin;
	   Face *face;
	   HalfEdge *twin;
	   HalfEdge *next;
	public:
	   HalfEdge();
	   HalfEdge(Vertex *o, Face *f, HalfEdge *t, HalfEdge *n);
	   ~HalfEdge();
	   Vertex* getOrigin();
	   Face* getFace();
	   HalfEdge* getTwin();
	   HalfEdge* getNext();
	   void setOrigin(Vertex *o);
	   void setFace(Face *f);
	   void setTwin(HalfEdge *t);
	   void setNext(HalfEdge *n);
    };

    class Face {
	private:
	    HalfEdge *boundary;
	public:
	    Face();
	    Face(HalfEdge *b);
	    ~Face();
	    HalfEdge* getBoundary();
	    void setBoundary(HalfEdge *b);
    };

    class DCEL {
	private:
	    std::vector<Vertex*> vertices;
	    std::vector<HalfEdge*> edges;
	    std::vector<Face*> faces;
	    bool compareVectors(Vector3& a, Vector3& b);
	    Face* constructEnclosingTriangle(Vector3& a, Vector3& b, Vector3& c);
	    num triangleTest(Vector3& p, Vector3& q, Vector3& r, Vector3& w);
	    bool onSegment(const Vector3& p, const Vector3& q, const Vector3& r);
	public:
	    DCEL(bool delaunay, const std::vector<Vector3>& ps); //construct from set of points
	    ~DCEL();
	    std::vector<Vertex*> getVertices();
	    std::vector<HalfEdge*> getEdges();
	    std::vector<Face*> getFaces();
    };

}


#endif //_DCEL_H
