#include <geoc/io/output/FileOutput.h>
#include <geoc/io/File_utils.h>

using namespace geoc;
using namespace std;

FileOutput::FileOutput(const char* filename)
{
    openFile(f, filename, fstream::out);
}

FileOutput::~FileOutput()
{
    f.close();
}

void FileOutput::write(const char* str)
{
    f << str << endl;
}

void FileOutput::write(const std::string& str)
{
    write(str.c_str());
}

void FileOutput::write(const std::ostringstream& str)
{
    write(str.str().c_str());
}
