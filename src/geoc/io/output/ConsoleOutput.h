#ifndef _GEOC_CONSOLE_OUTPUT_H
#define _GEOC_CONSOLE_OUTPUT_H

#include <geoc/geoc.h>
#include "OutputStream.h"

namespace geoc {

/** \ingroup Output */
//! A stream for writing text to the console.
class DECLDIR ConsoleOutput : public OutputStream
{
public:
    
    ConsoleOutput();
    
    void write(const char* str);
    void write(const std::string& str);
    void write(const std::ostringstream& str);
};

} //namespace geoc

#endif //_GEOC_CONSOLE_OUTPUT_H
