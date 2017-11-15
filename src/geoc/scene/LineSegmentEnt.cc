#include <geoc/scene/LineSegmentEnt.h>
#include <geoc/gfx/Graphics.h>
#include <geoc/gfx/Font.h>
#include <geoc/math/Math.h>
#include <geoc/io/aux_functions.h>


using namespace geoc;
using namespace std;


LineSegmentEnt::LineSegmentEnt(const Vector3& p1, const Vector3& p2, const Colour3& col) : LineSegment(p1,p2), colour(col)
{
    box.add(p1);
    box.add(p2);
}


LineSegmentEnt::LineSegmentEnt(const LineSegment& s) : LineSegment(s)
{
    box.add(s[0]);
    box.add(s[1]);
}


void LineSegmentEnt::draw(Graphics& gfx) const
{
    gfx.drawSegment(this);
}


void LineSegmentEnt::drawLabel(const Font& font) const
{
    if (!label.empty())
    {
        const LineSegmentEnt& s = *this;
        Vector3 pos = (s[0] + s[1]) / 2;
        font.draw3D(pos, label);
    }
}


void LineSegmentEnt::setLabel(const std::string& label)
{
    this->label = label;
}


void LineSegmentEnt::read(std::istream& is, LineSegmentEnt& s)
{
    Vector3 v1, v2;
    read_vector3(is, v1);
    read_vector3(is, v2);
    s = LineSegmentEnt(v1, v2);
}


void LineSegmentEnt::write(std::ostream& os) const
{
    const LineSegmentEnt& s = *this;
    os << s[0] << " - " << s[1];
}


void LineSegmentEnt::write(std::fstream& fs) const
{
    const LineSegmentEnt& s = *this;
    write_vector3(fs, s[0]);
    fs << endl;
    write_vector3(fs, s[1]);
    fs << endl;
}
