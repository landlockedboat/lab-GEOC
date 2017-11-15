#include "MyObserver.h"
#include <geoc/scene/SceneManager.h>
#include <geoc/io/output/OutputSystem.h>
#include <geoc/io/output/FileOutput.h>
#include <sstream>
#include <string>


using namespace geoc;
using namespace std;


MyObserver::MyObserver(SceneManager* sceneMgr_) : sceneMgr(sceneMgr_), ch(0)
{
}


MyObserver::~MyObserver()
{
}


void MyObserver::enters(Point* p)
{
    if (!ch)
    {
	ch = new ConvexHull();
	sceneMgr->attach(ch);
    }
    
    ch->addPoint(p->position());
    ch->update();
    sceneMgr->attach(p);
}


void MyObserver::enters(ConvexHull* ch)
{
    this->ch = ch;
}


void MyObserver::leaves(Entity* e)
{
    if (e == ch) ch = 0;
}
