
#include <geoc/geometry/DCEL.h>

using namespace geoc;
using namespace std;

/******** VERTEX ************/

Vertex::Vertex()
{
    leaving = NULL;
}

Vertex::Vertex(const Vector3& point, HalfEdge *l) 
{
   v = point;
   leaving = l;
}

Vertex::~Vertex()
{

}

Vector3 Vertex::getVertex()
{
    return v;
}

HalfEdge* Vertex::getLeaving()
{
    return leaving;
}

void Vertex::setLeaving(HalfEdge *l)
{
   leaving = l;
}

/******** HalfEdge ************/

HalfEdge::HalfEdge()
{
   origin = NULL;
   face = NULL;
   twin = NULL;
   next = NULL;
}

HalfEdge::HalfEdge(Vertex *o, Face *f, HalfEdge *t, HalfEdge *n)
{
   origin = o;
   face = f;
   twin = t;
   next = n;
}

HalfEdge::~HalfEdge()
{

}

Vertex* HalfEdge::getOrigin()
{
    return origin;
}

Face* HalfEdge::getFace()
{
    return face;
}

HalfEdge* HalfEdge::getTwin()
{
    return twin;
}

HalfEdge* HalfEdge::getNext()
{
    return next;
}

void HalfEdge::setOrigin(Vertex *o)
{
    origin = o;
}

void HalfEdge::setFace(Face *f)
{
    face = f;
}

void HalfEdge::setTwin(HalfEdge *t)
{
    twin = t;
}

void HalfEdge::setNext(HalfEdge *n)
{
    next = n;
}

/********* FACE ***********/

Face::Face()
{
    boundary = NULL;
}

Face::Face(HalfEdge *b)
{
    boundary = b;
}

Face::~Face()
{

}

HalfEdge* Face::getBoundary()
{
    return boundary;
}

void Face::setBoundary(HalfEdge *b)
{
    boundary = b;
}

/******** DCEL *************/

DCEL::DCEL(bool delaunay, const vector<Vector3>& ps)
{
    //FIND ENCLOSING TRIANGLE

    num maxX, minX, avgX, maxY, minY, avgY;
    maxX = minX = avgX = ps[0][X];
    maxY = minY = avgY = ps[0][Y];

    for(int i = 1; i < ps.size(); ++i)
    {
       avgX += ps[i][X];
       avgY += ps[i][Y];

       if(maxX < ps[i][X]) maxX = ps[i][X];
       if(minX > ps[i][X]) minX = ps[i][X];
       if(maxY < ps[i][Y]) maxY = ps[i][Y];
       if(minY > ps[i][Y]) minY = ps[i][Y];  
    }

    //POINTS OF ENCLOSING TRIANGLE
    //TODO: fix this

    Vector3 m,n,l;
    m[0] = minX - abs((maxY-minY));;
    m[1] = minY - 1000;
    m[2] = 0;
    n[0] = minX + abs((maxX - minX)/2);
    n[1] = maxY + abs(maxX - minX);
    n[2] = 0;
    l[0] = maxX + abs((maxY-minY));
    l[1] = minY - 1000;
    l[2] = 0;

    Face *f = constructEnclosingTriangle(m,n,l);

    /////////// INSERT POINTS ////////////////
    //orientation test -> = 0 (on line), > 0 (left), < 0 (right)

    for(int i; i < ps.size(); ++i) {
        Vector3 w = ps[i];
        bool found = false;
        while(not found) {
            HalfEdge *e = f->getBoundary();
            int j = 0;
            //Walk through the triangulation to find the given point
            //All triangles except the one where the triangle is located have some segment which is to the right of the point 
            //(the point is to the left of the segment)
            bool objective = false;
            while(not objective and j < 3) {
                Vector3 p = e->getOrigin()->getVertex();
                Vector3 q = e->getNext()->getOrigin()->getVertex();
                if(Math::orientation2D(p,q,w) > 0) {
                    f = e->getTwin()->getFace();
                    objective = true;
                }
                e = e->getNext();
                ++j;
            }
            //
            if(not objective) {
                found = true;
            }
            //At this point, the point is in face f
            Face *location = f;

            //Push the new vertex
            Vertex *v = new Vertex(w,NULL);
            vertices.push_back(v);

            //Rename important stuff for readability
            HalfEdge *ab = f->getBoundary();
            HalfEdge *bc = f->getBoundary()->getNext();
            HalfEdge *ca = f->getBoundary()->getNext()->getNext();
            Vertex *a = ab->getOrigin();
            Vertex *b = bc->getOrigin();
            Vertex *c = ca->getOrigin();

            //Is the point in an edge?
            Vector3 A = a->getVertex();
            Vector3 B = b->getVertex();
            Vector3 C = c->getVertex();

            num test1 = Math::orientation2D(A,B,w);
            num test2 = Math::orientation2D(B,C,w);
            num test3 = Math::orientation2D(C,A,w);

            if((test1 == 0 and onSegment(A,B,w)) or (test2 == 0 and onSegment(B,C,w)) or (test3 == 0 and onSegment(C,A,w))) {
                //ON EDGE
                //CREATE EVERYTHING
                HalfEdge *ba = ab->getTwin();
                HalfEdge *ac = ba->getNext();
                HalfEdge *cb = ac->getNext();
            }
            else {
                //INSIDE
            }

        }
    }
}

Face* DCEL::constructEnclosingTriangle(Vector3& a, Vector3& b, Vector3& c)
{
    //CREATE DCEL STUFF
    //VERTICES
    Vertex *vA = new Vertex(a, NULL);
    Vertex *vB = new Vertex(b, NULL);
    Vertex *vC = new Vertex(c, NULL);
    vertices.push_back(vA);
    vertices.push_back(vB);
    vertices.push_back(vC);

    //FACES FWD DECLARATION
    Face *exterior = new Face(NULL);
    Face *f = new Face(NULL);
    faces.push_back(exterior);
    faces.push_back(f);

    //HALFEDGES
    HalfEdge *eAB = new HalfEdge(vA, f, NULL, NULL);
    HalfEdge *eBA = new HalfEdge(vB, exterior, NULL, NULL);
    HalfEdge *eBC = new HalfEdge(vB, f, NULL, NULL);
    HalfEdge *eCB = new HalfEdge(vC, exterior, NULL, NULL);
    HalfEdge *eCA = new HalfEdge(vC, f, NULL, NULL);
    HalfEdge *eAC = new HalfEdge(vA, exterior, NULL, NULL);
    edges.push_back(eAB);
    edges.push_back(eBA);
    edges.push_back(eBC);
    edges.push_back(eCB);
    edges.push_back(eCA);
    edges.push_back(eAC);

    //TIE VERTICES
    vA->setLeaving(eAB);
    vB->setLeaving(eBC);
    vC->setLeaving(eCA);

    //TIE FACES
    exterior->setBoundary(eBA);
    f->setBoundary(eAB);

    //TIE HalfEdgeS
    eAB->setTwin(eBA);
    eAB->setNext(eBC);
    eBA->setTwin(eAB);
    eBA->setNext(eAC);
    eBC->setTwin(eCB);
    eBC->setNext(eCA);
    eCB->setTwin(eBC);
    eCB->setNext(eBA);
    eCA->setTwin(eAC);
    eCA->setNext(eAB);
    eAC->setTwin(eCA);
    eAC->setNext(eCB);

    return f;
}

//Recieves a triangle pqr and a test point w
//Returns 0 if w lies in the interior of pqr, 1 if it lies on an edge, 2 if it lies in the exterior and 
//3 if it is a vertex of the triangle

num DCEL::triangleTest(Vector3& p, Vector3& q, Vector3& r, Vector3& w)
{
    if(p == w or q == w or r == w) return 3;

    //orientation test -> = 0 (on line), > 0 (left), < 0 (right)
    num test1 = geoc::Math::orientation2D(p,q,w);
    if(test1 == 0 and onSegment(p,q,w)) return 1;
    num test2 = geoc::Math::orientation2D(q,r,w);
    if(test2 == 0 and onSegment(q,r,w)) return 1;
    num test3 = geoc::Math::orientation2D(r,p,w);
    if(test3 == 0 and onSegment(r,p,w)) return 1;

    if((test1 > 0 and test2 > 0 and test3 > 0) or (test1 < 0 and test2 <0 and test3 <0)) {
        return 0;
    }
    else return 2;
}

bool DCEL::onSegment(const Vector3& p, const Vector3& q, const Vector3& r)
{
    if(r[X] <= max(p[X],q[X]) and r[X] >= min(p[X],q[X]) and
        r[Y] <= max(p[Y],q[Y]) and r[Y] >= min(p[Y],q[Y])) return true;
    else return false;
}

DCEL::~DCEL()
{

}

std::vector<Vertex*> DCEL::getVertices()
{
    return vertices;
}

std::vector<HalfEdge*> DCEL::getEdges()
{
    return edges;
}

std::vector<Face*> DCEL::getFaces()
{
    return faces;
}

