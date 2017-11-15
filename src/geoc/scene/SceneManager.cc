#include <geoc/geoc.h>
#include <geoc/GeocException.h>
#include <geoc/scene/SceneManager.h>
#include <geoc/scene/Entity.h>
#include <geoc/scene/cmd/Command.h>
#include <geoc/gfx/Graphics.h>
#include <geoc/gfx/Font.h>
#include <geoc/gfx/Font.h>
#include <geoc/camera/Camera.h>
#include <geoc/math/BoundingBox.h>
#include <geoc/io/File_utils.h>
#include <cstring>
#include <geoc/gl.h>

#include <cstdio>
#include <iostream>


using namespace geoc;
using namespace std;


const size_t max_command_size = 10;

void writeToFile(const std::string& header, list<const Entity*>& entities, fstream& f);

struct geoc::SceneManager_Impl
{
    list<Entity*>		entities;     // Entities currently drawn on the screen.
    list<Entity*>		all_entities; // All entities in memory (superset of the above).
    list<Command>		commands;
    list<Command>		redo_commands;
    BoundingBox3		bb;
};


SceneManager::SceneManager()
{
    impl = new SceneManager_Impl;
}


SceneManager::~SceneManager()
{
    if (impl)
    {
        foreach (Entity* e, impl->all_entities) delete e;
        safe_delete(impl);
    }
}


void SceneManager::attach(Entity* e)
{
    // Insert it in the scene and create an insert command.
    impl->entities.push_back(e);
    impl->all_entities.push_back(e);
    
    list<Command>& commands = impl->commands;
    if (commands.size() == max_command_size)
    {
        Command& cmd = commands.front();
        if (cmd.type == Command::cmd_delete)
        {
            impl->all_entities.remove(cmd.item);
            leaves(cmd.item);
            delete cmd.item;
        }
        commands.pop_front();
    }
    commands.push_back(Command(Command::cmd_insert, e, impl->entities));
    
    // Update the scene's bounding box.
    impl->bb.add(e->bb().min());
    impl->bb.add(e->bb().max());
    
    // Update the scene's position.
    Spatial::setPosition(impl->bb.center());
}


void SceneManager::attachObserver(Observer<Entity>* o)
{
    Subject<Entity>::attach(o);
}


void SceneManager::detachLast()
{
    // We do not actually delete the item from memory. Instead we create a DeleteCommand
    // holding that item, in case the user wants to undo the deletion operation later on.
    if (impl->entities.empty()) return;
    
    Entity* e = impl->entities.back();
    leaves(e);
    impl->entities.remove(e);
    
    Command cmd = Command(Command::cmd_delete, e, impl->entities);
    list<Command>& commands = impl->commands;
    if (commands.size() == max_command_size)
    {
        Command& c = commands.front();
        if (c.type == Command::cmd_delete)
        {
            impl->all_entities.remove(c.item);
            leaves(c.item);
            delete c.item;
        }
        commands.pop_front();
    }
    commands.push_back(cmd);
}


void SceneManager::undo()
{
    list<Command>& commands = impl->commands;
    if (commands.empty()) return;
    
    // Grab the top command, call its undo method, create the opposite command, store it,
    // and delete the original command from the stack and from memory.
    Command& cmd = commands.back();
    commands.pop_back();
    cmd.undo();
    impl->redo_commands.push_back(cmd);
}


void SceneManager::redo()
{
    list<Command>& redo_commands = impl->redo_commands;
    if (redo_commands.empty()) return;
    
    Command& cmd = redo_commands.back();
    redo_commands.pop_back();
    cmd.redo();
    
    list<Command>& commands = impl->commands;
    if (commands.size() == max_command_size)
    {
        Command& c = commands.front();
        if (c.type == Command::cmd_delete)
        {
            impl->all_entities.remove(c.item);
            leaves(c.item);
            delete c.item;
        }
        commands.pop_front();
    }
    commands.push_back(cmd);
}


void SceneManager::clear()
{
    foreach (Entity* e, impl->all_entities)
    {
        leaves(e);
        delete e;
    }
    impl->entities.clear();
    impl->all_entities.clear();
    impl->commands.clear();
    impl->redo_commands.clear();
    impl->bb = BoundingBox3();
    sceneCleared();
}


void SceneManager::render(Graphics& gfx) const
{
    foreach (Entity* entity, impl->entities)
    {
        entity->draw(gfx);
    }
}


void SceneManager::renderLabels(Font& font, const Camera& cam) const
{
    const num min_size = 0.01;
    num size = cam.zoom() == 0.0 ? min_size : 1.0 / cam.zoom() * 17.0;
    
    font.setSize(size);
    font.startRender();
    
    foreach (Entity* entity, impl->entities)
    {
        Vector3 c = entity->bb().center();
        
        glPushMatrix();
        glTranslatef(c[X], c[Y], c[Z]);
        applyInverseRotation();
        glTranslatef(-c[X], -c[Y], -c[Z]);
        
        glBegin(GL_QUADS);
        entity->drawLabel(font);
        glEnd();
        
        glPopMatrix();
    }
    
    font.endRender();
}


void SceneManager::save(const char* filename) const
{
    fstream f;
    openFile(f, filename, fstream::out);
    
    if (!impl->entities.empty())
    {
        // Write entities in the same order they were read.
        string header;
        string old_header;
        
        list<const Entity*> ents;
        
        foreach (const Entity* e, impl->entities)
        {
            // Group up consecutive elements of the same kind into
            // a single write operation.
            header = e->getHeader();
            if (old_header.empty()) old_header = header;
            
            // Skip empty header entities.
            if (!header.empty())
            {
                if (header.compare(old_header) == 0) ents.push_back(e);
                else if (!ents.empty())
                {
                    // Write the current group.
                    writeToFile(old_header, ents, f);
                    
                    // New group.
                    ents.clear();
                    ents.push_back(e);
                    old_header = header;
                }
            }
        }
        
        // Write the last group.
        if (!ents.empty()) writeToFile(old_header, ents, f);
    }
    
    f.close();
}


Vector3 SceneManager::center() const
{
    return impl->bb.center();
}


const Vector3& SceneManager::min() const
{
    return impl->bb.min();
}


const Vector3& SceneManager::max() const
{
    return impl->bb.max();
}


num SceneManager::width() const
{
    return impl->bb.max()[X] - impl->bb.min()[X];
}


num SceneManager::height() const
{
    return impl->bb.max()[Y] - impl->bb.min()[Y];
}


num SceneManager::depth() const
{
    return impl->bb.max()[Z] - impl->bb.min()[Z];
}


num SceneManager::radius() const
{
    return (impl->bb.max() - impl->bb.min()).norm() * 0.5;
}


bool SceneManager::empty() const
{
    return impl->all_entities.empty();
}


void writeToFile(const std::string& header, list<const Entity*>& entities, fstream& f)
{
    f << header << endl;
    
    foreach (const Entity* entity, entities)
    {
        f << *entity << endl;
    }
}
