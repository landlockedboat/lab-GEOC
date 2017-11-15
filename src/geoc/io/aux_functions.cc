#include <geoc/io/aux_functions.h>
#include <geoc/math/Vector.h>
#include <iostream>
#include <cstdlib>
#include <cmath>


using namespace geoc;
using namespace std;


void geoc::read_vector3(std::istream& is, Vector3& v)
{
    if (!is.good()) return;
    
    // Skip leading white space.
    char k = is.peek();
    while (k == '\r' || k == '\n' || k == '\t' || k == ' ')
    {
        is.get();
        k = is.peek();
    }
    
    // If we reach EOF, there is no data to parse => read fails.
    if (is.eof())
    {
        is.setstate(ios::failbit);
        return;
    }
    
    num vals[] = {0, 0, 0};
    
    int i = 0;
    num val = 0;
    num dec = 0;
    num mult = 1;
    num sign = 1;
    num exp_val = 0;
    num exp_sign = 1;
    bool period = false;
    bool exp = false;
    char c;
    for (;;)
    {
        c = is.get();
        if (c == ' ' || c == '\n' || is.eof())
        {
            if (exp)    vals[i] = (sign * (val + dec / mult)) * pow(10, exp_sign * exp_val);
            else        vals[i] = sign * (val + dec / mult);
            val = 0;
            dec = 0;
            mult = 1;
            sign = 1;
            exp_val = 0;
            exp_sign = 1;
            period = false;
            exp = false;
            i++;
            
            if (c == '\n' || is.eof()) break;
        }
        else if (c == '.')
        {
            period = true;
        }
        else if (c == '-')
        {
            if (exp)    exp_sign = -1;
            else        sign = -1;
        }
        else if (c >= '0' && c <= '9')
        {
            if (period)
            {
                mult *= 10;
                dec *= 10;
                dec = dec + c - '0';
            }
            else if (exp)
            {
                exp_val *= 10;
                exp_val = exp_val + c - '0';
            }
            else
            {
                val *= 10;
                val = val + c - '0';
            }
        }
        else if (c == 'e')
        {
            exp = true;
            period = false;
        }
        else if (c != '\r' && c != '+')
        {
            is.setstate(ios::failbit);
            return;
        }
    }
    
    v[0] = vals[0];
    v[1] = vals[1];
    v[2] = vals[2];
    
    // Skip trailing whitespace.
    c = is.peek();
    while (c == '\r' || c == '\n' || c == '\t' || c == ' ')
    {
        is.get();
        c = is.peek();
    }
    
    if (is.eof()) is.clear(ios::eofbit);
}


void geoc::write_vector3(std::ostream& os, const Vector3& v)
{
    os << v[0] << " " << v[1];
    if (v[2]) os << " " << v[2];
}
