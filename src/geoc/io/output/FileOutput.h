#ifndef _GEOC_FILE_OUTPUT_H
#define _GEOC_FILE_OUTPUT_H

#include <geoc/geoc.h>
#include "OutputStream.h"
#include <fstream>

namespace geoc {

/** \ingroup Output */
//! A stream for writing text to a file.
class DECLDIR FileOutput : public OutputStream
{
    std::fstream f;
    
public:
    
    FileOutput(const char* filename);
    ~FileOutput();
    
    void write(const char* str);
    void write(const std::string& str);
    void write(const std::ostringstream& str);
};

} //namespace geoc

#endif //_GEOC_FILE_OUTPUT_H
