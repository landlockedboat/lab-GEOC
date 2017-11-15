#ifndef _GEOC_OBJECT_LOADER_H
#define _GEOC_OBJECT_LOADER_H

#include <geoc/geoc.h>
#include "ILoader.h"
#include <list>

namespace geoc {

/** \ingroup Loader */
//! An entity that can handle the loading of elements from a file.
/*!
 * The ObjectLoader is an aggregate of loaders. Attach concrete loaders to the ObjectLoader
 * to add functionality to it.
 * \sa Loader
 */
class DECLDIR ObjectLoader
{
    typedef std::list<ILoader*> LoaderList;
    typedef LoaderList::iterator LoaderList_iterator;
    typedef LoaderList::const_iterator LoaderList_const_iterator;
    
    LoaderList loaders;
    
public:
    
    ~ObjectLoader();
    
    //! Attempts to load elements from the given file stream.
    void load(const char* filename);
    
    //! Attaches a loader to the object loader.
    /*!
     * The object loader takes ownership of the attached loader.
     */
    void attach(ILoader* load);
    
    //! Detaches a loder from the object loader.
    /*!
     * The specified loader is detached and deleted from memory.
     */
    void detach(ILoader* loader);
};


} //namespace geoc

#endif //_GEOC_OBJECT_LOADER_H
