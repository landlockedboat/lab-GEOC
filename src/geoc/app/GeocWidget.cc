#include <geoc/app/GeocWidget.h>
#include <geoc/gfx/Graphics.h>
#include <geoc/gfx/Font.h>
#include <geoc/camera/Camera.h>
#include <geoc/io/input/Input.h>
#include <geoc/io/input/Keyboard.h>
#include <geoc/io/input/Mouse.h>
#include <geoc/io/screen/ScreenInput.h>
#include <geoc/io/loader/ObjectLoader.h>
#include <geoc/scene/SceneManager.h>
#include <geoc/app/input_translation.h>
#include <geoc/app/camera_control/CamCtrlContext.h>
#include <geoc/app/update_requests.h>
#include <geoc/math/Vector.h>
#include <geoc/GeocException.h>

#include <QMouseEvent>
#include <QKeyEvent>
#include <QMessageBox>
#include <QFileDialog>
#include <QApplication>


using namespace geoc;


GeocWidget::GeocWidget(QWidget* parent, bool designer)
    : QGLWidget(parent),
      _sceneMgr(0), _camCtrlContext(0), _gfx(0), _input(0), _kbd(0), _mouse(0), _prev_mouse_pos(0),
      _screenInput(0), _objectLoader(0), _font(0),
      _drawLabels(false), _mouseMoved(false), _designer(designer), _saveFile("output.txt")
{
    if (!designer)
    {
        // Initialise the scene manager.
        _sceneMgr = new SceneManager();
        
        // Initialise input subsystem.
        _kbd    = new Keyboard;
        _mouse  = new Mouse;
        _input  = new Input(*_kbd, *_mouse);
        
        // Initialise the object loader.
        _objectLoader = new ObjectLoader;
        
        _prev_mouse_pos = new ScreenPos;
    }
}


GeocWidget::~GeocWidget()
{
    if (_sceneMgr)          safe_delete(_sceneMgr);
    if (_camCtrlContext)    safe_delete(_camCtrlContext);
    if (_gfx)               safe_delete(_gfx);
    if (_input)             safe_delete(_input);
    if (_kbd)               safe_delete(_kbd);
    if (_mouse)             safe_delete(_mouse);
    if (_prev_mouse_pos)    safe_delete(_prev_mouse_pos);
    if (_screenInput)       safe_delete(_screenInput);
    if (_objectLoader)      safe_delete(_objectLoader);
    if (_font)              safe_delete(_font);
}


void GeocWidget::initializeGL()
{    
    // Initialise graphics subsystem.
    _gfx = new Graphics();
    _gfx->initialise(width(), height(), 0, 0);
    
    if (!_designer)
    {
        setMouseTracking(true);
    }
    
    const QGLContext* c = context();
    if (!c->isValid())
    {
        throw GEOC_EXCEPTION("Invalid GL context");
    }
    
    // Initialise font.
    _font = new Font();
    
    // Initialise camera handling subsystem.
    _camCtrlContext = new CamCtrlContext(*_input, *_gfx, *_sceneMgr);
    _camCtrlContext->setDimensions(width(), height());
    _camCtrlContext->resetCamera();
    
    // Initialise screen input subsystem.
    _screenInput = new ScreenInput(_camCtrlContext->camera(), *_sceneMgr);
}


void GeocWidget::resizeGL(int w, int h)
{
    _gfx->setViewport(w, h, 0, 0);
    
    if (!_designer)
    {
        _camCtrlContext->setDimensions(width(), height());
        _camCtrlContext->updateZoom();
        _camCtrlContext->centerCamera();
    }
}


void GeocWidget::paintGL()
{
    _gfx->newFrame();
    
    // Draw the logo if required.
    if (_designer)
    {
        _font->startRender(Font::render_2d);
        glBegin(GL_QUADS);
        _font->draw2D(width() / 2.0, height() / 2.0, "Geoc Widget");
        glEnd();
        _font->endRender();
    }
    else
    {
        const Camera& cam = _camCtrlContext->camera();
        
        cam.applyProjectionMatrix();
        
        cam.applyInverseRotation();
        cam.applyInverseTranslation();
        
        _sceneMgr->applyTranslation();
        _sceneMgr->applyRotation();
        _sceneMgr->applyInverseTranslation();
        
        if (_gfx->getLightingState()) _gfx->updateLighting();
        
        // Render the scene.
        _sceneMgr->render(*_gfx);
        //_gfx->flush();
        
        // Render labels.
        if (_drawLabels) _sceneMgr->renderLabels(*_font, cam);
        
        // Render the state of the screen input subsystem.
        _screenInput->draw(*_gfx);
        
        emit render(); // Fire signal.
    }
    
    // Flush out the render.
    _gfx->flush();
    
    _gfx->endFrame();
}


void GeocWidget::mousePressEvent(QMouseEvent* event)
{
    if (_designer) return;
    
    ScreenPos pos = ScreenPos(event->x(), event->y());
    
    Mouse::button bt = translate_mouse(event->button());
    if (bt == Mouse::unknown) return;
    
    _mouse->setState(bt, true);
    
    if (bt == Mouse::RMB)
    {
        if ( _kbd->up(Keyboard::Key_ctrl) && _kbd->up(Keyboard::Key_shift) )
        {
            char request = 0;
            request |= _screenInput->mouseRightClicked(pos);
            handleRequest(request);
        }
    }
    
    setFocus();
}


void GeocWidget::mouseReleaseEvent(QMouseEvent* event)
{
    if (_designer) return;
    
    ScreenPos pos = ScreenPos(event->x(), event->y());
    
    Mouse::button bt = translate_mouse(event->button());
    if (bt == Mouse::unknown) return;
    
    _mouse->setState(bt, false);
    
    if (bt == Mouse::LMB)
    {
        _mouse->setState(Mouse::LMB, false);
        if (!_mouseMoved && _kbd->up(Keyboard::Key_ctrl) && _kbd->up(Keyboard::Key_shift) )
        {
            char request = 0;
            request |= _screenInput->mouseClicked(pos);
            handleRequest(request);
        }
        _mouseMoved = false;
    }
    
    // Fire signal.
    emit mouseClicked(*this, pos, bt);
}


void GeocWidget::mouseMoveEvent(QMouseEvent* event)
{
    if (_designer) return;
    
    ScreenPos pos = ScreenPos(event->x(), event->y());
    ScreenPos delta = pos - *_prev_mouse_pos;
    
    char request = 0;
    request |= _camCtrlContext->mouseMoved(pos);
    request |= _screenInput->mouseMoved(pos);
    handleRequest(request);
    
    if (_mouse->down(Mouse::LMB)) _mouseMoved = true;
    
    _mouse->setPosition(pos[X], pos[Y]);
    _mouse->setDelta(delta[X], delta[Y]);
    
    // Fire signal.
    emit mouseMoved(*this, *_prev_mouse_pos, pos);
    
    *_prev_mouse_pos = pos;
}


void GeocWidget::wheelEvent(QWheelEvent* event)
{
    if (_designer) return;
    
    handleRequest(_camCtrlContext->mouseWheel(event->delta()));
    
    /*int x, y;
    mouse->getPos(&x, &y);
    m_screenInput->mouseMoved(ScreenPos(x, y));*/
}


void GeocWidget::keyPressEvent(QKeyEvent* event)
{
    if (_designer) return;
    
    Keyboard::key key = translate_key(event->key());
    if (key != -1) _kbd->setState(key, true);
    
    // Handle key event.
    switch (key)
    {
    case Keyboard::Key_escape:
        requestExit();
        break;
        
    case Keyboard::Key_backspace:
        _sceneMgr->detachLast();
        handleRequest(GEOC_APP_REDISPLAY);
        break;
        
    case Keyboard::Key_Z:
    {
        if (_kbd->down(Keyboard::Key_ctrl))
        {
            _sceneMgr->undo();
            handleRequest(GEOC_APP_REDISPLAY);
        }
        break;
    }
        
    case Keyboard::Key_R:
    {
        if (_kbd->down(Keyboard::Key_ctrl))
        {
            _sceneMgr->redo();
            handleRequest(GEOC_APP_REDISPLAY);
        }
        break;
    }
        
    case Keyboard::Key_pgup:
        _gfx->increaseThickness();
        handleRequest(GEOC_APP_REDISPLAY);
        break;
        
    case Keyboard::Key_pgdown:
        _gfx->decreaseThickness();
        handleRequest(GEOC_APP_REDISPLAY);
        break;
        
    case Keyboard::Key_L:
        toggleLabels(true);
        
    default:
        break;
    }
    
    // Send the key to the camera control and screen input subsystems.
    char request = 0;
    request |= _camCtrlContext->keyPressed(key);
    if (request & GEOC_APP_REDISPLAY)
    {
        ScreenPos pos;
        _mouse->getPos(&pos[X], &pos[Y]);
        _screenInput->mouseMoved(pos);
    }
    
    ScreenPos pos;
    _input->getMousePos(pos);
    request |= _screenInput->keyPressed(key, pos);
    handleRequest(request);
}


void GeocWidget::keyReleaseEvent(QKeyEvent* event)
{
    if (_designer) return;
    
    Keyboard::key key = translate_key(event->key());
    if (key != -1) _kbd->setState(key, false);
    
    // Fire signal.
    emit keyPressed(*this, key);
}


void GeocWidget::handleRequest(char code)
{
    if (code & GEOC_APP_REDISPLAY)          redisplay();
    if (code & GEOC_APP_STATUS_BAR_UPDATE)  updateStatus();
}


void GeocWidget::toggleLabels(bool key)
{
    _drawLabels = !_drawLabels;
    redisplay();
    
    // Fire signal.
    emit labelsToggled(*this, key);
}


void GeocWidget::resetCamera()
{
    _camCtrlContext->resetCamera();
    
    // Fire signal.
    updateStatus();
}


void GeocWidget::updateStatus()
{
    emit updateStatus(_camCtrlContext->getCameraMode(),
                      _camCtrlContext->getCameraProjection(),
                      _screenInput->stateDescription());
}


void GeocWidget::loadScene(const char* filename)
{
    _sceneMgr->clear();
    
    try
    {
        _objectLoader->load(filename);
    }
    catch (GeocException& e)
    {
        QMessageBox(QMessageBox::Warning, "Load Scene", e.what(), QMessageBox::Ok, this).exec();
    }
    
    resetCamera();
    
    // Fire signal.
    updateStatus();
    
    _lastFileLoaded = filename;
}


void GeocWidget::loadScene()
{
    QString file = QFileDialog::getOpenFileName(this, "Load Scene", ".", "Scene files (*.txt)", 0, QFileDialog::DontUseNativeDialog);
    //QString file = QFileDialog::getOpenFileName(this, "Load Scene", ".", "Scene files (*.txt)");
    if (!file.isEmpty())
    {
        loadScene(file.toStdString().c_str());
    }
}


void GeocWidget::reloadScene()
{
    if (_lastFileLoaded.empty())
    {
        QMessageBox(QMessageBox::Information, "Reload Scene", "No scene has been loaded", QMessageBox::Ok, this).exec();
    }
    else
    {
        loadScene(_lastFileLoaded.c_str());
    }
}


void GeocWidget::saveScene()
{
    _sceneMgr->save(_saveFile.c_str());
}


void GeocWidget::saveSceneAs()
{
    QString file = QFileDialog::getSaveFileName(this, "Load Scene", ".", "Scene files (*.txt)", 0, QFileDialog::DontUseNativeDialog);
    if (!file.isEmpty())
    {
        _saveFile = file.toStdString();
        if (_saveFile.find(".txt") == std::string::npos) _saveFile += ".txt";
        saveScene();
    }
}
