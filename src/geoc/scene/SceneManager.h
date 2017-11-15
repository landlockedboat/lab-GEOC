#ifndef _GEOC_SCENE_MANAGER_H
#define _GEOC_SCENE_MANAGER_H

#include <geoc/geoc.h>
#include <geoc/io/Subject.h>
#include <geoc/math/Spatial.h>

namespace geoc {

struct SceneManager_Impl;
class Entity;
class Graphics;
class Camera;
class Font;
template <class T> class Observer;

/** \ingroup Scene */
//! Handles the scene.
class DECLDIR SceneManager : public Spatial, public Subject<Entity>	//Inherit from subject to notify observers when an entity leaves the scene.
{
    SceneManager_Impl* impl;	// Pimpl
    
    SceneManager& operator= (const SceneManager&);
    SceneManager(const SceneManager&);
    
public:
    
    SceneManager();
    ~SceneManager();
    
    //! Adds the given entity to the scene.
    /*!
     * The attached entity will be drawn on the screen on future redisplays.
     */
    void attach(Entity* e);
    
    //! Attaches the given entity observer to the scene manager.
    /*!
     * Entity observers will be notified when an entity leaves the scene.
     */
    void attachObserver(Observer<Entity>* o);
    
    //! Removes the last entity added to the scene.
    void detachLast();
    
    //! Clears the scene.
    void clear();
    
    //! Undoes the last operation.
    void undo();
    
    //! Undoes the last undo operation.
    void redo();
    
    //! Renders the scene.
    void render(Graphics& gfx) const;
    
    //! Renders the labels in the scene.
    void renderLabels(Font& font, const Camera& cam) const;
    
    //! Saves the scene to the file specified by the given string.
    void save(const char* filename) const;
    
    //! Returns the scene's center.
    Vector3 center() const;
    
    //! Returns the scene's min point.
    const Vector3& min() const;
    
    //! Returns the scene's max point.
    const Vector3& max() const;
    
    //! Returns the scene's width.
    num width() const;
    
    //! Returns the scene's height.
    num height() const;
    
    //! Returns the scene's depth.
    num depth() const;
    
    //! Returns the scene's radius.
    num radius() const;
    
    //! Returns true if the scene is empty, false otherwise.
    /**
     * A scene is empty if the SceneManager has no Entity objects attached to it.
     */
    bool empty() const;
};

} //namespace geoc

#endif //_GEOC_SCENE_MANAGER_H
