#ifndef _GEOC_LOADER_METHODS_CC
#define _GEOC_LOADER_METHODS_CC


#include <geoc/geoc.h>
#include "Loader.h"
#include <geoc/io/File_utils.h>
#include <string>

namespace geoc {


template <class T>
GEOC_LOADER_CODE Loader<T>::load(std::fstream& f)
{
    using std::string;
    using std::fstream;
    
    //Read the section header.
    string sectionHeader;
    //f >> sectionHeader;
    readString(f, sectionHeader);
    
    if (f.fail()) return GEOC_LOADER_ERROR;
    
    //Check the value of the section header, then read elements.
    if (sectionHeader.compare(T::header()) == 0)
    {
        //Skip any possible comment.
        skipLine(f);
        
        do
        {
            T* t = cons_f();
            
            int pos = f.tellg();
            
            //Read the next element.
            load_f(f, *t);
            
            if (f.bad())
            {
                delete t;
                return GEOC_LOADER_ERROR;
            }
            
            if (f.fail()) //We reach the start of another section.
            {
                f.clear();
                f.seekg(pos);
                
                delete t;
                return GEOC_LOADER_SUCCESS;
            }
            
            //Send it to our observers.
            Subject<T>::enters(t);
        }
        while (!f.eof());
        
        return GEOC_LOADER_SUCCESS;
    }
    
    return GEOC_LOADER_UNEXPECTED_INPUT;
}


} //namespace geoc

#endif //_GEOC_LOADER_METHODS_CC
