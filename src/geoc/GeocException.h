#ifndef _GEOC_EXCEPTION_H
#define _GEOC_EXCEPTION_H

#include <geoc/geoc.h>
#include <exception>
#include <sstream>

namespace geoc {

//! Represents framework exceptions.
/*!
 * The file geoc/geoc.h provides the following macro for throwing exceptions:
 * 
 * #define GEOC_EXCEPTION(what) GeocException(__FILE__, __LINE__, what)
 */
class DECLDIR GeocException : public std::exception
{
    char* mWhat;
    
    void buildErrorString(const char* file, int line, const char* what);
    
public:
    
    //! Builds an exception from a C string.
    GeocException(const char* what) throw();
    
    //! Builds an exception from an ostringstream.
    GeocException(const std::ostringstream& what) throw();
    
    //! Builds an exception from a C string with file and line information.
    GeocException(const char* file, int line, const char* what) throw();
    
    //! Builds an exception from an ostringstream with file and line information.
    GeocException(const char* file, int line, const std::ostringstream& what) throw();
    
    virtual ~GeocException() throw();
    
    //! Gets the description for the exception.
    const char* what() const throw();
};

} //namespace geoc

#endif //_GEOC_EXCEPTION_H
