#ifndef _MY_OBSERVER_H
#define _MY_OBSERVER_H

#include <geoc/io/Observer.h>
#include <geoc/scene/Entity.h>

namespace geoc {
class Point;
class LineSegmentEnt;
class TriangleEnt;
class CircleEnt;
class SceneManager;
class OutputSystem;
}

class MyObserver : public geoc::Observer<geoc::Point>,
	           public geoc::Observer<geoc::LineSegmentEnt>,
	           public geoc::Observer<geoc::TriangleEnt>,
	           public geoc::Observer<geoc::CircleEnt>
{
    geoc::SceneManager* sceneMgr;
    geoc::OutputSystem* outputSystem;
    
public:
    
    MyObserver(geoc::SceneManager* sceneMgr, geoc::OutputSystem* outputSystem);
    
    void enters(geoc::Point* p);
    void enters(geoc::LineSegmentEnt* s);
    void enters(geoc::TriangleEnt* t);
    void enters(geoc::CircleEnt* c);
};

#endif //_MY_OBSERVER_H
