#include <geoc/geoc.h>
#include <geoc/GeocException.h>
#include <geoc/gfx/Graphics.h>
#include <geoc/scene/Point.h>
#include <geoc/scene/LineSegmentEnt.h>
#include <geoc/scene/TriangleEnt.h>
#include <geoc/scene/CircleEnt.h>
#include <geoc/math/Math.h>
#include <geoc/math/Vector.h>
#include <geoc/gl.h>
#include <geoc/glu.h>
#include <stdlib.h>
#include <list>
#include <vector>
#include <algorithm>


using namespace geoc;
using std::list;
using std::vector;
using std::search;


static const num g_thickness_step = 0.5;


template <class T>
struct element
{
    const T* item;
    
    element(const T* t)
    {
        item = t;
    }
};


struct polygon
{
    const vector<Vector3>* points;
    Colour3 colour;
    
    polygon(const vector<Vector3>* ps, const Colour3& c)
    {
        points = ps;
        colour = c;
    }
    
    ~polygon()
    {
        delete points;
    }
};


void render_(const Point& p);
void render_(const LineSegmentEnt& s);
void render_(const TriangleEnt& t);
void render_(const CircleEnt& c, GLUquadricObj* quadric);
void render_(const polygon& p);


struct geoc::Graphics_impl
{
    int  width;
    int  height;
    int  x;
    int  y;
    num  thickness;
    bool antialiasing;
    bool depthTest;
    bool culling;
    bool drawing;
    bool lighting;
    bool wireframe;
    GLUquadricObj* quadric;
    list<GLuint>   displayLists;
    
    vector<Point>          point_pool;
    vector<LineSegmentEnt> segment_pool;
    vector<TriangleEnt>    triangle_pool;
    vector<CircleEnt>      circle_pool;
    vector<polygon>        polygon_pool;
    
    vector< element<Point> >          points;
    vector< element<LineSegmentEnt> > segments;
    vector< element<TriangleEnt> >    triangles;
    vector< element<CircleEnt> >      circles;
    vector< element<polygon> >        polygons;
};


Graphics::Graphics()
{
    impl = new Graphics_impl;
    impl->thickness    = 1.0;
    impl->antialiasing = false;
    impl->depthTest    = false;
    impl->culling      = false;
    impl->drawing      = false;
    impl->lighting     = false;
    impl->wireframe    = false;
    impl->quadric      = gluNewQuadric();
    
    if (impl->quadric == 0) throw GEOC_EXCEPTION("Unable to retrieve a quadric");
    
    gluQuadricDrawStyle(impl->quadric, GLU_LINE);
    gluQuadricNormals(impl->quadric, GLU_NONE);
    gluQuadricTexture(impl->quadric, GL_FALSE);
}


Graphics::~Graphics()
{
    if (impl->quadric) gluDeleteQuadric(impl->quadric);
    
    //Free display lists.
    foreach (GLuint id, impl->displayLists)
    {
        glDeleteLists(id, 1);
    }
    impl->displayLists.clear();
    
    impl->quadric = 0;
    safe_delete(impl);
}


void Graphics::resize(int width, int height)
{
    glViewport(impl->x, impl->y, width, height);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    impl->width	= width;
    impl->height	= height;
}


void Graphics::initialise(int width, int height, num x, num y)
{
    //glEnable(GL_DOUBLE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    
    glShadeModel(GL_SMOOTH);
    
    setDepthTest(true);
    setCulling(true);
    setAntialiasing(true);
    
    glClearColor(0x40 / 255.0, 0x80 / 255.0, 0x80 / 255.0, 0);
    
    float ambientLight[] = {0.5f, 0.5f, 0.5f, 1.0f};
    float diffuseLight[] = {1.0f, 1.0f, 1.0f, 1.0f};
    float specularLight[] = {0.2f, 0.2f, 0.2f, 1.0f};
    
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
    
    float matSpecular[] = {0.3f, 0.3f, 0.3f, 1.0f};
    /*float matAmbient[] = {0.2f, 0.2f, 0.2f, 1.0f};
    float matDiffuse[] = {0.5f, 0.5f, 0.5f, 1.0f};*/
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
    /*glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);*/
    glMateriali(GL_FRONT, GL_SHININESS, 128);
    
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    
    setViewport(width, height, x, y);
}


void Graphics::shutdown()
{
}


void Graphics::setViewport(int width, int height, num x, num y)
{
    setOrigin(x, y);
    resize(width, height);
}


void Graphics::drawCube(const Vector3& pos, num d)
{
    glPushMatrix();
    
    glTranslatef(pos[X], pos[Y], pos[Z]);
    
    static float f = 0.0f;
    f += 0.002;
    
    glRotatef(f, 0, 1, 0);
    
    glBegin(GL_QUADS);
    //Front
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-d, -d, d);
    glVertex3f(d, -d, d);
    glVertex3f(d, d, d);
    glVertex3f(-d, d, d);
    
    //Back
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(-d, d, -d);
    glVertex3f(d, d, -d);
    glVertex3f(d, -d, -d);
    glVertex3f(-d, -d, -d);
    
    //Left
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(-d, -d, -d);
    glVertex3f(-d, -d, d);
    glVertex3f(-d, d, d);
    glVertex3f(-d, d, -d);
    
    //Right
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(d, -d, d);
    glVertex3f(d, -d, -d);
    glVertex3f(d, d, -d);
    glVertex3f(d, d, d);
    
    //Top
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-d, d, d);
    glVertex3f(d, d, d);
    glVertex3f(d, d, -d);
    glVertex3f(-d, d, -d);
    
    //Bottom
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(-d, -d, d);
    glVertex3f(-d, -d, -d);
    glVertex3f(d, -d, -d);
    glVertex3f(d, -d, d);
    glEnd();
    
    glPopMatrix();
}


void Graphics::drawPoint(const Point* p) const
{
    element<Point> e = element<Point>(p);
    impl->points.push_back(e);
}


void Graphics::drawPoint(const Vector3& v) const
{
    impl->point_pool.push_back(Point(v));
}


void Graphics::drawPoint(const Vector2& v) const
{
    impl->point_pool.push_back(Point(v));
}


void Graphics::drawPoint(num x, num y, num z) const
{
    drawPoint(Vector3(x, y, z));
}


void Graphics::drawSegment(const LineSegmentEnt* s) const
{
    element<LineSegmentEnt> e = element<LineSegmentEnt>(s);
    impl->segments.push_back(e);
}


void Graphics::drawSegment(const Vector3& p1, const Vector3& p2) const
{
    LineSegmentEnt s = LineSegmentEnt(p1, p2);
    impl->segment_pool.push_back(s);
}

void Graphics::drawSegment(const Vector2& p1, const Vector2& p2) const
{
    LineSegmentEnt s = LineSegmentEnt(p1, p2);
    impl->segment_pool.push_back(s);
}


void Graphics::drawSegment(const Vector3 ps[2]) const
{
    drawSegment(ps[0], ps[1]);
}

void Graphics::drawTriangle(const TriangleEnt* t) const
{
    element<TriangleEnt> e = element<TriangleEnt>(t);
    impl->triangles.push_back(e);
}


void Graphics::drawTriangle(const Vector3 p1, const Vector3& p2, const Vector3& p3) const
{
    impl->triangle_pool.push_back(TriangleEnt(p1, p2, p3));
}


void Graphics::drawTriangle(const Vector3 ps[3]) const
{
    drawTriangle(ps[0], ps[1], ps[2]);
}


void Graphics::drawCircle(const CircleEnt* c) const
{
    element<CircleEnt> e = element<CircleEnt>(c);
    impl->circles.push_back(e);
}


void Graphics::drawCircle(const Vector3& p1, const Vector3& p2, const Vector3& p3) const
{
    impl->circle_pool.push_back(CircleEnt(p1, p2, p3));
}


void Graphics::drawCircle(const Vector3 ps[3]) const
{
    drawCircle(ps[0], ps[1], ps[2]);
}


void Graphics::drawPolygon(const Vector3* ps, int n, const Colour3& colour) const
{
    vector<Vector3>* points = new vector<Vector3>(n);
    for (int i = 0; i < n; ++i)
    {
        (*points)[i] = *ps;
        ps++;
    }
    
    polygon* p = new polygon(points, colour);
    
    element<polygon> e = element<polygon>(p);
    impl->polygons.push_back(e);
}


void Graphics::drawPolygon(const Vector2* ps, int n, const Colour3& colour) const
{
    vector<Vector3>* points = new vector<Vector3>(n);
    for (int i = 0; i < n; ++i)
    {
        const Vector2& v = *ps;
        (*points)[i] = Vector3(v[X], v[Y], 0);
        ps++;
    }
    
    polygon* p = new polygon(points, colour);
    
    element<polygon> e = element<polygon>(p);
    impl->polygons.push_back(e);
}


unsigned int Graphics::createStaticGeometry(const TriangleEnt* t, int n, const Vector3* normals, const Vector3* colours, bool flat, bool grayscale)
{
    GLuint id = glGenLists(1);
    if (id == 0) throw GEOC_EXCEPTION("glGenLists() failed");
    
    glNewList(id, GL_COMPILE);
    glBegin(GL_TRIANGLES);
    
    for (int i = 0; i < n; ++i)
    {
        const TriangleEnt& triangle = *t;
        
        if (grayscale)
        {
            glColor3f(0.5, 0.5, 0.5);
        }
        else if (!colours)
        {
            glColor3f(t->colour[R], t->colour[G], t->colour[B]);
        }
        else
        {
            glColor3f((*colours)[R], (*colours)[G], (*colours)[B]);
            colours++;
        }
        if (normals)
        {
            glNormal3f((*normals)[X], (*normals)[Y], (*normals)[Z]);
            normals++;
        }
        glVertex3f(triangle[0][X], triangle[0][Y], flat ? 0.0 : triangle[0][Z]);
        
        
        if (colours)
        {
            glColor3f((*colours)[R], (*colours)[G], (*colours)[B]);
            colours++;
        }
        if (normals)
        {
            glNormal3f((*normals)[X], (*normals)[Y], (*normals)[Z]);
            normals++;
        }
        glVertex3f(triangle[1][X], triangle[1][Y], flat ? 0.0 : triangle[1][Z]);
        
        
        if (colours)
        {
            glColor3f((*colours)[R], (*colours)[G], (*colours)[B]);
            colours++;
        }
        if (normals)
        {
            glNormal3f((*normals)[X], (*normals)[Y], (*normals)[Z]);
            normals++;
        }
        glVertex3f(triangle[2][X], triangle[2][Y], flat ? 0.0 : triangle[2][Z]);
        
        t++;
    }
    
    glEnd();
    glEndList();
    
    impl->displayLists.push_front(id);
    
    return id;
}


unsigned int Graphics::createStaticGeometry(const LineSegmentEnt* s, int n, bool flat)
{
    GLuint id = glGenLists(1);
    if (id == 0) throw GEOC_EXCEPTION("glGenLists() failed");
    
    glNewList(id, GL_COMPILE);
    glBegin(GL_LINES);
    
    for (int i = 0; i < n; ++i)
    {
        const LineSegmentEnt& segment = *s;
        const Colour3& colour = segment.colour;
        
        glColor3f(colour[R], colour[G], colour[B]);
        glVertex3f(segment[0][X], segment[0][Y], flat ? 0.0 : segment[0][Z]);
        glVertex3f(segment[1][X], segment[1][Y], flat ? 0.0 : segment[1][Z]);
        s++;
    }
    
    glEnd();
    glEndList();
    
    impl->displayLists.push_front(id);
    
    return id;
}


void Graphics::deleteStaticGeometry(unsigned int id)
{
    int id_arr[1];
    *id_arr = id;
    list<GLuint>::iterator displayList =
            search(impl->displayLists.begin(), impl->displayLists.end(), id_arr, id_arr+1);
    
    if (displayList != impl->displayLists.end())
    {
        glDeleteLists(*displayList, 1);
        impl->displayLists.erase(displayList);
    }
    else throw GEOC_EXCEPTION("The ID specified does not belong to any created static geometry");
}


void Graphics::drawStaticGeometry(unsigned int id) const
{
    glCallList(id);
}


void Graphics::newFrame()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
}


void Graphics::endFrame()
{
    glFlush();
}


void Graphics::flush()
{
    //Draw points.
    glBegin(GL_POINTS);
    foreach (element<Point> p, impl->points)	render_(*p.item);
    foreach (const Point& p, impl->point_pool)	render_(p);
    glEnd();
    impl->points.clear();
    impl->point_pool.clear();
    
    //Draw segments.
    glBegin(GL_LINES);
    foreach (element<LineSegmentEnt> s, impl->segments)		render_(*s.item);
    foreach (const LineSegmentEnt& s, impl->segment_pool)	render_(s);
    glEnd();
    impl->segments.clear();
    impl->segment_pool.clear();
    
    //Draw triangles.
    glBegin(GL_TRIANGLES);
    foreach (element<TriangleEnt> t, impl->triangles)	render_(*t.item);
    foreach (const TriangleEnt& t, impl->triangle_pool)	render_(t);
    glEnd();
    impl->triangles.clear();
    impl->triangle_pool.clear();
    
    //Draw circles.
    foreach (element<CircleEnt> c, impl->circles)	render_(*c.item, impl->quadric);
    foreach (const CircleEnt& c, impl->circle_pool)	render_(c, impl->quadric);
    impl->circles.clear();
    impl->circle_pool.clear();
    
    //Draw polygons.
    foreach (element<polygon> p, impl->polygons)	render_(*p.item);
    foreach (const polygon& p, impl->polygon_pool)	render_(p);
    impl->polygons.clear();
    impl->polygon_pool.clear();
}


void Graphics::setOrigin(int x, int y)
{
    impl->x = x;
    impl->y = y;
}


void Graphics::setColour(const Colour3& colour)
{
    glColor3f(colour[R], colour[G], colour[B]);
}


void Graphics::setColour(num r, num g, num b)
{
    glColor3f(r, g, b);
}


void Graphics::setLighting(bool state)
{
    if (state && !impl->lighting)
    {
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glEnable(GL_COLOR_MATERIAL);
        glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
        impl->lighting = true;
    }
    else if (!state && impl->lighting)
    {
        glDisable(GL_COLOR_MATERIAL);
        glDisable(GL_LIGHT0);
        glDisable(GL_LIGHTING);
        impl->lighting = false;
    }
}


void Graphics::updateLighting()
{
    //static const float lightDir[] = {200.0f, 20.0f, 300.0f, 0.0f};
    static const float lightDir[] = {1, 0, 1, 0.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, lightDir);
}

bool Graphics::getLightingState() const
{
    return impl->lighting;
}


void Graphics::setWireframe(bool state)
{
    if (state && !impl->wireframe)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        impl->wireframe = true;
    }
    else if (!state && impl->wireframe)
    {
        glPolygonMode(GL_FRONT, GL_FILL);
        impl->wireframe = false;
    }
}


void Graphics::toggleWireframe()
{
    if (impl->wireframe) setWireframe(false);
    else setWireframe(true);
}


bool Graphics::getWireframeState() const
{
    return impl->wireframe;
}


void Graphics::setAntialiasing(bool state)
{
    if (state && !impl->antialiasing)
    {
        glEnable(GL_POINT_SMOOTH);
        glEnable(GL_LINE_SMOOTH);
        glEnable(GL_POLYGON_SMOOTH);
        impl->antialiasing = true;
    }
    else if (!state && impl->antialiasing)
    {
        glDisable(GL_POINT_SMOOTH);
        glDisable(GL_LINE_SMOOTH);
        glDisable(GL_POLYGON_SMOOTH);
        impl->antialiasing = false;
    }
}


bool Graphics::getAntialiasingState() const
{
    return impl->antialiasing;
}


void Graphics::setDepthTest(bool state)
{
    if (state && !impl->depthTest)
    {
        glEnable(GL_DEPTH_TEST);
        impl->depthTest = true;
    }
    else if (!state && impl->depthTest)
    {
        glDisable(GL_DEPTH_TEST);
        impl->depthTest = false;
    }
}


bool Graphics::getDepthTestState() const
{
    return impl->depthTest;
}


void Graphics::setCulling(bool state)
{
    if (state && !impl->culling)
    {
        glEnable(GL_CULL_FACE);
        impl->culling = true;
    }
    else if (!state && impl->culling)
    {
        glDisable(GL_CULL_FACE);
        impl->culling = false;
    }
}


bool Graphics::getCullingState() const
{
    return impl->culling;
}


void Graphics::setPointSize(num size)
{
    glPointSize((GLfloat)size);
}


void Graphics::setLineWidth(num size)
{
    glPointSize((GLfloat)size);
}


void Graphics::setThickness(num t)
{
    impl->thickness = t;
    glPointSize((GLfloat)t);
    glLineWidth((GLfloat)t);
}


void Graphics::increaseThickness()
{
    num& t = impl->thickness;
    t += g_thickness_step;
    glPointSize((GLfloat)t);
    glLineWidth((GLfloat)t);
}


void Graphics::decreaseThickness()
{
    num& t = impl->thickness;
    t -= g_thickness_step;
    glPointSize((GLfloat)t);
    glLineWidth((GLfloat)t);
}


int Graphics::width() const
{
    return impl->width;
}


int Graphics::height() const
{
    return impl->height;
}


num Graphics::aspectRatio() const
{
    return (num)impl->width / (num)impl->height;
}


void Graphics::getViewportOrigin(int& x, int& y) const
{
    x = impl->x;
    y = impl->y;
}


void render_(const Point& p)
{
    const Colour3& c = p.colour;
    
    glColor3f(c[R], c[G], c[B]);
    glVertex3f(p[X], p[Y], p[Z]);
}


void render_(const LineSegmentEnt& s)
{
    const Colour3& c = s.colour;
    
    glColor3f(c[R], c[G], c[B]);
    glVertex3f(s[0][X], s[0][Y], s[0][Z]);
    glVertex3f(s[1][X], s[1][Y], s[1][Z]);
}


void render_(const TriangleEnt& t)
{
    glColor3f(t.colour[R], t.colour[G], t.colour[B]);
    glVertex3f(t[0][X], t[0][Y], t[0][Z]);
    glVertex3f(t[1][X], t[1][Y], t[1][Z]);
    glVertex3f(t[2][X], t[2][Y], t[2][Z]);
}


void render_(const CircleEnt& c, GLUquadricObj* quadric)
{	
    const Colour3& colour = c.colour;
    glColor3f(colour[R], colour[G], colour[B]);
    
    const Vector3& p1 = c[0];
    const Vector3& p2 = c[1];
    const Vector3& p3 = c[2];
    
    num x1, y1;
    num x2, y2;
    num x3, y3;
    
    x1 = p1[X];
    y1 = p1[Y];
    
    x2 = p2[X];
    y2 = p2[Y];
    
    x3 = p3[X];
    y3 = p3[Y];
    
    //Swap points if necessary to avoid division by 0.
    if (x2 == 0.0 && x1 == 0.0)
    {
        x2 = p3[X];
        y2 = p3[Y];
        
        x3 = p2[X];
        y3 = p2[Y];
    }
    
    num ma = (y2 - y1) / (x2 - x1);
    num mb = (y3 - y2) / (x3 - x2);
    
    num x =	( ma*mb*(y1 - y3) + mb*(x1 + x2) - ma*(x2 + x3) ) /
            ( 2*(mb-ma) );
    
    num y =	-(1.0 / ma) * (x - (x1 + x2)/2.0) + (y1 + y2)/2.0;
    
    num radius = sqrt( Math::square(x2 - x) + Math::square(y2 - y) );
    
    glPushMatrix();
    glTranslatef(x, y, 0.0);
    gluDisk(quadric, radius, radius, 128, 8);
    glPopMatrix();
}


void render_(const polygon& p)
{
    glColor3f(p.colour[R], p.colour[G], p.colour[B]);
    
    glBegin(GL_POLYGON);
    
    foreach (Vector3 v, *p.points)
    {
        glVertex3f(v[X], v[Y], v[Z]);
    }
    
    glEnd();
}
