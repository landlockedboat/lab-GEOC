#ifndef _GEOC_COMMAND_H
#define _GEOC_COMMAND_H

#include <geoc/geoc.h>
#include <list>

namespace geoc {

class Entity;

/** \ingroup Scene */
//! Represents a scene command.
/*!
 * A command can be either an insertion or a deletion command.
 */
class Command
{
    std::list<Entity*>&	items;
    
public:
    enum cmd_type { cmd_insert, cmd_delete };
    
    Entity*				item;
    cmd_type			type;
    
public:
    Command(cmd_type t, Entity* e, std::list<Entity*>& es) : items(es), item(e), type(t) {}
    
    //! Undoes the command's operation.
    void undo();
    
    //! Applies the command's operation.
    void redo();
};

} //namespace geoc

#endif //_GEOC_COMMAND_H
