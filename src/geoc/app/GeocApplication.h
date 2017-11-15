#ifndef _GEOC_APPLICATION_H
#define _GEOC_APPLICATION_H

#include <geoc/geoc.h>
#include <geoc/io/input/Keyboard.h>
#include <geoc/io/input/Mouse.h>
#include <geoc/math/Vector_fwd_decl.h>
#include <QMainWindow>
#include <string>

namespace geoc {

class GeocWidget;
class ObjectLoader;
class OutputSystem;
class ScrollList;

/** \ingroup App */
//! Base application class for viewer applications.
/*!
 * This class is just a handy way to quickly write a viewer application.
 * Simply derive this class and override its hooks to add functionality.
 */
class DECLDIR GeocApplication : public QMainWindow
{
    Q_OBJECT
    
    GeocWidget*	    _geocWidget;
    OutputSystem*   _outputSystem;
    ScrollList*	    _scrollList;
    QStatusBar*	    _statusBar;
    QMenuBar*	    _menuBar;
    QAction*	    _labels;
    
    bool _mouseMoved;
    bool _drawLabels;
    
private:
    
    GeocApplication(const GeocApplication&) : QMainWindow() {}
    void operator=(const GeocApplication&) {}
    
public:
    
    GeocApplication(QWidget* parent = NULL);
    virtual ~GeocApplication();
    
    //! Sets up the application.
    /*!
     * \param argc The number of arguments.
     * \param argv An array of pointers to each of the arguments.
     * \param width The desired screen width.
     * \param height The desired screen height.
     */
    void setup(int argc, char** argv, int width = 640, int height = 560);
    
    //! Gets the output subsystem associated with this application.
    /*!
     * \sa OutputSystem
     */
    OutputSystem& outputSystem() const { return *_outputSystem; }
    
protected: // Qt functions.
    
    void keyPressEvent(QKeyEvent* event);
    void closeEvent(QCloseEvent* event);
    
protected: // Helper functions.
    
    //! Loads a scene from the given file.
    void loadScene(const char* filename);
    
    //! Requests a redisplay.
    void redisplay();
    
    //! Retrieves the geoc widget associated with this application.
    GeocWidget& geocWidget() { return *_geocWidget; }
    
protected: // Hooks.
    
    //! Hook called upon initialisation.
    /*!
     * \param int The number of arguments in the arguments array.
     * \param char** An array of pointers to each argument.
     */
    virtual void init(int, char**) {}
    
    //! Hook called upon exit.
    virtual void shutdown() {}
    
protected slots:
    
    //! Hook called to render the scene.
    virtual void render() {}
    
    //! Updates the status bar.
    void updateStatusBar(const std::string& camera_mode,
                         const std::string& camera_projection,
                         const std::string& input_desc);
    
    //! Updates the labels checkbox.
    /*!
     * \param GeocWidget The GeocWidget that triggered the event.
     * \param key True if the toggle was triggered with a key binding, false otherwise.
     */
    void labelsToggled(GeocWidget&, bool key);
    
    //! Processes a key press event.
    /*!
     * \param GeocWidget The GeocWidget that triggered the event.
     * \param key The pressed key.
     */
    virtual void keyPressed(GeocWidget&, Keyboard::key) {}
    
    //! Processes a mouse click event.
    /*!
     * \param GeocWidget The GeocWidget that triggered the event.
     * \param ScreenPos The position on the screen where the mouse was clicked.
     * \param button The clicked button.
     */
    virtual void mouseClicked(GeocWidget&, const ScreenPos&, Mouse::button) {}
    
    //! Processes a mouse move event.
    /*!
     * \param GeocWidget The GeocWidget that triggered the event.
     * \param ScreenPos The old mouse position.
     * \param ScreenPos The new mouse position.
     */
    virtual void mouseMoved(GeocWidget&, const ScreenPos&, const ScreenPos&) {}
    
    //! Quits the application.
    void quit();
    
    //! Loads a scene, prompting the user for the scene file to be loaded.
    void loadScene();
    
    //! Reloads the previously loaded scene file.
    /*!
    * loadScene() must have been called prior to calling this method.
    * \sa loadScene
    */
    void reloadScene();
    
    //! Saves the scene to a file.
    void saveScene();
    
    //! Saves the scene to a file.
    void saveSceneAs();
    
    //! Shows the about dialog.
    void showAbout();
    
    //! Toggles labels in the scene.
    void toggleLabels();
};

} //geoc namespace end


#endif //_GEOC_APPLICATION_H
