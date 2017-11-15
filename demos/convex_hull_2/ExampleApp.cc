#include "ExampleApp.h"
#include "MyObserver.h"
#include <geoc/io/loader/ObjectLoader.h>
#include <geoc/io/loader/Loader.h>
#include <geoc/io/screen/ScreenInput.h>
#include <geoc/io/screen/PointState.h>
#include <geoc/scene/SceneManager.h>
#include <geoc/app/GeocWidget.h>
#include <cstdio>

#include "ConvexHull.h"

using namespace geoc;
using namespace std;

void ExampleApp::init(int argc, char** argv)
{
    GeocWidget& w = geocWidget();
    
    myObserver = new MyObserver(&w.sceneManager());
    
    PointState* pState = new PointState;
    
    ScreenInput& screenInput = w.screenInput();
    screenInput.setTransition(Keyboard::Key_P, pState);
    
    Loader<ConvexHull>* chLoader = new Loader<ConvexHull>;
    
    ObjectLoader& oLoader = w.objectLoader();
    oLoader.attach(chLoader);
    
    pState->attach(myObserver);
    chLoader->attach(myObserver);
    w.sceneManager().attachObserver(myObserver);
    
    if (argc > 1) loadScene(argv[1]);
    
    w.gfx().setPointSize(4);
    w.gfx().setWireframe(true);
    
    printf("Example application initialised.\n");
}

void ExampleApp::shutdown()
{
    printf("Example application shutting down.\n");
    
    safe_delete(myObserver);
}
