#ifndef _GEOC_OUTPUT_STREAM_H
#define _GEOC_OUTPUT_STREAM_H

#include <string>
#include <sstream>

namespace geoc {

/** \ingroup Output */
//! An interface for all output streams.
class DECLDIR OutputStream
{
public:
    
    virtual ~OutputStream() {}
    
    //! Writes the given C string to the output stream.
    virtual void write(const char* str) = 0;
    
    //! Writes the given string to the output stream.
    virtual void write(const std::string& str) = 0;
    
    //! Writes the given ostringstream to the output stream.
    virtual void write(const std::ostringstream& str) = 0;
};

} //namespace geoc

#endif //_GEOC_OUTPUT_STREAM_H
