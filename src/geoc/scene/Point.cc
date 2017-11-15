#include <geoc/scene/Point.h>
#include <geoc/gfx/Graphics.h>
#include <geoc/gfx/Font.h>
#include <geoc/io/aux_functions.h>

using namespace geoc;
using namespace std;


Point::Point(const Vector3& position, const Colour3& color) : pos(position), box(BoundingBox3(&pos, &pos+1)), colour(color) {}


Point::Point(num x, num y, num z, num r, num g, num b) : pos(Vector3(x,y,z)), box(BoundingBox3(&pos, &pos+1)), colour(Vector3(r,g,b)) {}


const num& Point::operator[](int coord) const
{
    GEOC_DEBUG_ASSERT(coord >= 0 && coord <= 2);
    return pos[coord];
}


void Point::draw(Graphics& gfx) const
{
    gfx.drawPoint(this);
}


void Point::drawLabel(const Font& font) const
{
    if (!label.empty()) font.draw3D(pos, label);
}


void Point::setLabel(const std::string& label)
{
    this->label = label;
}


void Point::read(std::istream& is, Point& p)
{
    Vector3 v;
    read_vector3(is, v);
    p = Point(v);
}


void Point::write(std::ostream& os) const
{
    const Point& p = *this;
    os << "( " << p[X] << ", " << p[Y] << ", " << p[Z] << ")";
}

void Point::write(std::fstream& fs) const
{
    write_vector3(fs, pos);
}
