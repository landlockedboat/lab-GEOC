#include "MyObserver.h"
#include <geoc/scene/SceneManager.h>
#include <geoc/scene/Point.h>
#include <geoc/scene/LineSegmentEnt.h>
#include <geoc/scene/TriangleEnt.h>
#include <geoc/scene/CircleEnt.h>
#include <geoc/io/output/OutputSystem.h>
#include <geoc/io/output/FileOutput.h>
#include <sstream>
#include <string>

using namespace geoc;
using namespace std;

MyObserver::MyObserver(SceneManager* scenemgr, OutputSystem* outSys) :
    sceneMgr(scenemgr), outputSystem(outSys)
{
}


void MyObserver::enters(Point* p)
{
    sceneMgr->attach(p);
    ostringstream os;
    os << "Point enters: " << *p;
    outputSystem->write(os);
}


void MyObserver::enters(LineSegmentEnt* s)
{
    sceneMgr->attach(s);
    ostringstream os;
    os << "Segment enters: " << *s;
    outputSystem->write(os);
}


void MyObserver::enters(TriangleEnt* t)
{
    sceneMgr->attach(t);
    outputSystem->write("Triangle enters (coords not shown)");
}


void MyObserver::enters(CircleEnt* c)
{
    sceneMgr->attach(c);
    outputSystem->write("Circle enters (coords not shown)");
}
