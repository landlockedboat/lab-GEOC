#ifndef _GEOC_LOADER_H
#define _GEOC_LOADER_H

#include <geoc/geoc.h>
#include "ILoader.h"
#include <geoc/io/Subject.h>
#include <fstream>
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/functional/factory.hpp>

namespace geoc {


/** \ingroup Loader */
//! An entity that can load elements from a file.
template <class T>
class Loader :	public ILoader, public Subject<T>
{
    typedef boost::function<void (std::istream&, T&)> load_t;
    typedef boost::function<T* ()> cons_t;
    cons_t cons_f;
    load_t load_f;
    
public:
    
    Loader(cons_t cons = boost::factory<T*>(), load_t load = boost::bind(&T::read, _1, _2)) : cons_f(cons), load_f(load) {}
    
    //! Loads elements of type T from the given file stream.
    /**
     * Observers attached to the Loader are notified about the elements read.
     */
    GEOC_LOADER_CODE load(std::fstream& f);
};


} //namespace geoc

#include "Loader.cc"

#endif //_GEOC_LOADER_H
