#include <geoc/scene/TriangleEnt.h>
#include <geoc/gfx/Graphics.h>
#include <geoc/gfx/Font.h>
#include <geoc/math/Math.h>
#include <geoc/io/aux_functions.h>


using namespace geoc;
using namespace std;


bool TriangleEnt::operator==(const TriangleEnt& t) const
{
    return Triangle::operator==(t);
}


void TriangleEnt::draw(Graphics& gfx) const
{
    gfx.drawTriangle(this);
}


void TriangleEnt::drawLabel(const Font& font) const
{
    if (!label.empty())
    {
        const TriangleEnt& t = *this;
        Vector3 pos = (t[0] + t[1] + t[2]) / 3;
        font.draw3D(pos, label);
    }
}


void TriangleEnt::setLabel(const std::string& label)
{
    this->label = label;
}


void TriangleEnt::read(std::istream& is, TriangleEnt& t)
{
    Vector3 v1, v2, v3;
    read_vector3(is, v1);
    read_vector3(is, v2);
    read_vector3(is, v3);
    (Triangle&)t = Triangle(v1, v2, v3);
}


void TriangleEnt::write(std::ostream& os) const
{
    const Triangle& t = *this;
    os << "[" << t[0] << ", " << t[1] << ", " << t[2] << "]";
}

void TriangleEnt::write(std::fstream& fs) const
{
    const Triangle& t = *this;
    write_vector3(fs, t[0]);
    fs << endl;
    write_vector3(fs, t[1]);
    fs << endl;
    write_vector3(fs, t[2]);
    fs << endl;
}

