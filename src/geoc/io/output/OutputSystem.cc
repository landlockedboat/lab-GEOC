#include <geoc/io/output/OutputSystem.h>

using namespace geoc;
using namespace std;

typedef list<OutputStream*>::iterator Stream;

OutputSystem::~OutputSystem()
{
    foreach (OutputStream* stream, streams)
    {
        if (stream) safe_delete(stream);
    }
    streams.clear();
}

void OutputSystem::attach(OutputStream* stream)
{
    streams.push_front(stream);
}

void OutputSystem::detach(OutputStream* stream)
{
    streams.remove(stream);
}

void OutputSystem::write(const char* str)
{
    foreach (OutputStream* stream, streams)
    {
        stream->write(str);
    }
}

void OutputSystem::write(const std::string& str)
{
    write(str.c_str());
}

void OutputSystem::write(const std::ostringstream& str)
{
    write(str.str().c_str());
}
