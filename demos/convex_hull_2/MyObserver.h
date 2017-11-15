#ifndef _MY_OBSERVER_H
#define _MY_OBSERVER_H

#include <geoc/io/Observer.h>
#include <geoc/scene/Point.h>
#include <geoc/scene/Entity.h>
#include "ConvexHull.h"

namespace geoc {
class SceneManager;
}

class MyObserver : public geoc::Observer<geoc::Point>,
	           public geoc::Observer<ConvexHull>,
	           public geoc::Observer<geoc::Entity>
{
    geoc::SceneManager* sceneMgr;
    ConvexHull* ch;
    
public:
    
    MyObserver(geoc::SceneManager* sceneMgr);
    ~MyObserver();
    
    void enters(geoc::Point* s);
    void enters(ConvexHull* ch);
    
    void leaves(geoc::Entity* e);
};

#endif //_MY_OBSERVER_H
