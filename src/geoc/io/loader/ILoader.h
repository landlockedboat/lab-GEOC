#ifndef _GEOC_ILOADER_H
#define _GEOC_ILOADER_H

#include <geoc/geoc.h>

namespace geoc {


/** \ingroup Loader */
enum GEOC_LOADER_CODE
{
	GEOC_LOADER_SUCCESS, GEOC_LOADER_UNEXPECTED_INPUT, GEOC_LOADER_ERROR
};
	
	
/** \ingroup Loader */
//! An interface for all concrete loaders.
class DECLDIR ILoader
{
public:
	
	virtual ~ILoader() {}
    
    //! Loads elements from the given file stream.
	virtual GEOC_LOADER_CODE load(std::fstream& f) = 0;
};


} // geoc namespace end


#endif // _GEOC_ILOADER_H
