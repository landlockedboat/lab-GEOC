#include <geoc/geoc.h>
#include <geoc/GeocException.h>
#include <stdio.h>	//fprintf
#include <string.h>	//strlen
#include <stdlib.h>	//malloc
#include <errno.h>	//errno, strerror etc.
#include <sstream>	//ostringstream
#include <string>	//string


using namespace geoc;
using namespace std;


void GeocException::buildErrorString(const char* file, int line, const char* what)
{
    int whatLen = 0;
    int fileLen = 0;
    
    mWhat = 0;
    
    if (file)
    {
        fileLen = strlen(file);
    }
    whatLen = strlen(what);
    
    mWhat = (char*)malloc(fileLen + whatLen + 16 + 1);
    if (!mWhat)
    {
        mWhat = (char*)"Could not build exception string";
    }
    else
    {
        if (file && line)	sprintf(mWhat, "File: %s Line %d:\n%s", file, line, what);
        else				sprintf(mWhat, "%s", what);
    }
}


GeocException::GeocException(const char* what) throw()
{
    buildErrorString(0, 0, what);
}


GeocException::GeocException(const std::ostringstream& what) throw()
{
    buildErrorString(0, 0, what.str().c_str());
}


GeocException::GeocException(const char* file, int line, const char* what) throw()
{
    buildErrorString(file, line, what);
}


GeocException::GeocException(const char* file, int line, const std::ostringstream& what) throw()
{
    buildErrorString(file, line, what.str().c_str());
}


GeocException::~GeocException() throw()
{
    if (mWhat) safe_free(mWhat);
}


const char* GeocException::what() const throw()
{
    return mWhat;
}
