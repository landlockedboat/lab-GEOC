
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
Face* ext;

void DCEL::tieTriangle(HalfEdge* eAB, HalfEdge* eBC, HalfEdge* eCA, Face* f)
{
    eAB->setNext(eBC);
    eBC->setNext(eCA);
    eCA->setNext(eAB);
    
    eAB->setFace(f);
    eBC->setFace(f);
    eCA->setFace(f);
    
    f->setBoundary(eAB);
}

void DCEL::tieEdges(HalfEdge* eAB, Vertex* a, HalfEdge* eBA, Vertex* b)
{
    eAB->setOrigin(a);
    eBA->setOrigin(b);
    
    a->setLeaving(eAB);
    b->setLeaving(eBA);
    
    eAB->setTwin(eBA);
    eBA->setTwin(eAB);
}

void DCEL::makeTriangle(
    Vertex* a,
    Vertex* b,
    Vertex* c,
    HalfEdge* eAB,
    HalfEdge* eBC,
    HalfEdge* eCA,
    HalfEdge* eBA,
    HalfEdge* eAC,
    HalfEdge* eCB,
    Face* f
    )
{
    tieEdges(eAB, a, eBA, b);
    tieEdges(eBC, b, eCB, c);
    tieEdges(eCA, c, eAC, a);
    
    tieTriangle(eAB, eBC, eCA, f);

}

/*oid makeCounterClockwise(
    Vertex* a,
    Vertex* b,
    Vertex* c,
    HalfEdge* eAB,
    HalfEdge* eBC,
    HalfEdge* eCA
    )
{
    Vector3 A = a->getVertex();
    Vector3 B = b->getVertex();
    Vector3 C = c->getVertex();

    num clockwise = Math::orientation2D(A, B, C);
    if(!clockwise)
    {
        return;
    }

    eAB = eAB->getTwin();
    eBC = eBC->getTwin();
    eCA = eCA->getTwin();

    a = eAB->getOrigin();
    b = eBC->getOrigin();
    c = eCA->getOrigin();
}*/

void DCEL::insertPointInsideTriangle(
    Vertex* w,
    Face* f1,
    Face* f2,
    Face* f3)
{
    //THE POINT IS INSIDE
    //GET STUFF
    
    HalfEdge *eAB = f1->getBoundary();
    HalfEdge *eBC = eAB->getNext();
    HalfEdge *eCA = eBC->getNext();

    Vertex *a = eAB->getOrigin();
    Vertex *b = eBC->getOrigin();
    Vertex *c = eCA->getOrigin();

    //CREATE FACES
    faces.push_back(f2);
    faces.push_back(f3);

    //CREATE EDGES
    HalfEdge *eAW = new HalfEdge();
    HalfEdge *eBW = new HalfEdge();
    HalfEdge *eCW = new HalfEdge();
    HalfEdge *eWA = new HalfEdge();
    HalfEdge *eWB = new HalfEdge();
    HalfEdge *eWC = new HalfEdge();
    
    edges.push_back(eAW);
    edges.push_back(eBW);
    edges.push_back(eCW);
    edges.push_back(eWA);
    edges.push_back(eWB);
    edges.push_back(eWC);

    //TIE EDGES
    eAB->setOrigin(a);
    eBC->setOrigin(b);
    eCA->setOrigin(c);

    tieEdges(eAW, a, eWA, w);
    tieEdges(eBW, b, eWB, w);
    tieEdges(eCW, c, eWC, w);

    tieTriangle(eAB, eBW, eWA, f1);
    tieTriangle(eBC, eCW, eWB, f2);
    tieTriangle(eWC, eCA, eAW, f3);
}

void DCEL::insertPointInTriangleEdge(
    Vertex* w,
    Face* f1,
    Face* f2,
    Face* f3,
    Face* f4)
{
    //THE POINT IS IN AN EDGE
    HalfEdge *eBC = f1->getBoundary();
    bool intersect = false;
    Vector3 p = w->getVertex();
    for(int k = 0; k < 3 and not intersect; ++k)
    {
        Vector3 A = eBC->getOrigin()->getVertex();
        Vector3 B = eBC->getNext()->getOrigin()->getVertex();
        if(onSegment(A,B,p)) intersect = true;
        else eBC = eBC->getNext();
    }

    f2 = eBC->getTwin()->getFace(); //this exists because of enclosing triangle

    HalfEdge *eCA = eBC->getNext();
    HalfEdge *eAB = eCA->getNext();

    HalfEdge *eCB = eBC->getTwin();
    HalfEdge *eBD = eCB->getNext();
    HalfEdge *eDC = eBD->getNext();

    Vertex *a = eAB->getOrigin();
    Vertex *b = eBC->getOrigin();
    Vertex *c = eCA->getOrigin();
    Vertex *d = eDC->getOrigin();

    //CREATE FACES
    f3 = new Face();
    f4 = new Face();
    faces.push_back(f3);
    faces.push_back(f4);

    //CREATE EDGES
    HalfEdge *eAW = new HalfEdge();
    HalfEdge *eCW = new HalfEdge();
    HalfEdge *eDW = new HalfEdge();
    HalfEdge *eWA = new HalfEdge();
    HalfEdge *eWC = new HalfEdge();
    HalfEdge *eWD = new HalfEdge();
    edges.push_back(eAW);
    edges.push_back(eCW);
    edges.push_back(eDW);
    edges.push_back(eWA);
    edges.push_back(eWC);
    edges.push_back(eWD);

    //TIE VERTEX
    a->setLeaving(eAB);
    b->setLeaving(eBC);
    c->setLeaving(eCA);
    d->setLeaving(eDC);
    w->setLeaving(eWA);

    //TIE FACES
    f1->setBoundary(eAB);
    f2->setBoundary(eBD);
    f3->setBoundary(eCA);
    f4->setBoundary(eDC);

    //TIE EDGES
    eAB->setOrigin(a);
    eBC->setOrigin(b);
    eWA->setOrigin(w);

    eCB->setOrigin(w);
    eBD->setOrigin(b);
    eDW->setOrigin(d);

    eCA->setOrigin(c);
    eAW->setOrigin(a);
    eWC->setOrigin(w);

    eDC->setOrigin(d);
    eCW->setOrigin(c);
    eWD->setOrigin(w);

    eAB->setNext(eBC);
    eBC->setNext(eWA);
    eWA->setNext(eAB);
    eAB->setFace(f1);
    eBC->setFace(f1);
    eWA->setFace(f1);

    eCB->setNext(eBD);
    eBD->setNext(eDW);
    eDW->setNext(eCB);
    eCB->setFace(f2);
    eBD->setFace(f2);
    eDW->setFace(f2);

    eCA->setNext(eAW);
    eAW->setNext(eWC);
    eWC->setNext(eCA);
    eCA->setFace(f3);
    eAW->setFace(f3);
    eWC->setFace(f3);

    eDC->setNext(eCW);
    eCW->setNext(eWD);
    eWD->setNext(eDC);
    eDC->setFace(f4);
    eCW->setFace(f4);
    eWD->setFace(f4);

    eAW->setTwin(eWA);
    eCW->setTwin(eWC);
    eDW->setTwin(eWD);
    eWA->setTwin(eAW);
    eWC->setTwin(eCW);
    eWD->setTwin(eDW);
}

void DCEL::doDelaunayFlip(HalfEdge* eBA)
{
        HalfEdge *eAW = eBA->getNext();
        HalfEdge *eWB = eAW->getNext();
        
        HalfEdge *eAB = eBA->getTwin();
        HalfEdge *eBV = eAB->getNext();
        HalfEdge *eVA = eBV->getNext();
        
        Vertex *a = eAW->getOrigin();
        Vertex *b = eBV->getOrigin();
        Vertex *v = eVA->getOrigin();
        Vertex *w = eWB->getOrigin();
        
        Face* face1 = eBA->getFace();
        Face* face2 = eAB->getFace();
        
        tieTriangle(eBV, eBA, eWB, face1);
        tieTriangle(eVA, eAW, eAB, face2);
        
        tieEdges(eAB, w, eBA, v);        
}


void DCEL::makeDelaunay(
Vertex* w, 
Face* face1,
Face* face2,
Face* face3,
Face* face4)
{
    stack<Face*> stack;
    //push adjacent faces
    if(face1 != NULL) stack.push(face1);
    if(face2 != NULL) stack.push(face2);
    if(face3 != NULL) stack.push(face3);
    if(face4 != NULL) stack.push(face4);

    while(not stack.empty())
    {
        Face* current = stack.top();
        stack.pop();

        //GET EVERYTHING
        HalfEdge *eWB = current->getBoundary();
        //find actual edWB
        Vector3 point = eWB->getOrigin()->getVertex();
        Vector3 p = w->getVertex();
        
        while(not compareVectors(p,point))
        {
            eWB = eWB->getNext();
            point = eWB->getOrigin()->getVertex();
        }
        
        HalfEdge *eBA = eWB->getNext();
        HalfEdge *eAW = eBA->getNext();
        
        HalfEdge *eAB = eBA->getTwin();
        HalfEdge *eBV = eAB->getNext();
        HalfEdge *eVA = eBV->getNext();
        
        Vertex *a = eAW->getOrigin();
        Vertex *b = eBV->getOrigin();
        Vertex *v = eVA->getOrigin();
        
        Face *f2 = eAB->getFace();
        
        if(f2 == ext)
        {
            return;
        }
        
        Vector3 A = a->getVertex();
        Vector3 B = b->getVertex();
        Vector3 V = v->getVertex();
        Vector3 W = w->getVertex();
        
        num test = Math::orientation2D(W,A,B);

        if(test < 0)
        {
            return;
        }
        
        num isInterior = Math::orientation25D(W,A,B,V);
        
        if(not isInterior)
        {
            continue;            
        }
        
        doDelaunayFlip(eBA);
        
        stack.push(current);
        stack.push(f2);
    }
}

void DCEL::insertPoint(bool delaunay, Vector3& p, Face* f)
{
    //FIND WHERE THE POINT IS LOCATED
    //THIS CAN BE IMPROVED
    bool found = false;
    int j = faces.size()-1;
    Face *f1;
    num test;
    while (not found) {
        f1 = faces[j];
        Vector3 a = f1->getBoundary()->getOrigin()->getVertex();
        Vector3 b = f1->getBoundary()->getNext()->getOrigin()->getVertex();
        Vector3 c = f1->getBoundary()->getNext()->getNext()->getOrigin()->getVertex();
        test = triangleTest(a,b,c,p);
        if(test != 2) found = true;
        else --j;
    }
    //At this point we should have found the face

    Vertex *w = new Vertex(p,NULL);
    vertices.push_back(w);

    //INCIDENT FACES
    Face *face1, *face2, *face3, *face4;
    face1 = face2 = face3 = face4 = NULL;
    if (test == 0) {
        face1 = f1;
        face2 = new Face();
        face3 = new Face();
        insertPointInsideTriangle(w, face1, face2, face3);
    }
    /*else if (test == 1) {
        face1 = f1;
        insertPointInTriangleEdge(w, face1, face2, face3, face4);
    }*/

    //DELAUNAY ALGORITHM
    /*if(delaunay)
    {
        makeDelaunay(w, face1, face2, face3, face4);
    }*/
}



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
    l[0] = minX - (distY / tan(60 * 180/M_PI)) - 1000;
    l[1] = minY -1000;
    l[2] = 0;
    n[0] = maxX + (distY / tan(60 * 180/M_PI)) + 1000;
    n[1] = minY - 1000;
    n[2] = 0;
    m[0] = (maxX + minX) / 2;
    m[1] = maxY + (distX/2) * tan(60 * 180/M_PI) + 1000;
    m[2] = 0;

    Face *f = constructEnclosingTriangle(m,n,l);

    for (int i = 0; i < ps.size(); ++i) {
        Vector3 p = ps[i];
        insertPoint(delaunay, p, f);
    }

    //TESTING
    for (int j = 0; j < faces.size(); ++j) {
        Face *f = faces[j];
        Vector3 a = f->getBoundary()->getOrigin()->getVertex();
        Vector3 b = f->getBoundary()->getNext()->getOrigin()->getVertex();
        Vector3 c = f->getBoundary()->getNext()->getNext()->getOrigin()->getVertex();
        if(f != ext and Math::orientation2D(a,b,c) > 0) cout << "ERROR" << endl;
    }
    cout << "OK" << endl;
}

bool DCEL::compareVectors(Vector3& a, Vector3& b)
{
    if(a[X] == b[X] and a[Y] == b[Y] and a[Z] == b[Z]) return true;
    else return false;
}

Face* DCEL::constructEnclosingTriangle(Vector3& A, Vector3& B, Vector3& C)
{
    //CREATE DCEL STUFF
    //VERTICES
    Vertex *a = new Vertex(A, NULL);
    Vertex *b = new Vertex(B, NULL);
    Vertex *c = new Vertex(C, NULL);
    vertices.push_back(a);
    vertices.push_back(b);
    vertices.push_back(c);

    //FACES FWD DECLARATION
    Face *exterior = new Face(NULL);
    Face *f = new Face(NULL);
    faces.push_back(exterior);
    faces.push_back(f);
    ext = exterior;

    //HALFEDGES
    HalfEdge *eAB = new HalfEdge();
    HalfEdge *eBC = new HalfEdge();
    HalfEdge *eCA = new HalfEdge();
    HalfEdge *eBA = new HalfEdge();
    HalfEdge *eAC = new HalfEdge();
    HalfEdge *eCB = new HalfEdge();
    edges.push_back(eAB);
    edges.push_back(eBC);
    edges.push_back(eCA);
    edges.push_back(eBA);
    edges.push_back(eAC);
    edges.push_back(eCB);
    
    makeTriangle(a, b, c, eAB, eBC, eCA, eBA, eAC, eCB, f);

    tieTriangle(eBA, eAC, eCB, exterior);

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

