#include <geoc/io/File_utils.h>
#include <geoc/GeocException.h>
#include <sstream>

using namespace geoc;
using namespace std;


void geoc::openFile(std::fstream& f, const char* filename, std::fstream::openmode flags)
{
    f.open(filename, flags);
    if (!f.is_open())
    {
        //Create the file and attempt to open it again.
        ofstream of(filename, flags);
        of.close();
        
        f.open(filename, flags);
        if (!f.is_open())
        {
            std::ostringstream s;
            s << "Unable to open file " << filename;
            throw GEOC_EXCEPTION(s);
        }
    }
}


int geoc::getLineNumber(std::fstream& f)
{
    streampos pos = f.tellg();
    f.seekg(0);
    
    char c;
    int line = 1;
    for (int i = 0; i < pos; ++i)
    {
        f.get(c);
        if (c == '\n') line++;
    }
    
    return line;
}


int geoc::getLinePosition(std::fstream& f)
{
    streampos start = f.tellg();
    
    char c;
    f.get(c);
    
    int pos = 0;
    while (c != '\n' && f.tellg() > 0)
    {
        f.seekg(-2, ios::cur);
        f.get(c);
        pos++;
    }
    
    f.seekg(start);
    
    return pos;
}


void geoc::skipLine(std::fstream& f)
{
    char c;
    do
    {
        f.get(c);
    }
    while (c != '\n');
}


void geoc::readString(std::fstream& f, std::string& s)
{
    using namespace std;
    
    // Skip leading white space.
    char c = f.peek();
    while (c == '\r' || c == '\n' || c == '\t' || c == ' ')
    {
        f.get();
        c = f.peek();
    }
    
    while (!f.eof() && (c != '\r' && c != '\n' && c != '\t' && c != ' '))
    {
        s.push_back(f.get());
        c = f.peek();
    }
}
