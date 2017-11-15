#include <geoc/app/GeocApplication.h>
#include <geoc/app/GeocWidget.h>
#include <geoc/app/update_requests.h>
#include <geoc/app/camera_control/CamCtrlContext.h>
#include <geoc/io/output/OutputSystem.h>
#include <geoc/io/output/ScrollList.h>
#include <geoc/io/input/Input.h>
#include <geoc/io/input/Keyboard.h>
#include <geoc/io/input/Mouse.h>
#include <geoc/io/screen/ScreenInput.h>
#include <geoc/app/input_translation.h>
#include <geoc/gfx/Graphics.h>
#include <geoc/gfx/Font.h>
#include <geoc/camera/Camera.h>
#include <geoc/scene/SceneManager.h>
#include <geoc/GeocException.h>
#include <cstdio>

#define _GEOC_ENABLE_CONSOLE_OUTPUT
#if defined WIN32 && defined _GEOC_ENABLE_CONSOLE_OUTPUT
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <io.h>
#include <FCNTL.H>
#endif

#include <QStyleFactory>
#include <QMenuBar>
#include <QStatusBar>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QGridLayout>
#include <QMessageBox>


using namespace geoc;
using namespace std;


GeocApplication::GeocApplication(QWidget* parent) : QMainWindow(parent),
    _geocWidget(0), _outputSystem(0), _scrollList(0), _statusBar(0),
    _mouseMoved(false), _drawLabels(false)
{
    // Initialise output subsystem.
    _outputSystem = new OutputSystem;
    
    setMouseTracking(true);
}


GeocApplication::~GeocApplication()
{
    if (_geocWidget)	safe_delete(_geocWidget);
    if (_outputSystem)
    {
        if (_scrollList) _outputSystem->detach(_scrollList);
        safe_delete(_outputSystem);
    }
}


void GeocApplication::setup(int argc, char** argv, int width, int height)
{
    resize(width, height);
    
#if defined WIN32 && defined _GEOC_ENABLE_CONSOLE_OUTPUT
    // Check if the process already owns a console.
    HWND h = GetConsoleWindow();
    if (h != NULL) return; // The process owns a console, nothing to do.
    
    // Allocate a new console.
    AllocConsole();
    
    // Set screen buffer properties.
    CONSOLE_SCREEN_BUFFER_INFO coninfo;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &coninfo);
    coninfo.dwSize.Y = 128;
    SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), coninfo.dwSize);
    
    // Redirect the standard output to the newly created console.
    long lStdHandle = (long)GetStdHandle(STD_OUTPUT_HANDLE);
    int hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
    FILE* fp = _fdopen( hConHandle, "w" );
    *stdout = *fp;
    setvbuf( stdout, NULL, _IONBF, 0 );
#endif
    
    // Initialise GeocWidget.
    _geocWidget = new GeocWidget(this);
    
    // Set Qt style.
    
#ifdef WIN32
    setStyle(QStyleFactory::create("windows"));
#endif
    
    setWindowTitle(QString("Geoc Viewer"));
    
    // Set up scroll list.
    
    _scrollList	= new ScrollList;
    _scrollList->setAttribute(Qt::WA_DeleteOnClose, true);
    _scrollList->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    _scrollList->setMinimumHeight(140);
    _scrollList->setMaximumHeight(140);
    _outputSystem->attach(_scrollList);
    
    // Set up widgets.
    
    QWidget* widget = new QWidget;
    widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setCentralWidget(widget);
    
    QGridLayout* grid = new QGridLayout(widget);
    grid->addWidget(_geocWidget, 0, 0);
    grid->addWidget(_scrollList, 1, 0);
    
    grid->setColumnStretch(0, 1);
    grid->setRowStretch(0, 1);
    grid->setRowStretch(1, 1);
    
    _geocWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    
    // Set up menu bar.
    
    _menuBar = menuBar();
    _menuBar->setAttribute(Qt::WA_DeleteOnClose, true);
    _menuBar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    
    QMenu* viewerMenu	= _menuBar->addMenu("&Viewer");
    QAction* quit	= viewerMenu->addAction("&Quit");
    
    QMenu* sceneMenu	= _menuBar->addMenu("&Scene");
    QAction* load	= sceneMenu->addAction("&Load");
    QAction* reload	= sceneMenu->addAction("&Reload");
    sceneMenu->addSeparator();
    QAction* save	= sceneMenu->addAction("&Save");
    QAction* saveAs	= sceneMenu->addAction("Save &As");
    sceneMenu->addSeparator();
    QAction* labels	= sceneMenu->addAction("Show labels");
    labels->setCheckable(true);
    
    QMenu* helpMenu	= _menuBar->addMenu("&Help");
    QAction* about	= helpMenu->addAction("&About");
    
    // Set up status bar.
    
    _statusBar = statusBar();
    _statusBar->setAttribute(Qt::WA_DeleteOnClose, true);
    _statusBar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    
    // Set up connections.
    
    connect(quit,   SIGNAL(triggered()), this, SLOT(quit()));
    connect(load,   SIGNAL(triggered()), this, SLOT(loadScene()));
    connect(reload, SIGNAL(triggered()), this, SLOT(reloadScene()));
    connect(save,   SIGNAL(triggered()), this, SLOT(saveScene()));
    connect(saveAs, SIGNAL(triggered()), this, SLOT(saveSceneAs()));
    connect(about,  SIGNAL(triggered()), this, SLOT(showAbout()));
    connect(labels, SIGNAL(triggered()), this, SLOT(toggleLabels()));
    
    connect(_geocWidget, SIGNAL(updateStatus(const std::string&,
                                             const std::string&,
                                             const std::string&)),
            this, SLOT(updateStatusBar(const std::string&,
                                       const std::string&,
                                       const std::string&)));
    
    connect(_geocWidget, SIGNAL(requestExit()), this, SLOT(quit()));
    
    connect(_geocWidget, SIGNAL(keyPressed(GeocWidget&, Keyboard::key)),
            this,	   SLOT(keyPressed(GeocWidget&, Keyboard::key)));
    
    connect(_geocWidget, SIGNAL(mouseClicked(GeocWidget&, const ScreenPos&, Mouse::button)),
            this,	   SLOT(mouseClicked(GeocWidget&, const ScreenPos&, Mouse::button)));
    
    connect(_geocWidget, SIGNAL(mouseMoved(GeocWidget&, const ScreenPos&, const ScreenPos&)),
            this,	   SLOT(mouseMoved(GeocWidget&, const ScreenPos&, const ScreenPos&)));
    
    connect(_geocWidget, SIGNAL(labelsToggled(GeocWidget&, bool)),
            this,	   SLOT(labelsToggled(GeocWidget&, bool)));
    
    connect(_geocWidget, SIGNAL(render()), this, SLOT(render()));
    
    _labels = labels;
    
    _geocWidget->setFocus(Qt::ActiveWindowFocusReason);
    show();
    
    init(argc, argv); //hook
    _geocWidget->resetCamera();
}


void GeocApplication::keyPressEvent(QKeyEvent* event)
{
    Keyboard::key key = translate_key(event->key());
    
    // Handle key event.
    switch (key)
    {
    case Keyboard::Key_escape:
        quit();
        
    case Keyboard::Key_G:
        saveScene();
        break;
        
    default:
        break;
    }
}


void GeocApplication::closeEvent(QCloseEvent* event)
{
    shutdown();
    event->accept();
}


void GeocApplication::quit()
{
    close();
}


void GeocApplication::updateStatusBar(const std::string& camCtrlContext_state,
                                      const std::string& camera_mode,
                                      const std::string& input_desc)
{
    ostringstream os;
    os << "Mode: ";
    os << camCtrlContext_state;
    
    os << ", Projection: ";
    os << camera_mode;
    
    os << ", Input State: " << input_desc;
    
    _statusBar->clearMessage();
    _statusBar->showMessage(QString(os.str().c_str()));
}


void GeocApplication::labelsToggled(GeocWidget&, bool key)
{
    if (key) _labels->setChecked(!_labels->isChecked());
}


void GeocApplication::loadScene(const char* filename)
{
    _geocWidget->loadScene(filename);
}


void GeocApplication::loadScene()
{
    _geocWidget->loadScene();
}


void GeocApplication::reloadScene()
{
    _scrollList->clear();
    _geocWidget->reloadScene();
}


void GeocApplication::saveScene()
{
    _geocWidget->saveScene();
}


void GeocApplication::saveSceneAs()
{
    _geocWidget->saveSceneAs();
}


void GeocApplication::showAbout()
{
    QMessageBox::about(this, "Geoc Viewer", "Geoc viewer, Spring 2012");
}


void GeocApplication::toggleLabels()
{
    _geocWidget->toggleLabels();
}


void GeocApplication::redisplay()
{
    _geocWidget->redisplay();
}
