#include "MyObserver.h"
#include "Polygon.h"
#include <geoc/scene/SceneManager.h>


using namespace geoc;
using namespace std;
using namespace polygon;


MyObserver::MyObserver(SceneManager* scenemgr) : sceneMgr(scenemgr) {}


void MyObserver::enters(Polygon* p)
{
    p->colour = Colour3(0, 0, 0);
    sceneMgr->attach(p);
}
