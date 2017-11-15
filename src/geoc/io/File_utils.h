#ifndef _GEOC_FILE_UTILS_H
#define _GEOC_FILE_UTILS_H

#include <geoc/geoc.h>
#include <fstream>

namespace geoc {

/** \ingroup IO */
//! Opens the given file.
DECLDIR void openFile(std::fstream& f, const char* filename, std::fstream::openmode flags = std::fstream::in | std::fstream::out);

/** \ingroup IO */
//! Gets the current line number of the given file stream.
DECLDIR int getLineNumber(std::fstream& f);

/** \ingroup IO */
//! Gets the position within the current line of the given file stream.
DECLDIR int getLinePosition(std::fstream& f);

/** \ingroup IO */
//! Skips a line in the given file stream.
DECLDIR void skipLine(std::fstream& f);

/** \ingroup IO */
//! Reads a string from the given file stream.
DECLDIR void readString(std::fstream& f, std::string& s);

}

#endif //_GEOC_FILE_UTILS_H
