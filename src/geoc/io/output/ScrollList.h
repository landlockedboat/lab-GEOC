#ifndef _GEOC_SCROLL_LIST_H
#define _GEOC_SCROLL_LIST_H

#include <geoc/geoc.h>
#include <geoc/io/output/OutputStream.h>
#include <QListWidget>

namespace geoc {

/** \ingroup Output */
//! A scroll list kind of output stream.
class ScrollList : public OutputStream, public QListWidget
{
public:
    
    ScrollList(QWidget* parent = 0);
    
    //! Adds a line to the scroll list.
    void write(const char* str);
    
    //! Adds a line to the scroll list.
    void write(const std::string& str);
    
    //! Adds a line to the scroll list.
    void write(const std::ostringstream& str);
};

} //namespace geoc

#endif //_GEOC_SCROLL_LIST_H
