#include <geoc/io/output/ConsoleOutput.h>
#include <iostream>

using namespace geoc;
using namespace std;


void ConsoleOutput::write(const char* str)
{
    cout << str << endl;
}


void ConsoleOutput::write(const std::string& str)
{
    cout << str << endl;
}


void ConsoleOutput::write(const std::ostringstream& str)
{
    cout << str << endl;
}
