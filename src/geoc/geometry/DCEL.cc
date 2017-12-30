
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

    num maxX, minX, maxY, minY;
    maxX = minX = ps[0][X];
    maxY = minY = ps[0][Y];

    for(int i = 1; i < ps.size(); ++i)
    {
       if(maxX < ps[i][X]) maxX = ps[i][X];
       if(minX > ps[i][X]) minX = ps[i][X];
       if(maxY < ps[i][Y]) maxY = ps[i][Y];
       if(minY > ps[i][Y]) minY = ps[i][Y];  
    }

    //POINTS OF ENCLOSING TRIANGLE

    Vector3 m,n,l;
    
    num distX = maxX - minX;
    num distY = maxY - minY;
    m[0] = minX - (distY / tan(60 * 180/M_PI)) - 1000;
    m[1] = minY -1000;
    m[2] = 0;
    n[0] = maxX + (distY / tan(60 * 180/M_PI)) + 1000;
    n[1] = minY - 1000;
    n[2] = 0;
    l[0] = (maxX + minX) / 2;
    l[1] = maxY + (distX/2) * tan(60 * 180/M_PI) + 1000;
    l[2] = 0;

    Face *f = constructEnclosingTriangle(m,n,l);

    /*Vector3 a = f->getBoundary()->getOrigin()->getVertex();
    Vector3 b = f->getBoundary()->getNext()->getOrigin()->getVertex();
    Vector3 c = f->getBoundary()->getNext()->getNext()->getOrigin()->getVertex();
    num test;
    for (int i = 0; i < ps.size(); ++i) {
        Vector3 w = ps[i];
        test = triangleTest(a,b,c,w);
        if(test == 2) std::cout << "error" << std::endl;
    }
    std::cout << "end" << std::endl;*/

    for (int i = 0; i < ps.size(); ++i) {
        //FIND WHERE THE POINT IS LOCATED
        //THIS CAN BE IMPROVED
        Vector3 p = ps[i];
        bool found = false;
        int j = 0;
        Face *f1;
        num test;
        while (not found) {
            f1 = faces[j];
            Vector3 a = f1->getBoundary()->getOrigin()->getVertex();
            Vector3 b = f1->getBoundary()->getNext()->getOrigin()->getVertex();
            Vector3 c = f1->getBoundary()->getNext()->getNext()->getOrigin()->getVertex();
            test = triangleTest(a,b,c,p);
            if(test != 2) found = true;
            else ++j;
        }
        //At this point we should have found the face

        Vertex *w = new Vertex(p,NULL);
        vertices.push_back(w);

        
        if (test == 0) {
            //THE POINT IS INSIDE
            //RENAME STUFF
            HalfEdge *eAB = f1->getBoundary();
            HalfEdge *eBA = eAB->getTwin();
            HalfEdge *eBC = eAB->getNext();
            HalfEdge *eCB = eBC->getTwin();
            HalfEdge *eCA = eBC->getNext();
            HalfEdge *eAC = eCA->getTwin();

            Vertex *a = eAB->getOrigin();
            Vertex *b = eBC->getOrigin();
            Vertex *c = eCA->getOrigin();

            //CREATE FACES
            Face *f2 = new Face(NULL);
            Face *f3 = new Face(NULL);
            faces.push_back(f2);
            faces.push_back(f3);

            //CREATE EDGES
            HalfEdge *eAW = new HalfEdge(a,f3,NULL,NULL);
            HalfEdge *eWA = new HalfEdge(w,f1,eAW,NULL);
            HalfEdge *eBW = new HalfEdge(b,f1,NULL,NULL);
            HalfEdge *eWB = new HalfEdge(w,f2,eBW,NULL);
            HalfEdge *eCW = new HalfEdge(c,f2,NULL,NULL);
            HalfEdge *eWC = new HalfEdge(w,f3,eCW,NULL);
            edges.push_back(eAW);
            edges.push_back(eWA);
            edges.push_back(eBW);
            edges.push_back(eWB);
            edges.push_back(eCW);
            edges.push_back(eWC);

            //TIE EDGES
            eAW->setTwin(eWA);
            eBW->setTwin(eWB);
            eCW->setTwin(eWC);

            eAB->setNext(eBW);
            eBW->setNext(eWA);
            eWA->setNext(eAB);

            eBC->setNext(eCW);
            eCW->setNext(eWB);
            eWB->setNext(eBC);

            eCA->setNext(eAW);
            eAW->setNext(eWC);
            eWC->setNext(eCA);

            eBC->setFace(f2);
            eCA->setFace(f3);

            //TIE FACES
            f2->setBoundary(eBC);
            f3->setBoundary(eCA);

            //TIE VERTEX
            w->setLeaving(eWA);
        }
        else if (test == 1) {
            //THE POINT IS IN AN EDGE

            HalfEdge *eCA = f1->getBoundary();
            bool intersect = false;
            for (int k = 0; k < 3 and not intersect; ++k) {
                Vector3 A = eCA->getOrigin()->getVertex();
                Vector3 B = eCA->getNext()->getOrigin()->getVertex();
                if (onSegment(A,B,p)) intersect = true;
                else eCA = eCA->getNext();
            }

            //GET EXISTING FACES
            Face *F1 = eCA->getFace();
            Face *f2 = eCA->getTwin()->getFace();

            //CREATE FACES
            Face *f3 = new Face(NULL);
            Face *f4 = new Face(NULL);
            faces.push_back(f3);
            faces.push_back(f4);

            //GET EXISTING EDGES
            HalfEdge *eAB = eCA->getNext();
            HalfEdge *eBC = eAB->getNext();
            HalfEdge *eAC = eCA->getTwin();
            HalfEdge *eCD = eAC->getNext();
            HalfEdge *eDA = eCD->getNext();
            

            //GET VERTICES
            Vertex *a = eAB->getOrigin();
            Vertex *b = eBC->getOrigin();
            Vertex *c = eCD->getOrigin();
            Vertex *d = eDA->getOrigin();

            //CREATE HALFEDGES
            HalfEdge *eBW = new HalfEdge(b,F1,NULL,NULL);
            HalfEdge *eWB = new HalfEdge(w,f3,eBW,NULL);
            HalfEdge *eCW = new HalfEdge(c,f3,NULL,NULL);
            HalfEdge *eWC = new HalfEdge(w,f4,eCW,NULL);
            HalfEdge *eDW = new HalfEdge(d,f4,NULL,NULL);
            HalfEdge *eWD = new HalfEdge(w,f2,eDW,NULL);
            edges.push_back(eBW);
            edges.push_back(eWB);
            edges.push_back(eCW);
            edges.push_back(eWC);
            edges.push_back(eDW);
            edges.push_back(eWD);

            //TIE EDGES

            eBW->setTwin(eWB);
            eCW->setTwin(eWC);
            eDW->setTwin(eWD);

            eAB->setNext(eBW);
            eBW->setNext(eCA);
            eCA->setNext(eAB);

            eBC->setNext(eCW);
            eCW->setNext(eWB);
            eWB->setNext(eBC);

            eCD->setNext(eDW);
            eDW->setNext(eWC);
            eWC->setNext(eCD);

            eDA->setNext(eAC);
            eAC->setNext(eWD);
            eWD->setNext(eDA);

            //some inecessary stuff here but just in case
            eAB->setFace(F1);
            eBW->setFace(F1);
            eCA->setFace(F1);

            eBC->setFace(f3);
            eCW->setFace(f3);
            eWB->setFace(f3);

            eCD->setFace(f4);
            eDW->setFace(f4);
            eWC->setFace(f4);

            eDA->setFace(f2);
            eAC->setFace(f2);
            eWD->setFace(f2);

            //TIE FACES
            F1->setBoundary(eAB);
            f2->setBoundary(eDA);
            f3->setBoundary(eBC);
            f4->setBoundary(eCD);

            //TIE VERTEX
            w->setLeaving(eCA);
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

