#include <geoc/scene/TriangulationEnt.h>
#include <geoc/io/aux_functions.h>
#include <geoc/math/Math.h>
#include <geoc/gfx/Graphics.h>
#include <geoc/gfx/Font.h>
#include <geoc/io/Timer.h>
#include <algorithm>
#include <istream>
#include <string>
#include <list>
#include <map>
#include <vector>
#include <geoc/gl.h>
#include <iostream>
#include <cstdio>
#include <sstream>


using namespace geoc;
using namespace std;


Colour3 computeColour(const Colour3& colour, num height, num factor);


class CompareVec3
{
public:
    bool operator() (const Vector3& lhs, const Vector3& rhs) const
    {
        if (lhs[X] < rhs[X]) return true;
        if (lhs[X] > rhs[X]) return false;
        if (lhs[Y] < rhs[Y]) return true;
        if (lhs[Y] > rhs[Y]) return false;
        if (lhs[Z] < rhs[Z]) return true;
        return false;
    }
};


void TriangulationEnt::read(std::istream& is, TriangulationEnt& t)
{
    using namespace std;
    
    Timer timer;
    timer.start();
    
    streampos start = is.tellg();
    is.seekg(0, ios::end);
    //streampos end = is.tellg();
    is.seekg(start, ios::beg);
    //int length = end - start;
    
    //vector<char> buf(length);
    //is.read(&buf[0], length);
    
    stringstream ss;
    //ss.rdbuf()->pubsetbuf(&buf[0], length);
    ss << is.rdbuf();
    
    vector<Vector3> pts;
    vector<int> idxs;
    
    // Read vectors.
    Vector3 v;
    streampos pos;
    
    for(;;)
    {
        pos = ss.tellg();
        
        read_vector3(ss, v);
        
        if (!ss.good()) break;
        
        t.m_bb.add(v);
        pts.push_back(v);
    }
    
    if (ss.bad() || pts.size() == 0) return;
    
    if (!ss.eof())
    {
        ss.clear();
        ss.seekg(pos);
        
        // We reached the boundary section. Read the header and then parse indices.
        string header;
        ss >> header;
        if (ss.good())
        {
            // Parse indices.
            int index;
            for(;;)
            {
                pos = ss.tellg();
                ss >> index;
                
                if (!ss.good()) break;
                
                idxs.push_back(index);
            }
        }
        
        if (ss.bad()) return;
        ss.clear(ss.rdstate() & ~ios::failbit);
        ss.seekg(pos);
    }
    
    timer.tick();
    printf("Reading time: %fs\n", timer.getDeltaTime());
    
    timer.tick();
    t.triang->triangulate(pts, idxs, t.segments, t.triangles, t.triangles_pruned);
    timer.tick();
    
    printf("Triangulation time: %fs\n", timer.getDeltaTime());
    cout << pts.size() << " points read, " << idxs.size() << " indices read" << endl;
    
    is.clear((is.rdstate() & ~ios::failbit) | ios::eofbit);
}


TriangulationEnt::~TriangulationEnt()
{
    for (int i = 0; i < nDrawModes; ++i)
    {
        if (geometry[i] > -1) gfx->deleteStaticGeometry(geometry[i]);
        geometry[i] = -1;
    }
}


void TriangulationEnt::prepare(Graphics* gfx, bool enable_3d)
{
    this->gfx = gfx;	// Save the gfx instance so that we can later delete the allocated static geometry
    // when the class dtor is called.
    
    if (!triangles_pruned.empty())
    {
        // Produce a pruned 2D triangulation.
        geometry[TRIANGULATION_2D_PRUNED] = gfx->createStaticGeometry(&triangles_pruned[0], triangles_pruned.size(), 0, 0, true);
        
        if (enable_3d)
        {
            vector<Vector3> normals, colours;
            normals.reserve(triangles_pruned.size() * 3);
            colours.reserve(triangles_pruned.size() * 3);
            
            // Produce a rough, gray 3D triangulation.
            foreach (TriangleEnt& t, triangles_pruned)
            {
                Vector3 n = normal(t);
                normals.push_back(n);
                normals.push_back(n);
                normals.push_back(n);
            }
            
            geometry[TRIANGULATION_3D_PRUNED_AND_GRAY] = gfx->createStaticGeometry(&triangles_pruned[0], triangles_pruned.size(), &normals[0], 0, false, true);
            
            // Give each vertex a colour based on height.
            // To do this we find out each vertex's height relative to the total height of
            // the terrain. The terrain is divided into three sections: sand, grass, and mountain.
            // Vertices in the sand section get a sand colour, vertices in the grass section get a
            // grass colour and so on. Furthermore, every vertex gets a different colour shade based
            // on its height; vertices at the top of a mountain look darker than vertices at the bottom
            // of the mountain.
            
            // Sand: E9C2A6
            // Vegetation: 668014
            // Mountain: 8B5742
            Colour3 sand = Colour3(0xBB / 255.0, 0x8A / 255.0, 0x5B / 255.0);
            Colour3 vege = Colour3(0x66 / 255.0, 0x80 / 255.0, 0x14 / 255.0);
            Colour3 mntn = Colour3(0x60 / 255.0, 0x33 / 255.0, 0x11 / 255.0);
            num max = m_bb.max()[Z];
            num min = m_bb.min()[Z];
            num height = max - min;
            num vege_threshold = 0.1;
            num mntn_threshold = 0.48;
            
            num sand_factor = vege_threshold;
            num vege_factor = mntn_threshold - vege_threshold;
            num mntn_factor = 1.0 - mntn_threshold;
            
            // Calculate colour factors for each vertex.
            // In addition, we will also use this loop to find out, for each vertex, the triangles incident to it,
            // just so that we can compute smoothed vertex normals later on.
            typedef std::map< Vector3, list<TriangleEnt*>, CompareVec3 > vertex_data_t;	//A map containing the triangles incident to
            //a vertex for each vertex in the triangulation.
            typedef pair< Vector3, list<TriangleEnt*> > vertex_pair; // The pair value the previous map holds.
            vertex_data_t vertex_data;
            
            foreach (TriangleEnt& t, triangles_pruned)
            {
                // Loop over the current triangle's vertices.
                for (int i = 0; i < 3; ++i)
                {
                    num alt = (t[i][Z] - min) / height;	// The current vertex's relative height.
                    alt = (alt < 0.01) ? 0.01 : alt;
                    
                    // Give the current vertex a colour.
                    if (alt < vege_threshold)		colours.push_back(computeColour(sand, alt / sand_factor, 0.15));
                    else if (alt < mntn_threshold)	colours.push_back(computeColour(vege, (alt - vege_threshold) / vege_factor, 0.15));
                    else							colours.push_back(computeColour(mntn, (alt - mntn_threshold) - mntn_factor, 0.30));
                    
                    // Insert the current triangle into the vertex's list of triangles.
                    vertex_data[t[i]].push_back(&t);
                }
            }
            
            // Produce a rough 3D triangulation.
            geometry[TRIANGULATION_3D_PRUNED] = gfx->createStaticGeometry(&triangles_pruned[0], triangles_pruned.size(), &normals[0], &colours[0]);
            
            // Produce a smooth 3D triangulation.
            // Calculate vertex normals to produce a smooth 3D triangulation.
            // To do this we compute the normalised average normal of the triangles incident to each vertex.
            const TriangleEnt* first_triangle = &triangles_pruned[0];
            foreach (vertex_pair vertex_p, vertex_data)
            {
                Vector3 vertex_normal;
                const Vector3& v = vertex_p.first;
                list<TriangleEnt*>& l = vertex_p.second;
                
                foreach (TriangleEnt* triangle, l) vertex_normal += normal(*triangle);
                
                vertex_normal.normalise();
                
                foreach (TriangleEnt* triangle, l)
                {
                    TriangleEnt& t = *triangle;
                    
                    for (int i = 0; i < 3; ++i)
                    {
                        if (t[i] == v)
                        {
                            int pos = triangle - first_triangle;
                            normals[3*pos + i] = vertex_normal;
                            break;
                        }
                    }
                }
            }
            geometry[TRIANGULATION_3D_PRUNED_AND_SMOOTH] = gfx->createStaticGeometry(&triangles_pruned[0], triangles_pruned.size(), &normals[0], &colours[0]);
        }
    }
    
    // Produce a raw 2D triangulation, using segments or triangles.
    if (!segments.empty())
    {
        geometry[TRIANGULATION_2D_RAW] = gfx->createStaticGeometry(&segments[0], segments.size(), true);
    }
    else if (!triangles.empty())
    {
        geometry[TRIANGULATION_2D_RAW] = gfx->createStaticGeometry(&triangles[0], triangles.size(), 0, 0, true);
    }
    
    printf("Preparation done\n");
}


void TriangulationEnt::draw(Graphics& gfx) const
{
    if (geometry[drawMode] != -1)
    {
        bool wireframe = gfx.getWireframeState();
        bool lighting = gfx.getLightingState();
        
        if (drawMode == TRIANGULATION_2D_RAW || drawMode == TRIANGULATION_2D_PRUNED)
        {
            gfx.setWireframe(true);
            gfx.setLighting(false);
        }
        
        gfx.drawStaticGeometry(geometry[drawMode]);
        
        if (drawMode == TRIANGULATION_2D_RAW || drawMode == TRIANGULATION_2D_PRUNED)
        {
            gfx.setWireframe(wireframe);
            gfx.setLighting(lighting);
        }
    }
}


void TriangulationEnt::drawLabel(const Font& f) const
{
    if (geometry[drawMode] != -1)
    {
        if (drawMode == TRIANGULATION_2D_RAW)
        {
            foreach (const LineSegmentEnt& s, segments) s.drawLabel(f);
            foreach (const TriangleEnt& t, triangles) t.drawLabel(f);
        }
        else
        {
            foreach (const TriangleEnt& t, triangles_pruned) t.drawLabel(f);
        }
    }
}


Colour3 computeColour(const Colour3& colour, num height, num factor)
{
    Colour3 dark	= colour - colour*factor;
    Colour3 light	= colour + colour*factor;
    return light + (dark - light) * height;
}
