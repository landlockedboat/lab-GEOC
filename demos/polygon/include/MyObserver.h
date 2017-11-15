#ifndef _MY_OBSERVER_H
#define _MY_OBSERVER_H

#include <geoc/io/Observer.h>
#include <geoc/scene/Entity.h>

namespace geoc {
class SceneManager;
}


namespace polygon {
class Polygon;
}


class MyObserver : public geoc::Observer<polygon::Polygon>
{
    geoc::SceneManager* sceneMgr;
    
public:
    
    MyObserver(geoc::SceneManager* sceneMgr);
    
    void enters(polygon::Polygon* p);
};

#endif //_MY_OBSERVER_H
