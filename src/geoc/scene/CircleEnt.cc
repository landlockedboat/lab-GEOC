#include <geoc/scene/CircleEnt.h>
#include <geoc/scene/Point.h>
#include <geoc/gfx/Graphics.h>
#include <geoc/gfx/Font.h>
#include <geoc/math/Math.h>
#include <geoc/io/aux_functions.h>


using namespace geoc;
using namespace std;


CircleEnt::CircleEnt(const Vector3& v1, const Vector3& v2, const Vector3& v3, const Colour3& col) : Circle(v1,v2,v3), colour(col)
{
    box.add(v1);
    box.add(v2);
    box.add(v3);
}


CircleEnt::CircleEnt(const Circle& c) : Circle(c)
{
    box.add(c[0]);
    box.add(c[1]);
    box.add(c[2]);
}


void CircleEnt::draw(Graphics& gfx) const
{
    gfx.drawCircle(this);
}


void CircleEnt::drawLabel(const Font& font) const
{
    //Maybe draw the label at the circle's center?
    const CircleEnt& c = *this;
    Vector3 pos = (c[0] + c[1] + c[2]) / 3;
    font.draw3D(pos, label);
}


void CircleEnt::setLabel(const std::string& label)
{
    this->label = label;
}


void CircleEnt::read(std::istream& is, CircleEnt& c)
{
    Vector3 v1, v2, v3;
    read_vector3(is, v1);
    read_vector3(is, v2);
    read_vector3(is, v3);
    c = CircleEnt(v1,v2,v3);
}


void CircleEnt::write(std::ostream& os) const
{
    const CircleEnt& c = *this;
    os << c[0] << std::endl << c[1] << std::endl << c[2];
}


void CircleEnt::write(std::fstream& fs) const
{
    const CircleEnt& c = *this;
    fs << "c" << endl;
    write_vector3(fs, c[0]);
    fs << endl;
    write_vector3(fs, c[1]);
    fs << endl;
    write_vector3(fs, c[2]);
    fs << endl;
}

