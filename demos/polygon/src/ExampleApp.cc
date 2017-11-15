#include "ExampleApp.h"
#include "MyObserver.h"
#include "PolygonState.h"
#include <geoc/gfx/Graphics.h>
#include <geoc/io/loader/ObjectLoader.h>
#include <geoc/io/loader/Loader.h>
#include <geoc/io/screen/ScreenInput.h>
#include <geoc/app/GeocWidget.h>
#include <cstdio>
#include "Polygon.h"


using namespace geoc;
using namespace std;


void ExampleApp::init(int argc, char** argv)
{
    GeocWidget& w = geocWidget();
    
    myObserver = new MyObserver(&w.sceneManager());
    
    // Configure states for the screen input state machine.
    PolygonState* pState = new PolygonState;
    ScreenInput& screenInput = w.screenInput();
    screenInput.setTransition(Keyboard::Key_O, pState);
    
    // Configure loaders.
    Loader<polygon::Polygon>* pLoader = new Loader<polygon::Polygon>;
    ObjectLoader& oLoader = w.objectLoader();
    oLoader.attach(pLoader);
    
    // Attach our observer to each screen input state.
    pState->attach(myObserver);
    
    // Attach our observer to each loader.
    pLoader->attach(myObserver);
    
    // Load an input file if necessary.
    if (argc > 1) loadScene(argv[1]);
    
    w.gfx().setPointSize(1.5);
    w.gfx().setWireframe(true);
    w.gfx().setCulling(false);
    
    printf("Example application initialised.\n");
}


void ExampleApp::shutdown()
{
    printf("Example application shutting down.\n");
    
    safe_delete(myObserver);
}
