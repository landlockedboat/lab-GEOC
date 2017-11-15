#ifndef _GEOC_GRAPHICS_H
#define _GEOC_GRAPHICS_H

#include <geoc/math/Vector_fwd_decl.h>

namespace geoc {

class Point;
class LineSegmentEnt;
class TriangleEnt;
class CircleEnt;
class Font;
struct Graphics_impl;

/** \ingroup Gfx */
//! The graphics subsystem.
class DECLDIR Graphics
{
    Graphics_impl* impl;
    
public:
    
    Graphics();
    ~Graphics();
    
    //! Initialises the graphics subsystem.
    /*!
     * \param width The viewport's width.
     * \param height The viewport's height.
     * \param x The x coordinate of the lower left corner of the screen.
     * \param y The y coordinate of the lower left corner of the screen.
     * Default values:
     * Deph test: enabled.
     * Face culling: enabled, set to cull clockwise faces.
     * Antialising: enabled.
     * Lighting: disabled.
     */
    void initialise(int width, int height, num x = 0, num y = 0);
    
    //! Shuts the graphics subsystem down.
    void shutdown();
    
    //! Sets up the viewport.
    /*!
     * \param width The desired viewport width.
     * \param height The desired viewport height.
     * \param x The x coordinate of the lower left corner of the screen.
     * \param y The y coordinate of the lower left corner of the screen.
     */
    void setViewport(int width, int height, num x = 0, num y = 0);
    
    //! Flushes out all cached render commands.
    void flush();
    
    //! Draws a cube.
    /*!
     * \param pos The center of the cube.
     * \param d Length of one side of the cube / 2.
     */
    void drawCube(const Vector3& pos, num d);
    
    //! Draws a point.
    void drawPoint(const Point* p) const;
    
    //! Draws a point.
    void drawPoint(const Vector3& v) const;
    
    //! Draws a point.
    void drawPoint(const Vector2& v) const;
    
    //! Draws a point.
    void drawPoint(num x, num y, num z = 0) const;
    
    //! Draws a line segment.
    void drawSegment(const LineSegmentEnt* s) const;
    
    //! Draws a segment.
    void drawSegment(const Vector3& p1, const Vector3& p2) const;
    
    //! Draws a segment.
    void drawSegment(const Vector2& p1, const Vector2& p2) const;
    
    //! Draws a segment.
    void drawSegment(const Vector3 ps[2]) const;
    
    //! Draws a triangle.
    void drawTriangle(const TriangleEnt* t) const;
    
    //! Draws a triangle.
    void drawTriangle(const Vector3 p1, const Vector3& p2, const Vector3& p3) const;
    
    //! Draws a triangle.
    void drawTriangle(const Vector3 ps[3]) const;
    
    //! Draws a circle.
    void drawCircle(const CircleEnt* c) const;
    
    //! Draws a circle.
    void drawCircle(const Vector3& p1, const Vector3& p2, const Vector3& p3) const;
    
    //! Draws a circle.
    void drawCircle(const Vector3 ps[3]) const;
    
    //! Draws a polygon.
    void drawPolygon(const Vector3* ps, int n, const Colour3& colour) const;
    
    //! Draws a polygon.
    void drawPolygon(const Vector2* ps, int n, const Colour3& colour) const;
    
    //! Creates static geometry.
    /*!
     * \return An ID used to draw the created geometry. Pass this ID to drawStaticGeometry.
     * \sa drawStaticGeometry
     */
    unsigned int createStaticGeometry(const TriangleEnt* t, int n, const Vector3* normals = 0, const Vector3* colours = 0, bool flat = false, bool grayscale = false);
    
    //! Creates static geometry.
    /*!
     * \return An ID used to draw the created geometry. Pass this ID to drawStaticGeometry.
     * \sa drawStaticGeometry
     */
    unsigned int createStaticGeometry(const LineSegmentEnt* s, int n, bool flat = false);
    
    //! Deletes static geometry.
    /*!
     * \param id An ID describing what geometry to delete. Geometry IDs are returned by createStaticGeometry.
     * \sa createStaticGeometry
     */
    void deleteStaticGeometry(unsigned int id);
    
    //! Draws static geometry.
    /*!
     * \param id An ID describing what geometry to draw. Geometry IDs are returned by createStaticGeometry.
     * \sa createStaticGeometry
     */
    void drawStaticGeometry(unsigned int id) const;
    
    //! Prepares the graphics system for rendering a new frame.
    void newFrame();
    
    //! Tells the graphics system to end the current frame, flushing out all render commands.
    void endFrame();
    
    //! Resizes the window.
    void resize(int width, int height);
    
    //! Sets the viewport's origin.
    /*!
     * \param x The x coordinate of the lower left corner of the screen.
     * \param y The y coordinate of the lower left corner of the screen.
     */
    void setOrigin(int x, int y);
    
    //! Sets the background colour.
    void setColour(const Colour3& colour);
    
    //! Sets the background colour.
    void setColour(num r, num g, num b);
    
    //! Enables or disables lighting.
    void setLighting(bool state);
    
    //! Updates the lighting in the scene.
    /*!
     * Call this when the camera's transform changes.
     * Light positions and directions are transformed by the view matrix,
     * therefore this function should be called to recalculate them.
     */
    void updateLighting();
    
    //! Enables or disables wireframe.
    void setWireframe(bool state);
    
    //! Toggles wireframe.
    void toggleWireframe();
    
    //! Enables or disables antialiasing.
    void setAntialiasing(bool state);
    
    //! Enables or disables depth testing.
    void setDepthTest(bool state);
    
    //! Enables or disables face culling.
    void setCulling(bool state);
    
    //! Sets the point size.
    void setPointSize(num size);
    
    //! Sets the line width.
    void setLineWidth(num size);
    
    //! Sets the global thickness of rendered geometry (point size, line width, etc).
    void setThickness(num t);
    
    //! Increases the global thickness of rendered geometry.
    void increaseThickness();
    
    //! Decreases the global thickness of rendered geometry.
    void decreaseThickness();
    
    //! Returns true if lighting is enabled, false otherwise.
    bool getLightingState() const;
    
    //! Returns true if wireframe is enabled, false otherwise.
    bool getWireframeState() const;
    
    //! Returns true if antialiasing is enabled, false otherwise.
    bool getAntialiasingState() const;
    
    //! Returns true if depth testing is enabled, false otherwise.
    bool getDepthTestState() const;
    
    //! Returns true if face culling is enabled, false otherwise.
    bool getCullingState() const;
    
    //! Returns the viewport's width.
    int width() const;
    
    //! Returns the viewport's height.
    int height() const;
    
    //! Returns the viewport's aspect ratio.
    num aspectRatio() const;
    
    //! Returns the lower left corner of the viewport.
    void getViewportOrigin(int& x, int& y) const;
};

} //namespace geoc

#endif //_GEOC_GRAPHICS_H
