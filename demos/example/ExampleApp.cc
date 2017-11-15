#include "ExampleApp.h"
#include "MyObserver.h"
#include <geoc/gfx/Graphics.h>
#include <geoc/io/loader/ObjectLoader.h>
#include <geoc/io/loader/Loader.h>
#include <geoc/io/screen/ScreenInput.h>
#include <geoc/io/screen/PointState.h>
#include <geoc/io/screen/LineSegmentState.h>
#include <geoc/io/screen/TriangleState.h>
#include <geoc/io/screen/CircleState.h>
#include <geoc/app/GeocWidget.h>
#include <cstdio>

using namespace geoc;
using namespace std;

void ExampleApp::init(int argc, char** argv)
{
    GeocWidget& w = geocWidget();
    
    myObserver = new MyObserver(&w.sceneManager(), &outputSystem());
    
    // Configure states for the screen input state machine.
    PointState*			pState = new PointState;
    LineSegmentState*	sState = new LineSegmentState;
    TriangleState*		tState = new TriangleState;
    CircleState*		cState = new CircleState;
    
    
    ScreenInput& screenInput = w.screenInput();
    screenInput.setTransition(Keyboard::Key_P, pState);
    screenInput.setTransition(Keyboard::Key_S, sState);
    screenInput.setTransition(Keyboard::Key_T, tState);
    screenInput.setTransition(Keyboard::Key_C, cState);
    
    // Loaders for the object loader.
    Loader<Point>*			pLoader = new Loader<Point>;
    Loader<LineSegmentEnt>*	sLoader = new Loader<LineSegmentEnt>;
    Loader<TriangleEnt>*	tLoader = new Loader<TriangleEnt>;
    Loader<CircleEnt>*		cLoader = new Loader<CircleEnt>;
    
    ObjectLoader& oLoader = w.objectLoader();
    oLoader.attach(pLoader);
    oLoader.attach(sLoader);
    oLoader.attach(tLoader);
    oLoader.attach(cLoader);
    
    // Attach our observer to each screen input state.
    pState->attach(myObserver);
    sState->attach(myObserver);
    tState->attach(myObserver);
    cState->attach(myObserver);
    
    // Attach our observer to each loader.
    pLoader->attach(myObserver);
    sLoader->attach(myObserver);
    tLoader->attach(myObserver);
    cLoader->attach(myObserver);
    
    // Load an input file if necessary.
    if (argc > 1) oLoader.load(argv[1]);
    
    w.gfx().setPointSize(1.5);
    w.gfx().setWireframe(true);
    w.gfx().setCulling(false);
    w.gfx().setAntialiasing(true);
    
    printf("Example application initialised.\n");
}


void ExampleApp::shutdown()
{
    printf("Example application shutting down.\n");
    
    safe_delete(myObserver);
}
