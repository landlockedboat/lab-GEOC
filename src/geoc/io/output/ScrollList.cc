#include <geoc/io/output/ScrollList.h>

using namespace geoc;
using namespace std;

ScrollList::ScrollList(QWidget* parent) : QListWidget(parent) {}

void ScrollList::write(const char* str)
{
    addItem(QString(str));
    setCurrentItem(item(count() - 1));
}

void ScrollList::write(const string& str)
{
    write(str.c_str());
}

void ScrollList::write(const ostringstream& str)
{
    write(str.str().c_str());
}
