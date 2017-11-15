#ifndef _GEOC_H
#define _GEOC_H

/*
 * Provides several macros which might become handy.
 */

#include <assert.h>
#include <boost/foreach.hpp>
#include <cstdlib>

#define foreach BOOST_FOREACH

#define GEOC_EXCEPTION(what) GeocException(__FILE__, __LINE__, what)

#ifdef _GEOC_DEBUG
#define GEOC_DEBUG_ASSERT(p) assert(p)
#define GEOC_DEBUG_CODE(p) p
#include <cstdio>
#else
#define GEOC_DEBUG_ASSERT(p)
#define GEOC_DEBUG_CODE(p)
#endif

typedef double num;

namespace geoc {

template <class T> inline void safe_free(T*& p) { free((void*)p); p = 0; }
template <class T> inline void safe_delete(T*& p) { delete p; p = 0; }
template <class T> inline void safe_delete_array(T*& p) { delete[] p; p = 0; }

} //namespace geoc

#ifdef _MSC_VER
#ifdef DLL_EXPORT
#define DECLDIR __declspec(dllexport)
#else
#define DECLDIR __declspec(dllimport)
#endif

#define NOMINMAX
#else
#define DECLDIR
#endif

#endif //_GEOC_H
