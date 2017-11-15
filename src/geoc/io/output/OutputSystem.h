#ifndef _GEOC_OUTPUT_SYSTEM_H
#define _GEOC_OUTPUT_SYSTEM_H

#include <geoc/geoc.h>
#include "OutputStream.h"
#include <list>

namespace geoc {

/** \ingroup Output */
//! The output subsystem.
/*!
 * The output subsystem provides the means to write a string to multiple streams
 * in an easy manner.
 */
class DECLDIR OutputSystem : public OutputStream
{
    std::list<OutputStream*>	streams;
    
public:
    
    ~OutputSystem();
    
    //! Attaches an output stream to the output system.
    /*!
     * The OutputSystem takes ownership of the given OutputStream.
     * \sa OutputStream
     */
    void attach(OutputStream* stream);
    
    //! Detaches an output stream from the output system.
    /**
     * \sa OutputStream
     */
    void detach(OutputStream* stream);
    
    //! Writes the given C string to all output streams.
    void write(const char* str);
    
    //! Writes the given string to all output streams.
    void write(const std::string& str);
    
    //! Writes the given ostringstream to all output streams.
    void write(const std::ostringstream& str);
};

} //namespace geoc

#endif //_GEOC_OUTPUT_SYSTEM_H
