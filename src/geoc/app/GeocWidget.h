#ifndef _GEOC_WIDGET_H
#define _GEOC_WIDGET_H

#include <geoc/geoc.h>
#include <geoc/io/input/Keyboard.h>
#include <geoc/io/input/Mouse.h>
#include <geoc/math/Vector_fwd_decl.h>
#include <QtOpenGL/QGLWidget>
#include <QtDesigner/QDesignerExportWidget>

namespace geoc {

class SceneManager;
class CamCtrlContext;
class Camera;
class Graphics;
class Input;
class Keyboard;
class Mouse;
class ScreenInput;
class ObjectLoader;
class LoaderInterface;
class OutputSystem;
class Font;

/** \ingroup App */
//! Core viewer component.
/*!
 * GeocWidget is the core component of a viewer application, holding an instance
 * of every subsystem except for OutputSystem.
 */
class QDESIGNER_WIDGET_EXPORT GeocWidget : public QGLWidget
{
    Q_OBJECT
    
    SceneManager*	_sceneMgr;
    CamCtrlContext*	_camCtrlContext;
    Graphics*		_gfx;
    Input*		_input;
    Keyboard*		_kbd;
    Mouse*		_mouse;
    ScreenPos*		_prev_mouse_pos;
    ScreenInput*	_screenInput;
    ObjectLoader*	_objectLoader;
    Font*		_font;
    
    bool _drawLabels;
    bool _mouseMoved;
    bool _designer;
    
    std::string	_saveFile;
    std::string	_lastFileLoaded;
    
    void updateStatus();
    
public:
    
    GeocWidget(QWidget* parent = 0, bool designer = false);
    
    ~GeocWidget();
    
    //! Requests a redisplay.
    void redisplay() { updateGL(); }
    
    //! Toggles labels in the scene.
    /*!
     * \param key True if the labels were toggled with a key binding, false otherwise.
     */
    void toggleLabels(bool key = false);
    
    //! Centers the camera.
    void resetCamera();
    
    //! Loads a scene from the given file.
    void loadScene(const char* filename);
    
    //! Loads a scene, prompting the user for the scene file to be loaded.
    void loadScene();
    
    //! Reloads the scene that was last loaded.
    void reloadScene();
    
    //! Saves the widget's scene.
    void saveScene();
    
    //! Saves the widget's scene to the specified file.
    void saveSceneAs();
    
    //! Retrieves the scene manager associated with this widget.
    /**
     * \sa SceneManager
     */
    SceneManager& sceneManager() { return *_sceneMgr; }
    
    //! Retrieves the screen input instance associated with this widget.
    /**
     * \sa ScreenInput
     */
    ScreenInput& screenInput() { return *_screenInput; }
    
    //! Retrieves the object loader associated with this widget.
    /**
     * \sa ObjectLoader
     */
    ObjectLoader& objectLoader() { return *_objectLoader; }
    
    //! Retrieves the graphics instance associated with this widget.
    /**
     * The widget must have been initialised prior to this call.
     * \sa Graphics
     * \sa initializeGL
     */
    Graphics& gfx() { makeCurrent(); return *_gfx; }
    
signals:
    
    //! Emited on every redraw.
    void render();
    
    //! Emited when the camera and input states change.
    void updateStatus(const std::string& camera_mode,
                      const std::string& camera_projection,
                      const std::string& input_desc);
    
    //! Emited when labels are toggled.
    void labelsToggled(GeocWidget& widget, bool key);
    
    //! Emited on every key press.
    void keyPressed(GeocWidget& widget, Keyboard::key key);
    
    //! Emited on every mouse click.
    void mouseClicked(GeocWidget& widget, const ScreenPos& pos, Mouse::button button);
    
    //! Emited on every mouse movement.
    void mouseMoved(GeocWidget& widget, const ScreenPos& old_pos, const ScreenPos& pos);
    
    //! Emited when the user requests the application to exit.
    void requestExit();
    
protected:
    
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void wheelEvent(QWheelEvent* event);
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);
    void handleRequest(char code);
};

} // geoc namespace end


#endif //_GEOC_WIDGET_H
