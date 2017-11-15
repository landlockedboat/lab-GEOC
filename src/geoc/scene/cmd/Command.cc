#include <geoc/geoc.h>
#include <geoc/scene/cmd/Command.h>


using namespace geoc;


void Command::undo()
{
    switch (type)
    {
    case cmd_insert:
        items.remove(item);
        break;
        
    case cmd_delete:
        items.push_back(item);
        break;
    }
}


void Command::redo()
{
    switch (type)
    {
    case cmd_insert:
        items.push_back(item);
        break;
        
    case cmd_delete:
        items.remove(item);
        break;
    }
}
