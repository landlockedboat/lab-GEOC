#ifndef _GEOC_IO_AUX_FUNCTIONS_H
#define _GEOC_IO_AUX_FUNCTIONS_H

#include <geoc/geoc.h>
#include <geoc/math/Vector_fwd_decl.h>
#include <iosfwd>

namespace geoc {

/** \ingroup IO */
//! Reads a Vector3 from the given input stream.
/*!
 * This will attempt to read three coordinates from the supplied input stream.
 * If, however, a newline character is found before reading the third coordinate, the coordinate is set to 0.
 */
DECLDIR void read_vector3(std::istream& is, Vector3& v);

/** \ingroup IO */
//! Writes a Vector3 to the given output stream.
/*!
 * The Z coordinate will not be written if it is equal to 0.
 */
DECLDIR void write_vector3(std::ostream& os, const Vector3& v);

} //namespace geoc

#endif //_GEOC_IO_AUX_FUNCTIONS_H
